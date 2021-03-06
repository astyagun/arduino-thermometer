#include "lcd_backlight.h"

#define BUTTON_DEBOUNCE_INTERVAL 10
#define OFF_INTERVAL 10000

Bounce debouncer = Bounce(); // Prevents triggering of LCD backlight by static electricity spikes

void LcdBacklight::setup() {
  pinMode(LCD_BACKLIGHT_BUTTON_PIN, INPUT_PULLUP);

  debouncer.attach(LCD_BACKLIGHT_BUTTON_PIN);
  debouncer.interval(BUTTON_DEBOUNCE_INTERVAL);

  pinMode(LCD_BACKLIGHT_PIN, OUTPUT);
  on();
}

void LcdBacklight::update() {
  debouncer.update();
  if(debouncer.fell()) on();
  off();
}

void LcdBacklight::on() {
  last_on_at = millis();
  digitalWrite(LCD_BACKLIGHT_PIN, HIGH);
}

void LcdBacklight::off() {
  unsigned int now     = millis();
  unsigned int elapsed = now - last_on_at;

  if(elapsed >= OFF_INTERVAL) digitalWrite(LCD_BACKLIGHT_PIN, LOW);
}
