/*This is the screen 3 for the program */

#include <MCUFRIEND_kbv.h>
#include <Adafruit_GFX.h>
#include <TouchScreen.h>

#include <Fonts/FreeSans9pt7b.h>
#include <Fonts/FreeSans12pt7b.h>
#include <Fonts/FreeSerif12pt7b.h>
#include <FreeDefaultFonts.h>

#define MINPRESSURE 1
#define MAXPRESSURE 1000

#define BLACK   0x0000
#define BLUE    0x001F
#define RED     0xF800
#define GREEN   0x07E0
#define CYAN    0x07FF
#define MAGENTA 0xF81F
#define YELLOW  0xFFE0
#define WHITE   0xFFFF
#define RGB(r, g, b) (((r&0xF8)<<8)|((g&0xFC)<<3)|(b>>3))
#define GREY      RGB(127, 127, 127)
#define DARKGREY  RGB(64, 64, 64)
#define TURQUOISE RGB(0, 128, 128)
#define PINK      RGB(255, 128, 192)
#define OLIVE     RGB(128, 128, 0)
#define PURPLE    RGB(128, 0, 128)
#define AZURE     RGB(0, 128, 255)
#define ORANGE    RGB(255,128,64)
#define ILI9341_BLACK       0x0000      /*   0,   0,   0 */
#define ILI9341_NAVY        0x000F      /*   0,   0, 128 */
#define ILI9341_DARKGREEN   0x03E0      /*   0, 128,   0 */
#define ILI9341_DARKCYAN    0x03EF      /*   0, 128, 128 */
#define ILI9341_MAROON      0x7800      /* 128,   0,   0 */
#define ILI9341_PURPLE      0x780F      /* 128,   0, 128 */
#define ILI9341_OLIVE       0x7BE0      /* 128, 128,   0 */
#define ILI9341_LIGHTGREY   0xC618      /* 192, 192, 192 */
#define ILI9341_DARKGREY    0x7BEF      /* 128, 128, 128 */
#define ILI9341_BLUE        0x001F      /*   0,   0, 255 */
#define ILI9341_GREEN       0x07E0      /*   0, 255,   0 */
#define ILI9341_CYAN        0x07FF      /*   0, 255, 255 */
#define ILI9341_RED         0xF800      /* 255,   0,   0 */
#define ILI9341_MAGENTA     0xF81F      /* 255,   0, 255 */
#define ILI9341_YELLOW      0xFFE0      /* 255, 255,   0 */
#define ILI9341_WHITE       0xFFFF      /* 255, 255, 255 */
#define ILI9341_ORANGE      0xFD20      /* 255, 165,   0 */
#define ILI9341_GREENYELLOW 0xAFE5      /* 173, 255,  47 */
#define ILI9341_PINK        0xF81F

MCUFRIEND_kbv tft;

const int XP = 8, XM = A2, YP = A3, YM = 9;
const int TS_LEFT = 155, TS_RT = 885, TS_TOP = 931, TS_BOT = 100;
TouchScreen ts = TouchScreen(XP, YP, XM, YM, 300);

Adafruit_GFX_Button Ok , Back , One , Two , Three , Four;
int pixel_x, pixel_y;

bool Touch_getXY(void)
{
  TSPoint p = ts.getPoint();
  pinMode(YP, OUTPUT);      //restore shared pins
  pinMode(XM, OUTPUT);
  digitalWrite(YP, HIGH);   //because TFT control pins
  digitalWrite(XM, HIGH);
  bool pressed = (p.z > MINPRESSURE && p.z < MAXPRESSURE);
  if (pressed) {
    pixel_x = map(p.x, 155, 885, 0, 320);
    pixel_y = map(p.y, 931, 100, 0, 480);
  }
  return pressed;
}

void showmsgXY(int x, int y, int sz, const GFXfont *f, const char *msg)
{
  int16_t x1, y1;
  uint16_t wid, ht;
  tft.setFont(f);
  tft.setCursor(x, y);
  tft.setTextColor(WHITE);
  tft.setTextSize(sz);
  tft.print(msg);
  tft.setFont(NULL);
}

