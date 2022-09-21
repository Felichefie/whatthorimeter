#include "adc.h"

float readCurrent(void){
  int data;
  float current;
  data = analogRead(portI);
  current = data + 150;
  current = (current * 0.024193) - 49.5403;
  return current;
}

float readVoltage(void){
  int data;
  float voltage;
  data = analogRead(portV);
  voltage = data;
  voltage = data / 40.95;
  return voltage;
}
