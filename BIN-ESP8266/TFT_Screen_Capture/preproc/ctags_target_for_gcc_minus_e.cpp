# 1 "C:\\Users\\Subhankar Karmakar\\Documents\\Arduino\\libraries\\TFT_eSPI\\examples\\Generic\\TFT_Screen_Capture\\TFT_Screen_Capture.ino"
/*
  This sketch has been written to test the Processing screenshot client.

  It has been created to work with the TFT_eSPI library here:
  https://github.com/Bodmer/TFT_eSPI

  It sends screenshots to a PC running a Processing client sketch.

  The Processing IDE that will run the client sketch can be downloaded
  here:  https://processing.org/

  The Processing sketch needed is contained within a tab attached to this
  Arduino sketch. Cut and paste that tab into the Processing IDE and run.
  Read the Processing sketch header for instructions.

  This sketch uses the GLCD, 2, 4, 6 fonts only.

  Make sure all the display driver and pin connections are correct by
  editing the User_Setup.h file in the TFT_eSPI library folder.

  Maximum recommended SPI clock rate is 27MHz when reading pixels, 40MHz
  seems to be OK with ILI9341 displays but this is above the manufacturers
  specified maximum clock rate.

  In the setup file you can define different write and read SPI clock rates
  
  In the setup file you can define TFT_SDA_READ for a TFT with bi-directional
  SDA pin (otherwise the normal MISO pin will be used to read from the TFT)

  >>>>   NOTE: NOT ALL TFTs SUPPORT READING THE CGRAM (pixel) MEMORY   <<<<

  #########################################################################
  ###### DON'T FORGET TO UPDATE THE User_Setup.h FILE IN THE LIBRARY ######
  #########################################################################
*/

// Created by: Bodmer  5/3/17
// Updated by: Bodmer 10/3/17
// Updated by: Bodmer 23/11/18 to support SDA reads and the ESP32
// Version: 0.07

// MIT licence applies, all text above must be included in derivative works

# 45 "C:\\Users\\Subhankar Karmakar\\Documents\\Arduino\\libraries\\TFT_eSPI\\examples\\Generic\\TFT_Screen_Capture\\TFT_Screen_Capture.ino" 2
# 46 "C:\\Users\\Subhankar Karmakar\\Documents\\Arduino\\libraries\\TFT_eSPI\\examples\\Generic\\TFT_Screen_Capture\\TFT_Screen_Capture.ino" 2

TFT_eSPI tft = TFT_eSPI(); // Invoke custom library

unsigned long targetTime = 0;
byte red = 0x1F;
byte green = 0;
byte blue = 0;
byte state = 0;
unsigned int colour = red << 11; // Colour order is RGB 5+6+5 bits each

void setup(void) {
  Serial.begin(921600); // Set to a high rate for fast image transfer to a PC

  tft.init();
  tft.setRotation(0);
  tft.fillScreen(0x0000 /*   0,   0,   0 */);

  randomSeed(analogRead(A0));

  targetTime = millis() + 1000;
}



