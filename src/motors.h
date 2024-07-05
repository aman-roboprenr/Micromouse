#include <Arduino.h>
#include <SparkFun_TB6612.h>
#include <encoders.h>
#include <speed_controller.h>
#include <sensors.h>
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
const int CELL_DISTANCE = 1550;
const int FRONT_WALL_THRESHOLD = 30;
void stopMoving(){
    brake(motor_right, motor_left);
    encodersReset();
}

bool forceStop(){
    int dis = getDistanceFront();
    return dis <= FRONT_WALL_THRESHOLD;
}
void moveOneCell(){
    int dist = currentForwardPosition();
    while(dist < CELL_DISTANCE){
        if(forceStop()){
            break;
        }
        float forward_component = forwardComponent(CELL_DISTANCE);
        int ang_offset = calculateSteeringAdjustment();
        float angular_component = angularComponent(ang_offset);
        // float angular_component = 0;
        Serial.println("offset");
        Serial.print(ang_offset);
        Serial.print(" ");
        Serial.print(angular_component);
        Serial.println();
        int r_speed = forward_component + angular_component;
        int l_speed = forward_component -  angular_component;
        Serial.println("speed");
        Serial.print(l_speed);
        Serial.print(" ");
        Serial.print(r_speed);
        Serial.println();
        motor_right.drive(r_speed);
        motor_left.drive(l_speed);
        dist = currentForwardPosition();
    }
    // Serial.println("here");
    encodersReset();
    stopMoving();
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


