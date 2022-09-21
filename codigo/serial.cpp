#include "serial.h"
#include "config.h"

void setupSerialPort(void) {
  Serial.begin(115200);
  delay(1000);
  pinMode(led_testigo, OUTPUT);
}

void printCurrent(float current){
  Serial.print("I: ");
  Serial.print(current);
  Serial.print(" .  "); 
}

void printVoltage(float voltage){
  Serial.print("V: ");
  Serial.print(voltage);
  Serial.print(" .  "); 
}

void printEnergy(double energy){
  Serial.print("E: ");
  Serial.print(energy, 4);
  Serial.print(" .  "); 
}

void printPower(float power){
  Serial.print("P: ");
  Serial.print(power);
  Serial.print(" .  "); 
}
