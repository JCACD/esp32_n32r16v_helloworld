#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_log.h"
#include "esp_random.h"   // 加這行

void app_main(void)
{
    printf("Hello world!\n");
    ESP_LOGI("main", "ESP32-S3 N32R16V is running with 32MB Flash & 16MB PSRAM!");

    const char *bars[] = {
        "▁",
        "▂",
        "▃",
        "▄",
        "▅",
        "▆",
        "▇",
        "█"
    };

    int level[16];

    while (1) {

        printf("\r");

        for (int i = 0; i < 16; i++)
        {
            level[i] = esp_random() % 8;
            printf("%s ", bars[level[i]]);
        }

        fflush(stdout);

        vTaskDelay(pdMS_TO_TICKS(120));
    }
}
// #include <stdio.h>
// #include "freertos/FreeRTOS.h"
// #include "freertos/task.h"
// #include "esp_log.h"

// void app_main(void)
// {
//     printf("Hello world!\n");
//     ESP_LOGI("main", "ESP32-S3 N32R16V is running with 32MB Flash & 16MB PSRAM!");
    
//     while(1) {
//         vTaskDelay(pdMS_TO_TICKS(1000));
//     }
// }
