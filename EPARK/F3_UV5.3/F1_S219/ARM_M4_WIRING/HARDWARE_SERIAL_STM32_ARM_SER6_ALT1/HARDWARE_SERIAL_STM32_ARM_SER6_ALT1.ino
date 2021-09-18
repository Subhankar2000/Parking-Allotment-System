// set RX and TX pins
  HardwareSerial Serial6(PC7, PC6);
   
// the setup function runs once when you press reset or power the board
  void setup() 
  {
  Serial6.begin(9600); // initialize Serial6
  }
   
// the loop function runs over and over again forever
  void loop()
  {
  // send "Hello World" message through alternative pins of Serial6
  Serial6.println("Hello World");
  // wait one second
  delay(1000);
  }
 
