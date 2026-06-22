#include <Arduino.h>

void setup() {
  // 初始化序列埠
  Serial.begin(115200);
  delay(1000);
}

void loop() {
  // 每隔一秒在序列埠監控視窗印出 Hello World
  Serial.println("Hello World from ESP32-S3!");
  delay(1000);
}
