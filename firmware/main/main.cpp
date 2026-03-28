#include <cstdio>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"

// Định nghĩa một lớp LED để quản lý
class Led {
private:
    gpio_num_t pin;
public:
    Led(gpio_num_t gpio_pin) : pin(gpio_pin) {
        gpio_reset_pin(pin);
        gpio_set_direction(pin, GPIO_MODE_OUTPUT);
    }

    void turnOn() { gpio_set_level(pin, 1); }
    void turnOff() { gpio_set_level(pin, 0); }
    
    void blink(int delay_ms) {
        turnOn();
        vTaskDelay(pdMS_TO_TICKS(delay_ms));
        turnOff();
        vTaskDelay(pdMS_TO_TICKS(delay_ms));
    }
};

extern "C" void app_main(void) {
    // Khởi tạo đối tượng LED ở chân GPIO 2
    Led myLed(GPIO_NUM_2); 

    while (true) {
        printf("Đang nháy đèn bằng C++... ✨\n");
        myLed.blink(500); // Nháy đèn mỗi 1 giây
    }
}