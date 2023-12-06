#include <stdio.h>
#include "driver/gpio.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/timers.h"
#include "FreeRTOSConfig.h"

struct QueueData
{
    int dataID;
    char message[30];
    char reject;
};

struct TaskType
{
    int taskID;
    char taskName[20];
};

QueueHandle_t xQueue;

struct TaskType Sensor_Air = {.taskName = "air", .taskID = 0};
struct TaskType Sensor_Moisture = {.taskName = "moisture", .taskID = 1};
struct TaskType Sensor_Water = {.taskName = "water", .taskID = 2};
struct TaskType Sensor_Light = {.taskName = "light", .taskID = 3};

void XQueue_Start(void *pvParameter)
{
    xQueue = xQueueCreate(10, sizeof(struct QueueData *));
    if (xQueue == NULL)
    {
        printf("Failed to create queue, not enough memory\n");
    }
    vTaskDelete(NULL);
}

void reception_Task(void *pvParameter)
{
    // Uses the "time.h" library to set the seed for the "rand()" random number function based on the current time.
    time_t t;
    srand((unsigned)time(&t));
    
    for (;;)
    {
        while (xQueue == NULL)
        {
            printf("xQueue is NULL\n");
        }

        // Create Data for Request
        int ran_job = (rand() % 4); // Randomly selects a number from 0 to 3 to choose a type of job (sensor).
        
        int ran_delay = (rand() % 5) + 1; // Randomly selects a number from 1 to 5 to create a random delay between requests.
        
        struct QueueData *xData = malloc(sizeof(struct QueueData)); // Allocates dynamic memory for a QueueData structure.

        // Generate Random Request
        if (xData != NULL)
        {
            // Based on the randomly chosen job type, sets up information for the request (xData).
            switch (ran_job)
            {
            case 0:
                xData->dataID = 0;
                strcpy(xData->message, "AIR");
                xData->reject = 0;
                break;
            case 1:
                xData->dataID = 1;
                strcpy(xData->message, "MOISTURE");
                xData->reject = 0;
                break;
            case 2:
                xData->dataID = 2;
                strcpy(xData->message, "WATER");
                xData->reject = 0;
                break;
            case 3:
                xData->dataID = 3;
                strcpy(xData->message, "LIGHT");
                xData->reject = 0;
                break;
            }

            // Uses xQueueSend to enqueue the request into the queue with a waiting time of 100 ticks. If the queue is full, prints an error message.
            if (xQueueSend(xQueue, (void *)&xData, 100) == errQUEUE_FULL)
            {
                printf("Failed to Import job with ID %d", ran_job);
            }
        }
        else
        {
            printf("Can't allocate new struct");
        }

        // Sets the delay time between each request based on the randomly chosen delay time.
        vTaskDelay(pdMS_TO_TICKS(100 * ran_delay));
    }
    vTaskDelete(NULL);
}

void active_Task(void *pvParameter)
{
    for (;;)
    {
        // Checks if the queue exists and if there is any request to receive.
        // If there is a request, proceeds with processing.
        struct TaskType *task = (struct TaskType *)pvParameter;
        struct QueueData *pRxMessage;
        if (xQueue != NULL)
        {
            if (xQueueReceive(xQueue, &pRxMessage, (TickType_t)10) == pdPASS)
            {
                // If the ID of the request matches the ID of the current task, prints the message of the request to the console and frees the memory of the request.
                if (pRxMessage->dataID == task->taskID)
                {
                    printf("%s\n", pRxMessage->message);
                    // always remember to free the memory when done.
                    free(pRxMessage);
                }

                // If the IDs do not match, prints an error message to the console and takes further action.
                // If the rejection count has not reached the limit (3 times), increments the rejection count and sends the request back to the front of the queue.
                // If the rejection limit has been exceeded, prints an error message and skips the request.
                else
                {
                    printf("%s: received %s, but it's not my task\n", task->taskName, pRxMessage->message);
                    if (pRxMessage->reject < 3)
                    {
                        pRxMessage->reject++;
                        xQueueSendToFront(xQueue, (void *)&pRxMessage, (TickType_t)10);
                    }
                    else
                    {
                        printf("This task %s is rejected %d times, skiping the task\n", pRxMessage->message, pRxMessage->reject++);
                        free(pRxMessage);
                    }
                }
            }
            else
            {
                printf("queue empty\n");
            }
        }

        vTaskDelay(pdMS_TO_TICKS(10));
    }
    vTaskDelete(NULL);
}

void app_main(void)
{
    // Create a Queue
    xTaskCreate(&XQueue_Start, "queue_start", 2048, NULL, 10, NULL);
    
    // Create the reception_Task
    xTaskCreate(&reception_Task, "rec", 2048, NULL, 10, NULL);
    
    // Create Tasks for Sensors (active_Task)
    xTaskCreate(&active_Task, "air", 2048, (void *)&Sensor_Air, 10, NULL);
    xTaskCreate(&active_Task, "moisture", 2048, (void *)&Sensor_Moisture, 10, NULL);
    xTaskCreate(&active_Task, "water", 2048, (void *)&Sensor_Water, 10, NULL);
    xTaskCreate(&active_Task, "light", 2048, (void *)&Sensor_Light, 10, NULL);
}   