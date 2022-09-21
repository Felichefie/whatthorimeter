#include "whatthorimeter.h"

const int miliToSeconds = 1000;

float getPower(float voltage, float current){
  float power;
  power = voltage * current;
  return power;
}

double getEnergy(float power, double energy){
  //extern float energy;
  energy += power/(MINUTES * SECONDS);
  //energy /= (INTEGRATION_MS * INTEGRATION_SAMPLES);
  return energy;
}
