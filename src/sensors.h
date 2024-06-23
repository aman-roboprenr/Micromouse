const int IR_RIGHT = A0;
const int IR_LEFT = A4;
const int IR_FRONT = A1;

int frontSensorOut = HIGH;  // HIGH at No Obstacle
int rightSensorOut = HIGH;  // HIGH at No Obstacle
int leftSensorOut = HIGH;  // HIGH at No Obstacle

void sensor_setup()
{
    pinMode(IR_FRONT, INPUT);
    Serial.println(F("Sensors setted"));

}

bool wall_in_left()
{
    leftSensorOut = digitalRead(IR_LEFT);

    if (leftSensorOut == LOW)
    {
        return true;
    }
    return false;
    // return true;
}
bool wall_in_right()
{
    rightSensorOut = digitalRead(IR_RIGHT);

    if (rightSensorOut == LOW)
    {
        return true;
    }
    return false;
    // return true;
}
bool wall_in_front()
{
    frontSensorOut = digitalRead(IR_FRONT);

    if (frontSensorOut == LOW)
    {
        return true;
    }
    return false;
}
