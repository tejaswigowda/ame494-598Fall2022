#include <Arduino.h>
#define LILYGO_WATCH_2019_WITH_TOUCH
#include <LilyGoWatch.h>

TTGOClass *ttgo;


char * HOSTNAME = "test-ame520";
char * WifiPASS = "12345678";

#include <WiFi.h>
#include <WebServer.h>



WebServer server(80);


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
      ttgo->tft->fillScreen(TFT_WHITE);
       ttgo->tft->drawString("ON",  5, 10);  
       server.send(200, "text/html", "<html><head></head><body><a href=\"./on\">on</a><br><a href=\"./off\">off</a></body><html>");
    });

    server.on("/off", []() {
      ttgo->tft->fillScreen(TFT_WHITE);
       ttgo->tft->drawString("OFF",  5, 10);  
       server.send(200, "text/html", "<html><head></head><body><a href=\"./on\">on</a><br><a href=\"./off\">off</a></body><html>");
     });

 
    server.on("/", []() {
      server.send(200, "text/html", "<html><head></head><body><a href=\"./on\">on</a><br><a href=\"./off\">off</a></body><html>");
    });

    
    server.begin();
    
}

void loop() {
    server.handleClient();
}
