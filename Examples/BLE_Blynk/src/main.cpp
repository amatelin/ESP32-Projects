#include <BlynkSimpleEsp32_BLE.h>
#include <BLEDevice.h>
#include <BLEServer.h>
#include <config.h>

#define BLYNK_PRINT Serial
#define BLYNK_USE_DIRECT_CONNECT

char blynkAuthToken[] = BLYNK_AUTH_TOKEN;

void setup() {
  // Start serial, will be used by WiFi and OTA Update routines
  Serial.begin(9600);
  Serial.println("Booting!");

  // Blynk setup
  Blynk.setDeviceName("Blynk");
  Blynk.begin(blynkAuthToken);

}

void loop() {
  // Blynk loop
  Blynk.run();
}
