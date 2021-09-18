#include <SPI.h>
#include <SD.h>

File myFile;

struct car {
  int yes = 0 ;
  int slot ;
  char ph_number[10] ;
  char number[7] ;
  long int sTime ;
  int type ;

  char otp[4] ;

} c[4][5] ;


int phn , nn , filei ;
int counter[4] ;
int C_IN ;
int C_OUT ;

void setup() {
  Serial.begin(9600);
  while (!Serial) {
  }

  Serial.print("Initializing SD card...");

  if (!SD.begin(10)) {
    Serial.println("initialization failed!");
    while (1);
  }
  Serial.println("initialization done.");

  myFile = SD.open("c0.txt");
  if (myFile) {
    for ( filei = 0 ; filei < 5 ; filei++ ) {
      myFile.print(filei);
      myFile.print(",");
      myFile.print(c[0][filei].yes);
      myFile.print(",");
      myFile.print(c[0][filei].slot);
      myFile.print(",");
      for ( phn = 0 ; phn < 10 ; phn++)
        myFile.print(c[0][filei].ph_number[phn]);
      myFile.print(",");
      for ( nn = 0 ; nn < 7 ; nn++)
        myFile.print(c[0][filei].number[nn]);
      myFile.print(",");
      myFile.print(c[0][filei].sTime);
      myFile.print(",");
      myFile.print(c[0][filei].type);
      myFile.print("#");
    }
    myFile.close();
    Serial.println("done.");
  } else {
    Serial.println("error opening c0.txt");
  }

myFile = SD.open("c1.txt", FILE_WRITE);
  if (myFile) {
    for ( filei = 0 ; filei < 5 ; filei++ ) {
      myFile.print(filei);
      myFile.print(",");
      myFile.print(c[1][filei].yes);
      myFile.print(",");
      myFile.print(c[1][filei].slot);
      myFile.print(",");
      for ( phn = 0 ; phn < 10 ; phn++)
        myFile.print(c[1][filei].ph_number[phn]);
      myFile.print(",");
      for ( nn = 0 ; nn < 7 ; nn++)
        myFile.print(c[1][filei].number[nn]);
      myFile.print(",");
      myFile.print(c[1][filei].sTime);
      myFile.print(",");
      myFile.print(c[1][filei].type);
      myFile.print("#");
    }
    myFile.close();
    Serial.println("done.");
  } else {
    Serial.println("error opening c1.txt");
  }

myFile = SD.open("c2.txt", FILE_WRITE);
  if (myFile) {
    for ( filei = 0 ; filei < 5 ; filei++ ) {
      myFile.print(filei);
      myFile.print(",");
      myFile.print(c[2][filei].yes);
      myFile.print(",");
      myFile.print(c[2][filei].slot);
      myFile.print(",");
      for ( phn = 0 ; phn < 10 ; phn++)
        myFile.print(c[2][filei].ph_number[phn]);
      myFile.print(",");
      for ( nn = 0 ; nn < 7 ; nn++)
        myFile.print(c[2][filei].number[nn]);
      myFile.print(",");
      myFile.print(c[2][filei].sTime);
      myFile.print(",");
      myFile.print(c[2][filei].type);
      myFile.print("#");
    }
    myFile.close();
    Serial.println("done.");
  } else {
    Serial.println("error opening c2.txt");
  }

  myFile = SD.open("c3.txt", FILE_WRITE);
  if (myFile) {
    for ( filei = 0 ; filei < 5 ; filei++ ) {
      myFile.print(filei);
      myFile.print(",");
      myFile.print(c[3][filei].yes);
      myFile.print(",");
      myFile.print(c[3][filei].slot);
      myFile.print(",");
      for ( phn = 0 ; phn < 10 ; phn++)
        myFile.print(c[3][filei].ph_number[phn]);
      myFile.print(",");
      for ( nn = 0 ; nn < 7 ; nn++)
        myFile.print(c[3][filei].number[nn]);
      myFile.print(",");
      myFile.print(c[3][filei].sTime);
      myFile.print(",");
      myFile.print(c[3][filei].type);
      myFile.print("#");
    }
    myFile.close();
    Serial.println("done.");
  } else {
    Serial.println("error opening c3.txt");
  }

  myFile = SD.open("counter[0].txt", FILE_WRITE);
  if (myFile) {
    myFile.print(counter[0]);
  }else {
    Serial.println("error opening counter[0].txt");
  }

myFile = SD.open("counter[1].txt", FILE_WRITE);
  if (myFile) {
    myFile.print(counter[1]);
  }else {
    Serial.println("error opening counter[1].txt");
  }

  myFile = SD.open("counter[2].txt", FILE_WRITE);
  if (myFile) {
    myFile.print(counter[2]);
  }else {
    Serial.println("error opening counter[2].txt");
  }

myFile = SD.open("counter[3].txt", FILE_WRITE);
  if (myFile) {
    myFile.print(counter[3]);
  }else {
    Serial.println("error opening counter[3].txt");
  }

myFile = SD.open("C_IN.txt", FILE_WRITE);
  if (myFile) {
    myFile.print(C_IN);
  }else {
    Serial.println("error opening C_IN.txt");
  }

  myFile = SD.open("C_OUT.txt", FILE_WRITE);
  if (myFile) {
    myFile.print(C_OUT);
  }else {
    Serial.println("error opening C_OUT.txt");
  }



  
  myFile = SD.open("test.txt");
  if (myFile) {
    Serial.println("test.txt:");

    while (myFile.available()) {
      Serial.write(myFile.read());
    }

    myFile.close();
  } else {
    Serial.println("error opening test.txt");
  }
}

void loop() {

}
