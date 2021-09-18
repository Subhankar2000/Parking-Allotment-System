#include "Wire.h"
 
void setup() 
{
  Wire.setSCL(PB_6); // alternative pinout of I2C1_SCL - PB6 (Morpho con) instead of PB8 (D15) 
  Wire.setSDA(PB_7); // alternative pinout of I2C1_SDA - PB7 (D10) instead of PB9 (D14) 
}

void loop() {

}
