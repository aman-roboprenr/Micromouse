#include <Arduino.h>
#include <SparkFun_TB6612.h>

/**
 * Hardware pin defines
 */
#define BOARD UKMARSBOT_V1
const int ENCODER_LEFT_CLK = 2;
const int ENCODER_RIGHT_CLK = 3;
const int ENCODER_LEFT_B = 4;
const int ENCODER_RIGHT_B = 5;
// const int LED_RIGHT = 6;
// const int LED_LEFT = 11;
// const int EMITTER = 12;
// const int SENSOR_RIGHT_MARK = A0;
// const int SENSOR_1 = A1;
// const int SENSOR_2 = A2;
// const int SENSOR_3 = A3;
// const int SENSOR_4 = A4;
// const int SENSOR_LEFT_MARK = A5;
// const int FUNCTION_PIN = A6;
// const int BATTERY_VOLTS = A7;


const int AIN1 = 2;
const int BIN1 = 7;
const int AIN2 = 4;
const int BIN2 = 8;
const int PWMA = 5;
const int PWMB = 6;
const int STBY = 9;

const int offsetA = 1;
const int offsetB = 1;


Motor motor1 = Motor(AIN1, AIN2, PWMA, offsetA, STBY);
Motor motor2 = Motor(BIN1, BIN2, PWMB, offsetB, STBY);

void stop_moving(){
    brake(motor1, motor2);
}

void move(bool is_forward,int time){
    if(is_forward){
      Serial.println(F("movinf fow\n"));
        forward(motor1, motor2, 100);
    }
    else{
        forward(motor1, motor2, -100);

    }
    delay(time);
}

void take_left(){
    Serial.println(F("movinf left\n"));
    left(motor1, motor2, 200);
    delay(700);
    move(true, 1200);
}

void take_right(){
    Serial.println(F("movinf right\n"));
    right(motor1, motor2, 200);
    delay(700);
    move(true, 1200);
}
    
void turn_around(){
    right(motor1, motor2, 200);
    delay(700);
    right(motor1, motor2, 200);
    delay(700);
    move(true, 1200);
}


