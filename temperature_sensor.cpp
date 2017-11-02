#include "temperature_sensor.h"

#define ONE_WIRE_PIN 2
#define TEMPERATURE_REQUEST_DELAY 10000
#define TEMPERATURE_READ_DELAY 750

OneWire oneWire(ONE_WIRE_PIN);
DallasTemperature sensors(&oneWire);
DeviceAddress sensorAddress;
unsigned long lastTemperatureRequestedAt;
unsigned long lastTemperatureReadAt;
float currentTemperature = TEMPERATURE_INVALID;

bool requestTemperature();
float getTemperature();

void setupTemperatureSensor() {
  #ifdef DEBUG
    Serial.begin(9600);
    Serial.println("Dallas Temperature IC Control Library Demo");
  #endif

  sensors.begin();
  sensors.setWaitForConversion(false);
  sensors.getAddress(sensorAddress, 0);

  #ifdef DEBUG
    // Parasite power must be off to request temperature without blocking
    Serial.print("Parasite power is: ");
    if(sensors.isParasitePowerMode()) Serial.println("ON");
    else Serial.println("OFF");
    Serial.print("Sensor resolution: ");
    Serial.println(sensors.getResolution(sensorAddress), DEC);
  #endif

  lastTemperatureReadAt = millis() - 1;
  requestTemperature();
}

float measureTemperature() {
  unsigned long now                 = millis();
  unsigned long elapsedSinceRequest = now - lastTemperatureRequestedAt;

  if(elapsedSinceRequest >= TEMPERATURE_REQUEST_DELAY) {
    if(!requestTemperature()) currentTemperature = TEMPERATURE_INVALID;
  }

  if(lastTemperatureReadAt < lastTemperatureRequestedAt) {
    now                 = millis();
    elapsedSinceRequest = now - lastTemperatureRequestedAt;
    if(elapsedSinceRequest > TEMPERATURE_READ_DELAY && sensors.isConversionAvailable(sensorAddress))
      currentTemperature = getTemperature();
  }

  return currentTemperature;
}

bool requestTemperature() {
  #ifdef DEBUG
    Serial.print("Requesting temperatures at ");
    Serial.print(millis(), DEC);
    Serial.println("...");
  #endif

  if(sensors.requestTemperaturesByAddress(sensorAddress)) {
    lastTemperatureRequestedAt = millis();

    #ifdef DEBUG
      Serial.print("Requested temperatures at ");
      Serial.print(lastTemperatureRequestedAt, DEC);
      Serial.println();
    #endif

    return true;
  } else {
    #ifdef DEBUG
      Serial.println("Failed requesting temperature by address! Is the sensor disconnected?");
    #endif

    return false;
  }
}

float getTemperature() {
  #ifdef DEBUG
    Serial.print("Reading temperature at ");
    Serial.print(millis(), DEC);
    Serial.println("...");
  #endif

  float temperature = sensors.getTempC(sensorAddress);

  if(temperature != DEVICE_DISCONNECTED_C) {
    lastTemperatureReadAt = millis();

    #ifdef DEBUG
      Serial.print("Done reading at ");
      Serial.print(lastTemperatureReadAt, DEC);
      Serial.println();
      Serial.print("Temperature is: ");
      Serial.println(temperature);
    #endif
  } else {
    temperature = TEMPERATURE_INVALID;

    #ifdef DEBUG
      Serial.println("Error reading temperature by address! Is the sensor disconnected?");
    #endif
  }

  return temperature;
}
