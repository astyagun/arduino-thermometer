#include "temperature_sensor.h"

OneWire oneWire(ONE_WIRE_PIN);
DallasTemperature sensors(&oneWire);
unsigned long lastTemperatureRequestedAt;
float currentTemperature = 0;

void requestTemperature();
float getTemperature();

void setupTemperatureSensor() {
  #ifdef DEBUG
    Serial.println("Dallas Temperature IC Control Library Demo");
  #endif

  sensors.begin();
  requestTemperature();
}

float measureTemperature() {
  unsigned long now     = millis();
  unsigned long elapsed = now - lastTemperatureRequestedAt;

  if (elapsed >= TEMPERATURE_REFRESH_DELAY) {
    currentTemperature = getTemperature();
    requestTemperature();
  }

  return currentTemperature;
}

void requestTemperature() {
  #ifdef DEBUG
    Serial.print("Requesting temperatures...");
  #endif

  sensors.requestTemperatures();
  lastTemperatureRequestedAt = millis();
}

float getTemperature() {
  float temperature = sensors.getTempCByIndex(0);

  #ifdef DEBUG
    Serial.println("DONE");
    Serial.print("Temperature is: ");
    Serial.println(temperature);
  #endif

  return temperature;
}
