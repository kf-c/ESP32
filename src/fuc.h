extern TFT_eSPI tft;
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