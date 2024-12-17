#define TFT
#include <TFT_eSPI.h>
#include<WiFi.h>
#include <HTTPClient.h>
#include<time.h>
#include<fuc.h>
TFT_eSPI tft = TFT_eSPI();
const char* ssid = "m0nesy";
const char* password = "by060326";
// 网络时间服务器地址，这里以NTP服务器为例
const char* ntpServer = "pool.ntp.org";
const long utcOffsetInSeconds = 28800;
hw_timer_t *timer = NULL;
void setup(){
  tft.init();//初始化
  tft.setRotation(3);                 //屏幕旋转方向
  tft.fillScreen(TFT_BLACK);//底色
  tft.setTextFont(2);
  tft.setTextSize(2);                 //字体大小
  tft.setTextColor(TFT_DARKGREEN);    //文字颜色
  // sprite.setSwapBytes(true);//决定字体是RGB还是BGR
  tft.setCursor(10,10);               //设置光标位置
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
  //time
  configTime(utcOffsetInSeconds, 0, ntpServer);
  while (!time(nullptr)) {
    print("Waiting for time sync...");
  }
  print("Waiting for time sync...");
  //定时器
  timer = timerBegin(0, 80, true); // 使用定时器 0，预分频器 80，计数器向上
  timerAttachInterrupt(timer, &onTimer, true); // 附加中断服务例程，启用真正的硬件中断
  timerAlarmWrite(timer, 10000, true); // 设置定时器为 1 秒（1000000 微秒）
  timerAlarmEnable(timer); // 启用定时器中断
}
void loop(){
}

