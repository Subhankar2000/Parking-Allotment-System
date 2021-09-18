/*
     CAR PARKING ALLOTMENT

     PROJECT MADE AFTER THE FIRST PROJECT NAMED - "CAR PARKING MANAGEMENT"

     THIS IS A NEW VERSION AND THIS PROJECT TRIES TO SOLVE THE CAR PARKING ALLOTMENT
     PROBLEM BY SORTING THE PLACES OF CAR TO BE KEPT ON SO THAT THERE WOULD BE LESS CHAOS
     SO THIS TAKES INPUT ON BASIS OF TIME , CALCULATES ELAPSED TIME AND THEN CHARGES
     AS PER THE TIME THE CAR WAS KEPT AND BECAUSE OF THIS A USER HAS TO PAY ONLY
     OF THE TIME KEPT INSIDE AND NOT ANY EXTRA AND ALSO THE PARKING SPACE IS LITTLE
     MORE SORTED BECAUSE THE CARS ARE KEPT IN A FLOOR - TIME DEPENDENT TYPE THAT IS
     EACH FLOOR IS ENTITLED TO A SPECIFIC AMOUNT OF TIME.

     THIS PROJECT IS MADE BY USING AN ARDUINO MEGA 2560 , 3.5" TFT RESISTIVE TOUCH DISPLAY , DS3231 RTC MODULE

     ALL THE LIBRARIES USED , ARE IN PUBLIC DOMAIN
*/

/*  START OF PRE PROCESSOR DIRECTIVES */

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

/*  UI DETAILS FOR THE 5x3 NUMPAD */
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
char textfieldr[TEXT_LEN + 1] = "";
uint8_t textfieldr_i = 0;
#define TS_MINX 155
#define TS_MINY 100
#define TS_MAXX 885
#define TS_MAXY 931
#define STATUS_X 10
#define STATUS_Y 65

/*  END OF PRE PROCESSOR DIRECTIVES */

MCUFRIEND_kbv tft;    /* CREATION OF OBJECT FOR TFT */
DS3231  rtc(SDA, SCL);  /* CREATION OF OBJECT FOR RTC */

int screen = 1 ;
/*  THE MAIN VARIABLE USED FOR SWITCHING IN BETWEEN SCREENS , THAT IS BASED ON THIS VALUE THE PARTS OF SETUP AND LOOP WILL BE EXECUTED  */

const int XP = 8, XM = A2, YP = A3, YM = 9;       /* FOR TOUCH INPUT*/
const int TS_LEFT = 155, TS_RT = 885, TS_TOP = 931, TS_BOT = 100;   /*CALIBERATED VALUES*/

TouchScreen ts = TouchScreen(XP, YP, XM, YM, 300);  /*TOUCH INPUT INITIALIZATION*/

int pixel_x, pixel_y;

/*BUTTONS DECLARATION*/
Adafruit_GFX_Button one , two , Ok , Back , One , Two , Three , Four , E , Finish ;
Adafruit_GFX_Button buttons[15];

/* CREATE 15 BUTTONS IN CLASSIC KEYPAD STYLE */
char buttonlabels[15][5] = {"Ok", "Clr", "Back", "1", "2", "3", "4", "5", "6", "7", "8", "9", "*", "0", "#" };
uint16_t buttoncolors[15] = {ILI9481_GREEN, ILI9481_DARKGREY, ILI9481_RED,
                             ILI9481_BLUE, ILI9481_BLUE, ILI9481_BLUE,
                             ILI9481_BLUE, ILI9481_BLUE, ILI9481_BLUE,
                             ILI9481_BLUE, ILI9481_BLUE, ILI9481_BLUE,
                             ILI9481_ORANGE, AZURE, ILI9481_ORANGE
                            };

/* STATUS THAT GOES ON WHILE SENDING DATA FROM THE KEYPAD */
void status(const __FlashStringHelper *msg) {
}

/*  STATUS THAT GOES ON WHILE SENDING DATA FROM THE KEYPAD */
void status(char *msg) {
}

/*  FOR THE TOUCH INPUT , THE FUNCTION THAT REGULATES TOUCH */
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

/*  CUSTOM FUNCTION THAT HELPS DISPLAYING TEXT WITH COLOR - GREEN */
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

