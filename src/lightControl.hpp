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
    pinMode(16, OUTPUT); //led azul esp8266
    pinMode(2, OUTPUT); //enchufe directo rojo 
    pinMode(5, OUTPUT); // enchufe normal directo
    pinMode(4, OUTPUT); //el otro con regleta no tan directo.
    pinMode(0, OUTPUT); // OTRO
}
void ResetState(){
    digitalWrite(16, LOW); 
    digitalWrite(2, LOW); 
    digitalWrite(5, LOW); 
    digitalWrite(4, LOW); 
    digitalWrite(0, LOW); 
}