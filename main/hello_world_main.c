#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_log.h"

void app_main(void)
{
    printf("Hello world!\n");
    ESP_LOGI("main", "ESP32-S3 N32R16V is running with 32MB Flash & 16MB PSRAM!");
    
    while(1) {
        vTaskDelay(pdMS_TO_TICKS(1000));
    }
}
