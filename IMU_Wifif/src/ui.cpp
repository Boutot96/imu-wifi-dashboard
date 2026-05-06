#include "ui.h"

lv_obj_t *label_distance;
lv_obj_t *label_pot;

void ui_init() {
    lv_obj_set_style_bg_color(lv_scr_act(), lv_color_black(), 0);
    lv_obj_set_style_bg_opa(lv_scr_act(), LV_OPA_COVER, 0);

    label_distance = lv_label_create(lv_scr_act());
    lv_label_set_text(label_distance, "-- cm");
    lv_obj_set_style_text_font(label_distance, &lv_font_montserrat_48, 0);
    lv_obj_align(label_distance, LV_ALIGN_CENTER, 0, -50);
    lv_obj_set_style_text_color(label_distance, lv_color_white(), 0);

    label_pot = lv_label_create(lv_scr_act());
    lv_label_set_text(label_pot, "Pot: --");
    lv_obj_set_style_text_font(label_pot, &lv_font_montserrat_48, 0);
    lv_obj_align(label_pot, LV_ALIGN_CENTER, 0, 50);
    lv_obj_set_style_text_color(label_pot, lv_color_white(), 0);
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