/*    FUNCTIONS FOR CHANGING VALUES OF SETUP AND LOOP SO THAT THE SPECIFIC SCREEN GETS INITIALIZED AND GETS OPEN
      SCREEN 1 - CAR PARKING MAIN MENU SCREEN FOR TAKING USER INPUT OF WANT TO KEEP CAR OR TAKE OUT CAR
      SCREEN 2 - AVAILABLE SLOTS SCREEN WHERE THE AVAILABLE SLOTS ARE SHOWN IF ANY
      SCREEN 3 - SLOT SELECTION SCREEN WHERE THE SLOT WHICH IS TO BE KEPT IS TAKEN FROM THE USER
      SCREEN 4 - UNIQUE IDENTIFICATION SCREEN WHERE THE USER PRESSES NUMPAD TO ENTER THE CAR'S NUMBER
      SCREEN 5 - CONFIRMATION SCREEN WHERE THE USER HAS TO PRESS FINISH IN ORDER TO KEEP CAR INSIDE

      SCREEN 21 - UNIQUE IDENTIFICATION SCREEN FOR TAKING THE CAR OUT THE USER ENTERS THE CAR'S NUMBER AND TAKES THE CAR OUT
      SCREEN 22 - FINAL CONFIRMATION SCREEN WHERE THE USER PRESSES FINISH AND TAKES THE CAR OUT
      SCREEN 22_0 - 220 - THE ERROR SCREEN WHERE THE USER WILL GET WHEN ENTERED THE WRONG CAR'S NUMBER OR WHICH IS NOT IN THE DATABASE

      NUMPAD - 9 - THE NUMPAD SCREEN WHERE THERE IS A MATRIX INPUT AVAILABLE AND INPUT IS DRAWN TO SCREEN 4
      NUMPAD1 - 91 - THE NUMPAD SCREEN WHERE THERE IS A MATRIX INPUT AVAILABLE AND INPUT IS DRAWN TO SCREEN 21

*/
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
void numpad1() {
  screen = 91 ;
  setup() ;
}
void screen21() {
  screen = 21 ;
  setup() ;
}
void screen22() {
  screen = 22 ;
  setup() ;
}
void screen22_0() {
  screen = 220 ;
  setup() ;
}


