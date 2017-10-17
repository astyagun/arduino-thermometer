// DS18B20+ sensor library: https://github.com/milesburton/Arduino-Temperature-Control-Library
#include <OneWire.h>
#include <DallasTemperature.h>

#define DEBUG

// Data wire is plugged into port 2 on the Arduino
#define ONE_WIRE_BUS 2

OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);

void setup(void)
{
  #ifdef DEBUG
    Serial.begin(9600);
    Serial.println("Dallas Temperature IC Control Library Demo");
  #endif

  sensors.begin();
}

void loop(void)
{
  #ifdef DEBUG
    Serial.print("Requesting temperatures...");
  #endif

  sensors.requestTemperatures();
  float temperature = sensors.getTempCByIndex(0);

  #ifdef DEBUG
    Serial.println("DONE");
    Serial.print("Temperature for the device 1 (index 0) is: ");
    Serial.println(temperature);
  #endif
}
