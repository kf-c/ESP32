
extern WiFiUDP ntpUDP;
extern NTPClient timeClient;

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
  if(currentSec<10){
    Serial.print("0");
    Serial.print(currentSec);
  }
  else Serial.print(currentSec);
  Serial.print(":");
  Serial.print(currentMinute);
  Serial.print(":");
  Serial.print(currentHour);
}