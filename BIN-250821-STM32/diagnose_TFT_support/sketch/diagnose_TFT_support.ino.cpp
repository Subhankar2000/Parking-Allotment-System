#include <Arduino.h>
#line 1 "C:\\Users\\SUBHAN~2\\AppData\\Local\\Temp\\arduino_modified_sketch_564437\\diagnose_TFT_support.ino"
#line 1 "C:\\Users\\SUBHAN~2\\AppData\\Local\\Temp\\arduino_modified_sketch_564437\\diagnose_TFT_support.ino"
#include <MCUFRIEND_kbv.h>
MCUFRIEND_kbv tft;
HardwareSerial Serial6(PA12, PA11);
// Assign human-readable names to some common 16-bit color values:
#define BLACK   0x0000
#define BLUE    0x001F
#define RED     0xF800
#define GREEN   0x07E0
#define CYAN    0x07FF
#define MAGENTA 0xF81F
#define YELLOW  0xFFE0
#define WHITE   0xFFFF
#define GRAY    0x8410

uint16_t version = MCUFRIEND_KBV_H_;

#line 17 "C:\\Users\\SUBHAN~2\\AppData\\Local\\Temp\\arduino_modified_sketch_564437\\diagnose_TFT_support.ino"
void setup();
#line 90 "C:\\Users\\SUBHAN~2\\AppData\\Local\\Temp\\arduino_modified_sketch_564437\\diagnose_TFT_support.ino"
void loop();
#line 17 "C:\\Users\\SUBHAN~2\\AppData\\Local\\Temp\\arduino_modified_sketch_564437\\diagnose_TFT_support.ino"
void setup()
{
  Serial6.begin(9600);
  if (!Serial) delay(5000);           //allow some time for Leonardo
  uint16_t ID = tft.readID(); //
  Serial6.println(F("Diagnose whether this controller is supported"));
  Serial6.println(F("There are FAQs in extras/mcufriend_how_to.txt"));
  Serial6.println(F(""));
  Serial6.print(F("tft.readID() finds: ID = 0x"));
  Serial6.println(ID, HEX);
  Serial6.println(F(""));
  Serial6.print(F("MCUFRIEND_kbv version: "));
  Serial6.print(version / 100);
  Serial6.print(F("."));
  Serial6.print((version / 10) % 10);
  Serial6.print(F("."));
  Serial6.println(version % 10);
  Serial6.println(F(""));
  if (ID == 0x0404) {
    Serial6.println(F("Probably a write-only Mega2560 Shield"));
    Serial6.println(F("#define USE_SPECIAL in mcufriend_shield.h"));
    Serial6.println(F("#define appropriate SPECIAL in mcufriend_special.h"));
    Serial6.println(F("e.g. USE_MEGA_16BIT_SHIELD"));
    Serial6.println(F("e.g. USE_MEGA_8BIT_SHIELD"));
    Serial6.println(F("Hint.  A Mega2560 Shield has a 18x2 male header"));
    Serial6.println(F("Often a row of resistor-packs near the 18x2"));
    Serial6.println(F("RP1-RP7 implies 16-bit but it might be 8-bit"));
    Serial6.println(F("RP1-RP4 or RP1-RP5 can only be 8-bit"));
  }
  if (ID == 0xD3D3) {
    uint16_t guess_ID = 0x9481; // write-only shield
    Serial6.println(F("Probably a write-only Mega2560 Shield"));
    Serial6.print(F("Try to force ID = 0x"));
    Serial6.println(guess_ID, HEX);
    tft.begin(guess_ID);
  }
  else tft.begin(ID);
  Serial6.println(F(""));
  if (tft.width() == 0) {
    Serial6.println(F("This ID is not supported"));
    Serial6.println(F("look up ID in extras/mcufriend_how_to.txt"));
    Serial6.println(F("you may need to edit MCUFRIEND_kbv.cpp"));
    Serial6.println(F("to enable support for this ID"));
    Serial6.println(F("e.g. #define SUPPORT_8347D"));
    Serial6.println(F(""));
    Serial6.println(F("New controllers appear on Ebay often"));
    Serial6.println(F("If your ID is not supported"));
    Serial6.println(F("run LCD_ID_readreg.ino from examples/"));
    Serial6.println(F("Copy-Paste the output from the Serial Terminal"));
    Serial6.println(F("to a message in Displays topic on Arduino Forum"));
    Serial6.println(F("or to Issues on GitHub"));
    Serial6.println(F(""));
    Serial6.println(F("Note that OPEN-SMART boards have diff pinout"));
    Serial6.println(F("Edit the pin defines in LCD_ID_readreg to match"));
    Serial6.println(F("Edit mcufiend_shield.h for USE_SPECIAL"));
    Serial6.println(F("Edit mcufiend_special.h for USE_OPENSMART_SHIELD_PINOUT"));
    while (1);    //just die
  } else {
    Serial6.print(F("PORTRAIT is "));
    Serial6.print(tft.width());
    Serial6.print(F(" x "));
    Serial6.println(tft.height());
    Serial6.println(F(""));
    Serial6.println(F("Run the examples/graphictest_kbv sketch"));
    Serial6.println(F("All colours, text, directions, rotations, scrolls"));
    Serial6.println(F("should work.  If there is a problem,  make notes on paper"));
    Serial6.println(F("Post accurate description of problem to Forum"));
    Serial6.println(F("Or post a link to a video (or photos)"));
    Serial6.println(F(""));
    Serial6.println(F("I rely on good information from remote users"));
  }
}

void loop()
{
  static uint8_t aspect = 0;
  const char *aspectname[] = {
    "PORTRAIT", "LANDSCAPE", "PORTRAIT_REV", "LANDSCAPE_REV"
  };
  const char *colorname[] = { "BLUE", "GREEN", "RED", "GRAY" };
  uint16_t colormask[] = { BLUE, GREEN, RED, GRAY };
  uint16_t ID = tft.readID(); //
  tft.setRotation(aspect);
  int width = tft.width();
  int height = tft.height();
  tft.fillScreen(colormask[aspect]);
  tft.drawRect(0, 0, width, height, WHITE);
  tft.drawRect(32, 32, width - 64, height - 64, WHITE);
  tft.setTextSize(2);
  tft.setTextColor(BLACK);
  tft.setCursor(40, 40);
  tft.print("ID=0x");
  tft.print(ID, HEX);
  if (ID == 0xD3D3) tft.print(" w/o");
  tft.setCursor(40, 70);
  tft.print(aspectname[aspect]);
  tft.setCursor(40, 100);
  tft.print(width);
  tft.print(" x ");
  tft.print(height);
  tft.setTextColor(WHITE);
  tft.setCursor(40, 130);
  tft.print(colorname[aspect]);
  tft.setCursor(40, 160);
  tft.setTextSize(1);
  tft.print("MCUFRIEND_KBV_H_ = ");
  tft.print(version);
  if (++aspect > 3) aspect = 0;
  delay(5000);
}
