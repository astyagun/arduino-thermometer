#include <Arduino.h>

// DS18B20+ sensor library: https://github.com/milesburton/Arduino-Temperature-Control-Library
#include <OneWire.h>
#include <DallasTemperature.h>
#include "common.h"

class TemperatureSensor {
  public:
    void  setup();
    float measure();
  private:
    OneWire           oneWire{TEMPERATURE_SENSOR_PIN};
    DallasTemperature sensors{&oneWire};
    DeviceAddress     sensorAddress;
    unsigned long     lastTemperatureRequestedAt;
    bool              allowsRead         = false;
    float             currentTemperature = TEMPERATURE_INVALID;

    #ifdef DEBUG
      unsigned long lastTemperatureReadAt;
    #endif

    bool  request();
    float read();
};
