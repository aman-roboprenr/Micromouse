#pragma once

#include "motors.h"
#include "maze.h"

#define SAFETY_DELAY 20

int x = START_I;
int y = START_J;
int cur_dxn = START_DXN;

void resetToStart(){
  x = START_I;
  y = START_J;
  cur_dxn = START_DXN;
}

void run(bool going_to_center, int speed){
    if(going_to_center){
      resetToStart();
    }
    setSpeed(speed);

    while(true){
        rememberWalls(x,y,cur_dxn);
        flood(going_to_center);

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
    stopMoving();
}
