#include <Arduino.h>

const char* mqtt_server = "192.168.1.55";
void setLightStatus(int port,int status,bool shouldMqtt)
{
    Serial.println("SETTING LIGHT STATUS:");
    Serial.println(port);
    Serial.println(status);
    if(shouldMqtt){
        Serial.println("MQTT TODO:");
    }else{
        if(status == 0){
            Serial.println("GPIO PORT OFF");
            digitalWrite(port, LOW); 
        }else if(status == 1){
            Serial.println("GPIO PORT ON");
            digitalWrite(port, HIGH); 
        }
    }
}
void InitPins(){
    pinMode(16, OUTPUT); 
    pinMode(5, OUTPUT);
    pinMode(4, OUTPUT);
}