/*   THE MAIN SETUP FOR THE ARDUINO
     ALL THE CODES FOR THE MAIN DRAWN THINGS ARE DECLARED HERE
     THE REST REDRAWAL OF ANY THING IS DONE VIA THE LOOP
*/
void setup(void)
{
  Serial.begin(9600);   /* FOR DEBUGGING PURPOSES */
  uint16_t ID = tft.readID(); /* COMMAND TO FIND OUT THE LCD DRIVER AUTOMATICALLY */
  Serial.print("TFT ID = 0x");
  Serial.println(ID, HEX);
  rtc.begin();

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

    Ok.initButton(&tft,  280, 460, 80, 30, ILI9481_GREEN, ILI9481_GREEN , BLACK, "Ok", 2);
    Back.initButton(&tft,  41, 460, 80, 30, ILI9481_RED, ILI9481_RED, WHITE, "Back", 2);

    Ok.drawButton(false);
    Back.drawButton(false);
    tft.drawRect(10 , 110, 60, 60, ILI9481_WHITE);
    tft.drawRect(10 , 110 + 60 + 20, 60, 60, ILI9481_WHITE);
    tft.drawRect(10 , 110 + 60 + 20 + 60 + 20, 60, 60, ILI9481_WHITE);
    tft.drawRect(10 , 110 + 60 + 20 + 60 + 20 + 60 + 20, 60, 60, ILI9481_WHITE);
    showmsgXY(10 + 60 + 15, 110 + 13, 1, &FreeSans9pt7b, "3rd Floor \n                 For parking time :\n                 more than 10 hours") ;
    showmsgXY(10 + 60 + 15, 110 + 60 + 20 + 13, 1, &FreeSans9pt7b, "2nd Floor \n                 For parking time :\n                 more than 6 hours") ;
    showmsgXY(10 + 60 + 15,  110 + 60 + 20 + 60 + 20 + 13, 1, &FreeSans9pt7b, "1st Floor \n                 For parking time :\n                 more than 3 hours") ;
    showmsgXY(10 + 60 + 15,  110 + 60 + 20 + 60 + 20 + 60 + 20 + 13, 1, &FreeSans9pt7b, "Ground Floor \n                 For parking time :\n                 less than 3 hours") ;
  }

  if ( screen == 3 ) {
    tft.fillScreen(BLACK);
    showmsgXY(40, 30, 2, &FreeSans9pt7b, "Slot Selection");
    showmsgXYM(1, 55, 1, &FreeSans9pt7b, "These Slots are just for keeping the      space sorted , you have to pay as per      time kept !") ;
    tft.setFont(NULL);

    One.initButton(&tft,  50, 150, 75, 50, WHITE, ILI9481_ORANGE, WHITE, "1", 3);
    Two.initButton(&tft,  50, 150 + 50 + 30, 75, 50, WHITE, ILI9481_ORANGE, WHITE, "2", 3);
    Three.initButton(&tft, 50, 150 + 50 + 30 + 50 + 30, 75, 50, WHITE, ILI9481_ORANGE, WHITE, "3", 3);
    Four.initButton(&tft,  50, 150 + 50 + 30 + 50 + 30 + 50 + 30, 75, 50, WHITE, ILI9481_ORANGE, WHITE, "4", 3);
    Ok.initButton(&tft,  280, 460, 80, 30, ILI9481_GREEN, ILI9481_GREEN , BLACK, "Ok", 2);
    Back.initButton(&tft,  41, 460, 80, 30, ILI9481_RED, ILI9481_RED, WHITE, "Back", 2);

    One.drawButton(false);
    Two.drawButton(false);
    Three.drawButton(false);
    Four.drawButton(false);
    Ok.drawButton(false);
    Back.drawButton(false);

    showmsgXY(98, 133, 1, &FreeSans9pt7b, "Ground Floor \n                    For parking time :\n                    less than 3 hours") ;
    showmsgXY(98, 133 + 80, 1, &FreeSans9pt7b, "1st Floor \n                    For parking time :\n                    more than 3 hours") ;
    showmsgXY(98, 133 + 80 + 80, 1, &FreeSans9pt7b, "2nd Floor \n                    For parking time :\n                    more than 6 hours") ;
    showmsgXY(98, 133 + 80 + 80 + 80, 1, &FreeSans9pt7b, "3rd Floor \n                    For parking time :\n                    more than 10 hours") ;
  }

  if ( screen == 4 ) {
    tft.fillScreen(BLACK);

    showmsgXY(75, 40, 2, &FreeSans12pt7b, "Unique \n  Identification");
    tft.setFont(NULL);


    Ok.initButton(&tft,  260, 460, 150, 40, ILI9481_GREEN, ILI9481_GREEN , BLACK, "Confirm", 2);
    Back.initButton(&tft,  41, 460, 80, 30, ILI9481_RED, ILI9481_RED, WHITE, "Back", 2);

    E.initButton(&tft,  160 , 210, 110, 50, WHITE, ILI9481_ORANGE, WHITE, "Numpad", 2);


    Back.drawButton(false);
    E.drawButton(false);

    showmsgXYM(1, 133, 1, &FreeSans9pt7b, "Enter your Vehicle's Registration no.     (from number plate) for our records") ;

    /*  EXECUTE THESE STATEMENTS AFTER RETURNING FROM NUMPAD SCREEN */
    showmsgXY(50 + 8, 260 + 14, 2 , NULL , textfield) ;
    tft.drawRect(50, 260, 220, 50, ILI9481_DARKGREY );
    showmsgXYM(35, 400, 1, &FreeSans9pt7b, "Press Confirm to keep your car");
    Ok.drawButton(false);
  }

  if ( screen == 5 ) {
    tft.fillScreen(BLACK);

    showmsgXYM(1, 50, 3, &FreeSans9pt7b, "Successful");
    showmsgXY(1, 95, 1, &FreeSans9pt7b, "You can now just keep your vehicle at \nthe prefered floor as per your choice of no. of hours , at the time of exit just \nchoose the option 2 and enter vehicle's number again , pay and take your car \nback , now press Finish Button") ;
    showmsgXY(65, 400, 2, &FreeSans9pt7b, "Thank You !") ;
    tft.setFont(NULL);

    Finish.initButton(&tft,  160 , 300, 150, 50, WHITE, BLUE, WHITE, "Finish", 3);
    Finish.drawButton(false);
  }

  if ( screen == 9 ) {
    tft.fillScreen(BLACK);
    for (uint8_t row = 0; row < 5; row++) {
      for (uint8_t col = 0; col < 3; col++) {
        buttons[col + row * 3].initButton(&tft, BUTTON_X + col * (BUTTON_W + BUTTON_SPACING_X),
                                          BUTTON_Y + row * (BUTTON_H + BUTTON_SPACING_Y), // x, y, w, h, outline, fill, text
                                          BUTTON_W, BUTTON_H, BLACK, buttoncolors[col + row * 3], ILI9481_WHITE,
                                          buttonlabels[col + row * 3], BUTTON_TEXTSIZE);
        buttons[0 + 0 * 3].initButton(&tft, BUTTON_X + 0 * (BUTTON_W + BUTTON_SPACING_X),
                                      BUTTON_Y + 0 * (BUTTON_H + BUTTON_SPACING_Y), // x, y, w, h, outline, fill, text
                                      BUTTON_W, BUTTON_H, BLACK, buttoncolors[0 + 0 * 3], BLACK,
                                      buttonlabels[0 + 0 * 3], BUTTON_TEXTSIZE);

        buttons[col + row * 3].drawButton();
      }
    }

    // create 'text field'
    tft.drawRect(TEXT_X, TEXT_Y, TEXT_W, TEXT_H, ILI9481_DARKGREY );
  }

  if ( screen == 91 ) {
    tft.fillScreen(BLACK);
    for (uint8_t row = 0; row < 5; row++) {
      for (uint8_t col = 0; col < 3; col++) {
        buttons[col + row * 3].initButton(&tft, BUTTON_X + col * (BUTTON_W + BUTTON_SPACING_X),
                                          BUTTON_Y + row * (BUTTON_H + BUTTON_SPACING_Y), // x, y, w, h, outline, fill, text
                                          BUTTON_W, BUTTON_H, BLACK, buttoncolors[col + row * 3], ILI9481_WHITE,
                                          buttonlabels[col + row * 3], BUTTON_TEXTSIZE);
        buttons[0 + 0 * 3].initButton(&tft, BUTTON_X + 0 * (BUTTON_W + BUTTON_SPACING_X),
                                      BUTTON_Y + 0 * (BUTTON_H + BUTTON_SPACING_Y), // x, y, w, h, outline, fill, text
                                      BUTTON_W, BUTTON_H, BLACK, buttoncolors[0 + 0 * 3], BLACK,
                                      buttonlabels[0 + 0 * 3], BUTTON_TEXTSIZE);
        buttons[col + row * 3].drawButton();
      }
    }

    // create 'text field'
    tft.drawRect(TEXT_X, TEXT_Y, TEXT_W, TEXT_H, ILI9481_DARKGREY );
  }

  if ( screen == 21) {
    tft.fillScreen(BLACK);

    showmsgXY(75, 40, 2, &FreeSans12pt7b, "Unique \n  Identification");
    tft.setFont(NULL);

    Ok.initButton(&tft,  260, 460, 150, 40, ILI9481_GREEN, ILI9481_GREEN , BLACK, "Confirm", 2);
    Back.initButton(&tft,  41, 460, 80, 30, ILI9481_RED, ILI9481_RED, WHITE, "Back", 2);

    E.initButton(&tft,  160 , 210, 110, 50, WHITE, ILI9481_ORANGE, WHITE, "Numpad", 2);

    Ok.drawButton(false);
    Back.drawButton(false);
    E.drawButton(false);

    showmsgXYM(1, 133, 1, &FreeSans9pt7b, "Enter your Vehicle's Registration no.     (from number plate) to take your car out") ;

    /*  EXECUTE THESE STATEMENTS AFTER RETURNING FROM NUMPAD SCREEN */
    showmsgXY(50 + 8, 260 + 14, 2 , NULL , textfieldr) ;
    tft.drawRect(50, 260, 220, 50, ILI9481_DARKGREY );
    showmsgXYM(25, 400, 1, &FreeSans9pt7b, "Press Confirm to take out your car");
    Ok.drawButton(false);
  }

  if ( screen == 22) {
    tft.fillScreen(BLACK);

    showmsgXYM(1, 50, 3, &FreeSans9pt7b, "Successful");
    showmsgXY(1, 95, 1, &FreeSans9pt7b, "You can now just take your car out by \npaying the correct amount and press \nthe Finish button") ;
    showmsgXY(65, 190, 2, &FreeSans9pt7b, "Thank You !") ;

    tft.setFont(NULL);

    Finish.initButton(&tft,  160 , 450, 150, 50, WHITE, BLUE, WHITE, "Finish", 3);
    Finish.drawButton(false);

    /*  EXECUTE THESE STATEMENTS AFTER SUCCESSFUL SEARCH  */
    showmsgXYM(1, 250, 1, &FreeSans9pt7b, "VEHICLE'S \nNUMBER      : ");
    showmsgXY(1 + 120, 250 + 22, 1, &FreeSans12pt7b, "12345");

    showmsgXYM(1, 250 + 25 + 40, 1, &FreeSans9pt7b, "TIME KEPT  : ");
    showmsgXY(1 + 120, 250 + 25 + 40, 1, &FreeSans12pt7b, "2.56 hrs");

    showmsgXYM(1, 250 + 25 + 40 + 40, 1, &FreeSans9pt7b, "AMOUNT \nTO BE PAID : ");
    showmsgXY(1 + 120, 250 + 25 + 40 + 40 + 20, 1, &FreeSans12pt7b, "Rs. 56");
  }

  if ( screen == 220) {
    tft.fillScreen(BLACK);
    showmsgXY(1, 100, 2, &FreeSans9pt7b, "The number you \nentered does not \nmatch our records \nplease go back and \nenter the correct \nnumber") ;
    tft.setFont(NULL);
    Back.initButton(&tft,  41, 460, 80, 30, ILI9481_RED, ILI9481_RED, WHITE, "Back", 2);
    Back.drawButton(false);
  }

}



