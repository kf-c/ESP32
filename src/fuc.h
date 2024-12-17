#ifndef TFT
#define TFT
#include <TFT_eSPI.h>
//#include"main.cpp"
#endif
extern TFT_eSPI tft;
void print(
    TFT_eSPI& tft,
     const char* str1,
     const char* str2 = nullptr,
     const char* str3 = nullptr
) {
    tft.fillScreen(TFT_BLACK);
    tft.drawString(str1,10,10);
    if (str2 != nullptr) {
        tft.drawString(str2, 10, 20 + tft.fontHeight(2));
    }

    if (str3 != nullptr) {
        tft.drawString(str3, 10, 30 + tft.fontHeight(2) * 2);
    }
    delay(1000); // 示例：在屏幕左上角绘制字符串
}
void onTimer() {
    print(tft,"time:",ctime((const time_t*)time(nullptr)));
}//Serial.print