#ifndef HEAD
#define HEAD
#include <TFT_eSPI.h>
#include<WiFi.h>
#include <WiFiUdp.h>
#include <HTTPClient.h>
#include <NTPClient.h>//时间服务提供程序
#endif
#include <ArduinoJson.h>
#include <WiFiClient.h>
// 替换为你申请到的心知天气API Key
const char* apiKey = "S1Ahf1JET_NF5BU4b";
// 心知天气API的基础URL
const char* host = "api.seniverse.com";
const char* apiUrl = "https://api.seniverse.com/v3/weather/now.json";
// 要查询天气的城市名称，可按需修改
const char* city = "xiamen";
  WiFiClient client;
  extern TFT_eSPI tft;
  extern NTPClient timeClient;
void print(
    const char* str1,
    const char*str2 = nullptr,
    const char* str3 = nullptr
){
    tft.fillScreen(TFT_BLACK);
    tft.drawString(str1,10,10);
    if(str2 != nullptr){
        tft.drawString(str2,10,30);
    }
    if(str3 != nullptr){
        tft.drawString(str3,10,50);
    }

}//master
void showMyFonts(int32_t x, int32_t y, const char str[], uint32_t color){
    tft.drawString(str,x,y,color);
}
void Display_Time() {

  timeClient.update();
  unsigned long epochTime = timeClient.getEpochTime();
  //打印时间
  int currentSec = timeClient.getSeconds();
  int currentMinute = timeClient.getMinutes();
  int currentHour = timeClient.getHours();
  int weekDay = timeClient.getDay();
  //将epochTime换算成年月日
  struct tm *ptm = gmtime ((time_t *)&epochTime);
  int monthDay = ptm->tm_mday;
  int currentMonth = ptm->tm_mon+1;
  int currentYear = ptm->tm_year+1900;

  tft.fillRect(112,28,32,32,TFT_BLACK);     //部分区域清屏，刷新秒
  //10+2+10=22，“数字”分辨率10*14像素，连续显示时间隔2像素
  tft.setTextColor(TFT_WHITE);
  tft.setCursor(112, 32, 1);
  if (currentSec < 10){                     //将 0-9 变为00-09
    tft.println(0);                    
    tft.setCursor(128, 32, 1);                          
    tft.println(currentSec);                     
  }
  else{
    tft.println(currentSec);               //显示文字
  }  


  if (currentSec==0){                       //刷新分
    tft.fillRect(50,28,44,32,TFT_BLACK);    //20+4+20=44 
  }
  tft.setCursor(50, 32, 1);                
  //tft.setTextFont(7);
  tft.setTextColor(TFT_CYAN);             
  tft.setTextSize(4);                     
  if (currentMinute < 10) {
    tft.println(0);                       
    tft.setCursor(66, 32, 1);               
    tft.setTextColor(TFT_CYAN);              
    tft.setTextSize(4);                     
    tft.println(currentMinute);               
  }
  else{
    tft.println(currentMinute);                
  }


  if (currentMinute==0 && currentSec==0){    //刷新时
    tft.fillRect(5,28,44,32,TFT_BLACK); 
  }
  tft.setCursor(5, 32, 1);            
  //tft.setTextFont(7);
  tft.setTextColor(TFT_CYAN);         
  tft.setTextSize(4);                
  if (currentHour < 10) {
    //tft.println(0);
    tft.setCursor(21, 32, 1);   
    tft.setTextColor(TFT_CYAN);     
    tft.setTextSize(4);                      
    tft.println(currentHour);        
  }
  else{
    tft.println(currentHour); 
  }
  tft.setCursor(40, 28, 1);                //时分分隔符
  tft.setTextColor(TFT_CYAN);       
  tft.setTextSize(4);                
  tft.println(":");                     
  
  
  tft.setCursor(89, 5, 1);                 //月日分隔符
  tft.setTextColor(TFT_WHITE);             
  tft.setTextSize(2);                     
  tft.println("/");                      

  if (currentHour==0 && currentMinute==0 && currentSec==0){      //刷新 日、周
    tft.fillRect(102,5,22,14,TFT_BLACK); 
    tft.fillRect(5,5,32,16,TFT_BLACK); 
  }
  tft.setCursor(102, 5, 1);                
  tft.setTextColor(TFT_YELLOW);          
  tft.setTextSize(2);                   
  if (monthDay < 10) {
    //tft.println(0);                         //"1_月01日",感觉太奇怪了,还是"1_月_1日"吧！
    tft.setCursor(114, 5, 1);         
    tft.setTextColor(TFT_YELLOW);    
    tft.setTextSize(2);             
    tft.println(monthDay);  
  }
  else {
    tft.println(monthDay);    
  }
  switch(weekDay){
    case 0: showMyFonts(2, 2, "周日", TFT_GREENYELLOW);break; 
    case 1: showMyFonts(2, 2, "周一", TFT_GREENYELLOW);break; 
    case 2: showMyFonts(2, 2, "周二", TFT_GREENYELLOW);break; 
    case 3: showMyFonts(2, 2, "周三", TFT_GREENYELLOW);break; 
    case 4: showMyFonts(2, 2, "周四", TFT_GREENYELLOW);break; 
    case 5: showMyFonts(2, 2, "周五", TFT_GREENYELLOW);break; 
    case 6: showMyFonts(2, 2, "周六", TFT_GREENYELLOW);break; 
    default: break;
  }

  if (monthDay==1 && currentHour==0 && currentMinute==0 && currentSec==0){   //刷新月
    tft.fillRect(65,5,22,14,TFT_BLACK); 
  }
  tft.setCursor(65, 5, 1);                 
  tft.setTextColor(TFT_YELLOW);        
  tft.setTextSize(2);                    
  if (currentMonth <10) {
    //tft.println(0);                        //"_1月_1日"比"1_月_1日"更好一点！
    tft.setCursor(77, 5, 1);               
    tft.setTextColor(TFT_YELLOW);          
    tft.setTextSize(2);                    
    tft.println(currentMonth);
  }
  else {
    tft.println(currentMonth);               
  }


  if (currentMonth==1 && monthDay==1 && currentHour==0 && currentMinute==0 && currentSec==0){  //刷新年
    tft.fillRect(180,5,23,7,TFT_BLACK); 
  }
  tft.setCursor(180, 5, 1);             
  tft.setTextColor(TFT_RED);          
  tft.setTextSize(1);                       
  tft.println(currentYear);               
  //delay(1000);
  //天气信息展示
}


