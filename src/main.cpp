//#include <TFT_eSPI.h>
#include<WiFi.h>
#include <WiFiUdp.h>
#include <HTTPClient.h>
#include <NTPClient.h>//时间服务提供程序
//TFT_eSPI tft = TFT_eSPI();
const char* ssid = "m0nesy";
const char* password = "by060326";
// 网络时间服务器地址，这里以NTP服务器为例
const char* ntpServer = "pool.ntp.org";
const long utcOffsetInSeconds = 28800;

WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP,"ntp.aliyun.com");

void setup(){

      //WiFi 连接
      Serial.begin(115200);
      WiFi.begin(ssid, password);
      while (WiFi.status() != WL_CONNECTED) {
      delay(500);
      Serial.print(".");
      }
      Serial.println("connected. ");//打印汉字
      //time
configTime(utcOffsetInSeconds, 0, ntpServer);
  while (!time(nullptr)) {
    delay(1000);
    Serial.println("Waiting for time sync...");
  }
  Serial.println("Time synced successfully");
}

void loop() {
  time_t now = time(nullptr);
  Serial.print("Current time is: ");
  Serial.println(ctime(&now));
  delay(1000);
  Serial.println("");
  //if you can see the time, the program is working
}