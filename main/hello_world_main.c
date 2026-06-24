#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_log.h"
#include "esp_random.h"
#include "esp_vfs_dev.h"   // 提供 USB Serial JTAG VFS API

static const char *TAG = "usb_hello";

void app_main(void)
{
    // 啟用 USB Serial JTAG 作為標準輸入/輸出
#ifdef CONFIG_USB_SERIAL_JTAG_ENABLED
    esp_vfs_usb_serial_jtag_use_driver();
#else
    printf("Warning: USB Serial JTAG not enabled in menuconfig.\n");
#endif

    const char *bars[] = { "▁", "▂", "▃", "▄", "▅", "▆", "▇", "█" };
    int level[16];

    printf("Starting Hello World animation over USB...\n");

    // 動畫顯示 "Hello World!" 字串
    const char *msg = "Hello World!";
    size_t len = strlen(msg);

    while (1) {
        // 每次隨機產生 16 個 bar
        for (int i = 0; i < 16; i++) {
            level[i] = esp_random() % 8;
        }

        // 清除行並回到行首
        printf("\033[2K\r");

        // 顯示動畫：前半段是隨機 bars，最後附上 Hello World!
        for (int i = 0; i < 16; i++) {
            printf("%s ", bars[level[i]]);
        }
        printf(" %s", msg);

        fflush(stdout);

        // 控制動畫幀率，避免 watchdog
        vTaskDelay(pdMS_TO_TICKS(100));
    }
}
