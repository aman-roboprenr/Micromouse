#include <Arduino.h>
#include <sensors.h>
#include <encoders.h>
#include <motors.h>
#include "maze.h"


#define START_I 3
#define START_J 0
#define START_DXN NORTH

#define SAFETY_DELAY 20

int x = START_I;
int y = START_J;
int cur_dxn = START_DXN;
void reachToTarget(){
  Serial.println("Going to targrt");
    while(true){
        // Serial.println("current cordinates");
        // Serial.print("x : ");
        // Serial.print(x);
        // Serial.print(", y : ");
        // Serial.print(y);
        rememberWalls(x,y,cur_dxn);
        // Serial.println("\nwall states");
        // printWallStates();
        flood(true);
        // Serial.println("costs");
        // printCost();
        // stop when we reach
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
          cur_dxn = best_dxn;
        }

        if(not wallInFront()){
          increment(x,y,cur_dxn);
          moveOneCell();
        }
        stopMoving();
        delay(SAFETY_DELAY);
        // Serial.println("done cell\n");
    }
}

void reachToStart(){
  Serial.println("Going to start");
  while(true){
      flood(false);

      // stop when we reach
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
        cur_dxn = best_dxn;
      }

      if(not wallInFront()){
        increment(x,y,cur_dxn);
        moveOneCell();
      }

      stopMoving();
      delay(SAFETY_DELAY);
  }
}

void setup() {
  Serial.begin(115200);
  sensorSetup();
  delay(SAFETY_DELAY);
  encoderSetup();
  delay(SAFETY_DELAY);
  // return;
  flood(true);
  reachToTarget();
  stopMoving();
  delay(SAFETY_DELAY);
  Serial.println("\nfreached target\n");
  flood(false);
  reachToStart();
  Serial.println("\nreached start\n");
  stopMoving();
  delay(SAFETY_DELAY);
  Serial.println("\n starting final run\n");
  flood(true);
  reachToTarget();
  stopMoving();
  // delay(SAFETY_DELAY);
  // flood(false);
  // reachToStart();
  stopMoving();
}

void loop() {
  // Serial.println(wallInFront());
  // Serial.println(getDistanceFront());
  // readSides();
  // Serial.println(getDistanceRight());
  // Serial.println(calculateSteeringAdjustment());
  // moveOneCell();
  // moveOneCell();
  // takeRight();
  // moveOneCell();
  // turnAround();
  // moveOneCell();
  // stopMoving();
  // delay(SAFETY_DELAY);
  // moveOneCell();
}

