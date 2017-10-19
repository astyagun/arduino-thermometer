#include "temperature_sensor.h"

#define ONE_WIRE_PIN 2
#define TEMPERATURE_REFRESH_DELAY 10000

OneWire oneWire(ONE_WIRE_PIN);
DallasTemperature sensors(&oneWire);
unsigned long lastTemperatureRequestedAt;
float currentTemperature = FLOAT_SMALLEST_NUMBER;

void requestTemperature();
float getTemperature();

void setupTemperatureSensor() {
  #ifdef DEBUG
    Serial.begin(9600);
    Serial.println("Dallas Temperature IC Control Library Demo");
  #endif

  sensors.begin();
  lastTemperatureRequestedAt = millis() - TEMPERATURE_REFRESH_DELAY;
}

float measureTemperature() {
  unsigned long now     = millis();
  unsigned long elapsed = now - lastTemperatureRequestedAt;

  if (elapsed >= TEMPERATURE_REFRESH_DELAY) {
    requestTemperature();
    currentTemperature = getTemperature();
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
