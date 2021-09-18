# 1 "C:\\Users\\Subhankar Karmakar\\Documents\\Arduino\\libraries\\TFT_eSPI\\examples\\Test and diagnostics\\Colour_Test\\Colour_Test.ino"

//   Diagnostic test for the displayed colour order
//
// Writen by Bodmer 17/2/19 for the TFT_eSPI library:
// https://github.com/Bodmer/TFT_eSPI

/* 
 Different hardware manufacturers use different colour order
 configurations at the hardware level.  This may result in
 incorrect colours being displayed.

 Incorrectly displayed colours could also be the result of
 using the wrong display driver in the library setup file.

 Typically displays have a control register (MADCTL) that can
 be used to set the Red Green Blue (RGB) colour order to RGB
 or BRG so that red and blue are swapped on the display.

 This control register is also used to manage the display
 rotation and coordinate mirroring. The control register
 typically has 8 bits, for the ILI9341 these are:

 Bit Function
 7   Mirror Y coordinate (row address order)
 6   Mirror X coordinate (column address order)
 5   Row/column exchange (for rotation)
 4   Refresh direction (top to bottom or bottom to top in portrait orientation)
 3   RGB order (swaps red and blue)
 2   Refresh direction (top to bottom or bottom to top in landscape orientation)
 1   Not used
 0   Not used

 The control register bits can be written with this example command sequence:
 
    tft.writecommand(TFT_MADCTL);
    tft.writedata(0x48);          // Bits 6 and 3 set
    
 0x48 is the default value for ILI9341 (0xA8 for ESP32 M5STACK)
 in rotation 0 orientation.
 
 Another control register can be used to "invert" colours,
 this swaps black and white as well as other colours (e.g.
 green to magenta, red to cyan, blue to yellow).
 
 To invert colours insert this line after tft.init() or tft.begin():

    tft.invertDisplay( invert ); // Where invert is true or false

*/

# 52 "C:\\Users\\Subhankar Karmakar\\Documents\\Arduino\\libraries\\TFT_eSPI\\examples\\Test and diagnostics\\Colour_Test\\Colour_Test.ino" 2

# 54 "C:\\Users\\Subhankar Karmakar\\Documents\\Arduino\\libraries\\TFT_eSPI\\examples\\Test and diagnostics\\Colour_Test\\Colour_Test.ino" 2

TFT_eSPI tft = TFT_eSPI(); // Invoke custom library

void setup(void) {
  tft.init();

  tft.fillScreen(0x0000 /*   0,   0,   0 */);

  // Set "cursor" at top left corner of display (0,0) and select font 4
  tft.setCursor(0, 0, 4);

  // Set the font colour to be white with a black background
  tft.setTextColor(0xFFFF /* 255, 255, 255 */, 0x0000 /*   0,   0,   0 */);

  // We can now plot text on screen using the "print" class
  tft.println("Intialised default\n");
  tft.println("White text");

  tft.setTextColor(0xF800 /* 255,   0,   0 */, 0x0000 /*   0,   0,   0 */);
  tft.println("Red text");

  tft.setTextColor(0x07E0 /*   0, 255,   0 */, 0x0000 /*   0,   0,   0 */);
  tft.println("Green text");

  tft.setTextColor(0x001F /*   0,   0, 255 */, 0x0000 /*   0,   0,   0 */);
  tft.println("Blue text");

  delay(5000);

}

void loop() {

  tft.invertDisplay( false ); // Where i is true or false

  tft.fillScreen(0x0000 /*   0,   0,   0 */);

  tft.setCursor(0, 0, 4);

  tft.setTextColor(0xFFFF /* 255, 255, 255 */, 0x0000 /*   0,   0,   0 */);
  tft.println("Invert OFF\n");

  tft.println("White text");

  tft.setTextColor(0xF800 /* 255,   0,   0 */, 0x0000 /*   0,   0,   0 */);
  tft.println("Red text");

  tft.setTextColor(0x07E0 /*   0, 255,   0 */, 0x0000 /*   0,   0,   0 */);
  tft.println("Green text");

  tft.setTextColor(0x001F /*   0,   0, 255 */, 0x0000 /*   0,   0,   0 */);
  tft.println("Blue text");

  delay(5000);


  // Binary inversion of colours
  tft.invertDisplay( true ); // Where i is true or false

  tft.fillScreen(0x0000 /*   0,   0,   0 */);

  tft.setCursor(0, 0, 4);

  tft.setTextColor(0xFFFF /* 255, 255, 255 */, 0x0000 /*   0,   0,   0 */);
  tft.println("Invert ON\n");

  tft.println("White text");

  tft.setTextColor(0xF800 /* 255,   0,   0 */, 0x0000 /*   0,   0,   0 */);
  tft.println("Red text");

  tft.setTextColor(0x07E0 /*   0, 255,   0 */, 0x0000 /*   0,   0,   0 */);
  tft.println("Green text");

  tft.setTextColor(0x001F /*   0,   0, 255 */, 0x0000 /*   0,   0,   0 */);
  tft.println("Blue text");

  delay(5000);
}
