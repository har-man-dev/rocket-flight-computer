# Build Log

## August 26, 2026 - Day 1: Initial Setup & Sensor Testing

### Completed
- Arduino IDE installed and configured
- CH340 driver installed for Nano recognition
- Blink sketch successfully uploaded, Nano confirmed working
- Adafruit BMP3XX library installed
- BMP388 wired to Nano via I2C (VIN, GND, SCK, SDI)

### Problem Encountered
BMP388 not detected by I2C scanner. Serial monitor returned "Could not find a valid BMP sensor."

### Troubleshooting Steps
- Verified power reaching sensor using multimeter, confirmed 5V present
- Tried second BMP388 board, same result
- Tested MPU6050 on same I2C pins, also not detected
- Determined root cause: header pins on sensor boards are press fit only, not soldered, causing unreliable signal connection on SCK and SDI lines

### Solution
Ordered soldering iron to permanently solder header pins onto all sensor boards. Code written and ready to upload once soldering is complete.

### Next Steps
- Solder header pins on BMP388 and MPU6050
- Upload BMP388 test sketch and confirm altitude readings
- Begin MPU6050 testing

## August 27, 2026 - Day 2 Afternoon: BMP388 Success

### Completed
- Soldering iron arrived, soldered header pins onto BMP388
- BMP388 successfully detected on I2C bus
- Live altitude, temperature, and pressure readings confirmed
- Reading: 122.72m altitude, 25.22C, 998.60 hPa

### Root cause confirmed
Press fit header pins were the issue. Soldering fixed it immediately.

### Next Steps
- Solder MPU6050 header pins
- Test MPU6050 independently
- Combine both sensors on same I2C bus

## August 27, 2026 - Day 2 Evening: MPU6050 & Dual Sensor Confirmation

### Completed
- Soldered header pins onto MPU6050
- MPU6050 raw data confirmed working
- I2C scanner found both sensors simultaneously
  - 0x68: MPU6050
  - 0x77: BMP388
- Both sensors operational on shared A4/A5 I2C lines
- Combined dual sensor code written and confirmed working

## August 27/28, 2026 - Day 2/3 Late Night/Early Morning: Full Flight Computer Complete

### Completed
- SD card module wired via SPI (MOSI D11, MISO D12, SCK D13, CS D10)
- Full flight computer code written and confirmed working
- Launch detection added, calibrated to threshold of 32740
- Debounce added requiring 2 consecutive readings above threshold
- Kalman filter added for smooth altitude data
- Moving average filter added for accelerometer noise reduction
- Automatic new flight file creation per launch (FLT001.csv, FLT002.csv etc.)
- Landing detection confirmed working
- Clean flight data confirmed, stable altitude readings
- All sensor data logging correctly to SD card

### Code Features
- BMP388 logs altitude, relative altitude, smoothed altitude, temperature, pressure
- MPU6050 logs raw and smoothed acceleration and gyroscope on all three axes
- Launch triggered by abs(AZ) exceeding 32740 for 2 consecutive readings
- Landing detected when smoothed altitude within 5m of base and AZ below 18000 for 10 seconds
- 30 reading base altitude average with 5 second warmup for accurate calibration

## August 28, 2026 - Day 3 Afternoon: Rocket Phase Planning & Parts Ordered

### Decisions Made
- Selected Estes Big Bertha (1948) as flight vehicle, 1.64 inch body tube diameter
- Estes Alpha III Launch Set 1427 ordered for launch pad and controller
- Engine bulk pack A8-3/B4-4/B6-4 ordered, arriving September 5
- Decided against breadboard for flight unit due to vibration risk
- Decided against hot glue and zip tie approach as unreliable
- Will build permanent soldered flight unit on perfboard

### Problem Identified
- SD card module pins pre-soldered at 90 degrees, will not fit flat inside body tube
- Solution: desolder pins using AUSTOR desoldering kit arriving tomorrow, resolder flat

### Parts Ordered
- Estes Big Bertha kit 1948
- Estes Alpha III Launch Set 1427 with pad and controller
- Engine bulk pack A8-3/B4-4/B6-4, 9 engines total
- ELEGOO perfboard variety pack, 5 sizes
- AUSTOR desoldering pump and solder wick kit
- 9V bare wire battery clip

### Next Steps
- Desolder and resolder SD card module pins flat
- Plan perfboard component layout to fit inside 42mm body tube
- Solder permanent flight unit on perfboard
- Build Big Bertha rocket
- Integrate flight computer into rocket body tube
- Test full system on 9V battery untethered before launch
- First launch on A or B motor


## August 29, 2026 - Day 4: SD Card Module Resoldered & Packaging Decisions

### Completed
- Desoldered perpendicular pins from SD card module
- Resoldered pins flat, SD card module confirmed working with test sketch
- Decided against inside tube mounting due to space constraints
- Decided to mount electronics externally on solderable breadboards on outside of rocket tube
- Ordered solderable breadboards, wire strippers, zip ties

## September 3 – 5, 2026 - Day 5 – 7: Solderable Breadboard Build Attempt 1

### Completed
- Soldered Nano, BMP388, MPU6050, and SD card module onto first solderable breadboard
- BMP388 confirmed at I2C address 0x77
- MPU6050 confirmed at I2C address 0x68
- All SPI wires confirmed via continuity test

### Problems Encountered
- SD card module failed to initialize, root cause not fully identified
- Arduino Nano fried during troubleshooting with multimeter while circuit was powered
- Desoldering tools insufficient to remove Nano cleanly

### Decision
- Scrapped first solderable breadboard
- Starting fresh on second solderable breadboard
- Using perpendicular SD card module to avoid reorientation issues
- Building one component at a time, testing each before proceeding

### Lessons Learned
- Never probe with multimeter while circuit is powered
- Test each component individually before combining
- Desoldering a Nano from solderable breadboard is extremely difficult with basic tools

### Next Steps
- Rebuild on second solderable breadboard
- Test SD card module first before adding sensors
- Build Big Bertha rocket
- Mount electronics externally on rocket tube with ballast for balance

## September 10, 2026 - Day 8: Flight Computer Complete

### Completed
- Rebuilt flight computer successfully on second solderable breadboard
- Lost second Nano to solder bridge, third Nano build succeeded
- BMP388, MPU6050, and SD card all confirmed working on permanent soldered board
- Flight data logged and verified, clean altitude and sensor readings confirmed
- Engines arrived
- Soldered board photo uploaded to repo
- README updated to reflect Phase 2 complete
- Full system tested untethered on 9V battery, confirmed working
- Clean flight data logged without USB connection

### Next Steps
- Build Estes Big Bertha rocket
- Mount flight computer externally on rocket tube
- First launch on A8-3 motor
