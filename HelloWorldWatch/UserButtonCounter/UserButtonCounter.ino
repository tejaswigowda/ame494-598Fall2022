#define LILYGO_WATCH_2019_WITH_TOUCH
#include <LilyGoWatch.h>

TTGOClass *ttgo;
 int count = 0;

void pressed()
{
    //uint16_t color = random(0xFFFF);
    //ttgo->eTFT->fillScreen(color);
    //ttgo->eTFT->setTextColor(color, TFT_WHITE);
    count++;
    ttgo->tft->drawString(String(count).c_str(),  5, 100, 4);
}
void released()
{
    uint16_t color = random(0xFFFF);
    ttgo->tft->fillScreen(color);
    ttgo->tft->setTextColor(color, TFT_WHITE);
    ttgo->tft->drawString("User Button released",  5, 100, 4);
}

void setup()
{
    Serial.begin(115200);
    ttgo = TTGOClass::getWatch();
    ttgo->begin();
    ttgo->openBL();

    ttgo->tft->fillScreen(TFT_BLACK);
    ttgo->tft->setTextColor(TFT_WHITE, TFT_BLACK);
    ttgo->tft->setTextFont(4);
    ttgo->tft->drawString("0",  5, 100, 4);

    ttgo->button->setPressedHandler(pressed);
   // ttgo->button->setReleasedHandler(released);

}

void loop()
{
    ttgo->button->loop();
}
