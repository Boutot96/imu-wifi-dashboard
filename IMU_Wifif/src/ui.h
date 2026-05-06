#ifndef UI_H
#define UI_H

#include <lvgl.h>

extern lv_obj_t *label_distance;
extern lv_obj_t *label_pot;
extern lv_obj_t *label_imu;

void ui_init();
void ui_update_distance(const char *value);
void ui_update_pot(const char *value);
void ui_update_imu(float ax, float ay, float az, float gx, float gy, float gz);

#endif