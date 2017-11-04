#include "lcd.h"

LiquidCrystal lcd(9, 8, 7, 6, 5, 4);
float lastTemperature = TEMPERATURE_INVALID;
LcdBacklight lcd_backlight;

void printToLcd(float);
bool shouldPrintToLcd(float);

void setupLcd() {
  lcd.begin(16, 2);
  // Температура:
  lcd.print("Te\xBC\xBE\x65pa\xBFypa:");

  lcd_backlight.setup();

  printToLcd(lastTemperature);
}

void updateLcd(float temperature) {
  if(shouldPrintToLcd(temperature)) printToLcd(temperature);
  lcd_backlight.update();
}

bool shouldPrintToLcd(float temperature) {
  if(lastTemperature != temperature) {
    lastTemperature = temperature;
    return true;
  }
  return false;
}

void printToLcd(float temperature) {
  lcd.setCursor(0, 1);
  if(temperature == TEMPERATURE_INVALID) {
    lcd.print("...");
  } else {
    lcd.print(temperature, 2);
    lcd.print(" ");
    lcd.print((char)0x99);
    lcd.print("C");
  }
  lcd.print("               ");
}
