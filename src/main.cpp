#include <Arduino.h>
#include <sensors.h>
#include <encoders.h>
#include <motors.h>
#include "maze.h"



void setup() {
  Serial.begin(115200);
  sensorSetup();
  delay(1000);
  encoderSetup();
  delay(1000);

  flood();
  Serial.println("flooded");
  printCost();
}

void loop() {
  Serial.println("observing walls");
  rememberWalls(0,0,0);
  printWallStates();
  delay(3000);
}

