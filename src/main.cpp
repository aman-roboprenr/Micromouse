#include <Arduino.h>
#include <sensors.h>
#include <encoders.h>
#include <motors.h>

void setup() {
  Serial.begin(115200);
  sensorSetup();
  delay(1000);
  encoderSetup();
  delay(1000);
}

void loop() {
  while(true){
    if(not wallInLeft()){
      Serial.println(F("should take a left\n"));
      takeLeft();
      moveOneCell();
    }
    else if(not wallInFront()){
      Serial.println(F("should move forward\n"));
      moveOneCell();
    }
    else if(not wallInRight()){
      Serial.println(F("should take a right\n"));
      takeRight();
      moveOneCell();
    }
    else{
      turnAround();
      moveOneCell();
    }
    stopMoving();
    delay(1000);
  }
}