void showmsgXYM(int x, int y, int sz, const GFXfont *f, const char *msg)
{
  int16_t x1, y1;
  uint16_t wid, ht;
  tft.setFont(f);
  tft.setCursor(x, y);
  tft.setTextColor(AZURE);
  tft.setTextSize(sz);
  tft.print(msg);
  tft.setFont(NULL);
}

void setup(void)
{
  Serial.begin(9600);
  uint16_t ID = tft.readID();
  Serial.print("TFT ID = 0x");
  Serial.println(ID, HEX);
  Serial.println("Setup Started for Screen 3");

  tft.begin(ID);
  tft.setRotation(0);            //PORTRAIT
  tft.fillScreen(BLACK);

  showmsgXY(40, 30, 2, &FreeSans9pt7b, "Slot Selection");
  showmsgXYM(1, 55, 1, &FreeSans9pt7b, "These Slots are just for keeping the      space sorted , you have to pay as per      time kept !") ;
  tft.setFont(NULL);

  One.initButton(&tft,  50, 150, 75, 50, WHITE, ILI9341_ORANGE, WHITE, "1", 3);
  Two.initButton(&tft,  50, 150 + 50 + 30, 75, 50, WHITE, ILI9341_ORANGE, WHITE, "2", 3);
  Three.initButton(&tft, 50, 150 + 50 + 30 + 50 + 30, 75, 50, WHITE, ILI9341_ORANGE, WHITE, "3", 3);
  Four.initButton(&tft,  50, 150 + 50 + 30 + 50 + 30 + 50 + 30, 75, 50, WHITE, ILI9341_ORANGE, WHITE, "4", 3);
  Ok.initButton(&tft,  280, 460, 80, 30, ILI9341_GREEN, ILI9341_GREEN , BLACK, "Ok", 2);
  Back.initButton(&tft,  41, 460, 80, 30, ILI9341_RED, ILI9341_RED, WHITE, "Back", 2);

  One.drawButton(false);
  Two.drawButton(false);
  Three.drawButton(false);
  Four.drawButton(false);
  Ok.drawButton(false);
  Back.drawButton(false);

  showmsgXY(98, 133, 1, &FreeSans9pt7b, "Ground Floor \n                    For parking time :\n                    less than 3 hours") ;
  showmsgXY(98, 133 + 80, 1, &FreeSans9pt7b, "1st Floor \n                    For parking time :\n                    more than 3 hours") ;
  showmsgXY(98, 133 + 80 + 80, 1, &FreeSans9pt7b, "2nd Floor \n                    For parking time :\n                    more than 6 hours") ;
  showmsgXY(98, 133 + 80 + 80 + 80, 1, &FreeSans9pt7b, "3rd Floor \n                    For parking time :\n                    more than 9 hours") ;
}

void loop(void)
{
  bool down = Touch_getXY();
  Ok.press(down && Ok.contains(pixel_x, pixel_y));
  Back.press(down && Back.contains(pixel_x, pixel_y));

  One.press(down && One.contains(pixel_x, pixel_y));
  Two.press(down && Two.contains(pixel_x, pixel_y));
  Three.press(down && Three.contains(pixel_x, pixel_y));
  Four.press(down && Four.contains(pixel_x, pixel_y));

  if (Ok.justReleased())
    Ok.drawButton();
  if (Back.justReleased())
    Back.drawButton();
  if (Ok.justPressed()) {
    Ok.drawButton(true);
    Serial.print("Go Forward to Screen 3") ;
  }
  if (Back.justPressed()) {
    Back.drawButton(true);
    Serial.print("Go Back to Screen 1") ;
  }

  if (One.justReleased())
    One.drawButton();
  if (Two.justReleased())
    Two.drawButton();
  if (One.justPressed()) {
    One.drawButton(true);
    Serial.print("Go Forward to Screen 3") ;
  }
  if (Two.justPressed()) {
    Two.drawButton(true);
    Serial.print("Go Back to Screen 1") ;
  }

  if (Three.justReleased())
    Three.drawButton();
  if (Four.justReleased())
    Four.drawButton();
  if (Three.justPressed()) {
    Three.drawButton(true);
    Serial.print("Go Forward to Screen 3") ;
  }
  if (Four.justPressed()) {
    Four.drawButton(true);
    Serial.print("Go Back to Screen 1") ;
  }

}