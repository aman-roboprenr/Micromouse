#include <Arduino.h>
#include <sensors.h>
#include <motors.h>

void setup() {
  Serial.begin(115200);
  Serial.println(F("Hello\n"));
  sensor_setup();
  // stop_moving();
  delay(3000);
}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.println(F("Hello\n"));
  while(true){
    if(not wall_in_left()){
      Serial.println(F("should take a left\n"));
      take_left();
    }
    else if(not wall_in_front()){
      Serial.println(F("should move forward\n"));
      move(true, 1200);
    }
    else if(not wall_in_right()){
      Serial.println(F("should take a right\n"));
      take_right();
    }
    else{
      turn_around();
    }
    // else if(wall_in_left() and wall_in_right() and wall_in_front()){
    //   Serial.println(F("should turn around\n"));

    //   turn_around();
    // }
    stop_moving();

    delay(2000);
  }
}

