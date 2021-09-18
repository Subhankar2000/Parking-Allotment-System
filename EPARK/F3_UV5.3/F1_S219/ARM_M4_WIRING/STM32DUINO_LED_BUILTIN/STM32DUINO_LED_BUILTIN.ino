/ the setup function runs once when you press reset or power the board
  void setup() 
 
{
  // initialize digital pin PC10 as an output.
  pinMode(PA5, OUTPUT);
  }
   
// the loop function runs over and over again forever
  void loop() 
  {
 
digitalWrite(PA5, HIGH); // turn the LED on (HIGH is the voltage level)
  delay(1000); // wait 1000ms
  digitalWrite(PA5, LOW); // turn the LED off by making the voltage LOW
  delay(1000); // wait 1000ms
 
}
