#include <Arduino.h>
#pragma once
const int ENCODER_LEFT_A = 3;
const int ENCODER_LEFT_B = 12;

const int ENCODER_RIGHT_A = 2;
const int ENCODER_RIGHT_B = 11;

// pid stuff

volatile int pos_left = 0;

void readEncoderLeft(){
  int b = digitalRead(ENCODER_LEFT_B);
  if(b>0){
    pos_left--;
  }
  else{
    pos_left++;
  }
  // Serial.println(pos_left);
}

void encoderSetupLeft(){
  pinMode(ENCODER_LEFT_A, INPUT);
  pinMode(ENCODER_LEFT_B, INPUT);
  attachInterrupt(digitalPinToInterrupt(ENCODER_LEFT_A), readEncoderLeft, RISING);
}

int currentPositionLeft(){
  int dist = 0;
  ATOMIC_BLOCK(ATOMIC_RESTORESTATE) {
    dist = pos_left;
  }
  return dist;
}

void resetLeft(){
  pos_left = 0;
}


volatile int pos_right = 0;

void readEncoderRight(){
  int b = digitalRead(ENCODER_RIGHT_B);
  if(b>0){
    pos_right++;
  }
  else{
    pos_right--;
  }
  // Serial.println(pos_left);
}

void encoderSetupRight(){
  pinMode(ENCODER_RIGHT_A, INPUT);
  pinMode(ENCODER_RIGHT_B, INPUT);
  attachInterrupt(digitalPinToInterrupt(ENCODER_RIGHT_A), readEncoderRight, RISING);
}

int currentPositionRight(){
  int dist = 0;
  ATOMIC_BLOCK(ATOMIC_RESTORESTATE) {
    dist = pos_right;
  }
  return dist;
}

void resetRight(){
  pos_right = 0;
}


float currentForwardPosition(){
  int l=0,r=0;
  ATOMIC_BLOCK(ATOMIC_RESTORESTATE) {
    r = pos_right;
    l = pos_left;
  }
  float fw = 0.5 * (l + r);
  return fw;
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