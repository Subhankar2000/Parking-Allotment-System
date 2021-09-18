# 1 "C:\\Users\\Subhankar Karmakar\\Documents\\Arduino\\libraries\\TFT_eSPI\\examples\\Sprite\\Sprite_draw\\Sprite_draw.ino"
/*

  Sketch to show how a Sprite is created, how to draw pixels
  and text within the Sprite and then push the Sprite onto
  the display screen.

  Example for library:
  https://github.com/Bodmer/TFT_eSPI

  A Sprite is notionally an invisible graphics screen that is
  kept in the processors RAM. Graphics can be drawn into the
  Sprite just as it can be drawn directly to the screen. Once
  the Sprite is completed it can be plotted onto the screen in
  any position. If there is sufficient RAM then the Sprite can
  be the same size as the screen and used as a frame buffer.

  A 16 bit Sprite occupies (2 * width * height) bytes in RAM.

  On a ESP8266 Sprite sizes up to 126 x 160 can be accomodated,
  this size requires 40kBytes of RAM for a 16 bit colour depth.
  
  When 8 bit colour depth sprites are created they occupy
  (width * height) bytes in RAM, so larger sprites can be
  created, or the RAM required is halved.

*/

// Set delay after plotting the sprite


// Width and height of sprite



# 36 "C:\\Users\\Subhankar Karmakar\\Documents\\Arduino\\libraries\\TFT_eSPI\\examples\\Sprite\\Sprite_draw\\Sprite_draw.ino" 2

TFT_eSPI tft = TFT_eSPI(); // Declare object "tft"

TFT_eSprite spr = TFT_eSprite(&tft); // Declare Sprite object "spr" with pointer to "tft" object

void setup()
{
  Serial.begin(250000);
  Serial.println();

  // Initialise the TFT registers
  tft.init();

  // Optionally set colour depth to 8 or 16 bits, default is 16 if not spedified
  // spr.setColorDepth(8);

  // Create a sprite of defined size
  spr.createSprite(128, 128);

  // Clear the TFT screen to blue
  tft.fillScreen(0x001F /*   0,   0, 255 */);
}

void loop(void)
{
  // Fill the whole sprite with black (Sprite is in memory so not visible yet)
  spr.fillSprite(0x0000 /*   0,   0,   0 */);

  // Number of pixels to draw
  uint16_t n = 100;

  // Draw 100 random colour pixels at random positions in sprite
  while (n--)
  {
    uint16_t colour = random(0x10000); // Returns colour 0 - 0xFFFF
    int16_t x = random(128); // Random x coordinate
    int16_t y = random(128); // Random y coordinate
    spr.drawPixel( x, y, colour); // Draw pixel in sprite
  }

  // Draw some lines
  spr.drawLine(1, 0, 128, 128 -1, 0x07E0 /*   0, 255,   0 */);
  spr.drawLine(0, 0, 128, 128, 0x07E0 /*   0, 255,   0 */);
  spr.drawLine(0, 1, 128 -1, 128, 0x07E0 /*   0, 255,   0 */);
  spr.drawLine(0, 128 -1, 128 -1, 0, 0xF800 /* 255,   0,   0 */);
  spr.drawLine(0, 128, 128, 0, 0xF800 /* 255,   0,   0 */);
  spr.drawLine(1, 128, 128, 1, 0xF800 /* 255,   0,   0 */);

  // Draw some text with Middle Centre datum
  spr.setTextDatum(4 /* Middle centre*/);
  spr.drawString("Sprite", 128 / 2, 128 / 2, 4);

  // Now push the sprite to the TFT at position 0,0 on screen
  spr.pushSprite(-40, -40);
  spr.pushSprite(tft.width() / 2 - 128 / 2, tft.height() / 2 - 128 / 2);
  spr.pushSprite(tft.width() - 128 + 40, tft.height() - 128 + 40);

  delay(1000);

  // Fill TFT screen with blue
  tft.fillScreen(0x001F /*   0,   0, 255 */);

  // Draw a blue rectangle in sprite so when we move it 1 pixel it does not leave a trail
  // on the blue screen background
  spr.drawRect(0, 0, 128, 128, 0x001F /*   0,   0, 255 */);

  int x = tft.width() / 2 - 128 / 2;
  int y = tft.height() / 2 - 128 / 2;

  uint32_t updateTime = 0; // time for next update

  while (true)
  {
    // Random movement direction
    int dx = 1; if (random(2)) dx = -1;
    int dy = 1; if (random(2)) dy = -1;

    // Pull it back onto screen if it wanders off
    if (x < -128/2) dx = 1;
    if (x >= tft.width()-128/2) dx = -1;
    if (y < -128/2) dy = 1;
    if (y >= tft.height()-128/2) dy = -1;

    // Draw it 50 time, moving in random direct or staying still
    n = 50;
    int wait = random (50);
    while (n)
    {
      if (updateTime <= millis())
      {
        // Use time delay so sprtie does not move fast when not all on screen
        updateTime = millis() + wait;

        // Push the sprite to the TFT screen
        spr.pushSprite(x, y);

        // Change coord for next loop
        x += dx;
        y += dy;
        n--;
        yield(); // Stop watchdog reset
      }
    }
  } // Infinite while, will not exit!
}
