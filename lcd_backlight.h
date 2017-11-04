#include <Arduino.h>
#include <Bounce2.h>

class LcdBacklight {
  public:
    unsigned int last_on_at;
    void setup();
    void update();
  private:
    void on();
    void off();
};
