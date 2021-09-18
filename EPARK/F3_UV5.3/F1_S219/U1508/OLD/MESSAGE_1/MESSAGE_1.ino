/*
   THIS IS THE HARDWARE SERIAL CODE FOR GSM SIM900A MODULE
   CONNECTS VIA serial 1 OF ARDUINO MEGA , HARDWARE SERIAL
   SENDS A FORMATTED MESSAGE TO +91-8617375453
*/

void setup()
{
  Serial1.begin(9600);
  Serial.begin(9600);

  /*-----MESSAGE------*/
  Serial1.println("AT+CMGF=1");
  delay(1000);
  Serial1.println("") ;
  Serial1.print("AT+CMGS=\"+91"
  Serial1.print(ph_textfield[0]);
  Serial1.print(ph_textfield[1]);
  Serial1.print(ph_textfield[2]);
  Serial1.print(ph_textfield[3]);
  Serial1.print(ph_textfield[4]);
  Serial1.print(ph_textfield[5]);
  Serial1.print(ph_textfield[6]);
  Serial1.print(ph_textfield[7]);
  Serial1.print(ph_textfield[8]);
  Serial1.print(ph_textfield[9]);
  Serial1.print("\"\r");
  delay(1000);
  Serial1.println("");
  Serial1.print("YOUR PIN : ");
  Serial1.print(number[0]) ;
  Serial1.print(number[1]) ;
  Serial1.print(number[2]) ;
  Serial1.print(number[4]) ;
  Serial1.println("");
  Serial1.print("YOUR VEHCILE TYPE");
  Serial1.print(100) ;
  Serial1.println("");
  Serial1.print("THE NUMBER OF CARS STILL IN PARKING SPACE : ");
  Serial1.print(20) ;
  Serial1.println("");

  delay(100);
  Serial1.println((char)26);
  delay(1000);
  /*-----MESSAGE------*/

}

void loop()
{
  /* THE LOOP IS NOT NEEDED */
  /* EXECUTE THE MSG BLOCK ONCE WHEN NEEDED */
}

