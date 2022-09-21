#include "internet.h"

#include <Preferences.h>

extern WiFiClientSecure net;
extern PubSubClient client;

bool connectWIFI(void){
  WiFi.mode(WIFI_STA);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.println("Connecting to Wi-Fi");
  while (WiFi.status() != WL_CONNECTED){
    delay(500);
    Serial.print(".");
  }
  Serial.println("Connected to Wi-Fi");
  return true;
}

unsigned long reconnectWifi(void) {
  unsigned long currentMillis = millis();
  static unsigned long previousMillis = 0;
  unsigned long interval = 30000;
  if ((WiFi.status() != WL_CONNECTED) && (currentMillis - previousMillis >= interval)) {
    Serial.print(millis());
    Serial.println("Reconnecting to WiFi...");
    WiFi.disconnect();
    WiFi.reconnect();
    previousMillis = currentMillis;
  }
}


bool connectAWS(void){  
  // Configure WiFiClientSecure to use the AWS IoT device credentials
  net.setCACert(AWS_CERT_CA);
  net.setCertificate(AWS_CERT_CRT);
  net.setPrivateKey(AWS_CERT_PRIVATE);
 
  // Connect to the MQTT broker on the AWS endpoint we defined earlier
  if(client.connected()){
    client.disconnect(); 
  }
  client.setServer(AWS_IOT_ENDPOINT, 8883);
 
  // Create a message handler
  client.setCallback(messageHandler);
 
  Serial.println("Connecting to AWS IOT");
 
  while (!client.connect(THINGNAME)){
    Serial.print(".");
    delay(100);
  }
 
  if (!client.connected()){
    Serial.println("AWS IoT Timeout!");
    return false;
  }
 
  // Subscribe to a topic
  client.subscribe(AWS_IOT_SUBSCRIBE_TOPIC);
 
  Serial.println("AWS IoT Connected!");
  return true;
}

void messageHandler(char* topic, byte* payload, unsigned int length){
  extern Preferences preferences;
  extern double energy;
 
  StaticJsonDocument<200> doc;
  deserializeJson(doc, payload);
  String message = doc["message"];    
  if(message.equals(RESET_ENERGY)){
    Serial.print(topic);
    Serial.println(message);
    energy = 0.00;
    preferences.putDouble("WH", energy);
  }
}

void publishMessage(float voltage, float current, float power, float energy){
  DynamicJsonDocument doc(512);
  JsonObject data = doc.createNestedObject("data");
  
  data["voltage"] = voltage;
  data["current"] = current;
  data["power"] = power;
  data["energy"] = energy;
  data["team"] = TEAM_NUMBER;
  
  char jsonBuffer[512];
  serializeJson(doc, jsonBuffer); // print to client
 
  client.publish(AWS_IOT_PUBLISH_TOPIC, jsonBuffer);
}
