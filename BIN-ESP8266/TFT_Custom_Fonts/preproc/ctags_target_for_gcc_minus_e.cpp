# 1 "C:\\Users\\Subhankar Karmakar\\Documents\\Arduino\\libraries\\TFT_eSPI\\examples\\320 x 240\\TFT_Custom_Fonts\\TFT_Custom_Fonts.ino"
/*
  Example for TFT_eSPI library

  Created by Bodmer 11/03/17

  Make sure LOAD_GFXFF is defined in the used User_Setup file
  within the library folder.

  --------------------------- NOTE ----------------------------------------
  The free font encoding format does not lend itself easily to plotting
  the background without flicker. For values that changes on screen it is
  better to use Fonts 1- 8 which are encoded specifically for rapid
  drawing with background.
  -------------------------------------------------------------------------

  #########################################################################
  ###### DON'T FORGET TO UPDATE THE User_Setup.h FILE IN THE LIBRARY ######
  ######   TO SELECT YOUR DISPLAY TYPE, PINS USED AND ENABLE FONTS   ######
  #########################################################################
*/

// Note the the tilda symbol ~ does not exist in some fonts at the moment


# 26 "C:\\Users\\Subhankar Karmakar\\Documents\\Arduino\\libraries\\TFT_eSPI\\examples\\320 x 240\\TFT_Custom_Fonts\\TFT_Custom_Fonts.ino" 2
# 27 "C:\\Users\\Subhankar Karmakar\\Documents\\Arduino\\libraries\\TFT_eSPI\\examples\\320 x 240\\TFT_Custom_Fonts\\TFT_Custom_Fonts.ino" 2

// Stock font and GFXFF reference handle



// Custom are fonts added to library "TFT_eSPI\Fonts\Custom" folder
// a #include must also be added to the "User_Custom_Fonts.h" file
// in the "TFT_eSPI\User_Setups" folder. See example entries.







// Use hardware SPI
TFT_eSPI tft = TFT_eSPI();

void setup(void) {

  Serial.begin(250000);

  tft.begin();

  tft.setRotation(1);

}

void loop() {

  // >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
  // Show custom fonts
  // >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

  // Where font sizes increase the screen is not cleared as the larger fonts overwrite
  // the smaller one with the background colour.

  // We can set the text datum to be Top, Middle, Bottom vertically and Left, Centre
  // and Right horizontally. These are the text datums that can be used:
  // TL_DATUM = Top left (default)
  // TC_DATUM = Top centre
  // TR_DATUM = Top right
  // ML_DATUM = Middle left
  // MC_DATUM = Middle centre <<< This is used below
  // MR_DATUM = Middle right
  // BL_DATUM = Bottom left
  // BC_DATUM = Bottom centre
  // BR_DATUM = Bottom right
  // L_BASELINE = Left character baseline (Line the 'A' character would sit on)
  // C_BASELINE = Centre character baseline
  // R_BASELINE = Right character baseline

  //Serial.println();

  // Set text datum to middle centre (MC_DATUM)
  tft.setTextDatum(4 /* Middle centre*/);

  // Set text colour to white with black background
  // Unlike the stock Adafruit_GFX library, the TFT_eSPI library DOES draw the background
  // for the custom and Free Fonts
  tft.setTextColor(0xFFFF /* 255, 255, 255 */, 0x0000 /*   0,   0,   0 */);

  tft.fillScreen(0xF81F /* 255,   0, 255 */); // Clear screen
  tft.setFreeFont(&FreeSans12pt7b); // Select the font
  tft.drawString("Yellowtail 32", 160, 60, 1);// Print the string name of the font
  tft.setFreeFont(&Yellowtail_32); // Select the font
  tft.drawString("abc MWy 123 |" /* Text that will be printed on screen in any font*/, 160, 120, 1);// Print the string name of the font
  delay(2000);

  tft.fillScreen(0x001F /*   0,   0, 255 */); // Clear screen
  tft.setFreeFont(&FreeSans12pt7b); // Select the font
  tft.drawString("Satisfy 24", 160, 60, 1);// Print the string name of the font
  tft.setFreeFont(&Satisfy_24); // Select the font
  tft.drawString("abc MWy 123 |" /* Text that will be printed on screen in any font*/, 160, 120, 1);// Print the test text in the custom font
  delay(2000);

  tft.fillScreen(0xF800 /* 255,   0,   0 */); // Clear screen
  tft.setFreeFont(&FreeSans12pt7b); // Select the font
  tft.drawString("Roboto 24", 160, 60, 1);// Print the string name of the font
  tft.setFreeFont(&Roboto_Thin_24); // Select the font
  tft.drawString("abc MWy 123 |" /* Text that will be printed on screen in any font*/, 160, 120, 1);// Print the test text in the custom font
  delay(2000);

  tft.fillScreen(0x7BEF /* 128, 128, 128 */); // Clear screen
  tft.setFreeFont(&FreeSans12pt7b); // Select the font
  tft.drawString("Orbitron 24", 160, 60, 1);// Print the string name of the font
  tft.setFreeFont(&Orbitron_Light_24); // Select the font
  tft.drawString("abc MWy 123 |" /* Text that will be printed on screen in any font*/, 160, 120, 1);// Print the test text in the custom font
  delay(2000);

  // Here we do not clear the screen and rely on the new text over-writing the old
  tft.setFreeFont(&FreeSans12pt7b); // Select the font
  tft.drawString("Orbitron 32", 160, 60, 1);// Print the string name of the font
  tft.setFreeFont(&Orbitron_Light_32); // Select the font
  tft.drawString("abc MWy 123 |" /* Text that will be printed on screen in any font*/, 160, 120, 1);// Print the test text in the custom font
  delay(2000);

  // Here we use text background padding to over-write the old text
  tft.fillScreen(0xFFE0 /* 255, 255,   0 */); // Clear screen
  tft.setTextColor(0xFFFF /* 255, 255, 255 */, 0x0000 /*   0,   0,   0 */);

  // Here we use text background padding to over-write the old text
  tft.setTextPadding(tft.width() - 20); // Blanked area will be width of screen minus 20 pixels
  tft.setFreeFont(&FreeSans12pt7b); // Select the font
  tft.drawString("Orbitron 32 with padding", 160, 60, 1);// Print the string name of the font
  tft.setFreeFont(&Orbitron_Light_32); // Select the font
  tft.drawString("abc MWy 123 |" /* Text that will be printed on screen in any font*/, 160, 120, 1);// Print the test text in the custom font
  delay(2000);

  // Use 80 pixel wide padding so old numbers over-write old ones
  // One of the problrms with proportionally spaced numbers is that they jiggle position
  tft.setTextPadding(80);
  tft.setTextDatum(4 /* Middle centre*/);
  tft.setFreeFont(&Orbitron_Light_32);
  for( int i = 100; i > 0; i--)
  {
    tft.drawNumber( i, 160, 200);
    delay(500);
  }

  // Reset text padding to zero (default)
  tft.setTextPadding(0);
}
