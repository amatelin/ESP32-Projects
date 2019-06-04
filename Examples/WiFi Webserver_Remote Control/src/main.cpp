#include <WiFiWrapper.hpp>
#include <OTAUpdate.hpp>
#include <ESPAsyncWebServer.h>


const char* ssid = "AndroidAP_8730";
const char* password = "tatatitatata";


#define LED_BUILTIN 2

bool LEDState = LOW;

AsyncWebServer server(80);

void blinkLED();
void turnOnLED();
void turnOffLED();
String sendHTML(uint8_t LEDState);

void setup() {
  // Start serial, will be used by WiFi and OTA Update routines
  Serial.begin(115200);
  Serial.println("Booting");

  // Start wiFi in STA mode
  WiFiWrapper.setup(ssid, password);

  // Prepare device for OTA Update protocol
  OTAUpdate.setup();

  // Setup server routes
  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request) {
    turnOffLED();
    request->send(200, "text/html", sendHTML(LEDState));
  });

  server.on("/led/toggle", HTTP_GET, [](AsyncWebServerRequest *request) {
    blinkLED();
    request->send(200, "text/html", sendHTML(LEDState));
  });

  server.on("/led/on", HTTP_GET, [](AsyncWebServerRequest *request) {
    turnOnLED();
    request->send(200, "text/html", sendHTML(LEDState));
  });

  server.on("/led/off", HTTP_GET, [](AsyncWebServerRequest *request) {
    turnOffLED();
    request->send(200, "text/html", sendHTML(LEDState));
  });

  // Allow CORS requests
  DefaultHeaders::Instance().addHeader("Access-Control-Allow-Origin", "*");

  // Start server
  server.begin();

  pinMode(LED_BUILTIN, OUTPUT);
}

void loop() {
  // Start OTA loop to handle possible firmware OTA updates
  OTAUpdate.handle();

}

void blinkLED() {
  digitalWrite(LED_BUILTIN, LEDState);
  LEDState = !LEDState;
};

void turnOffLED() {
  LEDState = LOW;
  digitalWrite(LED_BUILTIN, LEDState);
};

void turnOnLED() {
  LEDState = HIGH;
  digitalWrite(LED_BUILTIN, LEDState);
};


String sendHTML(uint8_t LEDState){
  String ptr = "<!DOCTYPE html> <html>\n";
  ptr +="<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0, user-scalable=no\">\n";
  ptr +="<title>LED Control</title>\n";
  ptr +="<style>html { font-family: Helvetica; display: inline-block; margin: 0px auto; text-align: center;}\n";
  ptr +="body{margin-top: 50px;} h1 {color: #444444;margin: 50px auto 30px;} h3 {color: #444444;margin-bottom: 50px;}\n";
  ptr +=".button {display: block;width: 80px;background-color: #3498db;border: none;color: white;padding: 13px 30px;text-decoration: none;font-size: 25px;margin: 0px auto 35px;cursor: pointer;border-radius: 4px;}\n";
  ptr +=".button-on {background-color: #3498db;}\n";
  ptr +=".button-on:active {background-color: #2980b9;}\n";
  ptr +=".button-off {background-color: #34495e;}\n";
  ptr +=".button-off:active {background-color: #2c3e50;}\n";
  ptr +="p {font-size: 14px;color: #888;margin-bottom: 10px;}\n";
  ptr +="</style>\n";
  ptr +="</head>\n";
  ptr +="<body>\n";
  ptr +="<h1>ESP32 Web Server</h1>\n";
    ptr +="<h3>Using Station(STA) Mode</h3>\n";

   if(LEDState)
  {ptr +="<p>LED Status: ON</p><a class=\"button button-off\" href=\"/led/off\">OFF</a>\n";}
  else
  {ptr +="<p>LED Status: OFF</p><a class=\"button button-on\" href=\"/led/on\">ON</a>\n";}


  ptr +="</body>\n";
  ptr +="</html>\n";
  return ptr;
}
