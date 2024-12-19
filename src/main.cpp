
#include <WiFi.h>
#include <WiFiClient.h>
#include <ArduinoJson.h>
// 替换为你自己的WiFi网络名称（SSID）和密码
const char* ssid = "m0nesy";
const char* password = "by060326";
// 替换为你申请到的心知天气API Key
const char* apiKey = "S1Ahf1JET_NF5BU4b";
// 心知天气API的基础URL
const char* apiUrl = "api.seniverse.com";
const char* host = "api.seniverse.com";
// 要查询天气的城市名称，可按需修改
const char* city = "xiamen";
WiFiClient client;
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
bool getWeatherInfo() {
    if (client.connect(apiUrl, 80)) {
        Serial.println("已连接到天气服务器");
        // 构建请求URL，按照心知天气API要求的格式
        /*String requestUrl = "/v3/weather/now.json?key=" + String(apiKey) + "=" + String(city) + "&language=zh-Hans&unit=c";
        Serial.println("正在发送请求: " + requestUrl);
        client.print(String("GET ") + requestUrl + " HTTP/1.1\r\n" +
             "Host: " + apiUrl + "\r\n" +
             "Connection: close\r\n\r\n");*/


//https://api.seniverse.com/v3/weather/now.json?key=SIMHXoFn5ZYDmEql3&location=xiamen&language=zh-Hans&unit=c
        //URL请求地址 //改为你的api密钥和城市拼音
        String url ="/v3/weather/now.json?key=SIMHXoFn5ZYDmEql3&location=xiamen&language=zh-Hans&unit=c";
        //发送网络请求
        client.print(String("GET ") + url + " HTTP/1.1\r\n" +
                    "Host: " + host + "\r\n" +
                    "Connection: close\r\n\r\n");
        //delay(5000);
        //定义answer变量用来存放请求网络服务器后返回的数据
        String answer;
        Serial.printf("Initial available bytes: %d\n", client.available());
        while(client.available())
        {
            //String line = client.readStringUntil('\r');
            //answer += line;
            answer += (char)client.read();
        }
        //断开服务器连接
        client.stop();
        //Serial.println();
        Serial.println(answer+url);
        Serial.println("closing connection");

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
        if (error) {
            Serial.print("deserializeJson() failed: ");
            Serial.println(error.c_str());
            return 0;

        }
        // 提取天气信息
        const char* weather = doc["results"][0]["now"]["text"].as<const char*>();
        double temperature = doc["results"][0]["now"]["temperature"].as<double>();
        Serial.println("当前城市: " + String(city));
        Serial.println("天气状况: " + String(weather));
        Serial.println("当前温度: " + String(temperature) + "℃");
        return true;
    } else {
        Serial.println("无法连接到天气服务器");
        return false;
    }
}
