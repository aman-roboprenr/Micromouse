#include <Arduino.h>
#include <util/atomic.h>
#pragma once
const int ENCODER_LEFT_A = 3;
const int ENCODER_LEFT_B = 12;

const int ENCODER_RIGHT_A = 2;
const int ENCODER_RIGHT_B = 11;

const float WHEEL_DIAMETER = 34.00;
const float ENCODER_PULSES = 28.00;
const float GEAR_RATIO = 23.65;

const float MM_PER_COUNT = PI * WHEEL_DIAMETER / (ENCODER_PULSES * GEAR_RATIO);
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
  int counts = 0;
  ATOMIC_BLOCK(ATOMIC_RESTORESTATE) {
    counts = pos_left;
  }
  return counts * MM_PER_COUNT;
  // return counts;
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
  int counts = 0;
  ATOMIC_BLOCK(ATOMIC_RESTORESTATE) {
    counts = pos_right;
  }
  // Serial.println(counts * MM_PER_COUNT);
  return counts * MM_PER_COUNT;
  // return counts;
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
  float counts = 0.5 * (l + r);
  // Serial.println(counts * MM_PER_COUNT);
  return counts * MM_PER_COUNT;
  // return counts;
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