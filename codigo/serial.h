#ifndef SERIAL_H
#define SERIAL_H
#include "Arduino.h"

void setupSerialPort(void);
void printCurrent(float);
void printVoltage(float);
void printPower(float);
void printEnergy(double);


#endif
