// set RX and TX pins
  HardwareSerial Serial1(PB7, PB6);
   
// the setup function runs once when you press reset or power the board
  void setup() {
  Serial1.begin(9600); // initialize Serial1
  }
   
// the loop function runs over and over again forever
  void loop()
  {
  // send "Hello World" message through alternative pins of Serial1
  Serial1.println("Hello World");
  // wait one second
  delay(1000);
  }
