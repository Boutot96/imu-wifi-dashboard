#ifndef DISPLAY_H
#define DISPLAY_H

#include <Arduino_GFX_Library.h>
#include <PCF8574.h>
#include <lvgl.h>
#include <Wire.h>

#define I2C_SDA_PIN 38
#define I2C_SCL_PIN 39
#define BKL_PIN 6

extern Arduino_ST7701_RGBPanel *gfx;
extern lv_disp_draw_buf_t draw_buf;

void display_init();
void my_disp_flush(lv_disp_drv_t *disp, const lv_area_t *area, lv_color_t *color_p);

#endif