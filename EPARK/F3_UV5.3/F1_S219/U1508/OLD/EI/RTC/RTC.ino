#include <DS3231.h>
#include <Wire.h>

DS3231  rtc(SDA, SCL);
long int a = 0 , b=0 ;
void setup()
{
  Serial.begin(9600);
  rtc.begin();
  
  
}

void loop()
{ 
  Serial.print(rtc.getDOWStr());
  Serial.print(" ");
  Serial.print(rtc.getDateStr());
  Serial.print(" -- ");
  Serial.println(rtc.getTimeStr());
  delay(1000);
}