void loop() {

  if (targetTime < millis()) {
    if (!false /* true produces a simple RGB color test screen*/)
    {
      targetTime = millis() + 1500; // Wait a minimum of 1.5s

      tft.setRotation(random(4));
      rainbow_fill(); // Fill the screen with rainbow colours

      tft.setTextColor(0x0000 /*   0,   0,   0 */); // Text background is not defined so it is transparent
      tft.setTextDatum(1 /* Top centre*/); // Top Centre datum
      int xpos = tft.width() / 2; // Centre of screen

      tft.setTextFont(0); // Select font 0 which is the Adafruit font
      tft.drawString("Original Adafruit font!", xpos, 5);

      // The new larger fonts do not need to use the .setCursor call, coords are embedded
      tft.setTextColor(0x0000 /*   0,   0,   0 */); // Do not plot the background colour

      // Overlay the black text on top of the rainbow plot (the advantage of not drawing the backgorund colour!)
      tft.drawString("Font size 2", xpos, 14, 2); // Draw text centre at position xpos, 14 using font 2
      tft.drawString("Font size 4", xpos, 30, 4); // Draw text centre at position xpos, 30 using font 4
      tft.drawString("12.34", xpos, 54, 6); // Draw text centre at position xpos, 54 using font 6

      tft.drawString("12.34 is in font size 6", xpos, 92, 2); // Draw text centre at position xpos, 92 using font 2
      // Note the x position is the top of the font!

      // draw a floating point number
      float pi = 3.1415926; // Value to print
      int precision = 3; // Number of digits after decimal point

      int ypos = 110; // y position

      tft.setTextDatum(2 /* Top right*/); // Top Right datum so text butts neatly to xpos (right justified)

      tft.drawFloat(pi, precision, xpos, ypos, 2); // Draw rounded number and return new xpos delta for next print position

      tft.setTextDatum(0 /* Top left (default)*/); // Top Left datum so text butts neatly to xpos (left justified)

      tft.drawString(" is pi", xpos, ypos, 2);

      tft.setTextSize(1); // We are using a font size multiplier of 1
      tft.setTextDatum(1 /* Top centre*/); // Top Centre datum
      tft.setTextColor(0x0000 /*   0,   0,   0 */); // Set text colour to black, no background (so transparent)

      tft.drawString("Transparent...", xpos, 125, 4); // Font 4

      tft.setTextColor(0xFFFF /* 255, 255, 255 */, 0x0000 /*   0,   0,   0 */); // Set text colour to white and background to black
      tft.drawString("White on black", xpos, 150, 4); // Font 4

      tft.setTextColor(0x07E0 /*   0, 255,   0 */, 0x0000 /*   0,   0,   0 */); // This time we will use green text on a black background

      tft.setTextFont(2); // Select font 2, now we do not need to specify the font in drawString()

      // An easier way to position text and blank old text is to set the datum and use width padding
      tft.setTextDatum(7 /* Bottom centre*/); // Bottom centre for text datum
      tft.setTextPadding(tft.width() + 1); // Pad text to full screen width + 1 spare for +/-1 position rounding

      tft.drawString("Ode to a Small Lump of Green Putty", xpos, 230 - 32);
      tft.drawString("I Found in My Armpit One Midsummer", xpos, 230 - 16);
      tft.drawString("Morning", xpos, 230);

      tft.setTextDatum(0 /* Top left (default)*/); // Reset to top left for text datum
      tft.setTextPadding(0); // Reset text padding to 0 pixels

      // Now call the screen server to send a copy of the TFT screen to the PC running the Processing client sketch
      screenServer();
    }
    else
    {
      tft.fillScreen(0x0000 /*   0,   0,   0 */);
      tft.fillRect( 0, 0, 16, 16, 0xF800 /* 255,   0,   0 */);
      tft.fillRect(16, 0, 16, 16, 0x07E0 /*   0, 255,   0 */);
      tft.fillRect(32, 0, 16, 16, 0x001F /*   0,   0, 255 */);
      screenServer();
    }
  }
}

// Fill screen with a rainbow pattern
void rainbow_fill()
{
  // The colours and state are not initialised so the start colour changes each time the funtion is called
  int rotation = tft.getRotation();
  tft.setRotation(random(4));
  for (int i = tft.height() - 1; i >= 0; i--) {
    // This is a "state machine" that ramps up/down the colour brightnesses in sequence
    switch (state) {
      case 0:
        green ++;
        if (green == 64) {
          green = 63;
          state = 1;
        }
        break;
      case 1:
        red--;
        if (red == 255) {
          red = 0;
          state = 2;
        }
        break;
      case 2:
        blue ++;
        if (blue == 32) {
          blue = 31;
          state = 3;
        }
        break;
      case 3:
        green --;
        if (green == 255) {
          green = 0;
          state = 4;
        }
        break;
      case 4:
        red ++;
        if (red == 32) {
          red = 31;
          state = 5;
        }
        break;
      case 5:
        blue --;
        if (blue == 255) {
          blue = 0;
          state = 0;
        }
        break;
    }
    colour = red << 11 | green << 5 | blue;
    // Draw a line 1 pixel wide in the selected colour
    tft.drawFastHLine(0, i, tft.width(), colour); // tft.width() returns the pixel width of the display
  }
  tft.setRotation(rotation);
}
# 1 "C:\\Users\\Subhankar Karmakar\\Documents\\Arduino\\libraries\\TFT_eSPI\\examples\\Generic\\TFT_Screen_Capture\\processing_sketch.ino"
// This is a copy of the processing sketch that can be used to capture the images
// Copy the sketch below and remove the /* and */ at the beginning and end.

