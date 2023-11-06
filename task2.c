#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "sdkconfig.h"
#include "driver/gpio.h"
#include "esp_log.h"
#include "esp_system.h"
#include <inttypes.h>
#include "esp_chip_info.h"
#include "esp_flash.h"
#include "spi_flash_mmap.h"

// Prioritized Pre-emptive Scheduling with Time Slicing

TaskHandle_t task1Handle = NULL;
TaskHandle_t task2Handle = NULL;
TaskHandle_t task3Handle = NULL;

void task1(void *pvParameters) {
    for (;;) {
        printf("Task1\n");
        vTaskDelay(1000 / portTICK_PERIOD_MS);  // Chờ 1000 milliseconds
    }
}

void task2(void *pvParameters) {
    for (;;) {
        printf("Task22\n");
        vTaskDelay(3000 / portTICK_PERIOD_MS);  // Chờ 3000 milliseconds
    }
}

void task3(void *pvParameters) {
    for (;;) {
        printf("Task333\n");
        vTaskDelay(2000 / portTICK_PERIOD_MS);  // Chờ 2000 milliseconds
    }
}

void app_main(void){

    xTaskCreate(task1, "Task1", 1000, NULL, 1, &task1Handle);
    xTaskCreate(task2, "Task2", 1000, NULL, 2, &task2Handle);
    xTaskCreate(task3, "Task3", 1000, NULL, 3, &task3Handle);
}