bool getWeatherInfo() {
    if (client.connect(host, 80)) {
        //Serial.println("已连接到天气服务器");
         // 构建请求URL
        String requestUrl = String(apiUrl) + "?key=" + apiKey + "&location=" + city + "&language=zh-Hans&unit=c";
        // 发送GET请求
        client.print("GET ");
        client.print(requestUrl);
        client.print(" HTTP/1.1\r\n");
        client.print("Host: ");
        client.print(host);          //url or host
        client.print("\r\n");
        client.print("Connection: close\r\n");
        client.print("\r\n");
        for(int i = 0; i < 5; i++) {
            Display_Time();
            delay(1000);
        }
        //Serial.printf("Initial available bytes: %d\n", client.available());
        // 接收服务器响应
        //定义answer变量用来存放请求网络服务器后返回的数据
        String answer;
        while(client.available())
        {
            String line = client.readStringUntil('\r');
            answer += line;
        }
        //断开服务器连接
        client.stop();
        //Serial.println("answer:"+answer);
        //Serial.println("closing connection");

        //获得json格式的数据
        String jsonAnswer;
        int jsonIndex;
        //找到有用的返回数据位置i 返回头不要
        for (int i = 0; i < answer.length(); i++) {
            if (answer[i] == '{') {
            jsonIndex = i;
            break;
            }
        }
        jsonAnswer = answer.substring(jsonIndex);

        //解析获取到的json数据
        // Stream& input;
        StaticJsonDocument<1024> doc;
        DeserializationError error = deserializeJson(doc, jsonAnswer);
        /*
        if (error) {
            Serial.print("deserializeJson() failed: ");
            Serial.println(error.c_str());
            return 0;

        }
        else Serial.println("deserializeJson() success");
        */
        // 提取天气信息
        const char* weather = doc["results"][0]["now"]["text"].as<const char*>();
        const char* location = doc["results"][0]["location"]["name"].as<const char*>();
        int temperature = doc["results"][0]["now"]["temperature"].as<int>();
        tft.fillRect(4,65,236,33,TFT_BLACK);
        tft.setCursor(4,70);
        tft.setTextColor(TFT_YELLOW);
        tft.print(String(location)+"   "+String(weather)+"   "+String(temperature) + "℃");        
        return true;
    } else {
        tft.setCursor(4,70);
        tft.println("NULL");
        return false;
    }
}