// The sketch runs in Processing version 3.3 on a PC, it can be downloaded here:
// https://processing.org/download/

/*

// This is a Processing sketch, see https://processing.org/ to download the IDE

// The sketch is a client that requests TFT screenshots from an Arduino board.
// The Arduino must call a screenshot server function to respond with pixels.

// It has been created to work with the TFT_eSPI library here:
// https://github.com/Bodmer/TFT_eSPI

// The sketch must only be run when the designated serial port is available and enumerated
// otherwise the screenshot window may freeze and that process will need to be terminated
// This is a limitation of the Processing environment and not the sketch.
// If anyone knows how to determine if a serial port is available at start up the PM me
// on (Bodmer) the Arduino forum.

// The block below contains variables that the user may need to change for a particular setup
// As a minimum set the serial port and baud rate must be defined. The capture window is
// automatically resized for landscape, portrait and different TFT resolutions.

// Captured images are stored in the sketch folder, use the Processing IDE "Sketch" menu
// option "Show Sketch Folder" or press Ctrl+K

// Created by: Bodmer  5/3/17
// Updated by: Bodmer 12/3/17
// Version: 0.07

// MIT licence applies, all text above must be included in derivative works


// ###########################################################################################
// #                  These are the values to change for a particular setup                  #
//                                                                                           #
int serial_port = 0;     // Use enumerated value from list provided when sketch is run       #
//                                                                                           #
// On an Arduino Due Programming Port use a baud rate of:115200)                             #
// On an Arduino Due Native USB Port use a baud rate of any value                            #
int serial_baud_rate = 921600; //                                                            #
//                                                                                           #
// Change the image file type saved here, comment out all but one                            #
//String image_type = ".jpg"; //                                                             #
String image_type = ".png";   // Lossless compression                                        #
//String image_type = ".bmp"; //                                                             #
//String image_type = ".tif"; //                                                             #
//                                                                                           #
bool save_border = true;   // Save the image with a border                                #
int border = 5;               // Border pixel width                                          #
bool fade = false;         // Fade out image after saving                                 #
//                                                                                           #
int max_images = 100; // Maximum of numbered file images before over-writing files           #
//                                                                                           #
int max_allowed  = 1000; // Maximum number of save images allowed before a restart           #
//                                                                                           #
// #                   End of the values to change for a particular setup                    #
// ###########################################################################################

// These are default values, this sketch obtains the actual values from the Arduino board
int tft_width  = 480;    // default TFT width  (automatic - sent by Arduino)
int tft_height = 480;    // default TFT height (automatic - sent by Arduino)
int color_bytes = 2;     // 2 for 16 bit, 3 for three RGB bytes (automatic - sent by Arduino)

import processing.serial.*;

Serial serial;           // Create an instance called serial

int serialCount = 0;     // Count of colour bytes arriving

// Stage window graded background colours
color bgcolor1 = color(0, 100, 104);      // Arduino IDE style background color 1
color bgcolor2 = color(77, 183, 187);     // Arduino IDE style background color 2
//color bgcolor2 = color(255, 255, 255);  // White

// TFT image frame greyscale value (dark grey)
color frameColor = 42;

color buttonStopped = color(255, 0, 0);
color buttonRunning = color(128, 204, 206);
color buttonDimmed  = color(180, 0, 0);
bool dimmed   = false;
bool running  = true;
bool mouseClick = false;

int[] rgb = new int[3]; // Buffer for the colour bytes
int indexRed   = 0;     // Colour byte index in the array
int indexGreen = 1;
int indexBlue  = 2;

int n = 0;

int x_offset = (500 - tft_width) /2; // Image offsets in the window
int y_offset = 20;

int xpos = 0, ypos = 0; // Current pixel position

int beginTime     = 0;
int pixelWaitTime = 1000;  // Maximum 1000ms wait for image pixels to arrive
int lastPixelTime = 0;     // Time that "image send" command was sent

int requestTime = 0;
int requestCount = 0;

int state = 0;  // State machine current state

int   progress_bar = 0; // Console progress bar dot count
int   pixel_count  = 0; // Number of pixels read for 1 screen
float percentage   = 0; // Percentage of pixels received

int  saved_image_count = 0; // Stats - number of images processed
int  bad_image_count  = 0;  // Stats - number of images that had lost pixels
String filename = "";

int drawLoopCount = 0;      // Used for the fade out

void setup() {

  size(500, 540);  // Stage size, can handle 480 pixels wide screen
  noStroke();      // No border on the next thing drawn
  noSmooth();      // No anti-aliasing to avoid adjacent pixel colour merging

  // Graded background and title
  drawWindow();

  frameRate(2000); // High frame rate so draw() loops fast

  // Print a list of the available serial ports
  println("-----------------------");
  println("Available Serial Ports:");
  println("-----------------------");
  printArray(Serial.list());
  println("-----------------------");

  print("Port currently used: [");
  print(serial_port);
  println("]");

  String portName = Serial.list()[serial_port];

  serial = new Serial(this, portName, serial_baud_rate);

  state = 99;
}

void draw() {

  if (mouseClick) buttonClicked();

  switch(state) {

  case 0: // Init varaibles, send start request
    if (running) {
      tint(0, 0, 0, 255);
      flushBuffer();
      println("");
      print("Ready: ");

      xpos = 0;
      ypos = 0;
      serialCount = 0;
      progress_bar = 0;
      pixel_count = 0;
      percentage   = 0;
      drawLoopCount = frameCount;
      lastPixelTime = millis() + 1000;

      state = 1;
    } else {
      if (millis() > beginTime) {
        beginTime = millis() + 500;
        dimmed = !dimmed;
        if (dimmed) drawButton(buttonDimmed);
        else drawButton(buttonStopped);
      }
    }
    break;

  case 1: // Console message, give server some time
    print("requesting image ");
    serial.write("S");
    delay(10);
    beginTime = millis();
    requestTime = millis() + 1000;
    requestCount = 1;
    state = 2;
    break;

  case 2: // Get size and set start time for rendering duration report
    if (millis() > requestTime) {
      requestCount++;
      print("*");
      serial.clear();
      serial.write("S");
      if (requestCount > 32) {
        requestCount = 0;
        System.err.println(" - no response!");
        state = 0;
      }
      requestTime = millis() + 1000;
    }
    if ( getSize() == true ) { // Go to next state when we have the size and bits per pixel
      getFilename();
      flushBuffer(); // Precaution in case image header size increases in later versions
      lastPixelTime = millis() + 1000;
      beginTime = millis();
      state = 3;
    }
    break;

  case 3: // Request pixels and render returned RGB values
    state = renderPixels(); // State will change when all pixels are rendered

    // Request more pixels, changing the number requested allows the average transfer rate to be controlled
    // The pixel transfer rate is dependant on four things:
    //    1. The frame rate defined in this Processing sketch in setup()
    //    2. The baud rate of the serial link (~10 bit periods per byte)
    //    3. The number of request bytes 'R' sent in the lines below
    //    4. The number of pixels sent in a burst by the server sketch (defined via NPIXELS)

    //serial.write("RRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRR"); // 32 x NPIXELS more
    serial.write("RRRRRRRRRRRRRRRR"); // 16 x NPIXELS more
    //serial.write("RRRRRRRR"); // 8 x NPIXELS more
    //serial.write("RRRR"); // 4 x NPIXELS more
    //serial.write("RR"); // 2 x NPIXELS more
    //serial.write("R"); // 1 x NPIXELS more
    if (!running) state = 4;
    break;

  case 4: // Pixel receive time-out, flush serial buffer
    flushBuffer();
    state = 6;
    break;

  case 5: // Save the image to the sketch folder (Ctrl+K to access)
    saveScreenshot();
    saved_image_count++;
    println("Saved image count = " + saved_image_count);
    if (bad_image_count > 0) System.err.println(" Bad image count = " + bad_image_count);
    drawLoopCount = frameCount; // Reset value ready for counting in step 6
    state = 6;
    break;

  case 6: // Fade the old image if enabled
    if ( fadedImage() == true ) state = 0; // Go to next state when image has faded
    break;

  case 99: // Draw image viewer window
    drawWindow();
    delay(50); // Delay here seems to be required for the IDE console to get ready
    state = 0;
    break;

  default:
    println("");
    System.err.println("Error state reached - check sketch!");
    break;
  }
}

void drawWindow()
{
  // Graded background in Arduino colours
  for (int i = 0; i < height - 25; i++) {
    float inter = map(i, 0, height - 25, 0, 1);
    color c = lerpColor(bgcolor1, bgcolor2, inter);
    stroke(c);
    line(0, i, 500, i);
  }
  fill(bgcolor2);
  rect( 0, height-25, width-1, 24);
  textAlign(CENTER);
  textSize(20);
  fill(0);
  text("Bodmer's TFT image viewer", width/2, height-6);

  if (running) drawButton(buttonRunning);
  else drawButton(buttonStopped);
}

void flushBuffer()
{
  //println("Clearing serial pipe after a time-out");
  int clearTime = millis() + 50;
  while ( millis() < clearTime ) serial.clear();
}

bool getSize()
{
  if ( serial.available() > 6 ) {
    println();
    char code = (char)serial.read();
    if (code == 'W') {
      tft_width = serial.read()<<8 | serial.read();
    }
    code = (char)serial.read();
    if (code == 'H') {
      tft_height = serial.read()<<8 | serial.read();
    }
    code = (char)serial.read();
    if (code == 'Y') {
      int bits_per_pixel = (char)serial.read();
      if (bits_per_pixel == 24) color_bytes = 3;
      else color_bytes = 2;
    }
    code = (char)serial.read();
    if (code == '?') {
      drawWindow();

      x_offset = (500 - tft_width) /2;
      tint(0, 0, 0, 255);
      noStroke();
      fill(frameColor);
      rect((width - tft_width)/2 - border, y_offset - border, tft_width + 2 * border, tft_height + 2 * border);
      return true;
    }
  }
  return false;
}

void saveScreenshot()
{
  println();
  if (saved_image_count < max_allowed)
  {
  if (filename == "") filename = "tft_screen_" + (n++);
  filename = filename  + image_type;
  println("Saving image as \"" + filename + "\"");
  if (save_border)
  {
    PImage partialSave = get(x_offset - border, y_offset - border, tft_width + 2*border, tft_height + 2*border);
    partialSave.save(filename);
  } else {
    PImage partialSave = get(x_offset, y_offset, tft_width, tft_height);
    partialSave.save(filename);
  }

  if (n>=max_images) n = 0;
  }
  else
  {
    System.err.println(max_allowed + " saved image count exceeded, restart the sketch");
  }
}

void getFilename()
{
  int readTime = millis() + 20;
  int inByte = 0;
  filename = "";
  while ( serial.available() > 0 && millis() < readTime && inByte != '.')
  {
    inByte = serial.read();
    if (inByte == ' ') inByte = '_';
    if ( unicodeCheck(inByte) ) filename += (char)inByte;
  }

  inByte = serial.read();
       if (inByte == '@') filename += "_" + timeCode();
  else if (inByte == '#') filename += "_" + saved_image_count%100;
  else if (inByte == '%') filename += "_" + millis();
  else if (inByte != '*') filename  = "";

  inByte = serial.read();
       if (inByte == 'j') image_type =".jpg";
  else if (inByte == 'b') image_type =".bmp";
  else if (inByte == 'p') image_type =".png";
  else if (inByte == 't') image_type =".tif";
}

bool unicodeCheck(int unicode)
{
  if (  unicode >= '0' && unicode <= '9' ) return true;
  if ( (unicode >= 'A' && unicode <= 'Z' ) || (unicode >= 'a' && unicode <= 'z')) return true;
  if (  unicode == '_' || unicode == '/' ) return true;
  return false;
}

String timeCode()
{
 String timeCode  = (int)year() + "_" + (int)month()  + "_" + (int)day() + "_";
        timeCode += (int)hour() + "_" + (int)minute() + "_" + (int)second(); 
 return timeCode;
}

int renderPixels()
{
  if ( serial.available() > 0 ) {

    // Add the latest byte from the serial port to array:
    while (serial.available()>0)
    {
      rgb[serialCount++] = serial.read();

      // If we have 3 colour bytes:
      if ( serialCount >= color_bytes ) {
        serialCount = 0;
        pixel_count++;
        if (color_bytes == 3)
        {
          stroke(rgb[indexRed], rgb[indexGreen], rgb[indexBlue], 1000);
        } else
        { // Can cater for various byte orders
          //stroke( (rgb[0] & 0x1F)<<3, (rgb[0] & 0xE0)>>3 | (rgb[1] & 0x07)<<5, (rgb[1] & 0xF8));
          //stroke( (rgb[1] & 0x1F)<<3, (rgb[1] & 0xE0)>>3 | (rgb[0] & 0x07)<<5, (rgb[0] & 0xF8));
          stroke( (rgb[0] & 0xF8), (rgb[1] & 0xE0)>>3 | (rgb[0] & 0x07)<<5, (rgb[1] & 0x1F)<<3);
          //stroke( (rgb[1] & 0xF8), (rgb[0] & 0xE0)>>3 | (rgb[1] & 0x07)<<5, (rgb[0] & 0x1F)<<3);
        }
        // We get some pixel merge aliasing if smooth() is defined, so draw pixel twice
        point(xpos + x_offset, ypos + y_offset);
        //point(xpos + x_offset, ypos + y_offset);

        lastPixelTime = millis();
        xpos++;
        if (xpos >= tft_width) {
          xpos = 0; 
          progressBar();
          ypos++;
          if (ypos>=tft_height) {
            ypos = 0;
            if ((int)percentage <100) {
              while (progress_bar++ < 64) print(" ");
              percent(100);
            }
            println("Image fetch time = " + (millis()-beginTime)/1000.0 + " s");
            return 5;
          }
        }
      }
    }
  } else
  {
    if (millis() > (lastPixelTime + pixelWaitTime))
    {
      println("");
      System.err.println(pixelWaitTime + "ms time-out for pixels exceeded...");
      if (pixel_count > 0) {
        bad_image_count++;
        System.err.print("Pixels missing = " + (tft_width * tft_height - pixel_count));
        System.err.println(", corrupted image not saved");
        System.err.println("Good image count = " + saved_image_count);
        System.err.println(" Bad image count = " + bad_image_count);
      }
      return 4;
    }
  }
  return 3;
}

void progressBar()
{
  progress_bar++;
  print(".");
  if (progress_bar >63)
  {
    progress_bar = 0;
    percentage = 0.5 + 100 * pixel_count/(0.001 + tft_width * tft_height);
    percent(percentage);
  }
}

void percent(float percentage)
{
  if (percentage > 100) percentage = 100;
  println(" [ " + (int)percentage + "% ]");
  textAlign(LEFT);
  textSize(16);
  noStroke();
  fill(bgcolor2);
  rect(10, height - 25, 70, 20);
  fill(0);
  text(" [ " + (int)percentage + "% ]", 10, height-8);
}

bool fadedImage()
{
  int opacity = frameCount - drawLoopCount;  // So we get increasing fade
  if (fade)
  {
    tint(255, opacity);
    //image(tft_img, x_offset, y_offset);
    noStroke();
    fill(50, 50, 50, opacity);
    rect( (width - tft_width)/2, y_offset, tft_width, tft_height);
    delay(10);
  }
  if (opacity > 50)       // End fade after 50 cycles
  {
    return true;
  }
  return false;
}

void drawButton(color buttonColor)
{
  stroke(0);
  fill(buttonColor);
  rect(500 - 100, 540 - 26, 80, 24);
  textAlign(CENTER);
  textSize(20);
  fill(0);
  if (running) text(" Pause ", 500 - 60, height-7);
  else text(" Run ", 500 - 60, height-7);
}

void buttonClicked()
{
  mouseClick = false;
  if (running) {
    running = false;
    drawButton(buttonStopped);
    System.err.println("");
    System.err.println("Stopped - click 'Run' button: ");
    //noStroke();
    //fill(50);
    //rect( (width - tft_width)/2, y_offset, tft_width, tft_height);
    beginTime = millis() + 500;
    dimmed = false;
    state = 4;
  } else {
    running = true;
    drawButton(buttonRunning);
  }
}

void mousePressed() {
  if (mouseX > (500 - 100) && mouseX < (500 - 20) && mouseY > (540 - 26) && mouseY < (540 - 2)) {
    mouseClick = true;
  }
}

*/
# 1 "C:\\Users\\Subhankar Karmakar\\Documents\\Arduino\\libraries\\TFT_eSPI\\examples\\Generic\\TFT_Screen_Capture\\screenServer.ino"
// Reads a screen image off the TFT and send it to a processing client sketch
// over the serial port. Use a high baud rate, e.g. for an ESP8266:
// Serial.begin(921600);

