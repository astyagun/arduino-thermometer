#include "temperature_sensor.h"
#include "lcd.h"

Lcd lcd;

void setup() {
  // Turn off Arduino UNO builtin LED
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, LOW);

  setupTemperatureSensor();
  lcd.setup();
}

void loop() {
  lcd.update(
    measureTemperature()
  );
}
