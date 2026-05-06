#ifndef IMU_H
#define IMU_H

struct IMUData {
    float ax, ay, az;
    float gx, gy, gz;
};

void imu_init();
IMUData imu_read();

#endif