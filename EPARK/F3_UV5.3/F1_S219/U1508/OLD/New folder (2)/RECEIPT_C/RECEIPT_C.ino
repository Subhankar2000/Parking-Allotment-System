/*  3.5" TFT DISPLAY WITH DRIVER ILI9481 */
#include <MCUFRIEND_kbv.h>
#include <Adafruit_GFX.h>
#include <TouchScreen.h>

/*   DS3231 RTC MODULE */
#include <DS3231.h>
#include <Wire.h>

/*  CUSTOM FONTS USED */
#include <Fonts/FreeSans9pt7b.h>
#include <Fonts/FreeSans12pt7b.h>
#include <Fonts/FreeSerif12pt7b.h>
#include <FreeDefaultFonts.h>

/*  TOUCHSCREEN ADJUSTMENT  */
#define MINPRESSURE 1
#define MAXPRESSURE 1000

/*  DEFINING COLORS SO THAT THEY CAN BE USED */
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
#define ILI9481_BLACK       0x0000      /*   0,   0,   0 */
#define ILI9481_NAVY        0x000F      /*   0,   0, 128 */
#define ILI9481_DARKGREEN   0x03E0      /*   0, 128,   0 */
#define ILI9481_DARKCYAN    0x03EF      /*   0, 128, 128 */
#define ILI9481_MAROON      0x7800      /* 128,   0,   0 */
#define ILI9481_PURPLE      0x780F      /* 128,   0, 128 */
#define ILI9481_OLIVE       0x7BE0      /* 128, 128,   0 */
#define ILI9481_LIGHTGREY   0xC618      /* 192, 192, 192 */
#define ILI9481_DARKGREY    0x7BEF      /* 128, 128, 128 */
#define ILI9481_BLUE        0x001F      /*   0,   0, 255 */
#define ILI9481_GREEN       0x07E0      /*   0, 255,   0 */
#define ILI9481_CYAN        0x07FF      /*   0, 255, 255 */
#define ILI9481_RED         0xF800      /* 255,   0,   0 */
#define ILI9481_MAGENTA     0xF81F      /* 255,   0, 255 */
#define ILI9481_YELLOW      0xFFE0      /* 255, 255,   0 */
#define ILI9481_WHITE       0xFFFF      /* 255, 255, 255 */
#define ILI9481_ORANGE      0xFD20      /* 255, 165,   0 */
#define ILI9481_GREENYELLOW 0xAFE5      /* 173, 255,  47 */

MCUFRIEND_kbv tft;    /* CREATION OF OBJECT FOR TFT */



const int XP = 8, XM = A2, YP = A3, YM = 9;       /* FOR TOUCH INPUT*/
const int TS_LEFT = 155, TS_RT = 885, TS_TOP = 931, TS_BOT = 100;   /*CALIBERATED VALUES*/

TouchScreen ts = TouchScreen(XP, YP, XM, YM, 300);  /*TOUCH INPUT INITIALIZATION*/

int pixel_x, pixel_y;   /* VARIABLES FOR TOUCH INPUT */

Adafruit_GFX_Button yes , no;

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


/*  CUSTOM FUNCTION THAT HELPS IN DISPLAYING TEXT EASILY WITH ONE FUNCTION */
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

/*  CUSTOM FUNCTION THAT HELPS DISPLAYING TEXT WITH COLOR - AZURE */
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

/*  CUSTOM FUNCTION THAT HELPS DISPLAYING TEXT WITH COLOR - RED */
void showmsgXYR(int x, int y, int sz, const GFXfont *f, const char *msg)
{
  int16_t x1, y1;
  uint16_t wid, ht;
  tft.setFont(f);
  tft.setCursor(x, y);
  tft.setTextColor(RED);
  tft.setTextSize(sz);
  tft.print(msg);
  tft.setFont(NULL);
}

/*  CUSTOM FUNCTION THAT HELPS DISPLAYING TEXT WITH COLOR - YELLOW */
void showmsgXYG(int x, int y, int sz, const GFXfont *f, const char *msg)
{
  int16_t x1, y1;
  uint16_t wid, ht;
  tft.setFont(f);
  tft.setCursor(x, y);
  tft.setTextColor(YELLOW);
  tft.setTextSize(sz);
  tft.print(msg);
  tft.setFont(NULL);
}

