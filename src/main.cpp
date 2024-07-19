#include <Arduino.h>
#include "sensors.h"
#include "encoders.h"
#include "speed_controller.h"
#include "motion_controller.h"

#define PUSH_BUTTON 10

int attempt = 0;



void buttonSetup(){
    pinMode(PUSH_BUTTON, INPUT_PULLUP);
    Serial.println("Buttons setted");

}

bool checkButton(){
    int a = digitalRead(PUSH_BUTTON);
    // Serial.println(a);
    return a==0;
}


void setup() {
  Serial.begin(115200);
  sensorSetup();
  delay(SAFETY_DELAY);
  encoderSetup();
  delay(SAFETY_DELAY);
  buttonSetup();
  delay(SAFETY_DELAY);

  // moveOneCell();
  // delay(500);
  // takeLeft();
  // delay(500);
  // takeRight();
  // delay(500);
  // turnAround();
}

void loop() {
  if(checkButton()){
    Serial.println("pressed");
    attempt+=1;
    delay(500);
    Serial.println("done");
  }
  
  switch (attempt)
    {
    case 1: // search
      /* code */
      delay(500);
      run(true, SEARCH_SPEED);
      stopMoving();
      delay(500);
      // coming back
      run(false, SEARCH_SPEED);
      stopMoving();
      Serial.println(attempt);
      attempt += 1;
      break;

    case 3: // RUN 1
      delay(500);
      /* code */
      run(true, RUN_1);
      Serial.println(attempt);
      stopMoving();
      delay(500);
      attempt += 1;
      break;

    case 5: // RUN 2
      delay(500);
      /* code */
      run(true, RUN_2);
      Serial.println(attempt);
      stopMoving();
      delay(500);

      attempt += 1;
      break;
    
    default:
      
      break;
    }
}

