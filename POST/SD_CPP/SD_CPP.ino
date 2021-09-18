#include <SPI.h>
#include "SdFat.h"
#include "sdios.h"
#include <SD.h>

const uint8_t chipSelect = SS;
SdFat sd;
ArduinoOutStream cout(Serial);

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
int counter[4] , cn ;
int C_IN ;
int C_OUT ;

void setup() {
  Serial.begin(230400);
  while (!Serial) {
  }

  cout << "\n-------------------------------------------------\n" ;
  cout << "INITILIZING SD CARD TO WRITE THE DETAILS IN THE RESPECTIVE FILES" ;

  if (!sd.begin(chipSelect, SD_SCK_MHZ(50))) {
    cout << "ERROR\n CANNOT OPEN SD CARD" ;
    sd.initErrorHalt();
  }
  cout << "INITIALIZATION OF SD CARD DONE !\n WRITING FILES TO SD CARD" ;
  cout << "DUMPING THE DATA FROM THE BUS !" ;

  cout << "\nTHE DATA WRITTEN INTO c0.epark IS : " ;
  ofstream sdout("c0.epark", ios::binary | ios::trunc);
  for ( filei = 0 ; filei < 5 ; filei++ ) {
    sdout << filei << "," << c[0][filei].yes << "," << c[0][filei].slot << "," ;
    cout << filei << "," << c[0][filei].yes << "," << c[0][filei].slot << "," ;
    for ( phn = 0 ; phn < 10 ; phn++) {
      sdout << c[0][filei].ph_number[phn] ;
      cout << c[0][filei].ph_number[phn] ;
    }
    sdout << "," ; cout << "," ;
    for ( nn = 0 ; nn < 7 ; nn++) {
      sdout << c[0][filei].number[nn] ;
      cout << c[0][filei].number[nn] ;
    }
    sdout << "," ; cout << "," ;
    sdout << c[0][filei].sTime << "," << c[0][filei].type << "#" ;
    cout << c[0][filei].sTime << "," << c[0][filei].type << "#" ;
  }
  sdout.close() ;

  cout << "\nTHE DATA WRITTEN INTO c1.epark IS : " ;
  ofstream sdout1("c1.epark", ios::binary | ios::trunc);
  for ( filei = 0 ; filei < 5 ; filei++ ) {
    sdout1 << filei << "," << c[1][filei].yes << "," << c[1][filei].slot << "," ;
    cout << filei << "," << c[1][filei].yes << "," << c[1][filei].slot << "," ;
    for ( phn = 0 ; phn < 10 ; phn++) {
      sdout1 << c[1][filei].ph_number[phn] ;
      cout << c[1][filei].ph_number[phn] ;
    }
    sdout1 << "," ; cout << "," ;
    for ( nn = 0 ; nn < 7 ; nn++) {
      sdout1 << c[1][filei].number[nn] ;
      cout << c[1][filei].number[nn] ;
    }
    sdout1 << "," ; cout << "," ;
    sdout1 << c[1][filei].sTime << "," << c[1][filei].type << "#" ;
    cout << c[1][filei].sTime << "," << c[1][filei].type << "#" ;
  }
  sdout1.close() ;

  cout << "\nTHE DATA WRITTEN INTO c2.epark IS : " ;
  ofstream sdout2("c2.epark", ios::binary | ios::trunc);
  for ( filei = 0 ; filei < 5 ; filei++ ) {
    sdout2 << filei << "," << c[2][filei].yes << "," << c[2][filei].slot << "," ;
    cout << filei << "," << c[2][filei].yes << "," << c[2][filei].slot << "," ;
    for ( phn = 0 ; phn < 10 ; phn++) {
      sdout2 << c[2][filei].ph_number[phn] ;
      cout << c[2][filei].ph_number[phn] ;
    }
    sdout2 << "," ; cout << "," ;
    for ( nn = 0 ; nn < 7 ; nn++) {
      sdout2 << c[2][filei].number[nn] ;
      cout << c[2][filei].number[nn] ;
    }
    sdout2 << "," ; cout << "," ;
    sdout2 << c[2][filei].sTime << "," << c[2][filei].type << "#" ;
    cout << c[2][filei].sTime << "," << c[2][filei].type << "#" ;
  }
  sdout2.close() ;

  cout << "\nTHE DATA WRITTEN INTO c3.epark IS : " ;
  ofstream sdout3("c3.epark", ios::binary | ios::trunc);
  for ( filei = 0 ; filei < 5 ; filei++ ) {
    sdout3 << filei << "," << c[3][filei].yes << "," << c[3][filei].slot << "," ;
    cout << filei << "," << c[3][filei].yes << "," << c[3][filei].slot << "," ;
    for ( phn = 0 ; phn < 10 ; phn++) {
      sdout3 << c[3][filei].ph_number[phn] ;
      cout << c[3][filei].ph_number[phn] ;
    }
    sdout3 << "," ; cout << "," ;
    for ( nn = 0 ; nn < 7 ; nn++) {
      sdout3 << c[3][filei].number[nn] ;
      cout << c[3][filei].number[nn] ;
    }
    sdout3 << "," ; cout << "," ;
    sdout3 << c[3][filei].sTime << "," << c[3][filei].type << "#" ;
    cout << c[3][filei].sTime << "," << c[3][filei].type << "#" ;
  }
  sdout3.close() ;

  cout << "\nTHE DATA WRITTEN INTO carray.epark IS : " ;
  ofstream ca("carray.epark", ios::binary | ios::trunc);
  for ( cn = 0 ; cn < 4 ; cn++ ) {
    ca << counter[cn] << "#" ;
    cout << counter[cn] << "#" ;
  }
  ca.close() ;

  cout << "\nTHE DATA WRITTEN INTO cinout.epark IS : " ;
  ofstream cio("cinout.epark", ios::binary | ios::trunc);
  cio << C_IN << "#" << C_OUT << "#" ;
  cout << C_IN << "#" << C_OUT << "#" ;
  cio.close() ;

  cout << "WRITING TO ALL FILES DONE !\n" ;
  cout << "\n-------------------------------------------------\n" ;

}

void loop() {

}
