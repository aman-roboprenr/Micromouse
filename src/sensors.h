#pragma once

int frontSensorOut = HIGH; // HIGH at No Obstacle

#define TRIGGER_LEFT A1
#define ECHO_LEFT A0
#define TRIGGER_RIGHT A4
#define ECHO_RIGHT A5
#define TRIGGER_FRONT A2
#define ECHO_FRONT A3

#define THRESHOLD_SIDE 140
#define THRESHOLD_FRONT 150
#define NO_WALL_CONST 50

const float STEERING_KP = 1.9;
const float STEERING_KD = 0;
const float STEERING_ADJUST_LIMIT = 18.0;

const float SOUND_SPEED = 0.340;

int ePrev = 0;
int delay_time = 10;



void sensorSetup()
{
    pinMode(ECHO_LEFT, INPUT);
    pinMode(TRIGGER_LEFT, OUTPUT);

    pinMode(ECHO_FRONT, INPUT);
    pinMode(TRIGGER_FRONT, OUTPUT);

    pinMode(ECHO_RIGHT, INPUT);
    pinMode(TRIGGER_RIGHT, OUTPUT);
    Serial.println(F("Sensors setted"));
}

int getDistanceLeft()
{
    int dist = 0;
    long unsigned Time = 0;
    digitalWrite(TRIGGER_LEFT, LOW);
    delayMicroseconds(2);
    digitalWrite(TRIGGER_LEFT, HIGH);
    delayMicroseconds(10);
    digitalWrite(TRIGGER_LEFT, LOW);
    Time = pulseIn(ECHO_LEFT, HIGH);
    dist = SOUND_SPEED * Time / 2;
    delay(delay_time);

    return dist;
}

int getDistanceRight()
{
    int dist = 0;
    long unsigned Time = 0;
    digitalWrite(TRIGGER_RIGHT, LOW);
    delayMicroseconds(10);
    digitalWrite(TRIGGER_RIGHT, HIGH);
    delayMicroseconds(10);
    digitalWrite(TRIGGER_RIGHT, LOW);
    Time = pulseIn(ECHO_RIGHT, HIGH);
    dist = SOUND_SPEED * Time / 2;
    delay(delay_time);
    return dist;
}

int getDistanceFront()
{
    int dist = 0;
    long unsigned Time = 0;
    digitalWrite(TRIGGER_FRONT, LOW);
    delayMicroseconds(2);
    digitalWrite(TRIGGER_FRONT, HIGH);
    delayMicroseconds(10);
    digitalWrite(TRIGGER_FRONT, LOW);
    Time = pulseIn(ECHO_FRONT, HIGH);
    dist = SOUND_SPEED * Time / 2;
    delay(delay_time);
    return dist;
}

bool wallInFront()
{
    return THRESHOLD_FRONT >= getDistanceFront();
}

bool wallInLeft()
{
    return THRESHOLD_SIDE >= getDistanceLeft();
}

bool wallInRight()
{
    return THRESHOLD_SIDE >= getDistanceRight();
}

//  +ve angular means we are a little to the right and need to move left
//  -ve angular means we are a little to the left and need to move right
int angularError()
{
    if (not wallInLeft() and not wallInRight())
    {
        return 0;
    }

    int left_reading = getDistanceLeft();
    int right_reading = getDistanceRight();
    if(left_reading >= THRESHOLD_SIDE)  left_reading = NO_WALL_CONST;
    if(right_reading >= THRESHOLD_SIDE)  right_reading = NO_WALL_CONST;

    return left_reading - right_reading;;
}

float calculateSteeringAdjustment() {
    int e = angularError();
    float pTerm = STEERING_KP * e;
    float dTerm = STEERING_KD * (e - ePrev);
    float adjustment = (pTerm + dTerm);
    adjustment = constrain(adjustment, -STEERING_ADJUST_LIMIT, STEERING_ADJUST_LIMIT);
    ePrev = e;
    return adjustment;
  }

void readSides()
{
    int left = getDistanceLeft();
    int right = getDistanceRight();
    int front = getDistanceFront();
    
    Serial.print("left -->  distance : ");
    Serial.print(left);
    Serial.print("  , wall : ");
    Serial.print(wallInLeft());
    Serial.println();

    Serial.print("front -->  distance : ");
    Serial.print(front);
    Serial.print("  , wall : ");
    Serial.print(wallInFront());
    Serial.println();

    Serial.print("right -->  distance : ");
    Serial.print(right);
    Serial.print("  , wall : ");
    Serial.print(wallInRight());
    Serial.println();

    Serial.println(angularError());
    Serial.println();
}

void readAdj(){
    Serial.println(calculateSteeringAdjustment());
    Serial.println();
}