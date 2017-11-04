#include <Arduino.h>
#include <Bounce2.h>

class LcdBacklight {
  public:
    unsigned int last_on_at;
    void setup();
    void update();
    void on();
    void off();
};
