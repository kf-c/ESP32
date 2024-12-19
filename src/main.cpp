#include <WiFi.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>

const char *ssid = "XMUNET+";
const char *password = "Ckf84861306";
String url = "https://api.seniverse.com/v3/weather/now.json";
String city = "厦门";
String key = "S1Ahf1JET_NF5BU4b";

void setup() {
  Serial.begin(11520);
  while(!Serial);
  Serial.println("Booting");
  // 连接WiFi
  /*WiFi.begin(ssid, password);
  while (WiFi.status()!= WL_CONNECTED) {
    delay(1000);
    Serial.println("WAiting...");
  }
  Serial.println("连接成功");
  Serial.print("IP地址:");
  Serial.println(WiFi.localIP());*/
}

void loop() {
  /*// 创建HTTPClient对象
  HTTPClient http;
  // 发送GET请求
  http.begin(url + "?key=" + key + "&location=" + city);
  int httpCode = http.GET();
  // 获取响应状态码
  Serial.printf("HTTP状态码:%d\n", httpCode);
  if (httpCode == HTTP_CODE_OK) {
    // 获取响应正文
    String response = http.getString();
    Serial.println("响应数据");
    Serial.println(response);
    // 创建DynamicJsonDocument对象
    DynamicJsonDocument doc(1024);
    // 解析JSON数据
    deserializeJson(doc, response);
    // 从解析后的JSON文档中获取值
    int temp = doc["results"][0]["now"]["temperature"].as<int>();
    String name = doc["results"][0]["location"]["name"].as<String>();
    String wea = doc["results"][0]["now"]["text"].as<String>();
    String Time = doc["results"][0]["last_update"].as<String>();
    Serial.printf("位置：%s\n", name);
    Serial.printf("温度：%d\n", temp);
    Serial.printf("天气：%s\n", wea);
    Serial.printf("更新时间：%s\n", Time);
  }
  http.end();
  delay(6000);*/
}