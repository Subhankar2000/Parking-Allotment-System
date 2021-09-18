# 1 "D:\\Arduino-STM32-ARM-M4\\portable\\sketchbook\\libraries\\TFT_eSPI\\examples\\320 x 240\\TFT_Terminal\\TFT_Terminal.ino"
# 1 "D:\\Arduino-STM32-ARM-M4\\portable\\sketchbook\\libraries\\TFT_eSPI\\examples\\320 x 240\\TFT_Terminal\\TFT_Terminal.ino"

/*************************************************************
  This sketch implements a simple serial receive terminal
  program for monitoring serial debug messages from another
  board.
  
  Connect GND to target board GND
  Connect RX line to TX line of target board
  Make sure the target and terminal have the same baud rate
  and serial stettings!

  The sketch works with the ILI9341 TFT 240x320 display and
  the called up libraries.
  
  The sketch uses the hardware scrolling feature of the
  display. Modification of this sketch may lead to problems
  unless the ILI9341 data sheet has been understood!

  Updated by Bodmer 21/12/16 for TFT_eSPI library:
  https://github.com/Bodmer/TFT_eSPI
  
  BSD license applies, all text above must be included in any
  redistribution
 *************************************************************/

# 27 "D:\\Arduino-STM32-ARM-M4\\portable\\sketchbook\\libraries\\TFT_eSPI\\examples\\320 x 240\\TFT_Terminal\\TFT_Terminal.ino" 2
# 28 "D:\\Arduino-STM32-ARM-M4\\portable\\sketchbook\\libraries\\TFT_eSPI\\examples\\320 x 240\\TFT_Terminal\\TFT_Terminal.ino" 2

TFT_eSPI tft = TFT_eSPI(); // Invoke custom library

// The scrolling area must be a integral multiple of TEXT_HEIGHT





// The initial y coordinate of the top of the scrolling area
uint16_t yStart = 16 /* Number of lines in top fixed area (lines counted from top of screen)*/;
// yArea must be a integral multiple of TEXT_HEIGHT
uint16_t yArea = 320 /* Bottom of screen area*/-16 /* Number of lines in top fixed area (lines counted from top of screen)*/-0 /* Number of lines in bottom fixed area (lines counted from bottom of screen)*/;
// The initial y coordinate of the top of the bottom text line
uint16_t yDraw = 320 /* Bottom of screen area*/ - 0 /* Number of lines in bottom fixed area (lines counted from bottom of screen)*/ - 16 /* Height of text to be printed and scrolled*/;

// Keep track of the drawing x coordinate
uint16_t xPos = 0;

// For the byte we read from the serial port
byte data = 0;

// A few test variables used during debugging
bool change_colour = 1;
bool selected = 1;

// We have to blank the top line each time the display is scrolled, but this takes up to 13 milliseconds
// for a full width line, meanwhile the serial buffer may be filling... and overflowing
// We can speed up scrolling of short text lines by just blanking the character we drew
int blank[19]; // We keep all the strings pixel lengths to optimise the speed of the top line blanking

void setup() {
  // Setup the TFT display
  tft.init();
  tft.setRotation(0); // Must be setRotation(0) for this sketch to work correctly
  tft.fillScreen(0x0000 /*   0,   0,   0 */);

  // Setup baud rate and draw top banner
  Serial.begin(9600);

  tft.setTextColor(0xFFFF /* 255, 255, 255 */, 0x001F /*   0,   0, 255 */);
  tft.fillRect(0,0,240,16, 0x001F /*   0,   0, 255 */);
  tft.drawCentreString(" Serial Terminal - 9600 baud ",120,0,2);

  // Change colour for scrolling zone text
  tft.setTextColor(0xFFFF /* 255, 255, 255 */, 0x0000 /*   0,   0,   0 */);

  // Setup scroll area
  setupScrollArea(16 /* Number of lines in top fixed area (lines counted from top of screen)*/, 0 /* Number of lines in bottom fixed area (lines counted from bottom of screen)*/);

  // Zero the array
  for (byte i = 0; i<18; i++) blank[i]=0;
}


void loop(void) {
  //  These lines change the text colour when the serial buffer is emptied
  //  These are test lines to see if we may be losing characters
  //  Also uncomment the change_colour line below to try them
  //
  //  if (change_colour){
  //  change_colour = 0;
  //  if (selected == 1) {tft.setTextColor(TFT_CYAN, TFT_BLACK); selected = 0;}
  //  else {tft.setTextColor(TFT_MAGENTA, TFT_BLACK); selected = 1;}
  //}

  while (Serial.available()) {
    data = Serial.read();
    // If it is a CR or we are near end of line then scroll one line
    if (data == '\r' || xPos>231) {
      xPos = 0;
      yDraw = scroll_line(); // It can take 13ms to scroll and blank 16 pixel lines
    }
    if (data > 31 && data < 128) {
      xPos += tft.drawChar(data,xPos,yDraw,2);
      blank[(18+(yStart-16 /* Number of lines in top fixed area (lines counted from top of screen)*/)/16 /* Height of text to be printed and scrolled*/)%19]=xPos; // Keep a record of line lengths
    }
    //change_colour = 1; // Line to indicate buffer is being emptied
  }
}

// ##############################################################################################
// Call this function to scroll the display one text line
// ##############################################################################################
int scroll_line() {
  int yTemp = yStart; // Store the old yStart, this is where we draw the next line
  // Use the record of line lengths to optimise the rectangle size we need to erase the top line
  tft.fillRect(0,yStart,blank[(yStart-16 /* Number of lines in top fixed area (lines counted from top of screen)*/)/16 /* Height of text to be printed and scrolled*/],16 /* Height of text to be printed and scrolled*/, 0x0000 /*   0,   0,   0 */);

  // Change the top of the scroll area
  yStart+=16 /* Height of text to be printed and scrolled*/;
  // The value must wrap around as the screen memory is a circular buffer
  if (yStart >= 320 /* Bottom of screen area*/ - 0 /* Number of lines in bottom fixed area (lines counted from bottom of screen)*/) yStart = 16 /* Number of lines in top fixed area (lines counted from top of screen)*/ + (yStart - 320 /* Bottom of screen area*/ + 0 /* Number of lines in bottom fixed area (lines counted from bottom of screen)*/);
  // Now we can scroll the display
  scrollAddress(yStart);
  return yTemp;
}

// ##############################################################################################
// Setup a portion of the screen for vertical scrolling
// ##############################################################################################
// We are using a hardware feature of the display, so we can only scroll in portrait orientation
void setupScrollArea(uint16_t tfa, uint16_t bfa) {
  tft.writecommand(0x33); // Vertical scroll definition
  tft.writedata(tfa >> 8); // Top Fixed Area line count
  tft.writedata(tfa);
  tft.writedata((320 /* Bottom of screen area*/-tfa-bfa)>>8); // Vertical Scrolling Area line count
  tft.writedata(320 /* Bottom of screen area*/-tfa-bfa);
  tft.writedata(bfa >> 8); // Bottom Fixed Area line count
  tft.writedata(bfa);
}

// ##############################################################################################
// Setup the vertical scrolling start address pointer
// ##############################################################################################
void scrollAddress(uint16_t vsp) {
  tft.writecommand(0x37); // Vertical scrolling pointer
  tft.writedata(vsp>>8);
  tft.writedata(vsp);
}
