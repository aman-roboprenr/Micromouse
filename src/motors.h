#include <Arduino.h>
#include <SparkFun_TB6612.h>
#include <encoders.h>

const int AIN1 = 2;
const int BIN1 = 7;
const int AIN2 = 4;
const int BIN2 = 8;
const int PWMA = 5;
const int PWMB = 6;
const int STBY = 9;

const int offsetA = 1;
const int offsetB = 1;

// right
Motor motor1 = Motor(AIN1, AIN2, PWMA, offsetA, STBY);
// left
Motor motor2 = Motor(BIN1, BIN2, PWMB, offsetB, STBY);


int TURN_DISTANCE = 100;
int CELL_DISTANCE = 9000;

void stopMoving(){
    brake(motor1, motor2);
}

void moveOneCell(){
    // it should be 16 cm for our testing 16cm
    motor1.drive(200);
    motor2.drive(200);
    // delay(5000);
    // int l_dist = currentPositionLeft();
    // int r_dist = currentPositionRight();
    // while(l_dist < CELL_DISTANCE and r_dist <CELL_DISTANCE){
    //     motor1.drive(rightSpeed(CELL_DISTANCE));
    //     motor2.drive(leftSpeed(CELL_DISTANCE));
    //     l_dist = currentPositionLeft();
    //     r_dist = currentPositionRight();
    // }
}

void takeLeft(){
    int TURN_DISTANCE = 100;
    int l_dist = currentPositionLeft();
    int r_dist = currentPositionRight();
    Serial.print(l_dist);
    Serial.print(" ");
    Serial.print(r_dist);
    Serial.println();
    while(l_dist > (TURN_DISTANCE * -1) and r_dist < TURN_DISTANCE){
        motor1.drive(rightSpeed(TURN_DISTANCE));
        motor2.drive(leftSpeed(TURN_DISTANCE * -1));
        l_dist = currentPositionLeft();
        r_dist = currentPositionRight();
        Serial.print(l_dist);
        Serial.print(" ");
        Serial.print(r_dist);
        Serial.println();
    }
}

void takeRight(){
    int l_dist = currentPositionLeft();
    int r_dist = currentPositionRight();
    Serial.print(l_dist);
    Serial.print(" ");
    Serial.print(r_dist);
    Serial.println();
    while(l_dist < TURN_DISTANCE and r_dist > (TURN_DISTANCE * -1)){
        motor1.drive(rightSpeed(TURN_DISTANCE * -1));
        motor2.drive(leftSpeed(TURN_DISTANCE ));
        l_dist = currentPositionLeft();
        r_dist = currentPositionRight();
        Serial.print(l_dist);
        Serial.print(" ");
        Serial.print(r_dist);
        Serial.println();
    }
}
    
void turnAround(){
    takeLeft();
    takeLeft();
}


