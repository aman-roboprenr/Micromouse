#include "queue.h"
#include "sensors.h"
#include <stdio.h>
#include <Arduino.h>
#pragma once

#define MAZE_WIDTH 5
#define MAZE_HEIGHT 4
#define MAZE_CELL_COUNT (MAZE_WIDTH * MAZE_HEIGHT)
#define MAX_COST (MAZE_CELL_COUNT - 1)

#define TARGET_I 2
#define TARGET_J 2
// #define NUMBER_OF_TARGETS (TARGET_TOP_LEFT_I-TARGET_BOTTOM_RIGHT_I + 1 )*(TARGET_BOTTOM_RIGHT_J-TARGET_TOP_LEFT_J + 1)

#define START_I MAZE_HEIGHT - 1
#define START_J MAZE_WIDTH-1
#define START_DXN NORTH

enum Dxn{NORTH, EAST, SOUTH, WEST, DXN_COUNT};

int dx[4] = {-1,0,1,0};
int dy[4] = {0,1,0,-1};

struct Cell{
    int wall_state=0;
    int cost;
};

Cell maze[MAZE_HEIGHT][MAZE_WIDTH];
struct Pair{
    int i;
    int j;
};

void setBit(int &val, int pos){
    val = val | (1<<pos);
}

void unsetBit(int &val, int pos){
    val = val & ~(1<<pos);
}

bool checkBit(int val, int pos){
    return val & (1<<pos);
}

bool isValidCell(int x, int y){
    return not (x < 0 or x>=MAZE_HEIGHT or y<0 or y>=MAZE_WIDTH );
}

bool wallInDxn(int i, int j, int dxn){
    return checkBit(maze[i][j].wall_state, dxn);
}
void setWall(int x, int y, int dxn){

    setBit(maze[x][y].wall_state, dxn);

    int a = x + dx[dxn];
    int b = y + dy[dxn];
    int new_dxn = (dxn+2)%DXN_COUNT;
    if(isValidCell(a,b)){
        setBit(maze[a][b].wall_state, new_dxn);
    }
}

int bestDirection(int i,int j){
    Pair tp;
    tp.i = NORTH;
    tp.j =  MAX_COST + 1;
    for(int k = NORTH; k<DXN_COUNT; k++){
        int x = i + dx[k], y= j+dy[k];
        if(isValidCell(x,y) and not wallInDxn(i,j,k) and maze[x][y].cost < tp.j){
            tp.i = k;
            tp.j = maze[x][y].cost;
        }
    }
    return tp.i;
}


void flood(bool going_to_target){
    // initialising max costs
    for (int x = 0; x < MAZE_HEIGHT; x++) {
      for (int y = 0; y < MAZE_WIDTH; y++) {
        maze[x][y].cost = MAX_COST;
      }
    }

    Queue<Pair, MAZE_CELL_COUNT/2> q;
    
    // adding targets
    if(going_to_target){
        Pair c;
        c.i = TARGET_I;
        c.j = TARGET_J;
        q.add(c);
        maze[TARGET_I][TARGET_J].cost = 0;
    }
    else{
        Pair c;
        c.i = START_I;
        c.j = START_J;
        q.add(c);
        maze[START_I][START_J].cost = 0;
    }
    

    
    while(q.size() > 0){
        // this removes the front head also
        Pair cur = q.head();
        int x = cur.i, y = cur.j;
        // cout << x << " " << y << endl;
        int cur_cost = maze[x][y].cost + 1;
        for(int k =0;k<4;k++){
            int i = x + dx[k], j = y + dy[k];
            if(isValidCell(i,j) and not wallInDxn(x,y,k) and maze[i][j].cost > cur_cost ){
                maze[i][j].cost = cur_cost;
                Pair tp;
                tp.i = i;
                tp.j = j;
                q.add(tp);
            }
        }
            
    }
}

void printCost(){
    for (int x = 0; x < MAZE_HEIGHT; x++) {
      for (int y = 0; y < MAZE_WIDTH; y++) {
        Serial.print(maze[x][y].cost);
        Serial.print("    ");
      }
      Serial.println();
    }
}

void rememberWalls(int i, int j, int dxn){
    if(wallInFront()){
        setWall(i, j, dxn);
    }
    if(wallInLeft()){
        setWall(i, j, (dxn+3)%DXN_COUNT);
    }
    if(wallInRight()){
        setWall(i, j, (dxn+1)%DXN_COUNT);
    }
}

void printWallStates(){
    for (int x = 0; x < MAZE_HEIGHT; x++) {
      for (int y = 0; y < MAZE_WIDTH; y++) {
        Serial.print(maze[x][y].wall_state);
        Serial.print("    ");
      }
      Serial.println();
    }
}

void increment(int &i, int &j, int dxn){
    i = i+dx[dxn];
    j = j+dy[dxn];
}
