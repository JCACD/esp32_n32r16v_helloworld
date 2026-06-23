#include <stdio.h>
#include <string.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_log.h"
#include "esp_random.h"

void app_main(void)
{
    const char *bars[] = { "▁", "▂", "▃", "▄", "▅", "▆", "▇", "█" };
    int level[16];

    while (1) {
        // 產生隨機高度
        for (int i = 0; i < 16; i++) {
            level[i] = esp_random() % 8;
        }

        // 顯示
        // printf("\033[2K\r");  // 清除行並回到行首
        for (int i = 0; i < 16; i++) {
            printf("%s ", bars[level[i]]);
        }
        fflush(stdout);

        vTaskDelay(pdMS_TO_TICKS(50));  // 必須要有，避免 watchdog
    }

    // 進度條範例
    for (int i = 0; i <= 100; i++) {
        printf("\rProgress: %d%%", i);
        fflush(stdout);
        vTaskDelay(pdMS_TO_TICKS(50));  // 用 FreeRTOS delay
    }

    printf("Program finished.\n");
}
