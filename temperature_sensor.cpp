#include "temperature_sensor.h"

OneWire oneWire(ONE_WIRE_PIN);
DallasTemperature sensors(&oneWire);

void requestTemperature();
float getTemperature();

void setupTemperatureSensor() {
  #ifdef DEBUG
    Serial.begin(9600);
    Serial.println("Dallas Temperature IC Control Library Demo");
  #endif

  sensors.begin();
}

float measureTemperature() {
  requestTemperature();
  return getTemperature();
}

void requestTemperature() {
  #ifdef DEBUG
    Serial.print("Requesting temperatures...");
  #endif

  sensors.requestTemperatures();
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
