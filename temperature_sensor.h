#include <Arduino.h>

/* #define DEBUG */

// DS18B20+ sensor library: https://github.com/milesburton/Arduino-Temperature-Control-Library
#include <OneWire.h>
#include <DallasTemperature.h>
#include "common.h"

void setupTemperatureSensor();
float measureTemperature();
