#include <Wire.h>
#include <ds3231.h>

ts t; //ts is a struct findable in ds3231.h
long long int unixtime1 ;

void setup() {
  Serial.begin(9600);
    Wire.setSCL(PB6); // alternative pinout of I2C1_SCL - PB6 (Morpho con) instead of PB8 (D15) 
 
Wire.setSDA(PB7); // alternative pinout of I2C1_SDA - PB7 (D10) instead of PB9 (D14) 
  Wire.begin(8);
  Wire.onReceive(receiveEvent);
  Wire.onRequest(requestEvent);
  DS3231_init(DS3231_INTCN); 
  
}

void loop()
{
  Wire.onReceive(receiveEvent);
  Wire.onRequest(requestEvent);
  delay(100);
  DS3231_get(&t); //get the value and pass to the function the pointer to t, that make an lower memory fingerprint and faster execution than use return
  //DS3231_get() will use the pointer of t to directly change t value (faster, lower memory used)
  DS3231_get(&t);
  Serial.print("Day : ");
  Serial.print(t.mon); //just print some data
  Serial.print("/");
  Serial.print(t.mday);
  Serial.print("/");
  Serial.println(t.year+100);
  Serial.print("Hour : ");
  Serial.print(t.hour);
  Serial.print(":");
  Serial.print(t.min);
  Serial.print(".");
  Serial.println(t.sec);
#ifdef CONFIG_UNIXTIME
  Serial.print("Timestamp : ");
  unixtime1 = t.unixtime+3154000000 ;
  Serial.print(unixtime1);
#endif
  Serial.println();
  Serial.println();
  delay(1000);
}

void receiveEvent(int howMany) {
  while (0 < Wire.available())
  {
    char c = Wire.read();      /* receive byte as a character */
    Serial.print(c);           /* print the character */
  }
  Serial.println();             /* to newline */
}

void requestEvent() {
  Wire.write("Hello NodeMCU");  /*send string on request */
}
