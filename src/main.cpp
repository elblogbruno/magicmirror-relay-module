#include <ESP8266WiFi.h>
#include <ESPAsyncWebServer.h>
#include <FS.h>
#include <ArduinoJson.h>
#include <ESP8266mDNS.h>
 
#include "config.h"  // Sustituir con datos de vuestra red
#include "API.hpp"
#include "Server.hpp"
#include "ESP8266_Utils.hpp"

#include <PubSubClient.h>


WiFiClient espClient;
PubSubClient client(espClient);
long lastMsg = 0;
char msg[50];
int value = 0;
// Callback function header
void callback(char* topic, byte* payload, unsigned int length);

void setup(void)
{
	Serial.begin(9600);
	SPIFFS.begin();
	ConnectWiFi_STA(true);
	InitServer();
	InitPins();
  ResetState();
  // Iniciar mDNS a direccion esp8266.local
   if (!MDNS.begin("relay")) 
   {             
     Serial.println("Error iniciando mDNS");
   }
   Serial.println("mDNS iniciado");
	Serial.println("Connecting to MQTT Server");
  	Serial.println(mqtt_server);
  	client.setServer(mqtt_server, 1883);
  	client.setCallback(callback);
}

void callback(char* topic, byte* payload, unsigned int length) {
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("] ");
  for (int i = 0; i < length; i++) {
    Serial.print((char)payload[i]);
  }
  Serial.println();
  // Switch on the LED if an 1 was received as first character
  if ((char)payload[0] == '1') {
    digitalWrite(16, LOW);  
     //client.publish("GPIO2", "TURNING LIGHT OFF");
    Serial.print("TURNING LIGHT OFF");// Turn the LED on (Note that LOW is the voltage level
    // but actually the LED is on; this is because
    // it is acive low on the ESP-01)
  } else if((char)payload[0] == '6'){
     digitalWrite(16, HIGH); 
     Serial.print("TURNING LIGHT ON"); 
      //client.publish("GPIO2", "TURNING LIGHT ON");
  }
  if((char)payload[0] == '2') {
    digitalWrite(5, LOW);
     //client.publish("GPIO2", "TURNING LIGHT OFF");
    Serial.print("TURNING PRINTER OFF"); // Turn the LED off by making the voltage HIGH
  }else if((char)payload[0] == '7'){
     digitalWrite(5, HIGH);
     Serial.print("TURNING PRINTER ON");
      //client.publish("GPIO2", "TURNING LIGHT ON");  
  }
 if((char)payload[0] == '3') {
    digitalWrite(4, LOW);
     //client.publish("GPIO2", "TURNING LIGHT OFF");
    Serial.print("TURNING LIGHT OFF"); // Turn the LED off by making the voltage HIGH
  }else if((char)payload[0] == '8'){
     //client.publish("GPIO2", "TURNING LIGHT ON");
     digitalWrite(4, HIGH);  
     Serial.print("TURNING LIGHT ON");
  }
  if((char)payload[0] == '4') {
    digitalWrite(0, LOW); //CONTROLA EL ENCHUFE ALTERNO
    //client.publish("GPIO2", "TURNING LIGHT OFF");
    Serial.print("TURNING LIGHT OFF"); // Turn the LED off by making the voltage HIGH
  }else if((char)payload[0] == '9'){
     digitalWrite(0, HIGH); 
     Serial.print("TURNING LIGHT ON"); 
     //client.publish("GPIO2", "TURNING LIGHT ON");
  }
  if((char)payload[0] == '5') {
    digitalWrite(2, LOW); //CONTROLA EL ENCHUFE directo ROJO
    //client.publish("GPIO2", "TURNING LIGHT OFF");
    Serial.print("TURNING LIGHT OFF"); // Turn the LED off by making the voltage HIGH
  }else if((char)payload[0] == '10'){
     digitalWrite(2, HIGH); 
     Serial.print("TURNING LIGHT ON"); 
     //client.publish("GPIO2", "TURNING LIGHT ON");
  }
}
 
void reconnect() {
  // Loop until we're reconnected
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    // Attempt to connect
    if (client.connect("ESP8266Client1")) {
      Serial.println("connected");
      // Once connected, publish an announcement...
      client.publish("PRINTER", "Hello");
      // ... and resubscribe
      client.subscribe("PRINTER");
      Serial.println("subscribed: " + client.state());
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
}
 
void loop() { 
  if (!client.connected()) {
    reconnect();
  }
  client.loop();
}