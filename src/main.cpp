
#include <Arduino.h>
#include <WiFi.h>
#include "fuc.h"

//const char* ssid = "m0nesy";
//const char* password = "by060326";
const char* ssid = "ppq";
const char* password = "pppppppp";
// 心知天气API的相关信息，替换为你自己申请的API Key
const char* apiKey = "SIMHXoFn5ZYDmEql3";
const char* apiUrl = "https://api.seniverse.com/v3/weather/now.json";

// 要查询天气的城市，可根据实际需求修改
const char* city = "Xiamen";

WiFiClient client;

void setup(){
    // WiFi 连接
    Serial.begin(115200);
    WiFi.begin(ssid, password);
    int timeout = millis();
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
        if(millis() - timeout > 30000){
            Serial.println("WiFi connection timeout");
            return;
        }
    }
    Serial.println(" WiFI connected");
    //ip 地址设置
    IPAddress local_IP(192, 168, 1, 100); // 设置的静态IP地址
    IPAddress gateway(192, 168, 1, 1);    // 网关地址
    IPAddress subnet(202, 168, 1, 0);     // 子网掩码
    IPAddress dns_server(8, 8, 8, 8);     // DNS服务器地址，可按需更换

    if (!WiFi.config(local_IP, gateway, subnet, dns_server)) {
        Serial.println("配置静态IP失败");
    }
    else Serial.println("配置静态IP成功");
}


int lastTimer = millis();
void loop() {
    if (millis() - lastTimer > 3000) {
        lastTimer = millis();
        getWeatherInfo();
    }
}