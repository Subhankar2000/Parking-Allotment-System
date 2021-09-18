#include <DS3231.h>
#include <Wire.h>

DS3231  rtc(SDA, SCL);
long int a = 0 , b = 0 ;

const int buttonPin = A15;
const int buttonPositive = 30 ;
const int buttonNegative = 31 ;
int buttonState = 0;

void setup() {
  /*----BUTTON LOGIC-----*/
  pinMode(13,OUTPUT);
  pinMode(buttonPositive, OUTPUT);
  pinMode(buttonNegative, OUTPUT);
  digitalWrite(buttonPositive, HIGH);
  digitalWrite(buttonNegative, LOW);
  /*----BUTTON LOGIC-----*/

  Serial1.begin(9600);
  Serial.begin(9600);
  rtc.begin();
}

void loop() {

  /*----BUTTON LOGIC-----*/
  buttonState = analogRead(buttonPin);

  if (buttonState > 100) {
    /*----START SENDING THE MESSAGE BY CALLING A FUNCTION OR SOMETHING AND THEN RE-ROUTE THE FUNCTION TO SETUP-----*/
    digitalWrite(13,HIGH);
    /*-----MESSAGE------*/
//    delay(1000);
//    Serial1.println("AT+CMGF=1");
//    delay(1000);
//    Serial1.println("AT+CMGS=\"+918617375453\"\r");
//    delay(1000);
//    Serial1.print(rtc.getDateStr());
//    Serial1.print(" -- ");
//    Serial1.println(rtc.getTimeStr());
//    Serial1.println("");
//    Serial1.print("THE NUMBER OF CARS WENT OUT OF PARKING SPACE : ");
//    Serial1.print(10) ;
//    Serial1.println("");
//    Serial1.print("THE TOTAL AMOUNT COLLECTED : ");
//    Serial1.print(100) ;
//    Serial1.println("");
//    Serial1.print("THE NUMBER OF CARS STILL IN PARKING SPACE : ");
//    Serial1.print(20) ;
//    Serial1.println("");
//
//    delay(100);
//    Serial1.println((char)26);
//    delay(1000);
    /*-----MESSAGE------*/}
//  } else {
      digitalWrite(13,LOW);
//    /*----START THE LOOP SCREEN 1-----*/
//  }
  /*----BUTTON LOGIC-----*/
}
