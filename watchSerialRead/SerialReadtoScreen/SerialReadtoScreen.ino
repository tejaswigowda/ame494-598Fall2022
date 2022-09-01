#define LILYGO_WATCH_2019_WITH_TOUCH
#include <LilyGoWatch.h>

TTGOClass *ttgo;

String inData;

void setup() {
  // initialize serial:
   Serial.begin(115200);
   ttgo = TTGOClass::getWatch();
   ttgo->begin();
   ttgo->openBL();

   ttgo->tft->fillScreen(TFT_BLACK);
   ttgo->tft->setTextColor(TFT_WHITE, TFT_BLACK);
   ttgo->tft->setTextFont(4);
}

void loop() {
    while (Serial.available() > 0)
    {
        char received = Serial.read();
        inData += received; 

        // Process message when new line character is received
        if (received == '\n')
        {
            Serial.print("Message Received: ");
            Serial.print(inData);

            ttgo->tft->fillScreen(TFT_BLACK);
            ttgo->tft->drawString(inData,  5, 10);
            
            inData = ""; // Clear received buffer
        }
    }
}
