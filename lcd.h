#include <Arduino.h>
// http://files.amperka.ru/datasheets/MT-16S2H.pdf
#include <LiquidCrystal.h>
#include "lcd_backlight.h"
#include "common.h"

class Lcd {
  public:
    void setup();
    void update(float);
  private:
    LiquidCrystal lcd{9, 8, 7, 6, 5, 4};
    LcdBacklight  lcd_backlight;
    float         lastTemperature = TEMPERATURE_INVALID;

    bool shouldPrint(float);
    void print(float);
};
