#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_random.h"

void app_main(void)
{
    const char *bars[] = {
        "▁", "▂", "▃", "▄", "▅", "▆", "▇", "█"
    };

    int level[16];

    while (1) {
        // 1. 產生隨機高度
        for (int i = 0; i < 16; i++) {
            level[i] = esp_random() % 8;
        }

        // 2. 動態顯示 (使用 ANSI 控制碼優化)
        // \033[2K : ANSI 控制碼，意思是「清除當前行所有字元 (Erase entire line)」
        // \r      : 游標回到行首 (Carriage Return)
        // 這樣可以確保每次覆蓋時不會留下上一幀的殘影
        printf("\033[2K\r"); 
        
        for (int i = 0; i < 16; i++) {
            printf("%s ", bars[level[i]]);
        }
        
        fflush(stdout); // 強制刷新輸出緩衝區，確保畫面即時更新

        // 3. 控制動畫幀率
        vTaskDelay(pdMS_TO_TICKS(120)); // 約 8 FPS
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
