/*
     PARKING ALLOTMENT SYSTEM

     PROJECT MADE AFTER THE FIRST PROJECT NAMED - "CAR PARKING MANAGEMENT"

     THIS IS A NEW VERSION AND THIS PROJECT TRIES TO SOLVE THE VEHICLE PARKING ALLOTMENT
     PROBLEM BY SORTING THE PLACES OF VEHICLE TO BE KEPT ON SO THAT THERE WOULD BE LESS CHAOS
     SO THIS TAKES INPUT ON BASIS OF TIME , CALCULATES ELAPSED TIME AND THEN CHARGES
     AS PER THE TIME THE VEHICLE WAS KEPT AND BECAUSE OF THIS A USER HAS TO PAY ONLY
     OF THE TIME KEPT INSIDE AND NOT ANY EXTRA AND ALSO THE PARKING SPACE IS LITTLE
     MORE SORTED BECAUSE THE VEHICLES ARE KEPT IN A FLOOR - TIME DEPENDENT TYPE THAT IS
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
#define TEXT_LEN 6
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

/* START OF DECLARING A UNION FOR STORING THE DATA OF THE VEHICLES COMING */

/*
    THE DATA IS STORED IN A 2D ARRAY OF STRUCTURE ELEMENTS
    AND THE OTHER DATA TYPES ARE CHOOSEN ACCORDINGLY
    THE VALUES OF TIME AND COST ARE DEFINED ACCURATELY AS PER
    THE HOUR SYSTEM AS DURING DEMONSTRATION WE CAN ONLY DEMONSTRATE THIS
    IN SECONDS , SO THE COST AS PER VEHICLE TYPE IS DIRECTLY SHOWN
    INSTEAD OF CALCULATING

    TO RE-SCALE IT TO A LARGER VALUE , SIMPLY CHNAGE THE STRUCTURE ELEMENTS SIZE
    AND RE SHAPE IT ACCORDINGLY AS PER NEED
*/

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


/*  DATA VARIABLES DECLATION ENDED */

MCUFRIEND_kbv tft;    /* CREATION OF OBJECT FOR TFT */
DS3231  rtc(SDA, SCL);  /* CREATION OF OBJECT FOR RTC MODULE*/

int screen = 1 ;
/*  THE MAIN VARIABLE USED FOR SWITCHING IN BETWEEN SCREENS , THAT IS BASED ON THIS VALUE THE PARTS OF SETUP AND LOOP WILL BE EXECUTED  */

const int XP = 8, XM = A2, YP = A3, YM = 9;       /* FOR TOUCH INPUT*/
const int TS_LEFT = 155, TS_RT = 885, TS_TOP = 931, TS_BOT = 100;   /*CALIBERATED VALUES*/

TouchScreen ts = TouchScreen(XP, YP, XM, YM, 300);  /*TOUCH INPUT INITIALIZATION*/

int pixel_x, pixel_y;   /* VARIABLES FOR TOUCH INPUT */

/*BUTTONS DECLARATION*/
Adafruit_GFX_Button one , two , Ok , Back , One , Two , Three , Four , TwoThreeOne , TwoThreeTwo , E , Finish ;
Adafruit_GFX_Button buttons[15];

/* CREATE 15 BUTTONS IN CLASSIC KEYPAD STYLE */
char buttonlabels[15][5] = {"Ok", "Clr", "Back", "1", "2", "3", "4", "5", "6", "7", "8", "9", "*", "0", "#" };
uint16_t buttoncolors[15] = {ILI9481_GREEN, ILI9481_DARKGREY, ILI9481_RED,
                             ILI9481_BLUE, ILI9481_BLUE, ILI9481_BLUE,
                             ILI9481_BLUE, ILI9481_BLUE, ILI9481_BLUE,
                             ILI9481_BLUE, ILI9481_BLUE, ILI9481_BLUE,
                             ILI9481_ORANGE, AZURE, ILI9481_ORANGE
                            };

/* STATUS THAT GOES ON WHILE SENDING DATA FROM THE KEYPAD FOR DEBUGGING PURPOSES */
void status(const __FlashStringHelper *msg) {
}

/*  STATUS THAT GOES ON WHILE SENDING DATA FROM THE KEYPAD FOR DEBUGGING PURPOSES */
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

/*  CUSTOM FUNCTION THAT HELPS DISPLAYING TEXT WITH COLOR - WHITE */
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

