# 1 "C:\\Users\\Subhankar Karmakar\\Documents\\Arduino\\libraries\\TFT_eSPI\\examples\\Sprite\\Animated_dial\\Animated_dial.ino"
// This example draws an animated dial with a rotating needle.

// The dial is a jpeg image, the needle is created using a rotated
// Sprite. The example operates by reading blocks of pixels from the
// TFT, thus the TFT setup must support reading from the TFT CGRAM.

// The sketch operates by creating a copy of the screen block where
// the needle will be drawn, the needle is then drawn on the screen.
// When the needle moves, the original copy of the sreen area is
// pushed to the screen to over-write the needle graphic. A copy
// of the screen where the new position will be drawn is then made
// before drawing the needle in the new postion. This technique
// allows the needle to move over other screen graphics.

// The sketch calculates the size of the buffer memory required and
// reserves the memory for the TFT block copy.

// Created by Bodmer 17/3/20 as an example to the TFT_eSPI library:
// https://github.com/Bodmer/TFT_eSPI
# 29 "C:\\Users\\Subhankar Karmakar\\Documents\\Arduino\\libraries\\TFT_eSPI\\examples\\Sprite\\Animated_dial\\Animated_dial.ino"
// Font attached to this sketch
# 31 "C:\\Users\\Subhankar Karmakar\\Documents\\Arduino\\libraries\\TFT_eSPI\\examples\\Sprite\\Animated_dial\\Animated_dial.ino" 2


# 34 "C:\\Users\\Subhankar Karmakar\\Documents\\Arduino\\libraries\\TFT_eSPI\\examples\\Sprite\\Animated_dial\\Animated_dial.ino" 2
TFT_eSPI tft = TFT_eSPI();
TFT_eSprite needle = TFT_eSprite(&tft); // Sprite object for needle
TFT_eSprite spr = TFT_eSprite(&tft); // Sprite for meter reading

// Jpeg image array attached to this sketch
# 40 "C:\\Users\\Subhankar Karmakar\\Documents\\Arduino\\libraries\\TFT_eSPI\\examples\\Sprite\\Animated_dial\\Animated_dial.ino" 2

// Include the jpeg decoder library
# 43 "C:\\Users\\Subhankar Karmakar\\Documents\\Arduino\\libraries\\TFT_eSPI\\examples\\Sprite\\Animated_dial\\Animated_dial.ino" 2

uint16_t* tft_buffer;
bool buffer_loaded = false;
uint16_t spr_width = 0;

// =======================================================================================
// This function will be called during decoding of the jpeg file
// =======================================================================================
bool tft_output(int16_t x, int16_t y, uint16_t w, uint16_t h, uint16_t* bitmap)
{
  // Stop further decoding as image is running off bottom of screen
  if ( y >= tft.height() ) return 0;

  // This function will clip the image block rendering automatically at the TFT boundaries
  tft.pushImage(x, y, w, h, bitmap);

  // Return 1 to decode next block
  return 1;
}

// =======================================================================================
// Setup
// =======================================================================================
void setup() {
  Serial.begin(115200); // Debug only

  // The byte order can be swapped (set true for TFT_eSPI)
  TJpgDec.setSwapBytes(true);

  // The jpeg decoder must be given the exact name of the rendering function above
  TJpgDec.setCallback(tft_output);

  tft.begin();
  tft.setRotation(0);
  tft.fillScreen(0x0000 /*   0,   0,   0 */);

  // Draw the dial
  TJpgDec.drawJpg(0, 0, dial, sizeof(dial));
  tft.drawCircle(120, 120, 90 /* Radius at tip*/-35 /* Visible length*/, 0x7BEF /* 128, 128, 128 */);

  // Load the font and create the Sprite for reporting the value
  spr.loadFont(NotoSansBold36);
  spr_width = spr.textWidth("277");
  spr.createSprite(spr_width, spr.fontHeight());
  uint16_t bg_color = tft.readPixel(120, 120); // Get colour from dial centre
  spr.fillSprite(bg_color);
  spr.setTextColor(0xFFFF /* 255, 255, 255 */, bg_color);
  spr.setTextDatum(4 /* Middle centre*/);
  spr.setTextPadding(spr_width);
  spr.drawNumber(0, spr_width/2, spr.fontHeight()/2);
  spr.pushSprite(120 - spr_width / 2, 120 - spr.fontHeight() / 2);

  // Plot the label text
  tft.setTextColor(0xFFFF /* 255, 255, 255 */, bg_color);
  tft.setTextDatum(4 /* Middle centre*/);
  tft.drawString("(degrees)", 120, 120 + 48, 2);

  // Define where the needle pivot point is on the TFT before
  // creating the needle so boundary calculation is correct
  tft.setPivot(120, 120);

  // Create the needle Sprite
  createNeedle();

  // Reset needle position to 0
  plotNeedle(0, 0);

  delay(2000);
}

