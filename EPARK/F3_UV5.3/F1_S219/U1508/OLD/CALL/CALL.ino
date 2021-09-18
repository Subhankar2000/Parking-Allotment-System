//ERFINDER CODE
#include <SoftwareSerial.h>

SoftwareSerial mySerial(50,51); // RX, TX

void setup()
{

Serial.begin(9600);


}

void loop() // run over and over
{
  Serial.println("Calling through GSM Modem");

// set the data rate for the SoftwareSerial port
mySerial.begin(9600);
delay(2000);
mySerial.println("ATD8617375453;"); // ATDxxxxxxxxxx; -- watch out here for semicolon at the end!!

Serial.println("Called ATD8617375453");
// print response over serial port
if (mySerial.available())
Serial.write(mySerial.read());
}

