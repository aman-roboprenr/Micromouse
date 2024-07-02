#pragma once

const int IR_RIGHT = A0;
const int IR_LEFT = A2;
const int IR_FRONT = A1;

int frontSensorOut = HIGH;  // HIGH at No Obstacle
int rightSensorOut = HIGH;  // HIGH at No Obstacle
int leftSensorOut = HIGH;  // HIGH at No Obstacle

const int NO_WALL_CONST = 8;

void sensorSetup()
{
    pinMode(IR_FRONT, INPUT);
    pinMode(IR_LEFT, INPUT);
    pinMode(IR_RIGHT, INPUT);
    Serial.println(F("Sensors setted"));

}

bool wallInLeft()
{
    leftSensorOut = digitalRead(IR_LEFT);

    if (leftSensorOut == LOW)
    {
        return true;
    }
    return false;
    // return true;
}
bool wallInRight()
{
    rightSensorOut = digitalRead(IR_RIGHT);

    if (rightSensorOut == LOW)
    {
        return true;
    }
    return false;
    // return true;
}
bool wallInFront()
{
    frontSensorOut = digitalRead(IR_FRONT);

    if (frontSensorOut == LOW)
    {
        return true;
    }
    return false;
}

//  +ve angular means we are a little to the right and need to move left
//  -ve angular means we are a little to the left and need to move right
int angularError(){
    int left_reading = NO_WALL_CONST, right_reading = NO_WALL_CONST;
    if(not wallInLeft() and not wallInRight()){
        return 0;
    }
    else if(not wallInLeft()){
        right_reading = analogRead(IR_RIGHT);
    }
    else if(not wallInRight()){
        left_reading = analogRead(IR_LEFT);
    }
    else{
        left_reading = analogRead(IR_LEFT);
        right_reading = analogRead(IR_RIGHT);
    }
    if(left_reading > NO_WALL_CONST){
        left_reading = NO_WALL_CONST;
    }
    if(right_reading > NO_WALL_CONST){
        right_reading = NO_WALL_CONST;
    }
    return left_reading - right_reading;
}

void readSides(){
    int left = analogRead(IR_LEFT);
    int right = analogRead(IR_RIGHT);
    Serial.print(left);
    Serial.print(" ");
    Serial.print(right);
    Serial.println();
}