void setup()
{
  Serial1.begin(9600);   
  Serial.begin(9600);    

  Serial1.println("AT+CMGF=1");    
  delay(1000);  
  Serial1.println("AT+CMGS=\"+918617375453\"\r"); 
  delay(1000);
  
  Serial1.println("");
  Serial1.print("THE NUMBER OF CARS WENT OUT OF PARKING SPACE : ");
  Serial1.print(10) ;
  Serial1.println("");
  Serial1.print("THE TOTAL AMOUNT COLLECTED : ");
  Serial1.print(100) ;
  Serial1.println("");
  Serial1.print("THE NUMBER OF CARS STILL IN PARKING SPACE : ");
  Serial1.print(20) ;
  Serial1.println("");
  
  delay(100);
  Serial1.println((char)26);
  delay(1000);
}

void loop()
{
  
}
