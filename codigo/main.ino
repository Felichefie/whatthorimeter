#include "config.h"
#include "serial.h"
#include "adc.h"
#include "digital.h"
#include "whatthorimeter.h"
#include "internet.h"
#include <Preferences.h>


WiFiClientSecure net = WiFiClientSecure();
PubSubClient client(net);

float v=0, v_instant=0;
float i=0, i_instant=0;
float p=0, p_instant=0;
double energy;
int samples;

unsigned long previousMillis = 0;
unsigned long interval = 10000;
unsigned long currentMillis;
bool isConnected;

TaskHandle_t Tarea1;

Preferences preferences;

void setup() {
  isConnected = false;
  energy = 0.0;
  preferences.begin("WhatHorimetro", false);
  energy = preferences.getDouble("WH",0);
  setupSerialPort();
  xTaskCreatePinnedToCore(
                    TareaADC,   /* función que realiza ejecuta en la tarea. */
                    "Tarea1",   /* nombre de la tarea. */
                    10000,      /* Tamaña del Stack patra la tarea */
                    NULL,       /* parametros que se envían a la tarea */
                    1,          /* prioridad de la tarea */
                    &Tarea1,    /* Manejador de la tarea1 */
                    0);         /* Se asigna al núcleo 0 */
  
  Serial.println("Principal ejecutando en nucleo: ");
  Serial.print(xPortGetCoreID());
  Serial.println("");

  connectWIFI();
  connectAWS();
  isConnected = true;
  samples = 0;
}

void loop() {
  if((WiFi.status() == WL_CONNECTED)){
      if(isConnected == true) {
        publishMessage(v, i, p, energy);
        printCurrent(i);
        printVoltage(v);
        printPower(p);
        printEnergy(energy);
        Serial.println("");
      } else {
        connectAWS();
        isConnected = true;
        samples = 0;
      }
  }
  currentMillis = millis();
  if ((WiFi.status() != WL_CONNECTED) && ((currentMillis - previousMillis) >= interval)) {
    Serial.print(millis());
    Serial.println("Reconnecting to WiFi...");
    WiFi.disconnect();
    WiFi.reconnect();
    isConnected = false;
    previousMillis = currentMillis;
  }
  client.loop();
  delay(INTEGRATION_MS * INTEGRATION_SAMPLES);
  if(isConnected == true){
    ledToggle();
  }
}

void TareaADC( void * pvParameters ){
  Serial.print("Tarea uno corriendo en el núcleo: ");
  Serial.println(xPortGetCoreID());
  Serial.println("");
  
  while(true){
    v_instant += readVoltage();
    i_instant += readCurrent();
    p_instant += getPower(v, i);
    delay(INTEGRATION_MS);
    if(samples == INTEGRATION_SAMPLES){
      v = v_instant / INTEGRATION_SAMPLES;
      i = i_instant / INTEGRATION_SAMPLES;
      p = p_instant / INTEGRATION_SAMPLES;
      energy = getEnergy(p, energy);
      preferences.putDouble("WH", energy);
      samples = 0; v_instant = 0;
      i_instant = 0; p_instant = 0;
    }
    samples++;
  }
}
