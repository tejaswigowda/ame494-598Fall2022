/*********
  Rui Santos
  Complete project details at https://randomnerdtutorials.com  
*********/

// Import required libraries
#include "WiFi.h"
#include "ESPAsyncWebServer.h"
#include "SPIFFS.h"

char * HOSTNAME = "test12345";
char * WifiPASS = "";

// Set LED GPIO
const int ledPin = 21;
// Stores LED state
String ledState;


// setting PWM properties
const int freq = 5000;
const int ledChannel = 0;
const int resolution = 8;
 



// Create AsyncWebServer object on port 80
AsyncWebServer server(80);

// Replaces placeholder with LED state value
String processor(const String& var){
  Serial.println(var);
  if(var == "STATE"){
    if(digitalRead(ledPin)){
      ledState = "ON";
    }
    else{
      ledState = "OFF";
    }
    Serial.print(ledState);
    return ledState;
  }
  return String();
}
 
void setup(){
  // Serial port for debugging purposes
  Serial.begin(115200);

    ledcSetup(ledChannel, freq, resolution);
  
  // attach the channel to the GPIO to be controlled
  ledcAttachPin(ledPin, ledChannel);


  // Initialize SPIFFS
  if(!SPIFFS.begin(true)){
    Serial.println("An Error has occurred while mounting SPIFFS");
    return;
  }

     // Start Wifi AP
    WiFi.mode(WIFI_AP_STA);
    WiFi.softAP(HOSTNAME, WifiPASS);



  // Route for root / web page
  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(SPIFFS, "/index.html", String(), false, processor);
  });
  
  // Route to load style.css file
  server.on("/script.js", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(SPIFFS, "/script.js", "script/javascript");
  });

  // Route to set GPIO to HIGH
  server.on("/bright", HTTP_GET, [](AsyncWebServerRequest *request){
          int p = request->arg("v").toInt();
            Serial.println(p);
      ledcWrite(ledChannel, map(v, 0, 100, 0, 255));

      request->send(200);
      
  });
  

  // Start server
  server.begin();
}
 
void loop(){
  
}
