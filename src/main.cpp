#include <Arduino.h>
#include "sensors.h"
#include "encoders.h"
#include "motors.h"
#include "maze.h"
#include "speed_controller.h"


#define START_I 3
#define START_J 0
#define START_DXN NORTH

#define SAFETY_DELAY 5

int x = START_I;
int y = START_J;
int cur_dxn = START_DXN;

void resetToStart(){
  x = START_I;
  y = START_J;
  cur_dxn = START_DXN;
}
void reachToTarget(){
  Serial.println("Going to targrt");
    while(true){
        rememberWalls(x,y,cur_dxn);
        flood(true);

        if(maze[x][y].cost == 0){
          break;
        }

        int best_dxn = bestDirection(x,y);
        if(best_dxn != cur_dxn){
          if(best_dxn == (cur_dxn+1)%DXN_COUNT){
            takeRight();
          }
          else if(best_dxn == (cur_dxn+2)%DXN_COUNT){
            turnAround();
          }
          else{
            takeLeft();
          }
          delay(SAFETY_DELAY);
          cur_dxn = best_dxn;
        }

        if(not wallInFront()){
          increment(x,y,cur_dxn);
          moveOneCell();
        }

        delay(SAFETY_DELAY);
    }
}

void reachToStart(){
  while(true){
      rememberWalls(x,y,cur_dxn);
      flood(false);

      if(maze[x][y].cost == 0){
        break;
      }

      int best_dxn = bestDirection(x,y);
      if(best_dxn != cur_dxn){
        if(best_dxn == (cur_dxn+1)%DXN_COUNT){
          takeRight();
        }
        else if(best_dxn == (cur_dxn+2)%DXN_COUNT){
          turnAround();
        }
        else{
          takeLeft();
        }
        delay(SAFETY_DELAY);
        cur_dxn = best_dxn;
      }

      if(not wallInFront()){
        increment(x,y,cur_dxn);
        moveOneCell();
      }
      delay(SAFETY_DELAY);
  }
}

void setup() {
  Serial.begin(115200);
  sensorSetup();
  delay(SAFETY_DELAY);
  encoderSetup();
  delay(SAFETY_DELAY);
  // search run
  setSpeed(SEARCH_SPEED);
  // return;
  flood(true);
  //  going to target
  reachToTarget();
  stopMoving();
  delay(SAFETY_DELAY);
  flood(false);
  // coming back to start
  reachToStart();
  stopMoving();
  delay(5000);

  // fast run 1 : assumes robot is places in the starting position
  resetToStart();
  setSpeed(RUN_1);
  delay(SAFETY_DELAY);
  flood(true);
  reachToTarget();
  stopMoving();
  delay(5000);

  // fast run 2 assumes robot is places in the starting position
  resetToStart();
  setSpeed(RUN_2);
  delay(SAFETY_DELAY);
  Serial.println("\n starting final run\n");
  flood(true);
  reachToTarget();
  stopMoving();
  delay(5000);
}

void loop() {

}

