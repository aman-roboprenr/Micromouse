#include <Arduino.h>
#include <SparkFun_TB6612.h>
#include <encoders.h>
#include <speed_controller.h>
#pragma once

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
    int dist = currentForwardPosition();
    while(dist < CELL_DISTANCE){
        float forwad_component = forwardComponent(CELL_DISTANCE);
        int r_speed = forwad_component;
        int l_speed = forwad_component;
        motor_right.drive(r_speed);
        motor_left.drive(l_speed);
        dist = currentForwardPosition();
    }
    encodersReset();
}

void takeLeft(){
    int r_dist = currentPositionRight();
    while(r_dist < TURN_DISTANCE){
        int l_speed = forwardComponent((TURN_DISTANCE * -1));
        int r_speed = forwardComponent(TURN_DISTANCE );
        motor_left.drive(l_speed);
        motor_right.drive(r_speed);
        r_dist = currentPositionRight();
    }
    encodersReset();
}

void takeRight(){
    int l_dist = currentPositionLeft();
    while(l_dist < TURN_DISTANCE ){
        int l_speed = forwardComponent((TURN_DISTANCE));
        int r_speed = forwardComponent(TURN_DISTANCE * -1 );
        motor_left.drive(l_speed);
        motor_right.drive(r_speed);
        l_dist = currentPositionLeft();
    }
    encodersReset();
}
    
void turnAround(){
    takeLeft();
    takeLeft();
    encodersReset();
}


