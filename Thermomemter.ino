// TODO: Read in background to prevent blocking reaction to button press
// TODO: Cache thermometer value to read it less often
// TODO: Turn display on by button and turn it off after delay

/* #define DEBUG */

#define REFRESH_DELAY 5000

#include "temperature_sensor.h"
#include "lcd.h"

void setup()
{
  #ifdef DEBUG
    Serial.begin(9600);
  #endif
  setupTemperatureSensor();
  setupLcd();
}

void loop()
{
  printToLcd(measureTemperature());
  lcdBacklightUpdate();
}
