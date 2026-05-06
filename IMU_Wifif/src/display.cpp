#include "display.h"

PCF8574 pcf8574(0x21);

Arduino_ESP32RGBPanel *bus = new Arduino_ESP32RGBPanel(
    16, 2, 1, 40, 7, 15, 41,
    46, 3, 8, 18, 17,
    14, 13, 12, 11, 10, 9,
    5, 45, 48, 47, 21
);

Arduino_ST7701_RGBPanel *gfx = new Arduino_ST7701_RGBPanel(
    bus, GFX_NOT_DEFINED, 0, false, 480, 480,
    st7701_type5_init_operations,
    sizeof(st7701_type5_init_operations),
    true, 10, 4, 20, 10, 4, 20
);

lv_disp_draw_buf_t draw_buf;

void my_disp_flush(lv_disp_drv_t *disp, const lv_area_t *area, lv_color_t *color_p) {
    uint32_t w = (area->x2 - area->x1 + 1);
    uint32_t h = (area->y2 - area->y1 + 1);
    gfx->draw16bitRGBBitmap(area->x1, area->y1, (uint16_t *)&color_p->full, w, h);
    lv_disp_flush_ready(disp);
}

void display_init() {
    Wire.begin(I2C_SDA_PIN, I2C_SCL_PIN);
    pcf8574.pinMode(P0, OUTPUT);
    pcf8574.pinMode(P2, OUTPUT);
    pcf8574.pinMode(P3, OUTPUT);
    pcf8574.pinMode(P4, OUTPUT);
    if (!pcf8574.begin()) {
        Serial.println("Can't init pcf8574");
    }
    pcf8574.digitalWrite(P3, HIGH); delay(100);
    pcf8574.digitalWrite(P4, HIGH); delay(100);
    pcf8574.digitalWrite(P4, LOW);  delay(120);
    pcf8574.digitalWrite(P4, HIGH); delay(120);
    pcf8574.digitalWrite(P0, HIGH); delay(100);
    pcf8574.digitalWrite(P0, LOW);  delay(120);
    pcf8574.digitalWrite(P0, HIGH); delay(120);
    pcf8574.digitalWrite(P2, HIGH); delay(120);

    pinMode(BKL_PIN, OUTPUT);
    analogWrite(BKL_PIN, 200);
    gfx->begin();

    lv_init();
    uint32_t bufSize = 480 * 40;
    lv_color_t *buf = (lv_color_t *)heap_caps_malloc(bufSize * 2, MALLOC_CAP_INTERNAL | MALLOC_CAP_8BIT);
    lv_disp_draw_buf_init(&draw_buf, buf, NULL, bufSize);

    static lv_disp_drv_t disp_drv;
    lv_disp_drv_init(&disp_drv);
    disp_drv.hor_res = 480;
    disp_drv.ver_res = 480;
    disp_drv.flush_cb = my_disp_flush;
    disp_drv.draw_buf = &draw_buf;
    lv_disp_drv_register(&disp_drv);
}