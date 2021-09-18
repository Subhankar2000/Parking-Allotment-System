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
/******************* UI details */
#define BUTTON_X 75
#define BUTTON_Y 120
#define BUTTON_W 60
#define BUTTON_H 45
#define BUTTON_SPACING_X 25
#define BUTTON_SPACING_Y 15
#define BUTTON_TEXTSIZE 2
#define TEXT_X 50
#define TEXT_Y 30
#define TEXT_W 220
#define TEXT_H 50
#define TEXT_TSIZE 3
#define TEXT_TCOLOR WHITE
#define TEXT_LEN 11
char textfield[TEXT_LEN + 1] = "";
uint8_t textfield_i = 0;
#define TS_MINX 155
#define TS_MINY 100
#define TS_MAXX 885
#define TS_MAXY 931
#define STATUS_X 10
#define STATUS_Y 65
/******************* UI details */

MCUFRIEND_kbv tft;

int screen = 1 ;
const int XP = 8, XM = A2, YP = A3, YM = 9;
const int TS_LEFT = 155, TS_RT = 885, TS_TOP = 931, TS_BOT = 100;
TouchScreen ts = TouchScreen(XP, YP, XM, YM, 300);
int pixel_x, pixel_y;

Adafruit_GFX_Button buttons[15];
/* create 15 buttons, in classic candybar phone style */
char buttonlabels[15][5] = {"Ok", "Clr", "Back", "1", "2", "3", "4", "5", "6", "7", "8", "9", "*", "0", "#" };
uint16_t buttoncolors[15] = {ILI9341_DARKGREEN, ILI9341_DARKGREY, ILI9341_RED,
                             ILI9341_BLUE, ILI9341_BLUE, ILI9341_BLUE,
                             ILI9341_BLUE, ILI9341_BLUE, ILI9341_BLUE,
                             ILI9341_BLUE, ILI9341_BLUE, ILI9341_BLUE,
                             ILI9341_ORANGE, AZURE, ILI9341_ORANGE
                            };

Adafruit_GFX_Button one , two ;
Adafruit_GFX_Button Ok , Back ;
Adafruit_GFX_Button One , Two , Three , Four;
Adafruit_GFX_Button E ;
Adafruit_GFX_Button Finish ;

void status(const __FlashStringHelper *msg) {
  tft.fillRect(STATUS_X, STATUS_Y, 240, 8, ILI9341_BLACK);
  tft.setCursor(STATUS_X, STATUS_Y);
  tft.setTextColor(ILI9341_WHITE);
  tft.setTextSize(1);
  tft.print(msg);
}

void status(char *msg) {
  tft.fillRect(STATUS_X, STATUS_Y, 240, 8, ILI9341_BLACK);
  tft.setCursor(STATUS_X, STATUS_Y);
  tft.setTextColor(ILI9341_WHITE);
  tft.setTextSize(1);
  tft.print(msg);
}

