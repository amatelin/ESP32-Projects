#include <Ticker.h>
#include <WiFiWrapper.hpp>
#include <OTAUpdate.hpp>

void blink();

const char* ssid = "AndroidAP_8730";
const char* password = "tatatitatata";

#define LED_BUILTIN 2

bool ledState;

Ticker timer1(blink, 1000);

void setup() {
  // Start serial, will be used by WiFi and OTA Update routines
  Serial.begin(115200);
  Serial.println("Booting");

  // Start wiFi in STA mode
  WiFiWrapper.setup(ssid, password);

  // Prepare device for OTA Update protocol
  OTAUpdate.setup();


  timer1.start();
  pinMode(LED_BUILTIN, OUTPUT);
}

void loop() {
  // Start OTA loop to handle possible firmware OTA updates
  OTAUpdate.handle();

  timer1.update();
}

void blink() {
  digitalWrite(LED_BUILTIN, ledState);
  ledState = !ledState;
  }
