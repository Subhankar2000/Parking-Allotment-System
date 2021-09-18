#include <ArduinoJson.h>

//HardwareSerial Seria2(D0,D1);

int count[4]={1,2,3,4};

void setup()
{
  Serial2.begin(115200);
  Serial.begin(115200);
}
 
void loop() {
  
  DynamicJsonBuffer jBuffer;
  JsonObject& root = jBuffer.createObject();

  for(int i = 0; i < 4; i++)
  {
    root[(String(i))] = count[i];
  }
  
  root.prettyPrintTo(Serial);
  root.printTo(Serial);
  
//  for(int i = 0; i < 4; i++)
//  {
//  Serial.println(count[i]) ;
//  
//  }
//  
  
  //delay(200);
  
//  Serial.println(s.available());
//  if(s.available() > 0)
//  {
//    root.printTo(s);
//  }
}
