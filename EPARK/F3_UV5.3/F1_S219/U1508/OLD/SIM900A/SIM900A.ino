/*THIS TUTORIAL USED GSM SIM900A MINI V3.9.2
 
  Connect 5VT to D9 and 5VR to D10
  Feed GSM SIM900A with Arduino's 5V

  Code by IDAYU SABRI - MYBOTIC
*/

#include <SoftwareSerial.h>

char msg;
char call;

void setup()
{
  Serial1.begin(9600);   // Setting the baud rate of GSM Module  
  Serial.begin(9600);    // Setting the baud rate of Serial Monitor (Arduino)
  Serial.println("GSM SIM900A BEGIN");
  Serial.println("Enter character for control option:");
  Serial.println("h : to disconnect a call");
  Serial.println("i : to receive a call");
  Serial.println("s : to send message");
  Serial.println("c : to make a call");  
  Serial.println("e : to redial");
  Serial.println();
  delay(100);
}

void loop()
{  
  if (Serial.available()>0)
   switch(Serial.read())
  {
    case 's':
      SendMessage();
      break;
    case 'c':
      MakeCall();
      break;
    case 'h':
      HangupCall();
      break;
    case 'e':
      RedialCall();
      break;
    case 'i':
      ReceiveCall();
      break;
  }
 if (Serial1.available()>0)
 Serial.write(Serial1.read());
}

void SendMessage()
{
  Serial1.println("AT+CMGF=1");    //Sets the GSM Module in Text Mode
  delay(1000);  // Delay of 1000 milli seconds or 1 second
  Serial1.println("AT+CMGS=\"+919563349171\"\r"); // Replace x with mobile number
  delay(1000);
  Serial1.println("This is a SMS from SIM Module");// The SMS text you want to send
  delay(100);
   Serial1.println((char)26);// ASCII code of CTRL+Z
  delay(1000);
}

void ReceiveMessage()
{
  Serial1.println("AT+CNMI=2,2,0,0,0"); // AT Command to recieve a live SMS
  delay(1000);
  if (Serial1.available()>0)
  {
    msg=Serial1.read();
    Serial.print(msg);
  }
}

void MakeCall()
{
  Serial1.println("ATD+919563349171;"); // ATDxxxxxxxxxx; -- watch out here for semicolon at the end!!
  Serial.println("Calling  "); // print response over serial port
  delay(1000);
}


void HangupCall()
{
  Serial1.println("ATH");
  Serial.println("Hangup Call");
  delay(1000);
}

void ReceiveCall()
{
  Serial1.println("ATA");
  delay(1000);
  {
    call=Serial1.read();
    Serial.print(call);
  }
}

void RedialCall()
{
  Serial1.println("ATDL");
  Serial.println("Redialing");
  delay(1000);
}
