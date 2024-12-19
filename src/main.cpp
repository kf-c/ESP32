#ifndef HEAD
#define HEAD
#include <TFT_eSPI.h>
#include<WiFi.h>
#include <WiFiUdp.h>
#include <ArduinoJson.h>
#include <HTTPClient.h>
#include <NTPClient.h>//时间服务提供程序
#include"xingkai_28.h"
#include<fuc.h>
#endif
TFT_eSPI tft = TFT_eSPI();
const char* ssid = "m0nesy";
const char* password = "by060326";

WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP,"ntp.aliyun.com");
const char *host = "api.seniverse.com";//心知天气服务器地址

void setup(){
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
}
  //time
  void loop() {
  // put your main code here, to run repeatedly:
  Display_Weather(); //天气信息每2分钟更新一次
  for(int i = 0; i < 115; i++) {
    Display_Time();
    delay(1000);   //间隔1秒访问ntp,刷新时间戳
  }
}

