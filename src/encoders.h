#include <Arduino.h>
#pragma once
const int ENCODER_LEFT_A = 3;
const int ENCODER_LEFT_B = 12;

const int ENCODER_RIGHT_A = 2;
const int ENCODER_RIGHT_B = 11;

// pid stuff
int pos_left = 0;
long prevT_left = 0;
float ePrev_left = 0;
float eIntegral_left = 0;



float leftSpeed(int target){

//  pid consts
  float kp = 0.9;
  float ki = 2;
  float kd = 2;

//  time dif
  float currT = micros();

  float deltaT = ( (float)(currT-prevT_left) )/ 1.0e6;

//  error
  int e = target - pos_left;

// pid vals
  float derivative = (e-ePrev_left)/deltaT ;
  float integral = eIntegral_left + e*deltaT;

//  pid signal
  float u = kp*e + ki*integral + kd*derivative;
//  motor values
  float pwr = fabs(u);
  if(pwr>255){
    pwr = 255;
  }
  if(u<0){
    pwr = pwr * -1;
  }
  ePrev_left = e;
  return pwr;
}

void readEncoderLeft(){
  int b = digitalRead(ENCODER_LEFT_B);
  if(b>0){
    pos_left--;
  }
  else{
    pos_left++;
  }
}

void encoderSetupLeft(){
  pinMode(ENCODER_LEFT_A, INPUT);
  pinMode(ENCODER_LEFT_B, INPUT);
  attachInterrupt(digitalPinToInterrupt(ENCODER_LEFT_A), readEncoderLeft, RISING);
}

int currentPositionLeft(){
  return pos_left;
}

void resetLeft(){
  pos_left = 0;
  prevT_left = 0;
  ePrev_left = 0;
  eIntegral_left = 0;
}

// pid stuff
int pos_right = 0;
long prevT_right = 0;
float ePrev_right = 0;
float eIntegral_right = 0;



float rightSpeed(int target){

//  pid consts
  float kp = 0.95;
  float ki = 2;
  float kd = 2;

//  time dif
  float currT = micros();

  float deltaT = ( (float)(currT-prevT_right) )/ 1.0e6;

//  error
  int e = target - pos_right;

// pid vals
  float derivative = (e-ePrev_right)/deltaT ;
  float integral = eIntegral_right + e*deltaT;

//  pid signal
  float u = kp*e + ki*integral + kd*derivative;
//  motor values
  float pwr = fabs(u);
  if(pwr>255){
    pwr = 255;
  }
  if(u<0){
    pwr = pwr * -1;
  }
  ePrev_right = e;
  return pwr;
}

void readEncoderRight(){
  int b = digitalRead(ENCODER_RIGHT_B);
  if(b>0){
    pos_right++;
  }
  else{
    pos_right--;
  }
}

void encoderSetupRight(){
  pinMode(ENCODER_RIGHT_A, INPUT);
  pinMode(ENCODER_RIGHT_B, INPUT);
  attachInterrupt(digitalPinToInterrupt(ENCODER_RIGHT_A), readEncoderRight, RISING);
}

int currentPositionRight(){
  return pos_right;
}

void resetRight(){
  pos_right = 0;
  prevT_right = 0;
  ePrev_right = 0;
  eIntegral_right = 0;
}


void encodersReset(){
  resetLeft();
  resetRight();
}

void encoderSetup(){
  encoderSetupLeft();
  encoderSetupRight();
  Serial.println("Encoders Setted");
}