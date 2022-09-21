#ifndef CONFIG_H
#define CONFIG_H

const int MINUTES = 60;
const int SECONDS = 60;
const int INTEGRATION_MS = 500;
const int INTEGRATION_SAMPLES = 10;

#define THINGNAME "vehiculo1"
#define TEAM_NUMBER 1

//#define THINGNAME "vehiculo2"
//#define TEAM_NUMBER 2

#define AWS_IOT_PUBLISH_TOPIC   "energia"
#define AWS_IOT_SUBSCRIBE_TOPIC "energia"
#define RESET_ENERGY "reset energy"

const int portV = 34;
const int portI = 35;

const int led_testigo = 2;

const char WIFI_SSID [] = "jardin";
const char WIFI_PASSWORD [] = "alexjrTplink1_";

const char AWS_IOT_ENDPOINT [] = "a2kqc7v47ghmtd-ats.iot.us-west-1.amazonaws.com";


#endif
