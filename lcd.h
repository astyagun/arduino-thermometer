#include <Arduino.h>
// http://files.amperka.ru/datasheets/MT-16S2H.pdf
#include <LiquidCrystal.h>
#include "common.h"

#define BUTTON_PIN A0
#define LCD_BACKLIGHT_PIN A2
#define LCD_BACKLIGHT_OFF_INTERVAL 1

void setupLcd();
void printToLcd(float);
void lcdBacklightUpdate();
