#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "led_strip.h"
#include "esp_log.h"

static const char *TAG = "LED_CONTROL";

// Định nghĩa chân GPIO cho LED trên ESP32-S3
#define LED_STRIP_BLINK_GPIO  48
// Số lượng LED (thường là 1 trên board)
#define LED_STRIP_LED_NUMBERS 1
// Độ phân giải xung RMT
#define LED_STRIP_RMT_RES_HZ  (10 * 1000 * 1000)

extern "C" void app_main(void)
{
    /* 1. Cấu hình LED Strip */
    led_strip_config_t strip_config = {}; // Khởi tạo trống để tránh lỗi missing field
    strip_config.strip_gpio_num = LED_STRIP_BLINK_GPIO;
    strip_config.max_leds = LED_STRIP_LED_NUMBERS;
    strip_config.led_model = LED_MODEL_WS2812; // Tự động nhận diện định dạng pixel
    strip_config.flags.invert_out = false;

    /* 2. Cấu hình RMT backend */
    led_strip_rmt_config_t rmt_config = {}; // Khởi tạo trống trước
    rmt_config.clk_src = RMT_CLK_SRC_DEFAULT;
    rmt_config.resolution_hz = LED_STRIP_RMT_RES_HZ;
    rmt_config.mem_block_symbols = 64; // Thêm dòng này để sửa lỗi missing initializer
    rmt_config.flags.with_dma = false;

    led_strip_handle_t led_strip;
    // Tạo device
    ESP_ERROR_CHECK(led_strip_new_rmt_device(&strip_config, &rmt_config, &led_strip));

    ESP_LOGI(TAG, "Đã khởi tạo LED RGB thành công!");

    while (1) {
        // Màu Đỏ (R, G, B)
        led_strip_set_pixel(led_strip, 0, 30, 0, 0); 
        led_strip_refresh(led_strip);
        vTaskDelay(pdMS_TO_TICKS(500));

        // Màu Xanh dương
        led_strip_set_pixel(led_strip, 0, 0, 0, 30);
        led_strip_refresh(led_strip);
        vTaskDelay(pdMS_TO_TICKS(500));

        // Tắt LED
        led_strip_clear(led_strip);
        vTaskDelay(pdMS_TO_TICKS(500));
    }
}