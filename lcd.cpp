#include "lcd.h"

#define BUTTON_PIN 3
#define BUTTON_DEBOUNCE_INTERVAL 10
#define LCD_BACKLIGHT_PIN A2
#define LCD_BACKLIGHT_OFF_INTERVAL 10000

LiquidCrystal lcd(9, 8, 7, 6, 5, 4);
float lastTemperature = TEMPERATURE_INVALID;
Bounce debouncer = Bounce(); // Prevents triggering of LCD backlight by static electricity spikes
volatile unsigned int lastBacklightOnTime;

void printToLcd(float);
bool shouldPrintToLcd(float);
void lcdBacklightUpdate();
void lcdBacklightOn();
void lcdBacklightOff();

void setupLcd() {
  pinMode(BUTTON_PIN, INPUT_PULLUP);
  lcd.begin(16, 2);
  // Температура:
  lcd.print("Te\xBC\xBE\x65pa\xBFypa:");

  debouncer.attach(BUTTON_PIN);
  debouncer.interval(BUTTON_DEBOUNCE_INTERVAL);

  pinMode(LCD_BACKLIGHT_PIN, OUTPUT);
  lcdBacklightOn();

  printToLcd(lastTemperature);
}

void updateLcd(float temperature) {
  if(shouldPrintToLcd(temperature)) printToLcd(temperature);
  lcdBacklightUpdate();
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

void lcdBacklightUpdate() {
  debouncer.update();
  if(debouncer.fell()) lcdBacklightOn();
  lcdBacklightOff();
}

void lcdBacklightOn() {
  lastBacklightOnTime = millis();
  digitalWrite(LCD_BACKLIGHT_PIN, HIGH);
}

void lcdBacklightOff() {
  unsigned int now     = millis();
  unsigned int elapsed = now - lastBacklightOnTime;

  if(elapsed >= LCD_BACKLIGHT_OFF_INTERVAL) digitalWrite(LCD_BACKLIGHT_PIN, LOW);
}
