#include <Arduino.h>
#include <OTAUpdate.hpp>
#include <WiFiWrapper.hpp>
#include <config.h>

const char* ssid = WIFI_SSID;
const char* password = WIFI_PASSWORD;

#define LED_BUILTIN 2

bool ledState;

void blink();

void setup() {
  // Start serial, will be used by WiFi and OTA Update routines
  Serial.begin(115200);
  Serial.println("Booting");

  // Start wiFi in STA mode
  WiFiWrapper.setup(ssid, password);

  // Prepare device for OTA Update protocol
  OTAUpdate.setup();

  pinMode(LED_BUILTIN, OUTPUT);
}

void loop() {
  // Start OTA loop to handle possible firmware OTA updates
  OTAUpdate.handle();
}

void blink() {
  digitalWrite(LED_BUILTIN, ledState);
  ledState = !ledState;
  }
