# Rocket Flight Computer

An Arduino-based flight computer that logs real-time altitude and acceleration data during model rocket launches.

## Status
- ✅ Flight computer electronics complete and tested
- ✅ Flight unit soldered on solderable breadboard, confirmed working
- ✅ Rocket built
- ✅ Bench test completed and launch/landing detection verified (see Testing & Debugging below)
- ⏳ Phase 4: Instrumented flight launch pending larger rocket airframe

## Features
- Real-time altitude logging via BMP388 barometric pressure sensor
- 6-axis acceleration and orientation tracking via MPU6050
- Kalman filter for smooth altitude data
- Moving average filter for accelerometer noise reduction
- Launch detection triggered by sustained acceleration above threshold
- Automatic new flight file creation per launch (FLT001.csv, FLT002.csv...)
- Landing detection with 10 second confirmation timer
- SD card data logging at 10Hz during flight
- 30 reading base altitude calibration on startup

## Hardware
- Arduino Nano ATmega328P
- BMP388 Barometric Pressure/Altitude Sensor
- MPU6050 6-Axis Accelerometer and Gyroscope
- Micro SD Card Module with Logic Level Converter
- 9V Battery Power
- Estes Amazon rocket airframe

## Build Phases
- ✅ Phase 1: Electronics prototyping and testing
- ✅ Phase 2: Flight unit soldered on solderable breadboard
- ✅ Phase 3: Rocket built
- ⏳ Phase 4: Instrumented launch pending custom payload rocket

## Build Log
See [BUILDLOG.md](BUILDLOG.md) for detailed progress notes.

## Testing & Debugging

Ran a hand lift bench test (FLT008) before the rocket was flight ready, since the electronics 
were too heavy for the original airframe. This uncovered a real bug: noise in the first couple 
of accelerometer readings right after sensor initialization was large enough to falsely trigger 
launch detection before any real motion occurred.

Fixed it by adding a settling period after MPU initialization and calibrating the launch and 
landing thresholds against a measured resting baseline instead of hardcoded values.

Verified the fix with a second test (FLT010), confirmed via Serial output that the system 
correctly waited for a real motion event, printed LAUNCHED only once actual motion was detected, 
and printed LANDED after a sustained ten second rest period.

Both raw flight logs are in [/flight-logs](flight-logs).

## Goals
- Flight unit soldered and confirmed working September 2026
- Instrumented launch pending custom payload rocket build
- Document full flight data analysis after first launch
