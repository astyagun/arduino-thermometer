#include <OneWire.h>
#include <DallasTemperature.h>
// DS18B20+ sensor library: https://github.com/milesburton/Arduino-Temperature-Control-Library
#include <LiquidCrystal.h>

/* #define DEBUG */

// Data wire is plugged into port 2 on the Arduino
#define ONE_WIRE_BUS 2
#define REFRESH_DELAY 5000

OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);
// http://files.amperka.ru/datasheets/MT-16S2H.pdf
LiquidCrystal lcd(13, 12, 11, 10, 9, 8);

void setup()
{
  #ifdef DEBUG
    Serial.begin(9600);
    Serial.println("Dallas Temperature IC Control Library Demo");
  #endif

  sensors.begin();

  lcd.begin(16, 2);
  lcd.print("Temperature:");
}

void loop()
{
  #ifdef DEBUG
    Serial.print("Requesting temperatures...");
  #endif

  sensors.requestTemperatures();
  float temperature = sensors.getTempCByIndex(0);

  lcd.setCursor(0, 1);
  lcd.print(temperature, 2);
  lcd.print(" ");
  lcd.print((char)0x99);
  lcd.print("C");

  #ifdef DEBUG
    Serial.println("DONE");
    Serial.print("Temperature is: ");
    Serial.println(temperature);
  #endif

  delay(REFRESH_DELAY);
}
