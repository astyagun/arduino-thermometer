#include <OneWire.h>
#include <DallasTemperature.h>
// DS18B20+ sensor library: https://github.com/milesburton/Arduino-Temperature-Control-Library
#include <LiquidCrystal.h>
#include <Neotimer.h>

/* #define DEBUG */

// Data wire is plugged into port 2 on the Arduino
#define ONE_WIRE_BUS 2
#define BUTTON_PIN A0
#define LCD_BACKLIGHT_PIN A2
#define REFRESH_DELAY 5000
#define LCD_BACKLIGHT_OFF_INTERVAL 1

OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);
// http://files.amperka.ru/datasheets/MT-16S2H.pdf
LiquidCrystal lcd(13, 12, 11, 10, 9, 8);
Neotimer lcdBacklightOffTimer = Neotimer(LCD_BACKLIGHT_OFF_INTERVAL);

void setupTemperatureSensor();
void setupLcd(LiquidCrystal&, Neotimer&);
float measureTemperature(DallasTemperature&);
void printToLcd(LiquidCrystal&, float);
void lcdBacklightOn(LiquidCrystal&, Neotimer&);
void lcdBacklightOff(LiquidCrystal&, Neotimer&);

void setup()
{
  #ifdef DEBUG
    Serial.begin(9600);
  #endif
  pinMode(BUTTON_PIN, INPUT_PULLUP);
  setupTemperatureSensor();
  setupLcd(lcd, lcdBacklightOffTimer);
}

void loop()
{
  float temperature = measureTemperature(sensors);
  printToLcd(lcd, temperature);
  if(digitalRead(BUTTON_PIN) == LOW) {
    lcdBacklightOn(lcd, lcdBacklightOffTimer);
  }
  lcdBacklightOff(lcd, lcdBacklightOffTimer);
}

// Setup

void setupTemperatureSensor() {
  #ifdef DEBUG
    Serial.println("Dallas Temperature IC Control Library Demo");
  #endif

  sensors.begin();
}

void setupLcd(LiquidCrystal &lcd, Neotimer &timer) {
  lcd.begin(16, 2);
  lcd.print("Temperature:");
  pinMode(LCD_BACKLIGHT_PIN, OUTPUT);
  lcdBacklightOn(lcd, timer);
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

void printToLcd(LiquidCrystal &lcd, float temperature) {
  lcd.setCursor(0, 1);
  lcd.print(temperature, 2);
  lcd.print(" ");
  lcd.print((char)0x99);
  lcd.print("C");
}

void lcdBacklightOn(LiquidCrystal &lcd, Neotimer &timer) {
  digitalWrite(LCD_BACKLIGHT_PIN, HIGH);
  timer.start();
}

void lcdBacklightOff(LiquidCrystal &lcd, Neotimer &timer) {
  if(timer.done()) digitalWrite(LCD_BACKLIGHT_PIN, LOW);
}