// =======================================================================================
// Loop
// =======================================================================================
void loop() {
  uint16_t angle = random(241); // random speed in range 0 to 240

  // Plot needle at random angle in range 0 to 240, speed 40ms per increment
  plotNeedle(angle, 30);

  // Pause at new position
  delay(2500);
}

// =======================================================================================
// Create the needle Sprite
// =======================================================================================
void createNeedle(void)
{
  needle.setColorDepth(16);
  needle.createSprite(5 /* Width of needle - make it an odd number*/, 35 /* Visible length*/); // create the needle Sprite

  needle.fillSprite(0x0000 /*   0,   0,   0 */); // Fill with black

  // Define needle pivot point relative to top left corner of Sprite
  uint16_t piv_x = 5 /* Width of needle - make it an odd number*/ / 2; // pivot x in Sprite (middle)
  uint16_t piv_y = 90 /* Radius at tip*/; // pivot y in Sprite
  needle.setPivot(piv_x, piv_y); // Set pivot point in this Sprite

  // Draw the red needle in the Sprite
  needle.fillRect(0, 0, 5 /* Width of needle - make it an odd number*/, 35 /* Visible length*/, 0x7800 /* 128,   0,   0 */);
  needle.fillRect(1, 1, 5 /* Width of needle - make it an odd number*/-2, 35 /* Visible length*/-2, 0xF800 /* 255,   0,   0 */);

  // Bounding box parameters to be populated
  int16_t min_x;
  int16_t min_y;
  int16_t max_x;
  int16_t max_y;

  // Work out the worst case area that must be grabbed from the TFT,
  // this is at a 45 degree rotation
  needle.getRotatedBounds(45, &min_x, &min_y, &max_x, &max_y);

  // Calculate the size and allocate the buffer for the grabbed TFT area
  tft_buffer = (uint16_t*) malloc( ((max_x - min_x) + 2) * ((max_y - min_y) + 2) * 2 );
}

// =======================================================================================
// Move the needle to a new position
// =======================================================================================
void plotNeedle(int16_t angle, uint16_t ms_delay)
{
  static int16_t old_angle = -120; // Starts at -120 degrees

  // Bounding box parameters
  static int16_t min_x;
  static int16_t min_y;
  static int16_t max_x;
  static int16_t max_y;

  if (angle < 0) angle = 0; // Limit angle to emulate needle end stops
  if (angle > 240) angle = 240;

  angle -= 120; // Starts at -120 degrees

  // Move the needle until new angle reached
  while (angle != old_angle || !buffer_loaded) {

    if (old_angle < angle) old_angle++;
    else old_angle--;

    // Only plot needle at even values to improve plotting performance
    if ( (old_angle & 1) == 0)
    {
      if (buffer_loaded) {
        // Paste back the original needle free image area
        tft.pushRect(min_x, min_y, 1 + max_x - min_x, 1 + max_y - min_y, tft_buffer);
      }

      if ( needle.getRotatedBounds(old_angle, &min_x, &min_y, &max_x, &max_y) )
      {
        // Grab a copy of the area before needle is drawn
        tft.readRect(min_x, min_y, 1 + max_x - min_x, 1 + max_y - min_y, tft_buffer);
        buffer_loaded = true;
      }

      // Draw the needle in the new postion, black in needle image is transparent
      needle.pushRotated(old_angle, 0x0000 /*   0,   0,   0 */);

      // Wait before next update
      delay(ms_delay);
    }

    // Update the number at the centre of the dial
    spr.drawNumber(old_angle+120, spr_width/2, spr.fontHeight()/2);
    spr.pushSprite(120 - spr_width / 2, 120 - spr.fontHeight() / 2);

    // Slow needle down slightly as it approaches the new position
    if (abs(old_angle - angle) < 10) ms_delay += ms_delay / 5;
  }
}

// =======================================================================================
