#include <Arduino.h>

/* #define DEBUG */
/* #define DEBUG_LOOP_LENGTH */

// DS18B20+ sensor library: https://github.com/milesburton/Arduino-Temperature-Control-Library
#include <OneWire.h>
#include <DallasTemperature.h>
#include "common.h"

#define ONE_WIRE_PIN 2

class TemperatureSensor {
  public:
    void setup();
    float measure();
  private:
    OneWire oneWire{ONE_WIRE_PIN};
    DallasTemperature sensors{&oneWire};
    DeviceAddress sensorAddress;
    unsigned long lastTemperatureRequestedAt;
    unsigned long lastTemperatureReadAt;
    float currentTemperature = TEMPERATURE_INVALID;
    #ifdef DEBUG
      #ifdef DEBUG_LOOP_LENGTH
        int lastLoopAt;
      #endif
    #endif

    bool request();
    float read();
};
