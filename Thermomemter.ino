// TODO: Cache thermometer value to read it less often
// TODO: Read in background to prevent blocking reaction to button press
// TODO: Turn fisplay on by button and turn it off after delay

/* #define DEBUG */

#define REFRESH_DELAY 5000

#include "temperature_sensor.h"
#include "lcd.h"

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
  float temperature = measureTemperature();
  printToLcd(temperature);
  if(digitalRead(BUTTON_PIN) == LOW) {
    lcdBacklightOn();
  }
  /* lcdBacklightOff(); */
}
