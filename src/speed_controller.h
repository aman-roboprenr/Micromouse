#include <Arduino.h>
#include <encoders.h>
#pragma once

const int VOLTAGE_CAP = 80;

//  pid consts
const float fw_kp = 1;
const float fw_ki = 2;
const float fw_kd = 0;

const float ang_kp = 1;
const float ang_ki = 0;
const float ang_kd = 0;

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
  float integral = eIntegral_fw + e*deltaT;

//  pid signal
  float u = fw_kp*e + fw_ki*integral + fw_kd*derivative;
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