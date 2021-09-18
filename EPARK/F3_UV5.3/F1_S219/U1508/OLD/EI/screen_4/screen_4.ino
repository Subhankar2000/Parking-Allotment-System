/*This is the screen 4 for the program */

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
#define ILI9481_PINK        0xF81F
#define TEXT_LEN 6
char textfield[TEXT_LEN + 1] = "";
uint8_t textfield_i = 0;
struct car {
  char number[6] ;
  char pin1[6] ;
  char pin2[6] ;
  long int sTime ;
  int type ;
} c[4][5] ;

int i = 0 , j , k  ;

String textFT  , textFrt ;

int n = 0 , nr = 0 , tempT1 = -1 , tempT2 = -2 , counter[4] , temp1 = -1 , temp2 = -2 , temp3 = -3 , temp4 = -4 , found = 0 , mfound = -1;

double bcm = 0.006944 , ccm = 0.00833 ;
long int a ;
long int timeTemp , T1;
double T ;
int l , m  , o , p , i_temp , j_temp;


int n1 ;


MCUFRIEND_kbv tft;

const int XP = 8, XM = A2, YP = A3, YM = 9;
const int TS_LEFT = 155, TS_RT = 885, TS_TOP = 931, TS_BOT = 100;
TouchScreen ts = TouchScreen(XP, YP, XM, YM, 300);


Adafruit_GFX_Button Ok , Back , E ;
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
  tft.setTextColor(WHITE);
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

    showmsgXY(75, 40, 2, &FreeSans12pt7b, "Unique \n Identification 1");
    tft.setFont(NULL);


    Ok.initButton(&tft,  260, 460, 150, 40, ILI9481_GREEN, ILI9481_GREEN , BLACK, "Confirm", 2);
    Back.initButton(&tft,  41, 460, 80, 30, ILI9481_RED, ILI9481_RED, WHITE, "Back", 2);

    E.initButton(&tft,  160 , 210, 110, 50, WHITE, ILI9481_ORANGE, WHITE, "Numpad", 2);


    Back.drawButton(false);
    E.drawButton(false);

    showmsgXYM(1, 133, 1, &FreeSans9pt7b, "Enter 6-digit PIN as per your wish and \nremember it") ;

    /*  EXECUTE THESE STATEMENTS AFTER RETURNING FROM NUMPAD SCREEN */
    if ( n1 == 104 ) {
      showmsgXY(50 + 8, 260 + 14, 2 , NULL , textfield) ;
      tft.drawRect(50, 260, 220, 50, ILI9481_DARKGREY );
      showmsgXYM(17, 400, 1, &FreeSans9pt7b, "   Press Confirm for next PIN 2");

      Ok.drawButton(false);
    }
}

void loop(void)
{
  bool down = Touch_getXY();

    Ok.press(down && Ok.contains(pixel_x, pixel_y));
    Back.press(down && Back.contains(pixel_x, pixel_y));
    E.press(down && E.contains(pixel_x, pixel_y));


    if (Back.justReleased())
      Back.drawButton();
    if ( n == 1 ) {
      if (Ok.justReleased())
        Ok.drawButton();
      if (Ok.justPressed()) {
        Ok.drawButton(true);
        for ( k = 0 ; k < TEXT_LEN  ; k++)
          c[i][counter[i]].number[k] = textfield[k];
        for ( k = 0 ; k < TEXT_LEN  ; k++)
          textfield[k] = ' ' ;
        textfield_i = 0 ;
//        screen5() ;
      }
    }
    if (Back.justPressed()) {
      Back.drawButton(true);

      for ( k = 0 ; k < TEXT_LEN  ; k++)
        textfield[k] = ' ' ;
      textfield_i = 0 ;
      n = 0 ;

      tempT1 = -1 ;
      tempT2 = -1 ;

//      screen23() ;
    }
    if (E.justReleased())
      E.drawButton();
    if (E.justPressed()) {
      E.drawButton(true);
//      numpad();
      n = 1 ;
    }
  }

