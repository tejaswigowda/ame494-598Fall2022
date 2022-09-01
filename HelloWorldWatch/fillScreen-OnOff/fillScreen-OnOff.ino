#define LILYGO_WATCH_2019_WITH_TOUCH
#include <LilyGoWatch.h>

TTGOClass *ttgo;

int screenOn = 0;

void pressed()
{

}
void released()
{
  if(screenOn == 0){
    screenOn = 1;
  }
  else{
    screenOn = 0;
  }
}

void setup()
{
    Serial.begin(115200);
    ttgo = TTGOClass::getWatch();
    ttgo->begin();
    ttgo->openBL();

    ttgo->button->setPressedHandler(pressed);
    ttgo->button->setReleasedHandler(released);

}

void loop()
{
    ttgo->button->loop();
    Serial.println(screenOn);

    if(screenOn == 0){
      ttgo->tft->fillScreen(TFT_RED);
      delay(1000);
      ttgo->tft->fillScreen(TFT_GREEN);
      delay(1000);
      ttgo->tft->fillScreen(TFT_BLUE);
      delay(1000);
    }
    else{
       ttgo->tft->fillScreen(TFT_BLACK);
    }
    
}
