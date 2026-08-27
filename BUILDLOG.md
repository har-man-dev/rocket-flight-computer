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
