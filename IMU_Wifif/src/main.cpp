#include <Arduino.h>
#include "display.h"
#include "ui.h"
#include "uart.h"

void setup() {
    delay(2000);
    Serial.begin(115200);
    display_init();
    ui_init();
    uart_init();
    Serial.println("Setup done");
}

void loop() {
    uart_update();
    lv_timer_handler();
    lv_refr_now(NULL);
    delay(5);
}