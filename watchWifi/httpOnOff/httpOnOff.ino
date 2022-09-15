#include <Arduino.h>
#define LILYGO_WATCH_2019_WITH_TOUCH
#include <LilyGoWatch.h>

TTGOClass *ttgo;

char * HOSTNAME = "testing-ame";
char * WifiPASS = "12345678";

#include <WiFi.h>
#include <WebServer.h>

WebServer server(80);

// Default Server IP: 192.168.4.1


void setup() {
    Serial.begin(115200);

    ttgo = TTGOClass::getWatch();
    ttgo->begin();
    ttgo->openBL();

    ttgo->tft->fillScreen(TFT_WHITE);
    ttgo->tft->setTextColor(TFT_BLACK, TFT_WHITE);
    ttgo->tft->setTextFont(4);
    ttgo->tft->drawString("Ready",  5, 10);
    
    // Start Wifi AP
    WiFi.mode(WIFI_AP_STA);
    WiFi.softAP(HOSTNAME, WifiPASS);
    // handle index -- HTTP Server
    
    server.on("/on", []() {
      Serial.println(1);
      ttgo->tft->fillScreen(TFT_WHITE);
       ttgo->tft->drawString("ON",  5, 10);  
       server.send(200, "");
    });

    server.on("/off", []() {
      Serial.println(0);
      ttgo->tft->fillScreen(TFT_WHITE);
       ttgo->tft->drawString("OFF",  5, 10);  
       server.send(200, "");
    });
 
    server.begin();
    
}

void loop() {
    server.handleClient();
}
