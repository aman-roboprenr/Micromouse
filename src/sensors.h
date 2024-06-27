const int IR_RIGHT = A0;
const int IR_LEFT = A4;
const int IR_FRONT = A1;

int frontSensorOut = HIGH;  // HIGH at No Obstacle
int rightSensorOut = HIGH;  // HIGH at No Obstacle
int leftSensorOut = HIGH;  // HIGH at No Obstacle


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
