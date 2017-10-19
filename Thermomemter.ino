// DS18B20+ sensor library: https://github.com/milesburton/Arduino-Temperature-Control-Library
#include <OneWire.h>
#include <DallasTemperature.h>

/* #define DEBUG */

// Data wire is plugged into port 2 on the Arduino
#define ONE_WIRE_BUS 2
#define REFRESH_DELAY 5000

/* #include <temperature_sensor.h> */
#include "lcd.h"

OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);

void setupTemperatureSensor();
float measureTemperature(DallasTemperature&);

void setup()
{
  #ifdef DEBUG
    Serial.begin(9600);
  #endif
  pinMode(BUTTON_PIN, INPUT_PULLUP);
  setupTemperatureSensor();
  setupLcd();
}

void loop()
{
  float temperature = measureTemperature(sensors);
  printToLcd(temperature);
  if(digitalRead(BUTTON_PIN) == LOW) {
    lcdBacklightOn();
  }
  /* lcdBacklightOff(); */
}

// Setup

void setupTemperatureSensor() {
  #ifdef DEBUG
    Serial.println("Dallas Temperature IC Control Library Demo");
  #endif

  sensors.begin();
}

// Loop

float measureTemperature(DallasTemperature &sensors) {
  #ifdef DEBUG
    Serial.print("Requesting temperatures...");
  #endif

  // TODO: Cache value to read it less often
  // TODO: Read in background to prevent blocking reaction to button press
  sensors.requestTemperatures();
  float temperature = sensors.getTempCByIndex(0);

  #ifdef DEBUG
    Serial.println("DONE");
    Serial.print("Temperature is: ");
    Serial.println(temperature);
  #endif

  return temperature;
}
