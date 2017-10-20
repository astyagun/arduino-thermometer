#define REFRESH_DELAY 5000

#include "temperature_sensor.h"
#include "lcd.h"

void setup() {
  // Turn off Arduino Uno builtin LED
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, LOW);
  setupTemperatureSensor();
  setupLcd();
}

void loop() {
  printToLcd(measureTemperature());
  lcdBacklightUpdate();
}
