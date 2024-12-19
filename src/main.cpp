#include <WiFi.h>
#include <WiFiClient.h>
#include <ArduinoJson.h>

// 替换为你自己的WiFi网络名称（SSID）和密码
const char* ssid = "ppq";
const char* password = "pppppppp";

// 替换为你申请到的心知天气API Key
const char* apiKey = "S1Ahf1JET_NF5BU4b";
// 心知天气API的基础URL
const char* apiUrl = "https://api.seniverse.com/v3/weather/now.json";
// 要查询天气的城市名称，可按需修改
const char* city = "Xiamen";

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
        // 构建请求URL，按照心知天气API要求的格式
        String requestUrl = "/v3/weather/now.json?key=" + String(apiKey) + "&location=" + String(city) + "&language=zh-Hans&unit=c";
        Serial.println("正在发送请求: " + requestUrl);
        client.println("GET " + requestUrl + " HTTP/1.1");
        client.println("Host: api.seniverse.com");
        client.println("Connection: close");
        client.println();

        // 等待服务器响应
        while (client.connected() &&!client.available()) {
            delay(100);
        }

        // 读取响应数据
        String response = "";
        while (client.available()) {
            response += (char)client.read();
        }
        client.stop();

        // 使用ArduinoJson库解析JSON数据
        StaticJsonDocument<2048> doc;  // 根据实际返回数据大小适当调整容量
        DeserializationError error = deserializeJson(doc, response);
        if (error) {
            Serial.println("解析JSON数据出错: " + String(error.c_str()));
            return false;
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