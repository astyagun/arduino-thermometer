#include "lcd.h"

void Lcd::setup() {
  lcd.begin(16, 2);
  // Температура:
  lcd.print("Te\xBC\xBE\x65pa\xBFypa:");

  lcd_backlight.setup();

  print(lastTemperature);
}

void Lcd::update(float temperature) {
  if(shouldPrint(temperature)) print(temperature);
  lcd_backlight.update();
}

bool Lcd::shouldPrint(float temperature) {
  if(lastTemperature != temperature) {
    lastTemperature = temperature;
    return true;
  }
  return false;
}

void Lcd::print(float temperature) {
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
