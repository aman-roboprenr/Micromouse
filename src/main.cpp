#include <Arduino.h>
#include <sensors.h>
#include <motors.h>

void setup() {
  
}

void loop() {
  // put your main code here, to run repeatedly:
  while(true){
    if(not wall_in_left()){
      take_left();
    }
    else if(not wall_in_front()){
      move_forward();
    }
    else if(not wall_in_right()){
      take_right();
    }
    else{
      turn_around();
    }
  }
}

