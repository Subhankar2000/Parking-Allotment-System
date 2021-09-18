void setup() {
  pinMode(PA5, OUTPUT);
  pinMode(PC13, INPUT);
}

void loop() {
  if(digitalRead(PC13)) // read button
  {
  digitalWrite(PA5, HIGH); // turn the LED on (HIGH is the voltage level)
  delay(100); // wait 100ms
  digitalWrite(PA5, LOW); // turn the LED off by making the voltage LOW
  delay(100); // wait 100ms
  }
  else
  {
  digitalWrite(PA5, HIGH); // turn the LED on (HIGH is the voltage level)
 
delay(500); // wait 500ms
  digitalWrite(PA5, LOW); // turn the LED off by making the voltage LOW
  delay(500); // wait 500ms
  }
  }
