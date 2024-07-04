#include <Arduino.h>
#include <sensors.h>
#include <encoders.h>
#include <motors.h>
#include "maze.h"

#define START_I 3
#define START_J 0
#define START_DXN NORTH

int x = START_I;
int y = START_J;
int cur_dxn = START_DXN;
void reachToTarget(){
  Serial.println("Going to targrt");
    while(true){
        rememberWalls(x,y,cur_dxn);
        flood(true);

        // stop when we reach
        if(maze[x][y].cost == 0){
          break;
        }

        int best_dxn = bestDirection(x,y);
        if(best_dxn != cur_dxn){
            while(cur_dxn != best_dxn){
                takeRight();
                cur_dxn = (cur_dxn + 1) % DXN_COUNT;
            }
        }

        if(not wallInFront()){
          increment(x,y,cur_dxn);
          moveOneCell();
        }
        stopMoving();
        delay(1000);
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
          while(cur_dxn != best_dxn){
              takeRight();
              cur_dxn = (cur_dxn + 1) % DXN_COUNT;
          }
      }

      if(not wallInFront()){
        increment(x,y,cur_dxn);
        moveOneCell();
      }

      stopMoving();
      delay(1000);
  }
}

void setup() {
  Serial.begin(115200);
  sensorSetup();
  delay(1000);
  encoderSetup();
  delay(1000);

  flood(true);
  reachToTarget();
  Serial.println("\nfreached target\n");
  delay(2000);
  flood(false);
  reachToStart();
  Serial.println("\nreached start\n");
  delay(2000);
  Serial.println("\n starting final run\n");
  flood(true);
  reachToTarget();
  flood(false);
  reachToStart();
  Serial.println("\n done \n");
}

void loop() {
  // flood();
  // Serial.println("hghgghdgh");
  // moveOneCell();
  // delay(1000);
}

