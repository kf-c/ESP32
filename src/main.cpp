#ifndef HEAD
#define HEAD
#include <TFT_eSPI.h>
#include<WiFi.h>
#include <WiFiUdp.h>
#include <HTTPClient.h>
#include <NTPClient.h>//时间服务提供程序
#include"xingkai_28.h"
#include"fuc.h"
#endif
TFT_eSPI tft = TFT_eSPI();
const char* ssid = "m0nesy";
const char* password = "by060326";
//const char* ssid = "ppq";
//const char* password = "pppppppp";
// 记录上次更新天气信息的时间戳（毫秒），用于定时更新
unsigned long lastUpdateTime = millis();
// 设置更新间隔，这里设为10分钟（600000毫秒），可根据需求调整
const unsigned long updateInterval = 20000;

bool getWeatherInfo();
WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP,"ntp.aliyun.com");

void setup(){
  Serial.begin(115200);
  while(!Serial);
  Serial.println("loaded.");
  tft.init();//初始化
  tft.setRotation(3);                 //屏幕旋转方向
  tft.fillScreen(TFT_BLACK);//底色
  tft.loadFont(xingkai_28);     
  tft.setTextColor(TFT_DARKGREEN);    //文字颜色
  // sprite.setSwapBytes(true);//决定字体是RGB还是BGR
  //WiFi 连接
  int try_time=-30;
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED&&try_time) {
  delay(500);try_time++;
  tft.print(".");
  }
  if(try_time){
    print("Connection Success");
  }
  else{
    print("Connection Failed");
  }
  delay(2000);
  timeClient.begin();
  timeClient.setTimeOffset(28800);  // + 1区 偏移3600， +8区 ：3600×8 = 28800
  delay(2500);
  tft.fillScreen(TFT_BLACK);
  Display_Time();
  getWeatherInfo();
  tft.setTextColor(TFT_ORANGE);
  Display_Time();
  getWeatherInfo();
  tft.drawString("--神山鬼眼",80,210);

  void loop() {
    if (millis() - lastUpdateTime >= updateInterval) {
        lastUpdateTime = millis();
        getWeatherInfo();
    }   
    delay(1000);
    Display_Time();
       //间隔1秒访问ntp,刷新时间戳

}

