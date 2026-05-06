#include "uart.h"
#include "ui.h"
#include <Arduino.h>

static String packet;

void uart_init() {
    Serial1.begin(115200, SERIAL_8N1, 44, 43);
}

void uart_update() {
    if (Serial1.available()) {
        packet = Serial1.readStringUntil('\n');
        packet.trim();
        if (packet.startsWith("<DIST:") && packet.endsWith(">")) {
            String value = packet.substring(6, packet.length() - 1);
            ui_update_distance(value.c_str());
        } else if (packet.startsWith("<VOLT:") && packet.endsWith(">")) {
            String value = packet.substring(6, packet.length() - 1);
            ui_update_pot(value.c_str());
        }
    }
}