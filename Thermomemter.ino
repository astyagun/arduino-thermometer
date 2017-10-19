#define REFRESH_DELAY 5000

#include "temperature_sensor.h"
#include "lcd.h"

void setup() {
  setupTemperatureSensor();
  setupLcd();
}

void loop() {
  printToLcd(measureTemperature());
  lcdBacklightUpdate();
}
