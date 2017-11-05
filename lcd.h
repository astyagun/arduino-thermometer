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
    LiquidCrystal lcd{LCD_PINS};
    LcdBacklight  lcd_backlight;
    float         lastTemperature = TEMPERATURE_INVALID;

    bool allowsPrint(float);
    void print(float);
};
