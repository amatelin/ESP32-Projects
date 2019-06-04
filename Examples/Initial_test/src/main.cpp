#include <Arduino.h>

#define LED 2

void setup() {
  pinMode(LED, OUTPUT);
}

void loop() {
delay(1000);
digitalWrite(LED, HIGH);
delay(500);
digitalWrite(LED, LOW);
delay(200);
digitalWrite(LED, HIGH);
delay(800);
digitalWrite(LED, LOW);
}
