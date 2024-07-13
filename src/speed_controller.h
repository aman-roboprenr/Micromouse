#include <Arduino.h>
#include <encoders.h>
#pragma once

int VOLTAGE_CAP = 100;

enum mode{SEARCH_SPEED=230, RUN_1=240, RUN_2=255};
//  pid consts
const float FORWARD_KP = 1;
const float FORWARD_KD = 0.0002;

const float ANGULAR_KP = 4;
const float ANGULAR_KD = 0.0008;


int ANGULAR_COMPONENT_LIMIT = 120;

long prevT_fw = 0;
float ePrev_fw = 0;

float forwardComponent(int target){
//  time dif
  float currT = micros();
  float deltaT = ( (float)(currT-prevT_fw) )/ 1.0e6;
  prevT_fw = currT;

//  error
  int pos = currentForwardPosition();
  int e = target - pos;

// pid vals
  float derivative = (e-ePrev_fw)/deltaT ;

//  pid signal
  float u = FORWARD_KP*e + FORWARD_KD*derivative;
//  motor values
  float pwr = fabs(u);
  if(pwr>VOLTAGE_CAP){
    pwr = VOLTAGE_CAP;
  }
  if(u<0){
    pwr = pwr * -1;
  }
  ePrev_fw = e;
  return pwr;
}


long prevT_ang = 0;
float ePrev_ang = 0;

float angularComponent(int target){
//  time dif
  float currT = micros();
  float deltaT = ( (float)(currT-prevT_ang) )/ 1.0e6;
  prevT_ang = currT;
//  error
  int e = target;

// pid vals
  float derivative = (e-ePrev_ang)/deltaT ;

//  pid signal
  float u = ANGULAR_KP*e + ANGULAR_KD*derivative;
//  motor values
  float pwr = fabs(u);
  if(pwr>VOLTAGE_CAP){
    pwr = VOLTAGE_CAP;
  }
  if(u<0){
    pwr = pwr * -1;
  }
  ePrev_ang = e;
  pwr = constrain(pwr, -ANGULAR_COMPONENT_LIMIT, ANGULAR_COMPONENT_LIMIT);

  return pwr;
}


void setSpeed(int option){
  VOLTAGE_CAP = option;
  ANGULAR_COMPONENT_LIMIT = VOLTAGE_CAP - 5;
}