#include <Arduino.h>
#include <sensors.h>
#include <encoders.h>
#include <motors.h>

void setup() {
  Serial.begin(115200);
  Serial.println(F("Hello\n"));
  sensorSetup();
  encoderSetup();
  // moveOneCell();
  // takeLeft();
  // stopMoving();
}

void loop() {
  // Serial.print(currentPositionLeft());
  // Serial.print(" ");
  // Serial.print(currentPositionRight());
  // Serial.println();
  // delay(2000);
  // put your main code here, to run repeatedly:
  // Serial.println(F("Hello\n"));
  // while(true){
  //   if(not wallInLeft()){
  //     Serial.println(F("should take a left\n"));
  //     takeLeft();
  //   }
  //   else if(not wallInFront()){
  //     Serial.println(F("should move forward\n"));
  //     moveOneCell();
  //   }
  //   else if(not wallInRight()){
  //     Serial.println(F("should take a right\n"));
  //     takeRight();
  //   }
  //   else{
  //     turnAround();
  //   }
  //   // else if(wall_in_left() and wall_in_right() and wall_in_front()){
  //   //   Serial.println(F("should turn around\n"));

  //   //   turn_around();
  //   // }
  //   stopMoving();
  // }
}