/*    FUNCTIONS FOR CHANGING VALUES OF SETUP AND LOOP SO THAT THE SPECIFIC SCREEN GETS INITIALIZED AND GETS OPEN
      SCREEN 1 - VEHICLE PARKING MAIN MENU SCREEN FOR TAKING USER INPUT OF WANT TO KEEP VEHICLE OR TAKE OUT VEHICLE
      SCREEN 2 - AVAILABLE SLOTS SCREEN WHERE THE AVAILABLE SLOTS ARE SHOWN IF ANY
      SCREEN 23 - FOR SELECTING THE TYPE OF VEHILCE WHICH THE USER WANTS TO PARK AS PER THAT COST IS DIVIDED
      SCREEN 3 - SLOT SELECTION SCREEN WHERE THE SLOT WHICH IS TO BE KEPT IS TAKEN FROM THE USER
      SCREEN 4 - UNIQUE IDENTIFICATION SCREEN WHERE THE USER PRESSES NUMPAD TO ENTER THE VEHICLE'S NUMBER
      SCREEN 5 - CONFIRMATION SCREEN WHERE THE USER HAS TO PRESS FINISH IN ORDER TO KEEP VEHICLE INSIDE


      SCREEN 21 - UNIQUE IDENTIFICATION SCREEN FOR TAKING THE VEHICLE OUT THE USER ENTERS THE VEHICLE'S NUMBER AND TAKES THE VEHICLE OUT
      SCREEN 22 - FINAL CONFIRMATION SCREEN WHERE THE USER PRESSES FINISH AND TAKES THE VEHICLE OUT
      SCREEN 22_0 - 220 - THE ERROR SCREEN WHERE THE USER WILL GET WHEN ENTERED THE WRONG VEHICLE'S NUMBER OR WHICH IS NOT IN THE DATABASE

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
void screen23() {
  screen = 23 ;
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
void numpad_pin1(){
  screen = 4015 ;
  setup() ;
}
void numpad_pin2(){
  screen = 4025 ;
  setup() ;
}
void pin1(){
  screen = 401501 ;
  setup() ;
}
void pin2(){
  screen = 402502 ;
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

    showmsgXY(1, 50, 3, &FreeSans9pt7b, "Parking");
    showmsgXYM(15, 50, 3, &FreeSans9pt7b, "\nAllotment");
    showmsgXY(15, 50 + 65, 3, &FreeSans9pt7b, "\nSystem");
    tft.setFont(NULL);
    one.initButton(&tft,  60, 150 + 100 + 55, 100, 50, YELLOW, YELLOW, BLACK, "1", 3);
    two.initButton(&tft,  60, 150 + 100 + 55 + 75, 100, 50, MAGENTA, MAGENTA, WHITE, "2", 3);


    tft.setCursor(120, 130 + 100 + 55);
    tft.setTextColor(YELLOW);
    tft.setTextSize(2);
    tft.print("Keep your");
    tft.setCursor(120, 150 + 100 + 57);
    tft.print("Vehicle inside");

    tft.setCursor(120, 242 + 100 + 20);
    tft.setTextColor(WHITE);
    tft.setTextSize(2);
    tft.print("Take your");
    tft.setCursor(120, 262 + 100 + 22);
    tft.print("Vehicle");


    temp1 = -1 ;
    temp2 = -1 ;
    temp3 = -1 ;
    temp4 = -1 ;

    i = -1 ;


    tempT1 = -1 ;
    tempT2 = -1 ;


    one.drawButton(false);
    two.drawButton(false);

  }

  if ( screen == 2 ) {
    tft.fillScreen(BLACK);

    showmsgXY(40, 30, 2, &FreeSans9pt7b, "Available Slots");
    showmsgXYM(1, 42, 1, NULL, "The Following slots are only occupied by users based on their preference of time they want to keep thier  Vehicles, this has nothing to do with the amount that has to be paid at the time of exit , the user's \npreference helps the parking space to be in a sorted condition !");
    tft.setFont(NULL);

    Ok.initButton(&tft,  280, 460, 80, 30, ILI9481_GREEN, ILI9481_GREEN , BLACK, "Ok", 2);
    Back.initButton(&tft,  41, 460, 80, 30, ILI9481_RED, ILI9481_RED, WHITE, "Back", 2);

    if (!( counter[0] == 5 && counter[1] == 5 && counter[2] == 5 && counter[3] == 5 ))
      Ok.drawButton(false);
    /* IF ALL THE PLACES ARE NOT FILLED THEN ONLY DRAW THE Ok.drawButton */


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

  if ( screen == 23 ) {
    tft.fillScreen(BLACK);

    showmsgXY(45, 30, 2, &FreeSans9pt7b, "Vehicle Type");
    showmsgXYM(1, 58, 1, &FreeSans9pt7b, "Choose the type of vehicle \non the basis of that the rate is divided") ;
    tft.setFont(NULL);

    TwoThreeOne.initButton(&tft,  50, 150 - 15, 75, 50, WHITE, ILI9481_ORANGE, WHITE, "1", 3);
    TwoThreeTwo.initButton(&tft,  50, 150 + 50 + 30 - 15, 75, 50, WHITE, ILI9481_ORANGE, WHITE, "2", 3);

    Ok.initButton(&tft,  280, 460, 80, 30, ILI9481_GREEN, ILI9481_GREEN , BLACK, "Ok", 2);
    Back.initButton(&tft,  41, 460, 80, 30, ILI9481_RED, ILI9481_RED, WHITE, "Back", 2);

    TwoThreeOne.drawButton(false);
    TwoThreeTwo.drawButton(false);
    Ok.drawButton(false);
    Back.drawButton(false);
    showmsgXY(98, 140 - 15, 1, &FreeSans9pt7b, "Bike \n                    Rs.25 for 1 hour\n") ;
    showmsgXY(98, 140 + 80 - 15, 1, &FreeSans9pt7b, "Car \n                    Rs.30 for 1 hour\n") ;
    showmsgXY(1, 280 - 15, 1, &FreeSans9pt7b, "These are the rates for 1 hour,however you have to pay as per time passed and hence if you have kept the vehicle for \nhalf hour you have to pay half \nthe amount , the time elapsed is \npresicely calculated and for after every \n11 hours the rate per hour is increased \nby Rs.5") ;
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
    if ( n == 1 ) {
      showmsgXY(50 + 8, 260 + 14, 2 , NULL , textfield) ;
      tft.drawRect(50, 260, 220, 50, ILI9481_DARKGREY );
      showmsgXYM(17, 400, 1, &FreeSans9pt7b, "Press Confirm to keep your Vehicle");

      Ok.drawButton(false);
    }
  }

  if ( screen == 5 ) {
    tft.fillScreen(BLACK);

    showmsgXYM(1, 50, 3, &FreeSans9pt7b, "Successful");
    showmsgXY(1, 95, 1, &FreeSans9pt7b, "You can now just keep your vehicle at \nthe prefered floor as per your choice of no. of hours , at the time of exit just \nchoose the option 2 and enter vehicle's number again , pay and take your \nVehicle back , now press Finish Button") ;
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


    Back.drawButton(false);
    E.drawButton(false);

    showmsgXYM(1, 133, 1, &FreeSans9pt7b, "Enter your Vehicle's Registration no.     (from number plate) to take your Vehicle out") ;

    /*  EXECUTE THESE STATEMENTS AFTER RETURNING FROM NUMPAD SCREEN */
    if ( nr == 1 ) {
      showmsgXY(50 + 8, 260 + 14, 2 , NULL , textfieldr) ;
      tft.drawRect(50, 260, 220, 50, ILI9481_DARKGREY );
      showmsgXYM(5, 400, 1, &FreeSans9pt7b, "Press Confirm to take out your Vehicle");
      Ok.drawButton(false);
    }
  }

  if ( screen == 22) {
    tft.fillScreen(BLACK);
    timeTemp = ((rtc.getUnixTime(rtc.getTime())) % 10000) ;
    showmsgXYM(1, 50, 3, &FreeSans9pt7b, "Successful");
    showmsgXY(1, 95, 1, &FreeSans9pt7b, "You can now just take your Vehicle out by paying the correct amount and press \nthe Finish button") ;
    showmsgXY(65, 190, 2, &FreeSans9pt7b, "Thank You !") ;

    tft.setFont(NULL);

    Finish.initButton(&tft,  160 , 450, 150, 50, WHITE, BLUE, WHITE, "Finish", 3);
    Finish.drawButton(false);

    /*  EXECUTE THESE STATEMENTS AFTER SUCCESSFUL SEARCH  */
    showmsgXYM(1, 250, 1, &FreeSans9pt7b, "VEHICLE'S \nNUMBER      : ");
    tft.setFont(&FreeSans12pt7b);
    tft.setCursor(1 + 120, 250 + 22);
    tft.setTextColor(WHITE);
    tft.setTextSize(1);

    tft.print(textfieldr) ;
    for ( k = 0 ; k < TEXT_LEN  ; k++)
      textfieldr[k] = ' ' ;
    textfieldr_i = 0 ;
    tft.setFont(NULL);


    showmsgXYM(1, 250 + 25 + 40, 1, &FreeSans9pt7b, "TIME KEPT  : ");


    /*
       CHANGE HERE TO DISPLAY TIME IN HOURS INSTEAD OF SECONDS
       FOR SIMPLICITY AND DEMONSTRATION ITS DEFINED IN SECONDS AND NOT IN HOURS
       THE COST MULTIPLIER SHOULD BE ALSO ADJUSTED AND REPLACED WITH MULTIPLIED VALUES
       BECAUSE OF PRECESION CAUSE AND VALUE CLOSE TO 0.0000 , THE COST VALUES ARE
       REPLACED WITH THEIR TYPE RATE VALUES

       CHANGE ACCORDINGLY !
    */


    tft.setFont(&FreeSans12pt7b);
    tft.setCursor(1 + 120, 250 + 25 + 40);
    tft.setTextColor(WHITE);
    tft.setTextSize(1);
    T1 = ( timeTemp - c[i_temp][j_temp].sTime) ;
    T = T1 / 3600 ;
    tft.print((timeTemp - c[i_temp][j_temp].sTime));
    tft.setFont(NULL);


    showmsgXYM(1, 250 + 25 + 40 + 40, 1, &FreeSans9pt7b, "AMOUNT \nTO BE PAID : ");

    if ( c[i_temp][j_temp].type == 2 ) {

      tft.setFont(&FreeSans12pt7b);
      tft.setCursor(1 + 120, 250 + 25 + 40 + 40 + 20);
      tft.setTextColor(WHITE);
      tft.setTextSize(1);
      T = ( timeTemp - c[i_temp][j_temp].sTime) * ccm;
      tft.print(30);
      tft.setFont(NULL);

    }
    else if ( c[i_temp][j_temp].type == 1 ) {

      tft.setFont(&FreeSans12pt7b);
      tft.setCursor(1 + 120, 250 + 25 + 40 + 40 + 20);
      tft.setTextColor(WHITE);
      tft.setTextSize(1);
      T = ( timeTemp - c[i_temp][j_temp].sTime) * bcm ;
      tft.print(25);
      tft.setFont(NULL);
    }

    for ( k = 0 ; k < TEXT_LEN  ; k++)
      textfieldr[k] = ' ' ;
    textfieldr_i = 0 ;
    i_temp = -1 ;
    j_temp = -1 ;
  }

  if ( screen == 220) {
    tft.fillScreen(BLACK);
    showmsgXY(1, 100, 2, &FreeSans9pt7b, "The number you \nentered does not \nmatch our records \nplease go back and \nenter the correct \nnumber") ;
    tft.setFont(NULL);
    Back.initButton(&tft,  41, 460, 80, 30, ILI9481_RED, ILI9481_RED, WHITE, "Back", 2);
    Back.drawButton(false);
    nr = 0 ;
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

    if ( counter[3] == 5 )
      tft.fillRect(10 , 110, 60, 60, RED);
    else
      tft.fillRect(10 , 110, 60, 60, GREEN);

    if (counter[2] == 5 )
      tft.fillRect(10 , 110 + 60 + 20, 60, 60, RED);
    else
      tft.fillRect(10 , 110 + 60 + 20, 60, 60, GREEN);

    if (counter[1] == 5 )
      tft.fillRect(10 , 110 + 60 + 20 + 60 + 20, 60, 60, RED);
    else
      tft.fillRect(10 , 110 + 60 + 20 + 60 + 20, 60, 60, GREEN);

    if (counter[0] == 5 )
      tft.fillRect(10 , 110 + 60 + 20 + 60 + 20 + 60 + 20, 60, 60, RED);
    else
      tft.fillRect(10 , 110 + 60 + 20 + 60 + 20 + 60 + 20, 60, 60, GREEN);


    if (!( counter[0] == 5 && counter[1] == 5 && counter[2] == 5 && counter[3] == 5 )) {
      if (Ok.justReleased())
        Ok.drawButton();
      if (Ok.justPressed()) {
        Ok.drawButton(true);
        screen3() ;
      }
    }

    if (Back.justReleased())
      Back.drawButton();

    if (Back.justPressed()) {
      Back.drawButton(true);
      screen1() ;
    }
  }

  if (screen == 23) {
    bool down = Touch_getXY();
    Ok.press(down && Ok.contains(pixel_x, pixel_y));
    Back.press(down && Back.contains(pixel_x, pixel_y));

    TwoThreeOne.press(down && TwoThreeOne.contains(pixel_x, pixel_y));
    TwoThreeTwo.press(down && TwoThreeTwo.contains(pixel_x, pixel_y));

    if (TwoThreeOne.justPressed()) {
      TwoThreeOne.drawButton(true);
      TwoThreeTwo.drawButton();
      tempT1 = 1 ;
      tempT2 = 0 ;

    }
    if (TwoThreeTwo.justPressed()) {
      TwoThreeTwo.drawButton(true);
      TwoThreeOne.drawButton();
      tempT1 = 0 ;
      tempT2 = 2 ;
    }
    if (Ok.justReleased())
      Ok.drawButton();
    if (Back.justReleased())
      Back.drawButton();

    if (Ok.justPressed()) {
      Ok.drawButton(true);


      if ( tempT1 == 1 && tempT2 == 0 ) {
        c[i][counter[i]].type = tempT1 ;
        screen4() ;
      }

      else if (tempT1 == 0 && tempT2 == 2 ) {
        c[i][counter[i]].type = tempT2 ;
        screen4() ;
      }

      //      if (tempT1 != 1 || tempT2 != 2 ){
      //        screen23() ;
      //        tempT1 = -1 ;
      //        tempT2 = -1 ;
      //      }

    }
    if (Back.justPressed()) {
      Back.drawButton(true);

      temp1 = -1 ;
      temp2 = -1 ;
      temp3 = -1 ;
      temp4 = -1 ;

      i = -1 ;


      tempT1 = -1 ;
      tempT2 = -1 ;


      screen3() ;
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

    if (One.justPressed()) {
      One.drawButton(true);
      Serial.print("One pressed") ;
      Two.drawButton();
      Three.drawButton();
      Four.drawButton();
      temp1 = 0 ;
      temp2 = 9 ;
      temp3 = 9 ;
      temp4 = 9 ;
    }
    if (Two.justPressed()) {
      Two.drawButton(true);
      Serial.print("Two pressed") ;
      One.drawButton();
      Three.drawButton();
      Four.drawButton();
      temp1 = 9 ;
      temp2 = 1 ;
      temp3 = 9 ;
      temp4 = 9 ;
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
      temp1 = 9 ;
      temp2 = 9 ;
      temp3 = 2 ;
      temp4 = 9 ;
    }
    if (Four.justPressed()) {
      Four.drawButton(true);
      Serial.print("Four Pressed") ;
      One.drawButton();
      Two.drawButton();
      Three.drawButton();
      temp1 = 9 ;
      temp2 = 9 ;
      temp3 = 9 ;
      temp4 = 3 ;
    }

    if (Ok.justReleased())
      Ok.drawButton();
    if (Back.justReleased())
      Back.drawButton();
    if (Ok.justPressed()) {
      Ok.drawButton(true);
      //      if (!( temp1 == 0 || temp2 == 1 || temp3 == 2 || temp4 == 3 ))
      //        screen3() ;

      if (temp1 == 0 && temp2 == 9 && temp3 == 9 && temp4 == 9 ) {
        i = 0 ;
        screen23() ;
      }

      else if (temp1 == 9 && temp2 == 1 && temp3 == 9 && temp4 == 9 ) {
        i = 1 ;
        screen23() ;
      }
      else if (temp1 == 9 && temp2 == 9 && temp3 == 2 && temp4 == 9 ) {
        i = 2 ;
        screen23() ;
      }
      else if (temp1 == 9 && temp2 == 9 && temp3 == 9 && temp4 == 3 ) {
        i = 3 ;
        screen23() ;
      }
    }
    if (Back.justPressed()) {
      Back.drawButton(true);
      temp1 = -1 ;
      temp2 = -1 ;
      temp3 = -1 ;
      temp4 = -1 ;

      i = -1 ;

      screen2() ;
    }
  }

  if (screen == 4) {
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
        screen5() ;
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

      screen23() ;
    }
    if (E.justReleased())
      E.drawButton();
    if (E.justPressed()) {
      E.drawButton(true);
      numpad();
      n = 1 ;
    }

  }

  if (screen == 5) {
    bool down = Touch_getXY();
    Finish.press(down && Finish.contains(pixel_x, pixel_y));

    if (Finish.justReleased())
      Finish.drawButton();

    if (Finish.justPressed()) {
      Finish.drawButton(true);

      c[i][counter[i]].sTime = (rtc.getUnixTime(rtc.getTime())) % 10000 ;
      counter[i] = counter[i] + 1 ;
      n = 0 ;

      temp1 = -1 ;
      temp2 = -1 ;
      temp3 = -1 ;
      temp4 = -1 ;

      i = -1 ;


      tempT1 = -1 ;
      tempT2 = -1 ;

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
          n = 0 ;
          for ( k = 0 ; k < TEXT_LEN  ; k++) {
            textfield[k] = ' ';

          }
          textfield_i = 0 ;
          screen4() ;
        }

        if (b == 0) {
          status(F("Ok"));
          if ( textfield_i != 6 ) {
            for ( k = 0 ; k < TEXT_LEN  ; k++)
              textfield[k] = ' ';
            textfield_i = 0 ;
            n = 0 ;
            screen4();
          } else {
            n = 1 ;
            screen4() ;
          }
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
          mfound = 0 ;

          nr = 0 ;
          for ( k = 0 ; k < TEXT_LEN  ; k++)
            textfieldr[k] = ' ' ;

          textfieldr_i = 0 ;
          screen21() ;
        }

        if (b == 0) {
          if ( textfieldr_i != 6 ) {
            for ( k = 0 ; k < TEXT_LEN  ; k++)
              textfieldr[k] = ' ';
            textfieldr_i = 0 ;

            mfound = 0 ;
            nr = 0 ;
            screen21();
          } else {
            mfound = 1 ;
            nr = 1 ;
            screen21() ;
          }



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


    if (Back.justReleased())
      Back.drawButton();

    if ( nr == 1 ) {
      if (Ok.justReleased())
        Ok.drawButton();
      if (Ok.justPressed()) {
        Ok.drawButton(true);



        if (mfound == 1) {
          for ( i = 0 ; i < 4 ; i++) {
            for ( j = 0 ; j < 5 ; j++) {
              if (c[i][j].number[0] == textfieldr[0] && c[i][j].number[1] == textfieldr[1] && c[i][j].number[2] == textfieldr[2] && c[i][j].number[3] == textfieldr[3]&& c[i][j].number[4] == textfieldr[4] && c[i][j].number[5] == textfieldr[5]) {

                found = 1 ;
                i_temp = i ;
                j_temp = j ;
                break ;
              }
            }
          }

          if (found == 1) {
            counter[i_temp] = counter[i_temp] - 1 ;
            found = 0 ;
            screen22() ;

          } else if (found == 0) {
            for ( k = 0 ; k < TEXT_LEN  ; k++)
              textfieldr[k] = ' ' ;
            textfieldr_i = 0 ;
            screen22_0() ;
          }
        }
      }
    }
    if (Back.justPressed()) {
      Back.drawButton(true);

      for ( k = 0 ; k < TEXT_LEN  ; k++)
        textfieldr[k] = ' ' ;
      textfieldr_i = 0 ;
      nr = 0 ;
      screen1() ;
    }
    if (E.justReleased())
      E.drawButton();
    if (E.justPressed()) {
      E.drawButton(true);
      numpad1() ;
      nr = 1;
    }

  }

  if (screen == 22) {
    bool down = Touch_getXY();
    Finish.press(down && Finish.contains(pixel_x, pixel_y));
    if (Finish.justReleased())
      Finish.drawButton();
    if (Finish.justPressed()) {
      Finish.drawButton(true);
      for ( k = 0 ; k < TEXT_LEN  ; k++)
        textfield[k] = ' ' ;
      textfield_i = 0 ;
      nr = 0 ;
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
      for ( k = 0 ; k < TEXT_LEN  ; k++)
        textfield[k] = ' ' ;
      textfield_i = 0 ;
      nr = 0 ;
      screen21() ;
    }
  }
}

/*    IMPROVEMENTS FROM THE PREVIOUS PROJECT - CAR PARKING MANAGEMENT
      1. PROGRAM SCALABILITY
      2. NO HARDWARE TRACKING FOR CAR'S POSITION (NO NEED OF R.F.I.D. AND I.R.)
      3. FULL COMPUTATION IS IMPLEMENTED IN THE MICRO-CONTROLLER AND DISPLAY CAN BE SWAPPED WITH ANY ILI94XX SERIES
      4. EASY DATA STORING AND FETCHING
      5. SCREENS DIVIDED INTO SECTIONS FOR EASY TROUBLE-SHOOTING
*/
