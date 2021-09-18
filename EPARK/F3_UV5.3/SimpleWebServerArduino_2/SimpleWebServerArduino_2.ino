#include <SoftwareSerial.h>
#include <ArduinoJson.h>
#include <Keypad.h>

SoftwareSerial s(5,6);

const byte ROWS = 4; 
const byte COLS = 4; 

char hexaKeys[ROWS][COLS] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};
byte rowPins[ROWS] = {4, 7, 8, 9};
byte colPins[COLS] = {10, 11, 12, 13};
Keypad customKeypad = Keypad( makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS);

int count[4];

void setup()
{
  s.begin(115200);
  Serial.begin(115200);
}
 
void loop() {
  DynamicJsonBuffer jBuffer;
  JsonObject& root = jBuffer.createObject();

  char customKey = customKeypad.getKey();
  if(customKey == 'A' && count[0] < 5){
    (count[0])++;  
  }
  else if(customKey == 'B' && count[1] < 5){
    (count[1])++;  
  }
  else if(customKey == 'C' && count[2] < 5){
    (count[2])++;  
  }
  else if(customKey == 'D' && count[3] < 5){
    (count[3])++;  
  }
  else if(customKey == '3' && count[0] > 0){
    (count[0])--;  
  }
  else if(customKey == '6' && count[1] > 0){
    (count[1])--;  
  }
  else if(customKey == '9' && count[2] > 0){
    (count[2])--;  
  }
  else if(customKey == '#' && count[3] > 0){
    (count[3])--;  
  }
  else{
    }

  for(int i = 0; i < 4; i++)
  {
    root[(String(i))] = count[i];
  }
  
  root.prettyPrintTo(Serial);
  root.printTo(s);
  //delay(200);
  
//  Serial.println(s.available());
//  if(s.available() > 0)
//  {
//    root.printTo(s);
//  }
}
