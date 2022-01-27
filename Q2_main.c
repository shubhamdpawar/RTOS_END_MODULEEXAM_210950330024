#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/timers.h"

TaskHandle_t loc_handle;
TimerHandle_t pt_handle;
TickType_t xTimeStamp;
void *const ptTimerID;

void pt_timer_handler(TimerHandle_t xTimer)
{
    printf("%d : Timer fired after 10000 seconds\n",xTimeStamp);
}

void task_1(void *data)
{
    while(1)
    {
    xTimeStamp = xTaskGetTickCount()*portTICK_PERIOD_MS;
    printf("%d : Hello this is start of first task\n",xTimeStamp);
    vTaskDelay(1000 / portTICK_PERIOD_MS);
    }

}
void task_2(void *data)
{
    while(1)
    {
    xTimeStamp = xTaskGetTickCount()*portTICK_PERIOD_MS;
    printf("%d : Hello this is start of second task\n",xTimeStamp);
    vTaskDelay(2000 / portTICK_PERIOD_MS);
    }

}
void task_3(void *data)
{
    pt_handle = xTimerCreate( "Timer",pdMS_TO_TICKS(10000),pdFALSE,ptTimerID,pt_timer_handler);
    xTimerStart(pt_handle,0);
    while(1)
    {
    xTimeStamp = xTaskGetTickCount()*portTICK_PERIOD_MS;    
    printf("%d : Hello this is start of third task\n",xTimeStamp);
    vTaskDelay(5000 / portTICK_PERIOD_MS);
    }

}



void app_main(void)
{
    xTaskCreate(task_1,"task1",2048,NULL,1,NULL);
    xTaskCreate(task_2,"task2",2048,NULL,1,NULL);
    xTaskCreate(task_3,"task3",2048,NULL,1,NULL);
}
