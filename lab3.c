#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"
#include "esp_log.h"
#include "esp_task_wdt.h"
#include "esp_system.h"

#define TASK_STACK_SIZE 2048

void task1(void *pvParameter)
{
    while (1)
    {
        for (int i = 0; i < 1000000; i++)
        {
            if (i == 999999)
            {
                ESP_LOGI("Task1", "Executing...");
                i = 0;
            }
        }
    }
}

void task2(void *pvParameter)
{
    while (1)
    {
        for (int i = 0; i < 1000000; i++)
        {
            if (i == 999999)
            {
                ESP_LOGI("Task2", "Executing...");
                i = 0;
            }
        }
    }
}

void task3(void *pvParameter)
{
    while (1)
    {
        for (int i = 0; i < 1000000; i++)
        {
            if (i == 999999)
            {
                ESP_LOGI("Task3", "Executing...");
                i = 0;
            }
        }
    }
}

void app_main()
{
    esp_task_wdt_deinit();

    // Create tasks and pin them to the same core (e.g., core 0)
    xTaskCreatePinnedToCore(task1, "Task1", TASK_STACK_SIZE, NULL, 1, NULL, 0);
    xTaskCreatePinnedToCore(task2, "Task2", TASK_STACK_SIZE, NULL, 2, NULL, 0);
    xTaskCreatePinnedToCore(task3, "Task3", TASK_STACK_SIZE, NULL, 3, NULL, 0);
}