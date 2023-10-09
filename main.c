#include <stdio.h>
#include "sdkconfig.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_system.h"
#include "esp_spi_flash.h"
#include "driver/gpio.h"

#define pinButton 16 // chan rx2

uint8_t button_previous_state = 0;

void button() {
    uint8_t button_current_state = gpio_get_level(pinButton);

    if(button_current_state == 0 && button_previous_state == 1){
            vTaskDelay(50 / portTICK_PERIOD_MS);

        button_current_state = gpio_get_level(pinButton);
        if(button_current_state == 0) {
            printf("ESP32\n");
        }  
    }

    button_previous_state = button_current_state;
}

void printMSSV() {
    printf ("MSSV \n") ;
    vTaskDelay (1000 / portTICK_PERIOD_MS) ;
}

void app_main(void)
{
    gpio_config_t GPIO_config = {};

    GPIO_config.pin_bit_mask = (1 << pinButton);       /*!< GPIO pin: set with bit mask, each bit maps to a GPIO */
    GPIO_config.mode = GPIO_MODE_INPUT;               /*!< GPIO mode: set input/output mode                     */                                    
    gpio_config(&GPIO_config);
    gpio_set_direction(GPIO_NUM_16, GPIO_MODE_INPUT);

    while(1) {
        button();
        printMSSV();
    }
}