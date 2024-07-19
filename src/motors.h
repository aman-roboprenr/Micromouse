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


const float TURN_DISTANCE = 78;
const float TURN_AROUND_DISTANCE = 170;
const float CELL_DISTANCE = 235;

const int SCALE_UP = 10;
const int FRONT_WALL_THRESHOLD = 40;

#define MOTOR_LIMIT 255

void stopMoving(){
    brake(motor_right, motor_left);
    encodersReset();
}

bool forceStop(){
    int dis = getDistanceFront();
    return dis < FRONT_WALL_THRESHOLD;
}

void moveOneCell(){
    encodersReset();
    int dist = currentForwardPosition();
    while(dist < CELL_DISTANCE){
        if(forceStop()){
            break;
        }
        float forward_component = forwardComponent((CELL_DISTANCE * SCALE_UP));
        int ang_offset = calculateSteeringAdjustment();
        float angular_component = angularComponent(ang_offset);
        // float angular_component = 0;
        int r_speed = forward_component + angular_component;
        int l_speed = forward_component -  angular_component;
        l_speed = constrain(l_speed, -MOTOR_LIMIT, MOTOR_LIMIT);
        r_speed = constrain(r_speed, -MOTOR_LIMIT, MOTOR_LIMIT);
        motor_right.drive(r_speed);
        motor_left.drive(l_speed);
        dist = currentForwardPosition();
    }
    stopMoving();
    encodersReset();
}

void takeLeft(){
    encodersReset();
    int r_dist = currentPositionRight();
        Serial.println("left turn");
    while(r_dist < TURN_DISTANCE){
        // Serial.println(r_dist);
        int l_speed = forwardComponent(((TURN_DISTANCE * SCALE_UP) * -1));
        int r_speed = forwardComponent((TURN_DISTANCE * SCALE_UP) );
        motor_left.drive(l_speed);
        motor_right.drive(r_speed);
        r_dist = currentPositionRight();
    }
    stopMoving();
    encodersReset();
}

void takeRight(){
    encodersReset();
    int l_dist = currentPositionLeft();
        Serial.println("right turn");
    while(l_dist < TURN_DISTANCE ){
        Serial.println(l_dist);
        int l_speed = forwardComponent(((TURN_DISTANCE * SCALE_UP)));
        int r_speed = forwardComponent((TURN_DISTANCE * SCALE_UP) * -1 );
        l_speed = constrain(l_speed, -MOTOR_LIMIT, MOTOR_LIMIT);
        r_speed = constrain(r_speed, -MOTOR_LIMIT, MOTOR_LIMIT);
        motor_left.drive(l_speed);
        motor_right.drive(r_speed);
        l_dist = currentPositionLeft();
    }
    stopMoving();
    encodersReset();
}
    
void turnAround(){
    encodersReset();
    int r_dist = currentPositionRight();
    Serial.println("turn around");
    while(r_dist < TURN_AROUND_DISTANCE){
        int l_speed = forwardComponent(((TURN_AROUND_DISTANCE * SCALE_UP) * -1));
        int r_speed = forwardComponent((TURN_AROUND_DISTANCE * SCALE_UP) );
        motor_left.drive(l_speed);
        motor_right.drive(r_speed);
        r_dist = currentPositionRight();
    }
    stopMoving();
    encodersReset();
}


