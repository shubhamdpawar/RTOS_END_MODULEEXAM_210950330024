#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"

QueueHandle_t data_Q;
TickType_t xTimeStamp;

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
    while(1)
    {
    xTimeStamp = xTaskGetTickCount()*portTICK_PERIOD_MS;
    printf("%d : Hello this is start of third task\n",xTimeStamp);
    vTaskDelay(5000 / portTICK_PERIOD_MS);
    }

}

void task_4(void *data)
{
    int msg = 2;
    while(1)
    {
    printf("Hello this is start of Send task\n");
    xQueueSend( data_Q, &msg,( TickType_t ) 2 );
    msg++;
    vTaskDelay(2000 / portTICK_PERIOD_MS);
    }

}

void task_5(void *data)
{
    int buf;
    while(1)
    {
    printf("Hello this is start of Recieve task\n");
    xQueueReceive( data_Q,&buf, 0);
    printf("recieved BUF: %d\n",buf);
    vTaskDelay(3000 / portTICK_PERIOD_MS);
    }

}

void app_main(void)
{

     data_Q = xQueueCreate( 5, sizeof(int));

    if( data_Q == NULL )
    {
        /* Queue was not created and must not be used. */
        printf("Queue not created\n");
    }else{
   xTaskCreate(task_1,"task1",2048,NULL,5,NULL);
    xTaskCreate(task_2,"task2",2048,NULL,6,NULL);
    xTaskCreate(task_3,"task3",2048,NULL,7,NULL);
    xTaskCreate(task_4,"sender",1024,NULL,8,NULL);
    xTaskCreate(task_5,"reciever",2048,NULL,9,NULL);
    }
}
