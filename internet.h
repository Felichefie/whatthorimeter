#ifndef INTERNET_H
#define INTERNET_H

#include "WiFi.h"
#include <PubSubClient.h>
#include "Arduino.h"
#include "config.h"
#include <WiFiClientSecure.h>
#include <ArduinoJson.h>
#include "certs_real.h"


bool connectWIFI(void);
bool connectAWS(void);
unsigned long reconnectWifi();
void messageHandler(char*, byte*, unsigned int);
void publishMessage(float, float, float, float);


#endif
