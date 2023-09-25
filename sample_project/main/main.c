#include <stdio.h>
#include <inttypes.h>
#include "sdkconfig.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_chip_info.h"
#include "esp_flash.h"
#include "driver/gpio.h"
#include "esp_log.h"



uint8_t signal = 0;

void toggleButton () {
    signal= gpio_get_level (GPIO_NUM_16);
    if (signal == 1 ) {
        printf("ESP32 \n");
        return;
    }
    else return;
}
void app_main(void)
{
    gpio_set_direction(GPIO_NUM_16, GPIO_MODE_INPUT);
while (1) {
    toggleButton();
    // printf(signal);
    printf ("MSSV \n") ;
    vTaskDelay (1000) ;
}
}
 