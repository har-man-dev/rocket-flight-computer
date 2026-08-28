# Rocket Flight Computer

An Arduino based flight computer that logs real time altitude and acceleration data during model rocket launches.

## Status
✅ Flight computer electronics complete and tested
🔧 Rocket build phase - parts ordered, awaiting delivery

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
- Estes Big Bertha rocket airframe

## Build Phases
- ✅ Phase 1: Electronics prototyping and testing
- 🔧 Phase 2: Flight unit soldering on perfboard
- ⏳ Phase 3: Rocket build and integration
- ⏳ Phase 4: First launch

## Build Log
See [BUILDLOG.md](BUILDLOG.md) for detailed progress notes.

## Goals
- Complete perfboard flight unit by early September 2026
- First launch before UW Fall Quarter begins
- Document full flight data analysis after first launch
