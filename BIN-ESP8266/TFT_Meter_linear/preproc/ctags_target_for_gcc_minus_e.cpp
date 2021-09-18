# 1 "C:\\Users\\Subhankar Karmakar\\Documents\\Arduino\\libraries\\TFT_eSPI\\examples\\320 x 240\\TFT_Meter_linear\\TFT_Meter_linear.ino"
/*
 An example analogue meter using a ILI9341 TFT LCD screen

 Needs Font 2 (also Font 4 if using large scale label)

 Make sure all the display driver and pin connections are correct by
 editing the User_Setup.h file in the TFT_eSPI library folder.

 #########################################################################
 ###### DON'T FORGET TO UPDATE THE User_Setup.h FILE IN THE LIBRARY ######
 #########################################################################
 
Updated by Bodmer for variable meter size
 */

// Define meter size as 1 for tft.rotation(0) or 1.3333 for tft.rotation(1)


# 20 "C:\\Users\\Subhankar Karmakar\\Documents\\Arduino\\libraries\\TFT_eSPI\\examples\\320 x 240\\TFT_Meter_linear\\TFT_Meter_linear.ino" 2
# 21 "C:\\Users\\Subhankar Karmakar\\Documents\\Arduino\\libraries\\TFT_eSPI\\examples\\320 x 240\\TFT_Meter_linear\\TFT_Meter_linear.ino" 2

TFT_eSPI tft = TFT_eSPI(); // Invoke custom library



float ltx = 0; // Saved x coord of bottom of needle
uint16_t osx = 1.3333*120, osy = 1.3333*120; // Saved x & y coords
uint32_t updateTime = 0; // time for next update

int old_analog = -999; // Value last displayed

int value[6] = {0, 0, 0, 0, 0, 0};
int old_value[6] = { -1, -1, -1, -1, -1, -1};
int d = 0;

void setup(void) {
  tft.init();
  tft.setRotation(1);
  Serial.begin(57600); // For debug
  tft.fillScreen(0x0000 /*   0,   0,   0 */);

  analogMeter(); // Draw analogue meter

  updateTime = millis(); // Next update time
}


void loop() {
  if (updateTime <= millis()) {
    updateTime = millis() + 35; // Update emter every 35 milliseconds

    // Create a Sine wave for testing
    d += 4; if (d >= 360) d = 0;
    value[0] = 50 + 50 * sin((d + 0) * 0.0174532925);

    plotNeedle(value[0], 0); // It takes between 2 and 12ms to replot the needle with zero delay
  }
}


// #########################################################################
//  Draw the analogue meter on the screen
// #########################################################################
void analogMeter()
{

  // Meter outline
  tft.fillRect(0, 0, 1.3333*239, 1.3333*126, 0x5AEB);
  tft.fillRect(5, 3, 1.3333*230, 1.3333*119, 0xFFFF /* 255, 255, 255 */);

  tft.setTextColor(0x0000 /*   0,   0,   0 */); // Text colour

  // Draw ticks every 5 degrees from -50 to +50 degrees (100 deg. FSD swing)
  for (int i = -50; i < 51; i += 5) {
    // Long scale tick length
    int tl = 15;

    // Coodinates of tick to draw
    float sx = cos((i - 90) * 0.0174532925);
    float sy = sin((i - 90) * 0.0174532925);
    uint16_t x0 = sx * (1.3333*100 + tl) + 1.3333*120;
    uint16_t y0 = sy * (1.3333*100 + tl) + 1.3333*140;
    uint16_t x1 = sx * 1.3333*100 + 1.3333*120;
    uint16_t y1 = sy * 1.3333*100 + 1.3333*140;

    // Coordinates of next tick for zone fill
    float sx2 = cos((i + 5 - 90) * 0.0174532925);
    float sy2 = sin((i + 5 - 90) * 0.0174532925);
    int x2 = sx2 * (1.3333*100 + tl) + 1.3333*120;
    int y2 = sy2 * (1.3333*100 + tl) + 1.3333*140;
    int x3 = sx2 * 1.3333*100 + 1.3333*120;
    int y3 = sy2 * 1.3333*100 + 1.3333*140;

    // Yellow zone limits
    //if (i >= -50 && i < 0) {
    //  tft.fillTriangle(x0, y0, x1, y1, x2, y2, TFT_YELLOW);
    //  tft.fillTriangle(x1, y1, x2, y2, x3, y3, TFT_YELLOW);
    //}

    // Green zone limits
    if (i >= 0 && i < 25) {
      tft.fillTriangle(x0, y0, x1, y1, x2, y2, 0x07E0 /*   0, 255,   0 */);
      tft.fillTriangle(x1, y1, x2, y2, x3, y3, 0x07E0 /*   0, 255,   0 */);
    }

    // Orange zone limits
    if (i >= 25 && i < 50) {
      tft.fillTriangle(x0, y0, x1, y1, x2, y2, 0xFDA0 /* 255, 180,   0 */);
      tft.fillTriangle(x1, y1, x2, y2, x3, y3, 0xFDA0 /* 255, 180,   0 */);
    }

    // Short scale tick length
    if (i % 25 != 0) tl = 8;

    // Recalculate coords incase tick lenght changed
    x0 = sx * (1.3333*100 + tl) + 1.3333*120;
    y0 = sy * (1.3333*100 + tl) + 1.3333*140;
    x1 = sx * 1.3333*100 + 1.3333*120;
    y1 = sy * 1.3333*100 + 1.3333*140;

    // Draw tick
    tft.drawLine(x0, y0, x1, y1, 0x0000 /*   0,   0,   0 */);

    // Check if labels should be drawn, with position tweaks
    if (i % 25 == 0) {
      // Calculate label positions
      x0 = sx * (1.3333*100 + tl + 10) + 1.3333*120;
      y0 = sy * (1.3333*100 + tl + 10) + 1.3333*140;
      switch (i / 25) {
        case -2: tft.drawCentreString("0", x0, y0 - 12, 2); break;
        case -1: tft.drawCentreString("25", x0, y0 - 9, 2); break;
        case 0: tft.drawCentreString("50", x0, y0 - 7, 2); break;
        case 1: tft.drawCentreString("75", x0, y0 - 9, 2); break;
        case 2: tft.drawCentreString("100", x0, y0 - 12, 2); break;
      }
    }

    // Now draw the arc of the scale
    sx = cos((i + 5 - 90) * 0.0174532925);
    sy = sin((i + 5 - 90) * 0.0174532925);
    x0 = sx * 1.3333*100 + 1.3333*120;
    y0 = sy * 1.3333*100 + 1.3333*140;
    // Draw scale arc, don't draw the last part
    if (i < 50) tft.drawLine(x0, y0, x1, y1, 0x0000 /*   0,   0,   0 */);
  }

  tft.drawString("%RH", 1.3333*(5 + 230 - 40), 1.3333*(119 - 20), 2); // Units at bottom right
  tft.drawCentreString("%RH", 1.3333*120, 1.3333*70, 4); // Comment out to avoid font 4
  tft.drawRect(5, 3, 1.3333*230, 1.3333*119, 0x0000 /*   0,   0,   0 */); // Draw bezel line

  plotNeedle(0, 0); // Put meter needle at 0
}

