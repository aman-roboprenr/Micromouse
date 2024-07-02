#pragma once

#define MAZE_WIDTH 5
#define MAZE_HEIGHT 4
#define MAZE_CELL_COUNT (MAZE_WIDTH * MAZE_HEIGHT)
#define MAX_COST (MAZE_CELL_COUNT - 1)

#define TARGET_TOP_LEFT_I 3
#define TARGET_TOP_LEFT_J 2
#define TARGET_BOTTOM_RIGHT_I 3
#define TARGET_BOTTOM_RIGHT_J 2
#define NUMBER_OF_TARGETS (TARGET_TOP_LEFT_I-TARGET_BOTTOM_RIGHT_I + 1 )*(TARGET_BOTTOM_RIGHT_J-TARGET_TOP_LEFT_J + 1)

Cell maze[MAZE_WIDTH][MAZE_HEIGHT];


enum Dxn{NORTH, EAST, SOUTH, WEST, DXN_COUNT};

int dy[4] = {1,0,-1,0};
int dx[4] = {0,1,0,-1};

struct Cell{
    int wall_state;
    int cost;
    bool visited=false;
};

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

bool isValidCell(int x, int y, int dx){
    if(x < 0 or x>=MAZE_WIDTH or y<0 or y>=MAZE_HEIGHT) return false;
    // return true;
    int to_check = (dx+2) % DXN_COUNT;

    // if there is a wall here then this cell is not a valid cell
    return not (checkBit(maze[x][y].wall_state, to_check));
}

void setWall(int x, int y, int dxn){

    setBit(maze[x][y].wall_state, dxn);

    int a = x + dx[dxn];
    int b = y + dy[dxn];
    int new_dxn = (dxn+2)%DXN_COUNT;
    if(isValidCell(a,b,new_dxn)){
        setBit(maze[a][b].wall_state, new_dxn);
    }
}

int bestDirection(int i,int j){
    Pair tp;
    tp.i = NORTH;
    tp.j =  MAX_COST + 1;
    for(int k = NORTH; k<DXN_COUNT; k++){
        int x = i + dx[k], y= j+dy[k];
        if(isValidCell(x,y,k) and maze[x][y].cost < tp.j){
            tp.i = k;
            tp.j = maze[x][y].cost;
        }
    }
    return tp.i;
}