bool Touch_getXY(void) {
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



void screen1() {
  screen = 1 ;
  setup() ;
}

void screen2() {
  screen = 2 ;
  setup() ;
}

void screen3() {
  screen = 3 ;
  setup() ;
}

void screen4() {
  screen = 4 ;
  setup() ;
}

void screen5() {
  screen = 5 ;
  setup() ;
}

void numpad() {
  screen = 9 ;
  setup() ;
}


void setup(void)
{
  Serial.begin(9600);
  uint16_t ID = tft.readID();
  Serial.print("TFT ID = 0x");
  Serial.println(ID, HEX);
  tft.begin(ID);
  tft.setRotation(0);            //PORTRAIT

  if ( screen == 1 ) {
    tft.fillScreen(BLACK);

    showmsgXY(15, 50, 3, &FreeSans9pt7b, "Car Parking");
    tft.setFont(NULL);
    one.initButton(&tft,  60, 150, 100, 50, YELLOW, YELLOW, BLACK, "1", 3);
    two.initButton(&tft,  60, 250, 100, 50, MAGENTA, MAGENTA, WHITE, "2", 3);


    tft.setCursor(120, 130);
    tft.setTextColor(YELLOW);
    tft.setTextSize(2);
    tft.print("Keep your car");
    tft.setCursor(120, 150);
    tft.print("inside");

    tft.setCursor(120, 242);
    tft.setTextColor(WHITE);
    tft.setTextSize(2);
    tft.print("Take your car");

    one.drawButton(false);
    two.drawButton(false);
  }

  if ( screen == 2 ) {
    tft.fillScreen(BLACK);

    showmsgXY(40, 30, 2, &FreeSans9pt7b, "Available Slots");
    showmsgXYM(1, 42, 1, NULL, "The Following slots are only occupied by users based on their preference of time they want to keep thier  cars, this has nothing to do with the amount that hasto be paid at the time of exit ,                     the user's preference helps the parking space to be  in a sorted condition !");
    tft.setFont(NULL);

    Ok.initButton(&tft,  280, 460, 80, 30, ILI9341_GREEN, ILI9341_GREEN , BLACK, "Ok", 2);
    Back.initButton(&tft,  41, 460, 80, 30, ILI9341_RED, ILI9341_RED, WHITE, "Back", 2);

    Ok.drawButton(false);
    Back.drawButton(false);
    tft.drawRect(10 , 110, 60, 60, ILI9341_WHITE);
    tft.drawRect(10 , 110 + 60 + 20, 60, 60, ILI9341_WHITE);
    tft.drawRect(10 , 110 + 60 + 20 + 60 + 20, 60, 60, ILI9341_WHITE);
    tft.drawRect(10 , 110 + 60 + 20 + 60 + 20 + 60 + 20, 60, 60, ILI9341_WHITE);
    showmsgXY(10 + 60 + 15, 110 + 13, 1, &FreeSans9pt7b, "3rd Floor \n                 For parking time :\n                 more than 9 hours") ;
    showmsgXY(10 + 60 + 15, 110 + 60 + 20 + 13, 1, &FreeSans9pt7b, "2nd Floor \n                 For parking time :\n                 more than 6 hours") ;
    showmsgXY(10 + 60 + 15,  110 + 60 + 20 + 60 + 20 + 13, 1, &FreeSans9pt7b, "1st Floor \n                 For parking time :\n                 more than 3 hours") ;
    showmsgXY(10 + 60 + 15,  110 + 60 + 20 + 60 + 20 + 60 + 20 + 13, 1, &FreeSans9pt7b, "Ground Floor \n                 For parking time :\n                 less than 3 hours") ;
  }

  if ( screen == 3 ) {
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

  if ( screen == 4 ) {
    tft.fillScreen(BLACK);

    showmsgXY(75, 40, 2, &FreeSans12pt7b, "Unique \n  Identification");
    tft.setFont(NULL);

    Ok.initButton(&tft,  280, 460, 80, 30, ILI9341_GREEN, ILI9341_GREEN , BLACK, "Ok", 2);
    Back.initButton(&tft,  41, 460, 80, 30, ILI9341_RED, ILI9341_RED, WHITE, "Back", 2);

    E.initButton(&tft,  160 , 210, 110, 50, BLACK, ILI9341_ORANGE, BLACK, "Numpad", 2);

    Ok.drawButton(false);
    Back.drawButton(false);
    E.drawButton(false);

    showmsgXYM(1, 133, 1, &FreeSans9pt7b, "Enter your Vehicle's Registration no.     (from number plate) for our records") ;
    tft.drawRect(50, 260, 220, 50, ILI9341_DARKGREY );
  }

  if ( screen == 5 ) {
    tft.fillScreen(BLACK);

    showmsgXY(5, 50, 3, &FreeSans9pt7b, "Confirmation");
    showmsgXY(1, 95, 1, &FreeSans9pt7b, "You can now just keep your vehicle at \nthe prefered floor as per your choice of no. of hours , at the time of exit just \nchoose the option 2 and enter vehicle's number again , pay and take your car \nback , now press finish or to edit the \nprovided data press Back .") ;
    tft.setFont(NULL);

    Finish.initButton(&tft,  160 , 300, 150, 50, BLACK, ILI9341_GREEN, BLACK, "Finish", 3);
    Back.initButton(&tft,  41, 460, 80, 30, ILI9341_RED, ILI9341_RED, WHITE, "Back", 2);

    Finish.drawButton(false);
    Back.drawButton(false);
  }

  if ( screen == 9 ) {
    tft.fillScreen(BLACK);
    for (uint8_t row = 0; row < 5; row++) {
      for (uint8_t col = 0; col < 3; col++) {
        buttons[col + row * 3].initButton(&tft, BUTTON_X + col * (BUTTON_W + BUTTON_SPACING_X),
                                          BUTTON_Y + row * (BUTTON_H + BUTTON_SPACING_Y), // x, y, w, h, outline, fill, text
                                          BUTTON_W, BUTTON_H, BLACK, buttoncolors[col + row * 3], ILI9341_WHITE,
                                          buttonlabels[col + row * 3], BUTTON_TEXTSIZE);
        buttons[col + row * 3].drawButton();
      }
    }

    // create 'text field'
    tft.drawRect(TEXT_X, TEXT_Y, TEXT_W, TEXT_H, ILI9341_DARKGREY );
  }
}

void loop(void)
{
  if (screen == 1) {
    bool down = Touch_getXY();
    one.press(down && one.contains(pixel_x, pixel_y));
    two.press(down && two.contains(pixel_x, pixel_y));
    if (one.justReleased())
      one.drawButton();
    if (two.justReleased())
      two.drawButton();
    if (one.justPressed()) {
      one.drawButton(true);
      screen2() ;
    }
    if (two.justPressed()) {
      two.drawButton(true);
    }
  }

  if (screen == 2) {
    bool down = Touch_getXY();
    Ok.press(down && Ok.contains(pixel_x, pixel_y));
    Back.press(down && Back.contains(pixel_x, pixel_y));
    if (Ok.justReleased())
      Ok.drawButton();
    if (Back.justReleased())
      Back.drawButton();
    if (Ok.justPressed()) {
      Ok.drawButton(true);
      screen3() ;
    }
    if (Back.justPressed()) {
      Back.drawButton(true);
      screen1() ;
    }
  }

  if (screen == 3 ) {
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
      screen4() ;
    }
    if (Back.justPressed()) {
      Back.drawButton(true);
      screen2() ;
    }

    if (One.justReleased())
      One.drawButton();
    if (Two.justReleased())
      Two.drawButton();
    if (One.justPressed()) {
      One.drawButton(true);
      Serial.print("One pressed") ;
    }
    if (Two.justPressed()) {
      Two.drawButton(true);
      Serial.print("Two pressed") ;
    }

    if (Three.justReleased())
      Three.drawButton();
    if (Four.justReleased())
      Four.drawButton();
    if (Three.justPressed()) {
      Three.drawButton(true);
      Serial.print("Three Pressed") ;
    }
    if (Four.justPressed()) {
      Four.drawButton(true);
      Serial.print("Four Pressed") ;
    }
  }

  if (screen == 4) {
    bool down = Touch_getXY();

    Ok.press(down && Ok.contains(pixel_x, pixel_y));
    Back.press(down && Back.contains(pixel_x, pixel_y));
    E.press(down && E.contains(pixel_x, pixel_y));

    if (Ok.justReleased())
      Ok.drawButton();
    if (Back.justReleased())
      Back.drawButton();
    if (Ok.justPressed()) {
      Ok.drawButton(true);
      screen5() ;
    }
    if (Back.justPressed()) {
      Back.drawButton(true);
      screen3() ;
    }
    if (E.justReleased())
      E.drawButton();
    if (E.justPressed()) {
      E.drawButton(true);
      numpad();
    }
    showmsgXY(50 + 8, 260 + 14, 2 , NULL , textfield) ;
  }

  if (screen == 5) {
    bool down = Touch_getXY();
    Finish.press(down && Finish.contains(pixel_x, pixel_y));
    Back.press(down && Back.contains(pixel_x, pixel_y));
    if (Finish.justReleased())
      Finish.drawButton();
    if (Back.justReleased())
      Back.drawButton();
    if (Finish.justPressed()) {
      Finish.drawButton(true);
      screen1() ;
    }
    if (Back.justPressed()) {
      Back.drawButton(true);
      screen4() ;
    }
  }

  if (screen == 9) {
    digitalWrite(13, HIGH);
    TSPoint p = ts.getPoint();
    pinMode(YP, OUTPUT);      //restore shared pins
    pinMode(XM, OUTPUT);
    digitalWrite(YP, HIGH);   //because TFT control pins
    digitalWrite(XM, HIGH);
    bool pressed = (p.z > MINPRESSURE && p.z < MAXPRESSURE);
    if (p.z > MINPRESSURE && p.z < MAXPRESSURE) {
      // scale from 0->1023 to tft.width
      p.x = map(p.x, TS_MINX, TS_MAXX, 0, tft.width());
      p.y = map(p.y, TS_MINY, TS_MAXY, tft.height(), 0);
    }

    // go thru all the buttons, checking if they were pressed
    for (uint8_t b = 0; b < 15; b++) {
      if (buttons[b].contains(p.x, p.y)) {
        //Serial.print("Pressing: "); Serial.println(b);
        buttons[b].press(true);  // tell the button it is pressed
      } else {
        buttons[b].press(false);  // tell the button it is NOT pressed
      }
    }

    // now we can ask the buttons if their state has changed
    for (uint8_t b = 0; b < 15; b++) {
      if (buttons[b].justReleased()) {
        // Serial.print("Released: "); Serial.println(b);
        buttons[b].drawButton();  // draw normal
      }

      if (buttons[b].justPressed()) {
        buttons[b].drawButton(true);  // draw invert!

        // if a numberpad button, append the relevant # to the textfield
        if (b >= 3) {
          if (textfield_i < TEXT_LEN) {
            textfield[textfield_i] = buttonlabels[b][0];
            textfield_i++;
            textfield[textfield_i] = 0; // zero terminate
          }
        }

        // clr button! delete char
        if (b == 1) {

          textfield[textfield_i] = 0;
          if (textfield > 0) {
            textfield_i--;
            textfield[textfield_i] = ' ';
          }
        }

        // update the current text field
        Serial.println(textfield);
        tft.setCursor(TEXT_X + 8, TEXT_Y + 14);
        tft.setTextColor(TEXT_TCOLOR, ILI9341_BLACK);
        tft.setTextSize(TEXT_TSIZE);
        tft.print(textfield);

        if (b == 2) {
          status(F("Back"));
          screen4() ;
        }

        if (b == 0) {
          status(F("Ok"));
          delay(100);
          Serial.print("Sending"); Serial.println(textfield);
          screen4() ;
        }

        delay(100); // UI debouncing
      }
    }
  }
}

