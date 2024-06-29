#include <Arduino.h>
#include <SparkFun_TB6612.h>
#include <encoders.h>

const int AIN1 = 4;
const int BIN1 = 7;
const int AIN2 = 13;
const int BIN2 = 8;
const int PWMA = 5;
const int PWMB = 6;
const int STBY = 9;

const int offsetA = 1;
const int offsetB = 1;

Motor motor_left = Motor(AIN1, AIN2, PWMA, offsetA, STBY);

Motor motor_right = Motor(BIN1, BIN2, PWMB, offsetB, STBY);


const int TURN_DISTANCE = 500;
const int CELL_DISTANCE = 1650;

void stopMoving(){
    brake(motor_right, motor_left);
    encodersReset();
}

void moveOneCell(){
    int l_dist = currentPositionLeft();
    int r_dist = currentPositionRight();
    while(l_dist < CELL_DISTANCE and r_dist <CELL_DISTANCE){
        int r_speed = rightSpeed(CELL_DISTANCE);
        int l_speed = leftSpeed(CELL_DISTANCE);
        motor_right.drive(r_speed);
        motor_left.drive(l_speed);
        l_dist = currentPositionLeft();
        r_dist = currentPositionRight();
    }
    encodersReset();
}

void takeLeft(){
    int l_dist = currentPositionLeft();
    int r_dist = currentPositionRight();
    while(l_dist > (TURN_DISTANCE * -1) and r_dist < TURN_DISTANCE){
        int l_speed = leftSpeed((TURN_DISTANCE * -1));
        int r_speed = rightSpeed(TURN_DISTANCE );
        motor_left.drive(l_speed);
        motor_right.drive(r_speed);
        l_dist = currentPositionLeft();
        r_dist = currentPositionRight();
    }
    encodersReset();
}

void takeRight(){
    int l_dist = currentPositionLeft();
    int r_dist = currentPositionRight();
    while(l_dist < TURN_DISTANCE  and r_dist > (TURN_DISTANCE * -1)){
        int l_speed = leftSpeed((TURN_DISTANCE));
        int r_speed = rightSpeed(TURN_DISTANCE * -1 );
        motor_left.drive(l_speed);
        motor_right.drive(r_speed);
        l_dist = currentPositionLeft();
        r_dist = currentPositionRight();
    }
    encodersReset();
}
    
void turnAround(){
    takeLeft();
    takeLeft();
    encodersReset();
}


