#include "imu.h"
#include <MPU6050.h>

static MPU6050 mpu;

// Initialize mpu object to the actual wired IMU
void imu_init() {
    mpu.initialize();
    Serial.println(mpu.testConnection() ? "MPU6050 connected" : "MPU6050 failed");
}

// Read from IMU adn store in the IMUData struct
// Returns the current IMU data
IMUData imu_read() {
    IMUData data;
    int16_t ax, ay, az, gx, gy, gz;
    mpu.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);
    data.ax = ax / 16384.0;
    data.ay = ay / 16384.0;
    data.az = az / 16384.0;
    data.gx = gx / 131.0;
    data.gy = gy / 131.0;
    data.gz = gz / 131.0;
    return data;
}