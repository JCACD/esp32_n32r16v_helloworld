#include <stdio.h>
#include <string.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_log.h"
#include "esp_random.h"
#include "driver/uart.h"      // 引入 UART 驅動，用於非阻塞讀取按鍵

void app_main(void)
{
    const char *bars[] = {
        "▁", "▂", "▃", "▄", "▅", "▆", "▇", "█"
    };

    int level[16];
    uint8_t ch;
    
    // 提示使用者
    printf("Starting animation... Press [ESC] key to stop.\n");
    vTaskDelay(pdMS_TO_TICKS(500)); // 稍微延遲讓使用者看到提示

    // 清空 UART 緩衝區，確保不會讀到開機時的殘留雜訊
    uart_flush(UART_NUM_0);

    while (1) {
        // ==========================================
        // 1. 非阻塞檢查是否按下 ESC 鍵
        // ==========================================
        // uart_read_bytes 的倒數第二個參數是長度(1 byte)，最後一個參數是 timeout。
        // 設定 timeout = 0 代表「非阻塞 (Non-blocking)」，沒資料會立刻返回 0。
        int len = uart_read_bytes(UART_NUM_0, &ch, 1, 0); 
        
        if (len > 0) {
            // ESC 鍵的 ASCII 碼是 27 (0x1B)
            if (ch == 27) { 
                printf("\n\033[2K\rESC pressed. Animation stopped.\n");
                break; // 跳出無窮迴圈
            }
        }

        // ==========================================
        // 2. 產生隨機高度
        // ==========================================
        for (int i = 0; i < 16; i++) {
            level[i] = esp_random() % 8;
        }

        // ==========================================
        // 3. 動態顯示 (使用 ANSI 控制碼優化)
        // ==========================================
        // \033[2K : ANSI 控制碼，意思是「清除當前行所有字元 (Erase entire line)」
        // \r      : 游標回到行首 (Carriage Return)
        // 這樣可以確保每次覆蓋時不會留下上一幀的殘影
        printf("\033[2K\r"); 
        
        for (int i = 0; i < 16; i++) {
            printf("%s ", bars[level[i]]);
        }
        
        fflush(stdout); // 強制刷新輸出緩衝區，確保畫面即時更新

        // ==========================================
        // 4. 控制動畫幀率
        // ==========================================
        vTaskDelay(pdMS_TO_TICKS(120)); // 約 8 FPS
    }
    
    printf("Program finished.\n");
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
