# IMU WiFi Dashboard

A multi-device IoT system that reads IMU orientation data from an MPU-6050 on an 
Elecrow CrowPanel ESP32 display, transmits it over WiFi to a Flask server, and 
visualizes it as a real-time web dashboard. A Raspberry Pi 4B provides additional 
sensor data (distance and voltage) to the same Flask server.

## Hardware

- Elecrow CrowPanel 2.1" HMI ESP32 Rotary Display (480x480)
- MPU-6050 IMU (accelerometer + gyroscope)
- Raspberry Pi 4B (8GB)
- HC-SR04 Ultrasonic Distance Sensor
- ADS7830 I2C ADC (8-channel, 8-bit)
- 10k Potentiometer

## Architecture

```
MPU-6050 --I2C--> CrowPanel ESP32 --WiFi-->|
                                           |--> Flask Server --> Web Browser (live graphs)
Pi 4B (HC-SR04 + ADS7830) ------WiFi------>|
                                           |
CrowPanel ESP32 <-------WiFi-------------- Flask Server (pot + cm data)
```

The CrowPanel reads IMU data and sends it to Flask over WiFi. The Pi reads distance 
and voltage and sends those to the same Flask server. The web frontend displays all 
data as live updating graphs. Flask also pushes pot and cm readings back to the 
CrowPanel display.

## Wiring

### MPU-6050 → CrowPanel I2C Port
| MPU-6050 | CrowPanel |
|----------|-----------|
| VCC      | 5V        |
| GND      | GND       |
| SDA      | SDA       |
| SCL      | SCL       |

### HC-SR04 → Pi 4B
| HC-SR04 | Pi GPIO          |
|---------|------------------|
| VCC     | Pin 2 (5V)       |
| GND     | Pin 6 (GND)      |
| TRIG    | Pin 16 (GPIO 23) |
| ECHO    | Pin 18 (GPIO 24) |

### ADS7830 → Pi 4B (I2C)
| ADS7830 | Pi GPIO        |
|---------|----------------|
| VCC     | Pin 1 (3.3V)   |
| GND     | Pin 9 (GND)    |
| SDA     | Pin 3 (GPIO 2) |
| SCL     | Pin 5 (GPIO 3) |
| CH0     | Potentiometer wiper |

## Software

### CrowPanel Firmware (C++ / Arduino)

Built with PlatformIO. Open `IMU_Wifif/` as a PlatformIO project.

Dependencies (auto-installed via `platformio.ini`):
- Arduino GFX Library 1.3.1
- LVGL 8.3.11
- PCF8574 library
- Adafruit CST8XX
- ElectronicCats MPU6050

```
platformio run --target upload
```

### Pi Side (C)

Dependencies:
```bash
sudo apt install libgpiod-dev libi2c-dev
```

Build and run:
```bash
cd pi/src
gcc -std=gnu99 -Wall -o output hcsr04.c ads7830.c uart.c main.c -lgpiod
./output
```

### Flask Server (Python) — In Progress

### Web Frontend — In Progress

## Project Structure

```
imu-wifi-dashboard/
├── IMU_Wifif/              # CrowPanel ESP32 firmware
│   ├── src/
│   │   ├── main.cpp        # Entry point
│   │   ├── display.h/cpp   # Display driver and LVGL init
│   │   ├── ui.h/cpp        # LVGL UI layout and updates
│   │   ├── uart.h/cpp      # UART packet parsing
│   │   └── imu.h/cpp       # MPU-6050 driver
│   ├── lv_conf.h
│   └── platformio.ini
├── pi/
│   └── src/                # Pi sensor drivers (C)
│       ├── hcsr04.h/c
│       ├── ads7830.h/c
│       ├── uart.h/c
│       └── main.c
├── server/                 # Flask backend (coming soon)
└── README.md
```

## Current Status

- [x] MPU-6050 IMU reading over I2C
- [x] Live IMU display on CrowPanel (ax, ay, az, gx, gy, gz)
- [x] Pi sensor drivers in C (HC-SR04, ADS7830)
- [ ] CrowPanel WiFi connection
- [ ] Flask server setup
- [ ] IMU data POST to Flask
- [ ] Real-time web dashboard
- [ ] Pi sensor data POST to Flask
- [ ] Flask pushing pot/cm data back to CrowPanel

## What I Learned

- MPU-6050 I2C communication on ESP32
- LVGL UI layout and multi-label display on a round screen
- UI design with SquareLine Studio
- Modular C++ firmware architecture (display, ui, uart, imu drivers)
- C sensor drivers on Linux using libgpiod and I2C ioctl
