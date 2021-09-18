#include <LiquidCrystal.h>

// initialize the library by associating any needed LCD interface pin
// with the arduino pin number it is connected to

LiquidCrystal lcd(51,50,48,49,46,47);

void setup() {
  pinMode(53, OUTPUT);
  pinMode(52, OUTPUT);
  pinMode(44, OUTPUT);
  pinMode(45, OUTPUT);
  digitalWrite(53, LOW);
  digitalWrite(52, HIGH);
  digitalWrite(44, HIGH);
  digitalWrite(53, LOW);
  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  // Print a message to the LCD.
  lcd.print("hello, world!");
}

void loop() {
  // set the cursor to column 0, line 1
  // (note: line 1 is the second row, since counting begins with 0):
  lcd.setCursor(0, 1);
  // print the number of seconds since reset:
  lcd.print(millis() / 1000);
}

