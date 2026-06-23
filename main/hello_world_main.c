#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_log.h"
#include "esp_random.h"
#include "esp_vfs_dev.h" // for esp_vfs_dev_usb_serial_jtag_register

static const char *TAG = "usb_anim";

void app_main(void)
{
    const char *bars[] = {
        "▁", "▂", "▃", "▄", "▅", "▆", "▇", "█"
    };
    int level[16];
    uint8_t ch;

    // 註冊 USB Serial JTAG 為 VFS 裝置（把 stdin/stdout/stderr 綁到 USB）
    // 若 menuconfig 已啟用，這個呼叫會把標準 I/O 綁到 USB Serial JTAG
    esp_vfs_dev_usb_serial_jtag_register();

    // 取得 stdin 的檔案描述符並設為 non-blocking
    int fd = fileno(stdin);
    int flags = fcntl(fd, F_GETFL, 0);
    if (flags == -1) {
        ESP_LOGW(TAG, "fcntl F_GETFL failed: %s", strerror(errno));
    } else {
        if (fcntl(fd, F_SETFL, flags | O_NONBLOCK) == -1) {
            ESP_LOGW(TAG, "fcntl F_SETFL failed: %s", strerror(errno));
        }
    }

    printf("Starting animation over USB... Press [ESC] key to stop.\n");
    vTaskDelay(pdMS_TO_TICKS(500));

    while (1) {
        // 非阻塞讀 stdin
        ssize_t r = read(fd, &ch, 1);
        if (r > 0) {
            if (ch == 27) { // ESC
                printf("\n\033[2K\rESC pressed. Animation stopped.\n");
                break;
            }
        } else if (r < 0 && errno != EAGAIN && errno != EWOULDBLOCK) {
            // 真正的錯誤
            ESP_LOGW(TAG, "read error: %s", strerror(errno));
        }

        // 產生隨機高度
        for (int i = 0; i < 16; i++) {
            level[i] = esp_random() % 8;
        }

        // 顯示
        printf("\033[2K\r");
        for (int i = 0; i < 16; i++) {
            printf("%s ", bars[level[i]]);
        }
        fflush(stdout);

        vTaskDelay(pdMS_TO_TICKS(120));
    }

    printf("Program finished.\n");
}
