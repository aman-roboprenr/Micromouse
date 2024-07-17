#include <Arduino.h>
#include "sensors.h"
#include "encoders.h"
#include "speed_controller.h"
#include "motion_controller.h"

void setup() {
  Serial.begin(115200);
  sensorSetup();
  delay(SAFETY_DELAY);
  encoderSetup();
  delay(SAFETY_DELAY);
  // takeLeft();
  // delay(500);
  // takeRight();
  // delay(500);
  // turnAround();
  // return;
  // search run
  // going to center
  run(true, SEARCH_SPEED);
// coming back
  run(false, SEARCH_SPEED);

  delay(5000);
  Serial.println("fast run");
  // fast run 1 : assumes robot is places in the starting position
  run(true, RUN_1);
  delay(5000);

  // fast run 2 assumes robot is places in the starting position
  run(true, RUN_2);
  delay(5000);

}

void loop() {
  // moveOneCell();
  delay(1000);
}

