#include "temperature_sensor.h"
#include "lcd.h"

TemperatureSensor temperature_sensor;
Lcd lcd;

void setup() {
  // Turn off Arduino UNO builtin LED
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, LOW);

  temperature_sensor.setup();
  lcd.setup();
}

void loop() {
  lcd.update(
    temperature_sensor.measure()
  );
}
