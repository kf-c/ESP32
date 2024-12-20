
#include <WiFi.h>
#include"fuc.h"
// 替换为你自己的WiFi网络名称（SSID）和密码
//const char* ssid = "m0nesy";
//const char* password = "by060326";
const char* ssid = "ppq";
const char* password = "pppppppp";
// 记录上次更新天气信息的时间戳（毫秒），用于定时更新
unsigned long lastUpdateTime = 0;
// 设置更新间隔，这里设为10分钟（600000毫秒），可根据需求调整
const unsigned long updateInterval = 3000; 
bool getWeatherInfo();
void setup() {
    Serial.begin(115200);
    // 连接WiFi网络
    WiFi.begin(ssid, password);
    while (WiFi.status()!= WL_CONNECTED) {
        delay(1000);
        Serial.println("正在连接WiFi...");
    }
    Serial.println("已连接到WiFi网络");
}
void loop() {
    if (millis() - lastUpdateTime >= updateInterval) {
        if (getWeatherInfo()) {
            Serial.println("天气信息更新成功");
        } else {
            Serial.println("天气信息更新失败，请检查网络或API设置");
        }
        lastUpdateTime = millis();
    }
    delay(1000);
}          