// At 921600 baud a 320 x 240 image with 16 bit colour transfers can be sent to the
// PC client in ~1.67s and 24 bit colour in ~2.5s which is close to the theoretical
// minimum transfer time.

// This sketch has been created to work with the TFT_eSPI library here:
// https://github.com/Bodmer/TFT_eSPI

// Created by: Bodmer 27/1/17
// Updated by: Bodmer 10/3/17
// Updated by: Bodmer 23/11/18 to support SDA reads and the ESP32
// Version: 0.08

// MIT licence applies, all text above must be included in derivative works

//====================================================================================
//                                  Definitions
//====================================================================================





// File names must be alpha-numeric characters (0-9, a-z, A-Z) or "/" underscore "_"
// other ascii characters are stripped out by client, including / generates
// sub-directories



// Filename extension
// '#' = add incrementing number, '@' = add timestamp, '%' add millis() timestamp,
// '*' = add nothing
// '@' and '%' will generate new unique filenames, so beware of cluttering up your
// hard drive with lots of images! The PC client sketch is set to limit the number of
// saved images to 1000 and will then prompt for a restart.


// Number of pixels to send in a burst (minimum of 1), no benefit above 8
// NPIXELS values and render times:
// NPIXELS 1 = use readPixel() = >5s and 16 bit pixels only
// NPIXELS >1 using rectRead() 2 = 1.75s, 4 = 1.68s, 8 = 1.67s


