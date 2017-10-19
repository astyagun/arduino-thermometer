#include "lcd.h"

LiquidCrystal lcd(13, 12, 11, 10, 9, 8);

void setupLcd() {
  lcd.begin(16, 2);
  lcd.print("Temperature:");
  pinMode(LCD_BACKLIGHT_PIN, OUTPUT);
  lcdBacklightOn();
}

void printToLcd(float temperature) {
  lcd.setCursor(0, 1);
  lcd.print(temperature, 2);
  lcd.print(" ");
  lcd.print((char)0x99);
  lcd.print("C");
}

void lcdBacklightOn() {
  digitalWrite(LCD_BACKLIGHT_PIN, HIGH);
}

void lcdBacklightOff() {
  digitalWrite(LCD_BACKLIGHT_PIN, LOW);
}
