#define MAIN
#include <Arduino.h>
#include <WiFi.h>
#include <WiFiUdp.h>
#include <HTTPClient.h>
#include <NTPClient.h> // 时间服务提供程序
#include "fuc.h"

const char* ssid = "m0nesy";
const char* password = "by060326";
// 网络时间服务器地址，这里以NTP服务器为例
const char* ntpServer = "pool.ntp.org";
const long utcOffsetInSeconds = 28800;
WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, "ntp.aliyun.com");
void setup(){
    // WiFi 连接
    Serial.begin(115200);
    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }
    Serial.println("connected. "); // 打印汉字
    // time
    timeClient.begin();
    timeClient.setTimeOffset(28800);  // + 1区 偏移3600， +8区 ：3600×8 = 2880
}

int lastTimer = millis();

void loop() {
    if (millis() - lastTimer > 1000) {
        lastTimer = millis();
        Display_Time();
    }
}