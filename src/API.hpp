#include "ESP8266_Utils_APIREST.hpp"
#include "lightControl.hpp"
void getData(AsyncWebServerRequest *request)
{
   AsyncResponseStream *response = request->beginResponseStream("application/json");
    
   // obtendríamos datos de GPIO, estado...
   StaticJsonDocument<300> jsonDoc;
   jsonDoc["id"] = random(0,10);
   jsonDoc["status"] = random(0,2);
   serializeJson(jsonDoc, *response);
   
   request->send(response);
}

void setData(AsyncWebServerRequest * request, uint8_t *data, size_t len, size_t index, size_t total)
{
  String bodyContent = GetBodyContent(data, len);

  StaticJsonDocument<200> doc;
  DeserializationError error = deserializeJson(doc, bodyContent);
  if (error) { request->send(400); return;}
 
  int id = doc["id"];
  bool ledStatus = doc["status"];
  bool mqtt = doc["mqtt"];
  Serial.println(id);
  Serial.println(ledStatus);
  Serial.println(mqtt);
  setLightStatus(id,ledStatus,mqtt);
  request->send(200);
}