//====================================================================================
//                           Screen server call with no filename
//====================================================================================
// Start a screen dump server (serial or network) - no filename specified
bool screenServer(void)
{
  // With no filename the screenshot will be saved with a default name e.g. tft_screen_#.xxx
  // where # is a number 0-9 and xxx is a file type specified below
  return screenServer("tft_screenshots/screenshot" /* In case none is specified*/);
}

//====================================================================================
//                           Screen server call with filename
//====================================================================================
// Start a screen dump server (serial or network) - filename specified
bool screenServer(String filename)
{
  delay(0); // Equivalent to yield() for ESP8266;

  bool result = serialScreenServer(filename); // Screenshot serial port server
  //bool result = wifiScreenServer(filename);   // Screenshot WiFi UDP port server (WIP)

  delay(0); // Equivalent to yield()

  //Serial.println();
  //if (result) Serial.println(F("Screen dump passed :-)"));
  //else        Serial.println(F("Screen dump failed :-("));

  return result;
}

//====================================================================================
//                Serial server function that sends the data to the client
//====================================================================================
bool serialScreenServer(String filename)
{
  // Precautionary receive buffer garbage flush for 50ms
  uint32_t clearTime = millis() + 50;
  while ( millis() < clearTime && Serial.read() >= 0) delay(0); // Equivalent to yield() for ESP8266;

  bool wait = true;
  uint32_t lastCmdTime = millis(); // Initialise start of command time-out

  // Wait for the starting flag with a start time-out
  while (wait)
  {
    delay(0); // Equivalent to yield() for ESP8266;
    // Check serial buffer
    if (Serial.available() > 0) {
      // Read the command byte
      uint8_t cmd = Serial.read();
      // If it is 'S' (start command) then clear the serial buffer for 100ms and stop waiting
      if ( cmd == 'S' ) {
        // Precautionary receive buffer garbage flush for 50ms
        clearTime = millis() + 50;
        while ( millis() < clearTime && Serial.read() >= 0) delay(0); // Equivalent to yield() for ESP8266;

        wait = false; // No need to wait anymore
        lastCmdTime = millis(); // Set last received command time

        // Send screen size etc using a simple header with delimiters for client checks
        sendParameters(filename);
      }
    }
    else
    {
      // Check for time-out
      if ( millis() > lastCmdTime + 10000 /* 10s Maximum time to wait at start transfer*/) return false;
    }
  }

  uint8_t color[3 * 8 /* Must be integer division of both TFT width and TFT height*/]; // RGB and 565 format color buffer for N pixels

  // Send all the pixels on the whole screen
  for ( uint32_t y = 0; y < tft.height(); y++)
  {
    // Increment x by NPIXELS as we send NPIXELS for every byte received
    for ( uint32_t x = 0; x < tft.width(); x += 8 /* Must be integer division of both TFT width and TFT height*/)
    {
      delay(0); // Equivalent to yield() for ESP8266;

      // Wait here for serial data to arrive or a time-out elapses
      while ( Serial.available() == 0 )
      {
        if ( millis() > lastCmdTime + 100 /* 100ms Time-out between pixel requests*/) return false;
        delay(0); // Equivalent to yield() for ESP8266;
      }

      // Serial data must be available to get here, read 1 byte and
      // respond with N pixels, i.e. N x 3 RGB bytes or N x 2 565 format bytes
      if ( Serial.read() == 'X' ) {
        // X command byte means abort, so clear the buffer and return
        clearTime = millis() + 50;
        while ( millis() < clearTime && Serial.read() >= 0) delay(0); // Equivalent to yield() for ESP8266;
        return false;
      }
      // Save arrival time of the read command (for later time-out check)
      lastCmdTime = millis();







      // Fetch N 565 format pixels from x,y and put in buffer
      if (8 /* Must be integer division of both TFT width and TFT height*/ > 1) tft.readRect(x, y, 8 /* Must be integer division of both TFT width and TFT height*/, 1, (uint16_t *)color);
      else
      {
        uint16_t c = tft.readPixel(x, y);
        color[0] = c>>8;
        color[1] = c & 0xFF; // Swap bytes
      }
      // Send buffer to client
      Serial.write(color, 2 * 8 /* Must be integer division of both TFT width and TFT height*/); // Write all pixels in the buffer

    }
  }

  Serial.flush(); // Make sure all pixel bytes have been despatched

  return true;
}

//====================================================================================
//    Send screen size etc using a simple header with delimiters for client checks
//====================================================================================
void sendParameters(String filename)
{
  Serial.write('W'); // Width
  Serial.write(tft.width() >> 8);
  Serial.write(tft.width() & 0xFF);

  Serial.write('H'); // Height
  Serial.write(tft.height() >> 8);
  Serial.write(tft.height() & 0xFF);

  Serial.write('Y'); // Bits per pixel (16 or 24)
  if (8 /* Must be integer division of both TFT width and TFT height*/ > 1) Serial.write(16 /* 24 for RGB colour format, 16 for 565 colour format*/);
  else Serial.write(16); // readPixel() only provides 16 bit values

  Serial.write('?'); // Filename next
  Serial.print(filename);

  Serial.write('.'); // End of filename marker

  Serial.write('@'); // Filename extension identifier

  Serial.write(*"png" /* jpg, bmp, png, tif are valid*/); // First character defines file type j,b,p,t
}
