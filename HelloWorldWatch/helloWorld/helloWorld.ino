  #define LILYGO_WATCH_2019_WITH_TOUCH
#include <LilyGoWatch.h>

TTGOClass *ttgo;

void setup()
{
    Serial.begin(115200);
    ttgo = TTGOClass::getWatch();
    ttgo->begin();
    ttgo->openBL();

    ttgo->tft->fillScreen(TFT_WHITE);
    ttgo->tft->setTextColor(TFT_BLACK, TFT_WHITE);
    ttgo->tft->setTextFont(4);
    ttgo->tft->drawString("Hello World",  5, 10);
}

void loop()
{ 
}
