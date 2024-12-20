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
        delay(4000);
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
        double temperature = doc["results"][0]["now"]["temperature"].as<double>();
        Serial.println("当前城市: " + String(location));
        Serial.println("天气状况: " + String(weather));
        Serial.println("当前温度: " + String(temperature) + "℃");
        
        return true;
    } else {
        Serial.println("无法连接到天气服务器");
        return false;
    }
    
}