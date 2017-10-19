#include "lcd.h"

#define BUTTON_PIN 3
#define LCD_BACKLIGHT_PIN A2
#define LCD_BACKLIGHT_OFF_INTERVAL 10000

LiquidCrystal lcd(13, 12, 11, 10, 9, 8);
volatile unsigned int lastBacklightOnTime;

void lcdBacklightOn();
void lcdBacklightOff();

void setupLcd() {
  pinMode(BUTTON_PIN, INPUT_PULLUP);
  lcd.begin(16, 2);
  // Температура:
  lcd.print("Te\xBC\xBE\x65pa\xBFypa:");

  pinMode(LCD_BACKLIGHT_PIN, OUTPUT);
  lcdBacklightOn();
  attachInterrupt(digitalPinToInterrupt(BUTTON_PIN), lcdBacklightOn, FALLING);
}

void printToLcd(float temperature) {
  lcd.setCursor(0, 1);
  if(temperature == FLOAT_SMALLEST_NUMBER) {
    lcd.print("...");
  } else {
    lcd.print(temperature, 2);
    lcd.print(" ");
    lcd.print((char)0x99);
    lcd.print("C");
  }
  lcd.print("               ");
}

void lcdBacklightUpdate() {
  lcdBacklightOff();
}

void lcdBacklightOn() {
  lastBacklightOnTime = millis();
  digitalWrite(LCD_BACKLIGHT_PIN, HIGH);
}

void lcdBacklightOff() {
  unsigned int now = millis();
  unsigned int elapsed = now - lastBacklightOnTime;

  if(elapsed >= LCD_BACKLIGHT_OFF_INTERVAL) digitalWrite(LCD_BACKLIGHT_PIN, LOW);
}
