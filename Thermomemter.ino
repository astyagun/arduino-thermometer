#include "temperature_sensor.h"
#include "lcd.h"

void setup() {
  // Turn off Arduino UNO builtin LED
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, LOW);

  setupTemperatureSensor();
  setupLcd();
}

void loop() {
  updateLcd(
    measureTemperature()
  );
}
