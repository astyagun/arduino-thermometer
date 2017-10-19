#include <Arduino.h>

// DS18B20+ sensor library: https://github.com/milesburton/Arduino-Temperature-Control-Library
#include <OneWire.h>
#include <DallasTemperature.h>

#define ONE_WIRE_PIN 2
#define TEMPERATURE_REFRESH_DELAY 5000

void setupTemperatureSensor();
float measureTemperature();