// #########################################################################
// Update needle position
// This function is blocking while needle moves, time depends on ms_delay
// 10ms minimises needle flicker if text is drawn within needle sweep area
// Smaller values OK if text not in sweep area, zero for instant movement but
// does not look realistic... (note: 100 increments for full scale deflection)
// #########################################################################
void plotNeedle(int value, byte ms_delay)
{
  tft.setTextColor(0x0000 /*   0,   0,   0 */, 0xFFFF /* 255, 255, 255 */);
  char buf[8]; dtostrf(value, 4, 0, buf);
  tft.drawRightString(buf, 1.3333*40, 1.3333*(119 - 20), 2);

  if (value < -10) value = -10; // Limit value to emulate needle end stops
  if (value > 110) value = 110;

  // Move the needle until new value reached
  while (!(value == old_analog)) {
    if (old_analog < value) old_analog++;
    else old_analog--;

    if (ms_delay == 0) old_analog = value; // Update immediately if delay is 0

    float sdeg = map(old_analog, -10, 110, -150, -30); // Map value to angle
    // Calcualte tip of needle coords
    float sx = cos(sdeg * 0.0174532925);
    float sy = sin(sdeg * 0.0174532925);

    // Calculate x delta of needle start (does not start at pivot point)
    float tx = tan((sdeg + 90) * 0.0174532925);

    // Erase old needle image
    tft.drawLine(1.3333*(120 + 20 * ltx - 1), 1.3333*(140 - 20), osx - 1, osy, 0xFFFF /* 255, 255, 255 */);
    tft.drawLine(1.3333*(120 + 20 * ltx), 1.3333*(140 - 20), osx, osy, 0xFFFF /* 255, 255, 255 */);
    tft.drawLine(1.3333*(120 + 20 * ltx + 1), 1.3333*(140 - 20), osx + 1, osy, 0xFFFF /* 255, 255, 255 */);

    // Re-plot text under needle
    tft.setTextColor(0x0000 /*   0,   0,   0 */);
    tft.drawCentreString("%RH", 1.3333*120, 1.3333*70, 4); // // Comment out to avoid font 4

    // Store new needle end coords for next erase
    ltx = tx;
    osx = 1.3333*(sx * 98 + 120);
    osy = 1.3333*(sy * 98 + 140);

    // Draw the needle in the new postion, magenta makes needle a bit bolder
    // draws 3 lines to thicken needle
    tft.drawLine(1.3333*(120 + 20 * ltx - 1), 1.3333*(140 - 20), osx - 1, osy, 0xF800 /* 255,   0,   0 */);
    tft.drawLine(1.3333*(120 + 20 * ltx), 1.3333*(140 - 20), osx, osy, 0xF81F /* 255,   0, 255 */);
    tft.drawLine(1.3333*(120 + 20 * ltx + 1), 1.3333*(140 - 20), osx + 1, osy, 0xF800 /* 255,   0,   0 */);

    // Slow needle down slightly as it approaches new postion
    if (abs(old_analog - value) < 10) ms_delay += ms_delay / 5;

    // Wait before next update
    delay(ms_delay);
  }
}