void showmsgXYB(int x, int y, int sz, const GFXfont *f, const char *msg)
{
  int16_t x1, y1;
  uint16_t wid, ht;
  tft.setFont(f);
  tft.setCursor(x, y);
  tft.setTextColor(BLACK);
  tft.setTextSize(sz);
  tft.print(msg);
  tft.setFont(NULL);
}

/*  CUSTOM FUNCTION THAT HELPS DISPLAYING TEXT WITH COLOR - MAGENTA */
void showmsgXYG1(int x, int y, int sz, const GFXfont *f, const char *msg)
{
  int16_t x1, y1;
  uint16_t wid, ht;
  tft.setFont(f);
  tft.setCursor(x, y);
  tft.setTextColor(MAGENTA);
  tft.setTextSize(sz);
  tft.print(msg);
  tft.setFont(NULL);
}
int screen = 145 ;
void setup(void)
{
  Serial.begin(9600);   /* FOR DEBUGGING PURPOSES */
  uint16_t ID = tft.readID(); /* COMMAND TO FIND OUT THE LCD DRIVER AUTOMATICALLY */
  Serial.print("TFT ID = 0x");
  Serial.println(ID, HEX);



  /*----BUTTON LOGIC-----*/

  Serial1.begin(9600);

  /*  TFT INITIALIZATION , CAN WORK FOR ALMOST ANY ILI94XX DISPLAY SUPPORTING THE MCUFRIEND AND ADAFRUIT GFX LIBRARY AND HAVING RESOLUTION 320X480
      ANY RESOLUTION ABOVE JUST TAKE A RATIO AND MULTIPLY THAT NUMBER WITH THE POSITIONS TO FIT THE SIZE OF THE SCREEN OR JUST RUN IT IN A BIGGER
      SCREEN YOU WILL GET A DISPLAY SIZE OF 3.5 INCHES
  */

  tft.begin(ID);
  tft.setRotation(0);            /* PORTRAIT */

  /*   HERE THE MAIN TRICK LIES OF HOW TO SETUP ALL BUTTONS WITHOUT WRITING ALL THEM IN ONE PLACE
       THE VALUES MENTIONED IN THE PREVIOUS COMMENT SIMPLY REPRESENT THE VALUES OF DIFFERENT SCREEN
       AND THE SCREEN THATS NEEDED THAT VALUE IS JUST SET IN THE FUNCTIONS FOR THAT SCREENS AND THE
       SETUP FUNCTION IS CALLED SO THAT THE PARTICULAR SECTION OF THE SETUP AND LOOP ONLY GETS EXECUTED
  */

  if ( screen == 145 ) {

    tft.fillScreen(BLACK);

    showmsgXYM(1, 50, 3, &FreeSans9pt7b, "E-Receipt");
    showmsgXY(1 , 50 + 40 , 2 , &FreeSans9pt7b, "Do you want \nE-receipt ?");
    tft.setFont(NULL);
    yes.initButton(&tft,  60 + 30, 200, 100, 50, GREEN, GREEN, BLACK, "Yes", 3);
    no.initButton(&tft,  60 + 170, 200, 100, 50, RED, RED, WHITE, "No", 3);

    showmsgXYG(1 , 260 , 1 , &FreeSans9pt7b, "If you click yes , you will be prompted to give your phone number and your \nphone number will be stored to provide an e-receipt at the end while taking your car out") ;
    showmsgXY(1 , 260 + 120 , 1 , &FreeSans9pt7b, "If you click no , then your entry will be \nconfirmed and you can keep your car");



    yes.drawButton(false);
    no.drawButton(false);

  }
}

void loop(void)
{
  if (screen == 145) {

    bool down = Touch_getXY();
    yes.press(down && yes.contains(pixel_x, pixel_y));
    no.press(down && no.contains(pixel_x, pixel_y));
    if (yes.justReleased())
      yes.drawButton();
    if (no.justReleased())
      no.drawButton();
    if (yes.justPressed()) {
      yes.drawButton(true);
      //screen45() ;
    }
    if (no.justPressed()) {
      no.drawButton(true);
      //screen5() ;
    }
  }
}

