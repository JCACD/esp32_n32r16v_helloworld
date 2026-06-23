#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_log.h"
#include "esp_random.h"

void app_main(void)
{
    const char *bars[] = {
        "▁", "▂", "▃", "▄", "▅", "▆", "▇", "█"
    };
    int level[16];
    uint8_t ch;
    
    while (1) {
        /* 產生隨機高度 */
        for (int i = 0; i < 16; i++) {
            level[i] = esp_random() % 8;
        }

        /* 顯示 */
        for (int i = 0; i < 16; i++) {
            printf("%s ", bars[level[i]]);
        }
        fflush(stdout);

        vTaskDelay(pdMS_TO_TICKS(120));
    }

    printf("Program finished.\n");
}
