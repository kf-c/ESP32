#include <ArduinoJson.h>
extern WiFiClient client;
extern const char* apiKey;
extern const char* apiUrl;  
extern const char* city;

void print(
     const char* str1,
     const char* str2 = nullptr,
     const char* str3 = nullptr
) {
    Serial.print(str1);
    if (str2 != nullptr) {
        Serial.print(str2);
    }

    if (str3 != nullptr) {
        Serial.print(str3);
    }
    delay(1000); // 示例：在屏幕左上角绘制字符串
}

void getWeatherInfo() {
  if (client.connect(apiUrl, 80)) {
    // 构建请求URL，按照心知天气API要求的格式
    String requestUrl = "/v3/weather/now.json?key=" + String(apiKey) + "&location=" + String(city) + "&language=zh-Hans&unit=c";
    Serial.println("正在发送请求: " + requestUrl);
    client.println("GET " + requestUrl + " HTTP/1.1");
    client.println("Host: api.seniverse.com");
    client.println("Connection: close");
    client.println();

    // 等待服务器响应
    int waitTime = 0;
    unsigned long timeout = millis();
    while (client.connected() && !client.available()) {
      if (millis() - timeout > 10000) {
        Serial.println("URL请求超时");
        return;
      }
    }

    // 读取响应数据
    String response = "";
    while (client.available()) {
      response += (char)client.read();
    }
    client.stop();

    // 使用ArduinoJson库解析JSON数据
    StaticJsonDocument<1024> doc;
    DeserializationError error = deserializeJson(doc, response);
    if (error) {
      Serial.println("解析JSON数据出错: " + String(error.c_str()));
      return;
    }

    // 提取天气信息，以下是示例提取当前温度和天气状况，根据API返回的实际结构调整
    const char* weather = doc["results"][0]["now"]["text"].as<const char*>();
    double temperature = doc["results"][0]["now"]["temperature"].as<double>();
    Serial.println("当前城市: " + String(city));
    Serial.println("天气状况: " + String(weather));
    Serial.println("当前温度: " + String(temperature) + "℃");
  } else {
    Serial.println("无法连接到天气服务器");
    static int count = 0; 
    count++;
    if (count > 5) {
      return;
    }
  }
}