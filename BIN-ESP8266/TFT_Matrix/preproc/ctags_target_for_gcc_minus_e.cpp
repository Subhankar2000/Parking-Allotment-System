# 1 "C:\\Users\\Subhankar Karmakar\\Documents\\Arduino\\libraries\\TFT_eSPI\\examples\\320 x 240\\TFT_Matrix\\TFT_Matrix.ino"
// A fun MATRIX-like screen demo of scrolling
// Screen will flicker initially until fully drawn
// then scroll smoothly

// Needs GLCD font

/*
 Make sure all the display driver and pin connections are correct by
 editing the User_Setup.h file in the TFT_eSPI library folder.

 #########################################################################
 ###### DON'T FORGET TO UPDATE THE User_Setup.h FILE IN THE LIBRARY ######
 #########################################################################
*/

# 17 "C:\\Users\\Subhankar Karmakar\\Documents\\Arduino\\libraries\\TFT_eSPI\\examples\\320 x 240\\TFT_Matrix\\TFT_Matrix.ino" 2
# 18 "C:\\Users\\Subhankar Karmakar\\Documents\\Arduino\\libraries\\TFT_eSPI\\examples\\320 x 240\\TFT_Matrix\\TFT_Matrix.ino" 2

TFT_eSPI tft = TFT_eSPI(); // Invoke custom library





uint16_t yStart = 0 /* Number of lines in top fixed area (lines counted from top of screen)*/;
uint16_t yArea = 320 - 0 /* Number of lines in top fixed area (lines counted from top of screen)*/ - 0 /* Number of lines in bottom fixed area (lines counted from bottom of screen)*/;
uint16_t yDraw = 320 - 0 /* Number of lines in bottom fixed area (lines counted from bottom of screen)*/ - 8 /* Height of text to be printed and scrolled*/;
byte pos[42];
uint16_t xPos = 0;

void setup() {
  Serial.begin(115200);
  randomSeed(analogRead(A0));
  tft.init();
  tft.setRotation(0);
  tft.fillScreen(0x0000 /*   0,   0,   0 */);
  setupScrollArea(0 /* Number of lines in top fixed area (lines counted from top of screen)*/, 0 /* Number of lines in bottom fixed area (lines counted from bottom of screen)*/);
}

void loop(void) {
  // First fill the screen with random streaks of characters
  for (int j = 0; j < 600; j += 8 /* Height of text to be printed and scrolled*/) {
    for (int i = 0; i < 40; i++) {
      if (pos[i] > 20) pos[i] -= 3; // Rapid fade initially brightness values
      if (pos[i] > 0) pos[i] -= 1; // Slow fade later
      if ((random(20) == 1) && (j<400)) pos[i] = 63; // ~1 in 20 probability of a new character
      tft.setTextColor(pos[i] << 5, 0x0000 /*   0,   0,   0 */); // Set the green character brightness
      if (pos[i] == 63) tft.setTextColor(0xFFFF /* 255, 255, 255 */, 0x0000 /*   0,   0,   0 */); // Draw white character
      xPos += tft.drawChar(random(32, 128), xPos, yDraw, 1); // Draw the character
    }
    yDraw = scroll_slow(8 /* Height of text to be printed and scrolled*/, 14); // Scroll, 14ms per pixel line
    xPos = 0;
  }

  //tft.setRotation(2);
  //tft.setTextColor(63 << 5, ILI9341_BLACK);
  //tft.drawCentreString("MATRIX",120,60,4);
  //tft.setRotation(0);

  // Now scroll smoothly forever
  while (1) {yield(); yDraw = scroll_slow(320,5); }// Scroll 320 lines, 5ms per line

}

void setupScrollArea(uint16_t TFA, uint16_t BFA) {
  tft.writecommand(0x33); // Vertical scroll definition
  tft.writedata(TFA >> 8);
  tft.writedata(TFA);
  tft.writedata((320 - TFA - BFA) >> 8);
  tft.writedata(320 - TFA - BFA);
  tft.writedata(BFA >> 8);
  tft.writedata(BFA);
}

int scroll_slow(int lines, int wait) {
  int yTemp = yStart;
  for (int i = 0; i < lines; i++) {
    yStart++;
    if (yStart == 320 - 0 /* Number of lines in bottom fixed area (lines counted from bottom of screen)*/) yStart = 0 /* Number of lines in top fixed area (lines counted from top of screen)*/;
    scrollAddress(yStart);
    delay(wait);
  }
  return yTemp;
}

void scrollAddress(uint16_t VSP) {
  tft.writecommand(0x37); // Vertical scrolling start address
  tft.writedata(VSP >> 8);
  tft.writedata(VSP);
}
