#include "temperature_sensor.h"
#include "lcd.h"

TemperatureSensor temperature_sensor;
Lcd lcd;
#ifdef DEBUG_LOOP_LENGTH
  #define MAX_LOOPS_TO_MEASURE 1500
  unsigned long lastLoopEndedAt = 0;
  byte loopLengths[MAX_LOOPS_TO_MEASURE];
  int loopNumber = 0;
#endif

void setup() {
  #if defined(DEBUG) || defined(DEBUG_LOOP_LENGTH)
    Serial.begin(9600);
  #endif

  // Turn off Arduino UNO builtin LED
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, LOW);

  temperature_sensor.setup();
  lcd.setup();
}

void loop() {
  lcd.update(
    temperature_sensor.measure()
  );

  #ifdef DEBUG_LOOP_LENGTH
    if(loopNumber <= MAX_LOOPS_TO_MEASURE) {
      unsigned long now = millis();
      if(now - lastLoopEndedAt > 1) {
        loopLengths[loopNumber] = now - lastLoopEndedAt;
        loopNumber++;
      }
      lastLoopEndedAt = now;
    }
    if(loopNumber == MAX_LOOPS_TO_MEASURE + 1) {
      Serial.print("Loop lengths:\r\n{");
      for(int i = 0; i < MAX_LOOPS_TO_MEASURE; i++) {
        Serial.print(loopLengths[i], DEC);
        Serial.print(", ");
      }
      Serial.println("}");
      loopNumber++;
    }
  #endif
}