/*   THE MAIN LOOP FOR THE ARDUINO
     ALL THE CODES FOR REDRAWING THE THINGS ARE DECLARED HERE
*/

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
      screen21() ;
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

    //    if (One.justReleased())
    //      One.drawButton();
    //    if (Two.justReleased())
    //      Two.drawButton();
    if (One.justPressed()) {
      One.drawButton(true);
      Serial.print("One pressed") ;
      Two.drawButton();
      Three.drawButton();
      Four.drawButton();
    }
    if (Two.justPressed()) {
      Two.drawButton(true);
      Serial.print("Two pressed") ;
      One.drawButton();
      Three.drawButton();
      Four.drawButton();
    }

    //    if (Three.justReleased())
    //      Three.drawButton();
    //    if (Four.justReleased())
    //      Four.drawButton();
    if (Three.justPressed()) {
      Three.drawButton(true);
      Serial.print("Three Pressed") ;
      One.drawButton();
      Two.drawButton();
      Four.drawButton();
    }
    if (Four.justPressed()) {
      Four.drawButton(true);
      Serial.print("Four Pressed") ;
      One.drawButton();
      Two.drawButton();
      Three.drawButton();
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

  }

  if (screen == 5) {
    bool down = Touch_getXY();
    Finish.press(down && Finish.contains(pixel_x, pixel_y));

    if (Finish.justReleased())
      Finish.drawButton();

    if (Finish.justPressed()) {
      Finish.drawButton(true);
      screen1() ;
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
        tft.setTextColor(TEXT_TCOLOR, ILI9481_BLACK);
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

  if (screen == 91) {
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

        // if a numberpad button, append the relevant # to the textfieldr
        if (b >= 3) {
          if (textfieldr_i < TEXT_LEN) {
            textfieldr[textfieldr_i] = buttonlabels[b][0];
            textfieldr_i++;
            textfieldr[textfieldr_i] = 0; // zero terminate
          }
        }

        // clr button! delete char
        if (b == 1) {

          textfieldr[textfieldr_i] = 0;
          if (textfieldr > 0) {
            textfieldr_i--;
            textfieldr[textfieldr_i] = ' ';
          }
        }

        // update the current text field
        Serial.println(textfieldr);
        tft.setCursor(TEXT_X + 8, TEXT_Y + 14);
        tft.setTextColor(TEXT_TCOLOR, ILI9481_BLACK);
        tft.setTextSize(TEXT_TSIZE);
        tft.print(textfieldr);

        if (b == 2) {
          status(F("Back"));
          screen21() ;
        }

        if (b == 0) {
          status(F("Ok"));
          delay(100);
          Serial.print("Sending"); Serial.println(textfieldr);
          screen21() ;
        }

        delay(100); // UI debouncing
      }
    }
  }

  if (screen == 21) {
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
      screen22() ;
    }
    if (Back.justPressed()) {
      Back.drawButton(true);
      screen1() ;
    }
    if (E.justReleased())
      E.drawButton();
    if (E.justPressed()) {
      E.drawButton(true);
      numpad1() ;
    }
  }

  if (screen == 22) {
    bool down = Touch_getXY();
    Finish.press(down && Finish.contains(pixel_x, pixel_y));
    if (Finish.justReleased())
      Finish.drawButton();
    if (Finish.justPressed()) {
      Finish.drawButton(true);
      screen1();
    }
  }

  if (screen == 220) {
    bool down = Touch_getXY();
    Back.press(down && Back.contains(pixel_x, pixel_y));
    if (Back.justReleased())
      Back.drawButton();
    if (Back.justPressed()) {
      Back.drawButton(true);
      screen21() ;
    }
  }
}