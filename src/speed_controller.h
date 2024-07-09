#include <Arduino.h>
#include <encoders.h>
#pragma once

const int VOLTAGE_CAP = 180;

//  pid consts
const float FORWARD_KP = 2;
const float FORWARD_KI = 0.0000001;
const float FORWARD_KD = 0;

const float ANGULAR_KP = 2.8;
const float ANGULAR_KI = 0;
const float ANGULAR_KD = 0.8;


const float ANGULAR_COMPONENT_LIMIT = 80;

long prevT_fw = 0;
float ePrev_fw = 0;
float eIntegral_fw = 0;

float forwardComponent(int target){
//  time dif
  float currT = micros();
  float deltaT = ( (float)(currT-prevT_fw) )/ 1.0e6;

//  error
  int pos = currentForwardPosition();
  int e = target - pos;

// pid vals
  float derivative = (e-ePrev_fw)/deltaT ;
  eIntegral_fw = eIntegral_fw + e*deltaT;

//  pid signal
  float u = FORWARD_KP*e + FORWARD_KI*eIntegral_fw + FORWARD_KD*derivative;
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
float eIntegral_ang = 0;

float angularComponent(int target){
//  time dif
  float currT = micros();
  float deltaT = ( (float)(currT-prevT_ang) )/ 1.0e6;

//  error
  int e = target;

// pid vals
  float derivative = (e-ePrev_ang)/deltaT ;
  eIntegral_ang = eIntegral_ang + e*deltaT;

//  pid signal
  float u = ANGULAR_KP*e + ANGULAR_KI*eIntegral_ang + ANGULAR_KD*derivative;
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


