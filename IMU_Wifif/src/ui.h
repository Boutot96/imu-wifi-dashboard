#ifndef UI_H
#define UI_H
#include <cstdio>
#include <lvgl.h>

extern lv_obj_t *label_distance;
extern lv_obj_t *label_pot;

void ui_init();
void ui_update_distance(const char *value);
void ui_update_pot(const char *value);

#endif