#include <SoftwareSerial.h>

SoftwareSerial gsm(9,10) ;

void setup(){
  Serial.begin(9600) ;
  gsm.begin(9600) ;
  gsm.println("AT+CMGF=1") ;
  delay(1000) ;
  gsm.println("AT+CMGS=\"+918617375453\"r") ;
  delay(1000) ;
  gsm.println("HELLO !") ;
  delay(100) ;
  gsm.println((char)26) ;
}

void loop(){
  
}
