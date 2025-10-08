#include <assert.h>

#include "esp_err.h"
#include "esp_log.h"
#include "nvs_flash.h"
#include "bsp/esp-bsp.h"
#include "bsp/display.h"
#include "lvgl.h"

static const char *TAG = "lvgl_hello";

static void app_lvgl_create_ui(void)
{
    lv_obj_t *label = lv_label_create(lv_screen_active());
    lv_label_set_text(label, "Hello, LVGL 9!");
    lv_obj_center(label);
}

void app_main(void)
{
    esp_err_t ret = nvs_flash_init();
    if (ret == ESP_ERR_NVS_NO_FREE_PAGES || ret == ESP_ERR_NVS_NEW_VERSION_FOUND) {
        ESP_ERROR_CHECK(nvs_flash_erase());
        ret = nvs_flash_init();
    }
    ESP_ERROR_CHECK(ret);

    const bsp_display_cfg_t cfg = {
        .lvgl_port_cfg = ESP_LVGL_PORT_INIT_CONFIG(),
        .buffer_size = 480 * 800,
        .double_buffer = BSP_LCD_DRAW_BUFF_DOUBLE,
        .flags = {
            .buff_dma = false,
            .buff_spiram = true,
            .sw_rotate = true,
        },
    };

    lv_display_t *disp = bsp_display_start_with_config(&cfg);
    assert(disp && "LVGL display initialization failed");

    ESP_ERROR_CHECK(bsp_display_backlight_on());
    ESP_ERROR_CHECK(bsp_display_brightness_set(100));

    if (bsp_display_lock(0)) {
        app_lvgl_create_ui();
        bsp_display_unlock();
        ESP_LOGI(TAG, "LVGL hello world screen created");
    } else {
        ESP_LOGE(TAG, "Failed to lock LVGL display");
    }
}
