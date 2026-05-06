#include "ui.h"
#include <cstdio>

lv_obj_t *label_distance;
lv_obj_t *label_pot;
lv_obj_t *label_imu;

void ui_init() {
    lv_obj_set_style_bg_color(lv_scr_act(), lv_color_black(), 0);
    lv_obj_set_style_bg_opa(lv_scr_act(), LV_OPA_COVER, 0);

    label_pot = lv_label_create(lv_scr_act());
    lv_label_set_text(label_pot, "Pot: --");
    lv_obj_set_style_text_font(label_pot, &lv_font_montserrat_20, 0);
    lv_obj_set_x(label_pot, -135);
    lv_obj_set_y(label_pot, -115);
    lv_obj_set_align(label_pot, LV_ALIGN_CENTER);
    lv_obj_set_style_text_color(label_pot, lv_color_white(), 0);

    label_distance = lv_label_create(lv_scr_act());
    lv_label_set_text(label_distance, "-- cm");
    lv_obj_set_style_text_font(label_distance, &lv_font_montserrat_20, 0);
    lv_obj_set_x(label_distance, 135);
    lv_obj_set_y(label_distance, -115);
    lv_obj_set_align(label_distance, LV_ALIGN_CENTER);
    lv_obj_set_style_text_color(label_distance, lv_color_white(), 0);

    label_imu = lv_label_create(lv_scr_act());
    lv_label_set_text(label_imu, "ax: 0.00      gx: 0.00\n\nay: 0.00      gy: 0.00\n\naz: 0.00      gz: 0.00");
    lv_obj_set_style_text_font(label_imu, &lv_font_montserrat_26, 0);
    lv_obj_set_x(label_imu, 4);
    lv_obj_set_y(label_imu, 73);
    lv_obj_set_align(label_imu, LV_ALIGN_CENTER);
    lv_obj_set_style_text_color(label_imu, lv_color_white(), 0);
}

void ui_update_distance(const char *value) {
    char buf[32];
    snprintf(buf, sizeof(buf), "%s cm", value);
    lv_label_set_text(label_distance, buf);
}

void ui_update_pot(const char *value) {
    char buf[32];
    snprintf(buf, sizeof(buf), "Pot: %s", value);
    lv_label_set_text(label_pot, buf);
}

void ui_update_imu(float ax, float ay, float az, float gx, float gy, float gz) {
    char buf[128];
    snprintf(buf, sizeof(buf),
        "ax:%.2f      gx:%.2f\n\nay:%.2f      gy:%.2f\n\naz:%.2f      gz:%.2f",
        ax, gx, ay, gy, az, gz);
    lv_label_set_text(label_imu, buf);
}