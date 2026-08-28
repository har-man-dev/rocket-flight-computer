#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <Adafruit_BMP3XX.h>
#include <MPU6050.h>

#define CS_PIN 10
#define LAUNCH_THRESHOLD 32740
#define LANDING_TIME 10000
#define SEA_LEVEL_HPA 1013.25

Adafruit_BMP3XX bmp;
MPU6050 mpu;
File dataFile;

bool launched = false;
bool landed = false;
unsigned long landingTimer = 0;
float baseAltitude = 0;
char filename[12];

// Kalman filter variables for altitude
float kalmanAlt = 0;
float kalmanErr = 1;
float processNoise = 0.01;
float measureNoise = 0.5;

float kalmanUpdate(float measurement) {
  float prediction = kalmanAlt;
  float predErr = kalmanErr + processNoise;
  float gain = predErr / (predErr + measureNoise);
  kalmanAlt = prediction + gain * (measurement - prediction);
  kalmanErr = (1 - gain) * predErr;
  return kalmanAlt;
}

// Moving average for accelerometer
#define ACCEL_SAMPLES 5
int16_t accelBuffer[ACCEL_SAMPLES];
int accelIndex = 0;

int16_t smoothAccel(int16_t newVal) {
  accelBuffer[accelIndex] = newVal;
  accelIndex = (accelIndex + 1) % ACCEL_SAMPLES;
  long sum = 0;
  for (int i = 0; i < ACCEL_SAMPLES; i++) sum += accelBuffer[i];
  return sum / ACCEL_SAMPLES;
}

void setup() {
  Serial.begin(115200);
  Wire.begin();

  if (!bmp.begin_I2C()) {
    Serial.println(F("BMP fail"));
    while (1);
  }
  bmp.setTemperatureOversampling(BMP3_OVERSAMPLING_8X);
  bmp.setPressureOversampling(BMP3_OVERSAMPLING_4X);
  bmp.setIIRFilterCoeff(BMP3_IIR_FILTER_COEFF_3);
  bmp.setOutputDataRate(BMP3_ODR_50_HZ);

  mpu.initialize();
  if (!mpu.testConnection()) {
    Serial.println(F("MPU fail"));
    while (1);
  }

  if (!SD.begin(CS_PIN)) {
    Serial.println(F("SD fail"));
    while (1);
  }

  int flightNum = 1;
  while (true) {
    snprintf(filename, sizeof(filename), "FLT%03d.csv", flightNum);
    if (!SD.exists(filename)) break;
    flightNum++;
  }

  dataFile = SD.open(filename, FILE_WRITE);
  if (dataFile) {
    dataFile.println(F("Time(ms),Altitude(m),RelativeAlt(m),SmoothedAlt(m),Temp(C),Pressure(hPa),AX,AY,AZ,SmoothedAZ,GX,GY,GZ"));
  }

  Serial.println(F("Warming up sensors..."));
  for (int i = 0; i < 20; i++) {
    bmp.performReading();
    delay(100);
  }

  Serial.println(F("Calibrating base altitude..."));
  float altSum = 0;
  for (int i = 0; i < 30; i++) {
    bmp.performReading();
    altSum += bmp.readAltitude(SEA_LEVEL_HPA);
    delay(200);
  }
  baseAltitude = altSum / 30.0;
  kalmanAlt = baseAltitude;

  for (int i = 0; i < ACCEL_SAMPLES; i++) accelBuffer[i] = 17000;

  Serial.print(F("Ready. File: "));
  Serial.println(filename);
  Serial.print(F("Base alt: "));
  Serial.println(baseAltitude);
  Serial.println(F("Waiting for launch..."));
}

void loop() {
  if (landed) return;

  int16_t ax, ay, az, gx, gy, gz;
  mpu.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);
  bmp.performReading();

  float altitude = bmp.readAltitude(SEA_LEVEL_HPA);
  float relativeAlt = altitude - baseAltitude;
  float smoothedAlt = kalmanUpdate(altitude) - baseAltitude;
  int16_t smoothedAZ = smoothAccel(az);

  if (!launched) {
    static int launchCount = 0;
    if (abs(az) > LAUNCH_THRESHOLD) {
      launchCount++;
      if (launchCount >= 2) {
        launched = true;
        Serial.println(F("LAUNCHED"));
      }
    } else {
      launchCount = 0;
      Serial.print(F("AZ: "));
      Serial.print(az);
      Serial.print(F(" Smoothed: "));
      Serial.print(smoothedAZ);
      Serial.print(F(" Alt: "));
      Serial.println(relativeAlt);
      delay(100);
      return;
    }
  }

  if (dataFile) {
    dataFile.print(millis()); dataFile.print(",");
    dataFile.print(altitude); dataFile.print(",");
    dataFile.print(relativeAlt); dataFile.print(",");
    dataFile.print(smoothedAlt); dataFile.print(",");
    dataFile.print(bmp.temperature); dataFile.print(",");
    dataFile.print(bmp.pressure / 100.0); dataFile.print(",");
    dataFile.print(ax); dataFile.print(",");
    dataFile.print(ay); dataFile.print(",");
    dataFile.print(az); dataFile.print(",");
    dataFile.print(smoothedAZ); dataFile.print(",");
    dataFile.print(gx); dataFile.print(",");
    dataFile.print(gy); dataFile.print(",");
    dataFile.println(gz);
    dataFile.flush();
  }

  if (launched && abs(smoothedAlt) < 5 && az < 18000) {
    if (landingTimer == 0) landingTimer = millis();
    if (millis() - landingTimer > LANDING_TIME) {
      landed = true;
      dataFile.close();
      Serial.println(F("LANDED. Logging stopped."));
    }
  } else {
    landingTimer = 0;
  }

  delay(100);
}
