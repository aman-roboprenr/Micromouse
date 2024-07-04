#include <Arduino.h>
#include <sensors.h>
#include <encoders.h>
#include <motors.h>
#include "maze.h"

#define START_I 3
#define START_J 0
#define START_DXN NORTH

void reachToTarget(){
    int x =START_I,y=START_J,cur_dxn = START_DXN;
    while(true){
        // Serial.print("standing at : ");
        // Serial.print(x);
        // Serial.print(" , ");
        // Serial.print(y);
        // Serial.println();

        // Serial.print("current dxn : ");
        // Serial.println(cur_dxn);
        
        rememberWalls(x,y,cur_dxn);
        // Serial.println("wall states : ");
        // printWallStates();
        
        flood();
        Serial.println("cost : ");
        printCost();

        // stop when we reach
        if(maze[x][y].cost == 0){
          break;
        }

        int best_dxn = bestDirection(x,y);
        Serial.print("best dxn : ");
        Serial.println(best_dxn);

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
        Serial.println();
    }
}

void setup() {
  Serial.begin(115200);
  sensorSetup();
  delay(1000);
  encoderSetup();
  delay(1000);

  flood();
  reachToTarget();
}

void loop() {
  // flood();
  // Serial.println("hghgghdgh");
  moveOneCell();
  delay(1000);
}

