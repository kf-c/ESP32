
  extern TFT_eSPI tft;
  extern NTPClient timeClient;
  extern const char *host;
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

  tft.fillRect(112,32,28,28,TFT_BLACK);     //部分区域清屏，刷新秒
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
void Display_Weather() {
  //创建TCP连接
  WiFiClient client;

  const int httpPort = 80;
  if (!client.connect(host, httpPort))
  {
    Serial.println("connection failed");  //网络请求无响应打印连接失败
    return;
  }

  //URL请求地址 //改为你的api密钥和城市拼音
  String url ="/v3/weather/now.json?key=P5NUAGdPc4f1boCQZ=xiamen&language=zh-Hans&unit=c";
  //发送网络请求
  client.print(String("GET ") + url + " HTTP/1.1\r\n" +
            "Host: " + host + "\r\n" +
            "Connection: close\r\n\r\n");
  //delay(5000);
  for(int i = 0; i < 5; i++) {
    Display_Time();//利用等待 天气服务器响应的时间 更新时间信息
    delay(1000);   //间隔1秒访问ntp,刷新时间戳
  }

  //定义answer变量用来存放请求网络服务器后返回的数据
   String answer0;
   String answer;
  while(client.available())
  {
    String line = client.readStringUntil('\r');
    answer += line;
  }
  //断开服务器连接
  client.stop();
  //Serial.println();
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
  StaticJsonDocument<512> doc;
  DeserializationError error = deserializeJson(doc, jsonAnswer);
  if (error) {
    Serial.print("deserializeJson() failed: ");
    Serial.println(error.c_str());
    return;
  }

  JsonObject results_0 = doc["results"][0];

  JsonObject results_0_location = results_0["location"];
  const char* results_0_location_id = results_0_location["id"]; // "WW0CWDZP17BC"
  const char* results_0_location_name = results_0_location["name"]; // "许昌"
  const char* results_0_location_country = results_0_location["country"]; // "CN"
  const char* results_0_location_path = results_0_location["path"]; // "许昌,许昌,河南,中国"
  const char* results_0_location_timezone = results_0_location["timezone"]; // "Asia/Shanghai"
  const char* results_0_location_timezone_offset = results_0_location["timezone_offset"]; // "+08:00"

  JsonObject results_0_now = results_0["now"];
  const char* results_0_now_text = results_0_now["text"]; // "阴"
  const char* results_0_now_code = results_0_now["code"]; // "9"
  const char* results_0_now_temperature = results_0_now["temperature"]; // "3"

  const char* results_0_last_update = results_0["last_update"]; // "2022-01-29T17:25:01+08:00"
  String now_address="",now_temperature="",now_weather="",now_weather_code="";
  now_address = results_0_location_name;
  now_weather = results_0_now_text;
  now_weather_code = results_0_now_code;
  now_temperature = results_0_now_temperature;

  tft.fillRect(5,65,32,16,TFT_BLACK);       //打印地区
  if(now_address=="厦门") {
    showMyFonts(5,65,"厦门" , TFT_GOLD);
  }
  #define X 4
  #define Y 110
  #define pX 68
  #define pY 68
  tft.fillRect(X,Y,64,16,TFT_BLACK);
  tft.fillRect(68,68,60,60,TFT_BLACK);
  switch (std::atoi(now_weather_code.c_str())) {//天气代码不是int类型，要先转换
  /************************************************************************************
  天气代码是由心知天气的API接口提供的，详见[天气现象代码说明]
  (https://seniverse.yuque.com/books/share/e52aa43f-8fe9-4ffa-860d-96c0f3cf1c49/yev2c3)
  *************************************************************************************/
    case 0: showMyFonts(X,Y,"晴" , TFT_GREEN); break;
    case 1: showMyFonts(X,Y,"夜晚晴" , TFT_GREEN); break;
    case 2: showMyFonts(X,Y,"晴" , TFT_GREEN); break;
    case 3: showMyFonts(X,Y,"夜晚晴" , TFT_GREEN); break;
    case 4: showMyFonts(X,Y,"多云" , TFT_GREEN); break;
    case 5: 
    case 6: showMyFonts(X,Y,"晴间多云" , TFT_GREEN); break;
    case 7: showMyFonts(X,Y,"大部多云" , TFT_GREEN); ;break;
    case 8: showMyFonts(X,Y,"大部多云" , TFT_GREEN); break;
    case 9: showMyFonts(X,Y,"阴" , TFT_GREEN);break;
    case 10: showMyFonts(X,Y,"阵雨" , TFT_GREEN); break;
    case 11: showMyFonts(X,Y,"雷阵雨" , TFT_GREEN); break;
    case 12: showMyFonts(X,Y,"雹" , TFT_GREEN); break;
    case 13: showMyFonts(X,Y,"小雨" , TFT_GREEN); break;
    case 14: showMyFonts(X,Y,"中雨" , TFT_GREEN); break;
    case 15: showMyFonts(X,Y,"大雨" , TFT_GREEN); break;
    case 16: showMyFonts(X,Y,"暴雨" , TFT_GREEN); break;
    case 17: showMyFonts(X,Y,"大暴雨" , TFT_GREEN); break;
    case 18: showMyFonts(X,Y,"特大暴雨" , TFT_GREEN); break;
    case 19: showMyFonts(X,Y,"冻雨" , TFT_GREEN);break;
    case 20: showMyFonts(X,Y,"雨夹雪" , TFT_GREEN); break;
    case 21: showMyFonts(X,Y,"阵雪" , TFT_GREEN); break;
    case 22: showMyFonts(X,Y,"小雪" , TFT_GREEN);break;
    case 23: showMyFonts(X,Y,"中雪" , TFT_GREEN); break;
    case 24: showMyFonts(X,Y,"大雪" , TFT_GREEN); break;
    case 25: showMyFonts(X,Y,"暴雪" , TFT_GREEN);break;
    case 26: showMyFonts(X,Y,"浮尘" , TFT_GREEN); break;
    case 27: showMyFonts(X,Y,"扬沙" , TFT_GREEN); break;
    case 28: 
    case 29: showMyFonts(X,Y,"沙尘暴" , TFT_GREEN);break;
    case 30: showMyFonts(X,Y,"雾" , TFT_GREEN); break;
    case 31: showMyFonts(X,Y,"霾" , TFT_GREEN); break;
    case 32: showMyFonts(X,Y,"风" , TFT_GREEN);break;
    case 33: 
    case 34: 
    case 35: 
    case 36: showMyFonts(X,Y,"大风" , TFT_GREEN); break;
    case 37: showMyFonts(X,Y,"冷" , TFT_GREEN); break;
    case 38: showMyFonts(X,Y,"热" , TFT_GREEN); break;
    case 99: showMyFonts(X,Y,"未知" , TFT_GREEN); break;
    default: break;
  }
  tft.fillRect(5,87,63,16,TFT_BLACK);       
  tft.setCursor(5, 88, 1);                 
  tft.setTextColor(TFT_SKYBLUE);             
  tft.setTextSize(2);                    
  tft.println(now_temperature);               

  if ( (( std::atoi(now_temperature.c_str()) ) < 10) && (( std::atoi(now_temperature.c_str()) ) >= 0)) {
    showMyFonts(24,87,"℃",TFT_SKYBLUE); 
  }
  else{
    showMyFonts(40,87,"℃",TFT_SKYBLUE); 
  }
}




