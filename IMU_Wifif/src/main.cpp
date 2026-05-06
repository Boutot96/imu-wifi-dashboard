#include <Arduino.h>
#include "display.h"
#include "ui.h"
#include "uart.h"
#include "imu.h"

void setup() {
    delay(2000);
    Serial.begin(115200);
    delay(2000);
    display_init();
    delay(500);    
    ui_init();
    uart_init();
    imu_init();

    
}

void loop() {

    IMUData data = imu_read();
    ui_update_imu(data.ax, data.ay, data.az, data.gx, data.gy, data.gz);
    uart_update();
    lv_timer_handler();
    lv_refr_now(NULL);
    delay(500);
}