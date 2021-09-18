/*
     PARKING CORTEX
     WITH GSM FOR SENDING MESSAGES
     SENDS MESSAGE TO THE OWNER THAT IS A SUMMARY
     SENDS MESSAGE TO THE USER , THAT IS AN E-RECEIPT

     PARKING CORTEX V4

     PROJECT MADE AFTER THE FIRST PROJECT NAMED - "CAR PARKING MANAGEMENT"

     THIS IS A NEW VERSION AND THIS PROJECT TRIES TO SOLVE THE VEHICLE PARKING ALLOTMENT
     PROBLEM BY SORTING THE PLACES OF VEHICLE TO BE KEPT ON SO THAT THERE WOULD BE LESS CHAOS
     SO THIS TAKES INPUT ON BASIS OF TIME , CALCULATES ELAPSED TIME AND THEN CHARGES
     AS PER THE TIME THE VEHICLE WAS KEPT AND BECAUSE OF THIS A USER HAS TO PAY ONLY
     OF THE TIME KEPT INSIDE AND NOT ANY EXTRA AND ALSO THE PARKING SPACE IS LITTLE
     MORE SORTED BECAUSE THE VEHICLES ARE KEPT IN A FLOOR - TIME DEPENDENT TYPE THAT IS
     EACH FLOOR IS ENTITLED TO A SPECIFIC AMOUNT OF TIME.

     THIS PROJECT IS MADE BY USING AN ARDUINO MEGA 2560 , 3.5" TFT RESISTIVE TOUCH DISPLAY , DS3231 RTC MODULE , GSM-SIM900A MODULE

     ALL THE LIBRARIES USED , ARE IN PUBLIC DOMAIN
*/


/*    IMPROVEMENTS FROM THE PREVIOUS PROJECT - CAR PARKING MANAGEMENT
      1. PROGRAM SCALABILITY
      2. NO HARDWARE TRACKING FOR CAR'S POSITION (NO NEED OF R.F.I.D. AND I.R.)
      3. FULL COMPUTATION IS IMPLEMENTED IN THE MICRO-CONTROLLER AND DISPLAY CAN BE SWAPPED WITH ANY ILI94XX SERIES
      4. EASY DATA STORING AND FETCHING
      5. SCREENS DIVIDED INTO SECTIONS FOR EASY TROUBLE-SHOOTING
*/

/*
      VERSION 1
      ONLY IMPROVED VERSION OF "CAR PARKING MANAGEMENT"

      VERSION 2
      ADDED GSM MODULE - TO SEND A SUMMARY TO THE PARKING SPACE OWNER TO DOUBLE CHECK THE AMOUNT COLLECRED

      VERSION 2.1
      ADDED FACILITY OF E-RECEIPT , SO THAT THE USER CAN GET A COPY OF ENTERED DATA , SO THAT THEY DON'T FORGET AND ALSO A E-RECORD IS MAINTAINED

      UPCOMING FEATURES - NON-VOLATILE MEMORY STORAGE SUCH AS SD-CARD OR EEP-ROM --> VERSION 3
*/

/*
   DIS-ADVANTAGES - NON-VOLATILE MEMORY
*/

/*  START OF PRE PROCESSOR DIRECTIVES */

/*  3.5" TFT DISPLAY WITH DRIVER ILI9481 */
#include <MCUFRIEND_kbv.h>
#include <Adafruit_GFX.h>
#include <TouchScreen.h>

/*   DS3231 RTC MODULE */
#include <Wire.h>
#include <ds3231.h>

/*  CUSTOM FONTS USED */
#include <Fonts/FreeSans9pt7b.h>
#include <Fonts/FreeSans12pt7b.h>
#include <Fonts/FreeSerif12pt7b.h>
#include <FreeDefaultFonts.h>

/*  TOUCHSCREEN ADJUSTMENT  */
#define MINPRESSURE 1
#define MAXPRESSURE 1000

/*  DEFINING COLORS SO THAT THEY CAN BE USED */
#define WHITE   0x0000
#define BLUE    0x001F
#define RED     0xF800
#define GREEN   0x07E0
#define CYAN    0x07FF
#define MAGENTA 0xF81F
#define YELLOW  0xFFE0
#define BLACK   0xFFFF
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
#define ILI9481_BLUE        0x80FF
#define ILI9481_GREEN       0x07E0
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
#define TEXT_LEN 4
#define ph_TEXT_LEN 10
char ph_textfield[ph_TEXT_LEN + 1] = "";
uint8_t ph_textfield_i = 0;

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
  int yes = 0 ;
  int slot ;
  char ph_number[10] ;
  char number[4] ;
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
int C_OUT = 0 ,  COST = 0 ;

long int a1 = 0 , b1 = 0 ;

const int buttonPin = PC13;
const int buttonPositive = 30 ;
const int buttonNegative = 31 ;
int buttonState = 0;

int C_IN = 0 ;

int ph_n , ph_tempT1 , ph_tempT2 ;

ts t; //ts is a struct findable in ds3231.h
long long int unixtime1 ;

HardwareSerial Serial6(PA12, PA11);

/*  DATA VARIABLES DECLATION ENDED */

MCUFRIEND_kbv tft;    /* CREATION OF OBJECT FOR TFT */

int screen = 1 ;
/*  THE MAIN VARIABLE USED FOR SWITCHING IN BETWEEN SCREENS , THAT IS BASED ON THIS VALUE THE PARTS OF SETUP AND LOOP WILL BE EXECUTED  */

const int XP = 8, XM = A2, YP = A3, YM = 9;       /* FOR TOUCH INPUT*/
const int TS_LEFT = 155, TS_RT = 885, TS_TOP = 931, TS_BOT = 100;   /*CALIBERATED VALUES*/

TouchScreen ts = TouchScreen(XP, YP, XM, YM, 300);  /*TOUCH INPUT INITIALIZATION*/

int pixel_x, pixel_y;   /* VARIABLES FOR TOUCH INPUT */

/*BUTTONS DECLARATION*/
Adafruit_GFX_Button yes , no , one , two , Ok , Back , One , Two , Three , Four , TwoThreeOne , TwoThreeTwo , E , Finish ;
Adafruit_GFX_Button buttons[15];

/* CREATE 15 BUTTONS IN CLASSIC KEYPAD STYLE */
char buttonlabels[15][5] = {"Ok", "Clr", "Back", "1", "2", "3", "4", "5", "6", "7", "8", "9", "*", "0", "#" };
uint16_t buttoncolors[15] = {ILI9481_GREEN, ILI9481_BLUE, ILI9481_RED,
                             ILI9481_DARKGREY, ILI9481_DARKGREY, ILI9481_DARKGREY,
                             ILI9481_DARKGREY, ILI9481_DARKGREY, ILI9481_DARKGREY,
                             ILI9481_DARKGREY, ILI9481_DARKGREY, ILI9481_DARKGREY,
                             ILI9481_ORANGE, ILI9481_DARKGREY, ILI9481_ORANGE
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
  tft.setTextColor(MAGENTA);
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

/*    FUNCTIONS FOR CHANGING VALUES OF SETUP AND LOOP SO THAT THE SPECIFIC SCREEN GETS INITIALIZED AND GETS OPEN
      SCREEN 1 - VEHICLE PARKING MAIN MENU SCREEN FOR TAKING USER INPUT OF WANT TO KEEP VEHICLE OR TAKE OUT VEHICLE
      SCREEN 2 - AVAILABLE SLOTS SCREEN WHERE THE AVAILABLE SLOTS ARE SHOWN IF ANY
      SCREEN 23 - FOR SELECTING THE TYPE OF VEHILCE WHICH THE USER WANTS TO PARK AS PER THAT COST IS DIVIDED
      SCREEN 3 - SLOT SELECTION SCREEN WHERE THE SLOT WHICH IS TO BE KEPT IS TAKEN FROM THE USER
      SCREEN 4 - UNIQUE IDENTIFICATION SCREEN WHERE THE USER PRESSES NUMPAD TO ENTER THE VEHICLE'S NUMBER
      SCREEN 145 - ASKING FOR AN E-RECEIPT , IF THE USER DECLINES THIS , THEN THE CONFIRMATION SCREEN WILL COME AND IF THE USER ACCEPTS IT , THEN PH. NO. SCREEN WILL COME
      SCREEN 45 - PHONE NUMBER SCREEN WHERE THE USER HAS TO ENTER PHONE NUMBER , IN ORDER TO RECEIVE AN E-RECEIPT AND IT WOULD BE STORED IN THE STRUCTURE FOR THE USER , SO AS THE USER WOULD GET AN
                  E-RECEIPT WHILE TAKING THE CAR OUT ALSO
      SCREEN 5 - CONFIRMATION SCREEN WHERE THE USER HAS TO PRESS FINISH IN ORDER TO KEEP VEHICLE INSIDE

      SCREEN 8341 - SENDING MESSAGE STATUS WHILE THE MESSAGE IS BEING SENT TO THE OWNER OF THE PARKING LOT
      SCREEN 1111 - SENDING E-RECEIPT SCREEN AFTER THE USER HAS ENTERED ALL THE DETAILS
      SCREEN 21 - UNIQUE IDENTIFICATION SCREEN FOR TAKING THE VEHICLE OUT THE USER ENTERS THE VEHICLE'S NUMBER AND TAKES THE VEHICLE OUT
      SCREEN 22 - FINAL CONFIRMATION SCREEN WHERE THE USER PRESSES FINISH AND TAKES THE VEHICLE OUT
      SCREEN 22_0 - 220 - THE ERROR SCREEN WHERE THE USER WILL GET WHEN ENTERED THE WRONG VEHICLE'S NUMBER OR WHICH IS NOT IN THE DATABASE

      NUMPAD - 9 - THE NUMPAD SCREEN WHERE THERE IS A MATRIX INPUT AVAILABLE AND INPUT IS DRAWN TO SCREEN 4
      NUMPAD1 - 91 - THE NUMPAD SCREEN WHERE THERE IS A MATRIX INPUT AVAILABLE AND INPUT IS DRAWN TO SCREEN 21
      NUMPAD_PH - 991 - THE NUMPAD SCREEN FOR ENTERING THE 10 DIGIT PHONE NUMBER

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
void screen8341() {
  screen = 8341 ;
  setup() ;
}
void screen145 () {
  screen = 145 ;
  setup() ;
}
void screen45 () {
  screen = 45 ;
  setup() ;
}
void ph_numpad()  {
  screen = 991 ;
  setup() ;
}
void screen1111() {
  screen = 1111 ;
  setup() ;
}


/*------ MINI V1 --------*/

void screen1001() {
  screen = 1001 ;
  setup() ;
}
void screen1002() {
  screen = 1002 ;
  setup() ;
}
void screen10023() {
  screen = 10023 ;
  setup() ;
}
void screen1003() {
  screen = 1003 ;
  setup() ;
}
void screen1004() {
  screen = 1004 ;
  setup() ;
}
void screen1005() {
  screen = 1005 ;
  setup() ;
}
void numpad100() {
  screen = 1009 ;
  setup() ;
}
void numpad1001() {
  screen = 10091 ;
  setup() ;
}
void screen10021() {
  screen = 10021 ;
  setup() ;
}
void screen10022() {
  screen = 10022 ;
  setup() ;
}
void screen10022_0() {
  screen = 100220 ;
  setup() ;
}


/*   THE MAIN SETUP FOR THE ARDUINO
     ALL THE CODES FOR THE MAIN DRAWN THINGS ARE DECLARED HERE
     THE REST REDRAWAL OF ANY THING IS DONE VIA THE LOOP
*/

int tft_first = 1 ;
void setup(void)
{
  /*  TFT INITIALIZATION , CAN WORK FOR ALMOST ANY ILI94XX DISPLAY SUPPORTING THE MCUFRIEND AND ADAFRUIT GFX LIBRARY AND HAVING RESOLUTION 320X480
      ANY RESOLUTION ABOVE JUST TAKE A RATIO AND MULTIPLY THAT NUMBER WITH THE POSITIONS TO FIT THE SIZE OF THE SCREEN OR JUST RUN IT IN A BIGGER
      SCREEN YOU WILL GET A DISPLAY SIZE OF 3.5 INCHES
  */

  Wire.begin(); //start i2c (required for connection)
  DS3231_init(DS3231_INTCN); //register the ds3231 (DS3231_INTCN is the default address of ds3231, this is set by macro for no performance loss)
  Serial6.begin(9600); // FOR GSM
  Serial.begin(9600);   /* FOR DEBUGGING PURPOSES */


  if ( tft_first == 1 ) {
    //     // //Serial.println("EPARK CORTEX S5 GSM ONLY [ACTUAL V4] ") ;
    //     // //Serial.println(".......................................");
    //     // //Serial.println(".......................................");
    //     // //Serial.println(".......................................");
    //     // //Serial.println("ALL READY TO DEBUG") ;
    //     // //Serial.println("PRINTING EVENTS IN THIS SERIAL MONITOR") ;
    //     // //Serial.println("ALL INITIALIZATION COMPLETE") ;
    //     // //Serial.println("PROCEDING TO DRAWING GRAPHICS") ;
    //     // //Serial.println("TINITILIZING WITH SCREEN 1 - VEHICLE PARKING MAIN MENU SCREEN FOR TAKING USER INPUT OF WANT TO KEEP VEHICLE OR TAKE OUT VEHICLE") ;
    //     // //Serial.println("FIRST TIME INITILIZATION #THIS WILL NOT BE PRINTED AGAIN#") ;
    uint16_t ID = tft.readID(); /* COMMAND TO FIND OUT THE LCD DRIVER AUTOMATICALLY */
    //     // //Serial.println("STARTING SCREEN FOR THE FIRST TIME WITH TFT ID = 0x") ;
    //
    //    Serial.print(ID, HEX);
    //     // //Serial.println("") ;
    tft.begin(ID);
    tft.setRotation(0);            /* PORTRAIT */
    tft_first = -1 ;
    // // //Serial.println("FIRST INITILIZATION DONE") ;
  }

  // // //Serial.println("SETTING UP THE OWNER BUTTON") ;

  pinMode(buttonPin, INPUT);

  /*----BUTTON LOGIC-----*/

  /*   HERE THE MAIN TRICK LIES OF HOW TO SETUP ALL BUTTONS WITHOUT WRITING ALL THEM IN ONE PLACE
       THE VALUES MENTIONED IN THE PREVIOUS COMMENT SIMPLY REPRESENT THE VALUES OF DIFFERENT SCREEN
       AND THE SCREEN THATS NEEDED THAT VALUE IS JUST SET IN THE FUNCTIONS FOR THAT SCREENS AND THE
       SETUP FUNCTION IS CALLED SO THAT THE PARTICULAR SECTION OF THE SETUP AND LOOP ONLY GETS EXECUTED
  */

  if ( screen == 1111 ) {

    // // //Serial.println("NOW ENTERING SETUP OF SCREEN 1111 - SENDING E-RECEIPT SCREEN AFTER THE USER HAS ENTERED ALL THE DETAILS") ;
    // // // //Serial.println("THIS SCREEN HAS NO LOOP PART, SO THIS WILL JUMP TO ANOTHER SETUP OF SCREEN") ;

    tft.fillScreen(BLACK);
    C_IN = C_IN  + 1;
    showmsgXY(1, 50 + 100, 3, &FreeSans9pt7b, "  SENDING");
    showmsgXY(15, 50 + 100, 3, &FreeSans9pt7b, "\n E-RECEIPT");
    delay(1000) ;
    Serial6.println("AT+CMGF=1") ;
    delay(1000) ;
    Serial6.print("AT+CMGS=\"+91") ;
    Serial6.print(c[i][counter[i]].ph_number[0]) ;
    Serial6.print(c[i][counter[i]].ph_number[1]) ;
    Serial6.print(c[i][counter[i]].ph_number[2]) ;
    Serial6.print(c[i][counter[i]].ph_number[3]) ;
    Serial6.print(c[i][counter[i]].ph_number[4]) ;
    Serial6.print(c[i][counter[i]].ph_number[5]) ;
    Serial6.print(c[i][counter[i]].ph_number[6]) ;
    Serial6.print(c[i][counter[i]].ph_number[7]) ;
    Serial6.print(c[i][counter[i]].ph_number[8]) ;
    Serial6.print(c[i][counter[i]].ph_number[9]) ;
    Serial6.print("\"\r") ;
    Serial6.println() ;
    delay(1000) ;
    Serial6.println("--- E-RECEIPT ---") ;
    Serial6.println("") ;
    Serial6.println("PARKING CORTEX") ;
    Serial6.println("VEHICLE ENTRY") ;
    Serial6.println("") ;
    Serial6.print("PIN : ") ;
    Serial6.print(c[i][counter[i]].number[0]);
    Serial6.print(c[i][counter[i]].number[1]);
    Serial6.print(c[i][counter[i]].number[2]);
    Serial6.print(c[i][counter[i]].number[3]);
    Serial6.println("") ;
    Serial6.print("FLOOR : ") ;
    if ( c[i][counter[i]].slot == 0 )
      Serial6.print("GROUND FLOOR") ;
    else if ( c[i][counter[i]].slot == 1 )
      Serial6.print("1st FLOOR") ;
    else if ( c[i][counter[i]].slot == 2 )
      Serial6.print("2nd FLOOR") ;
    else if ( c[i][counter[i]].slot == 3 )
      Serial6.print("3rd FLOOR") ;
    Serial6.println("") ;
    Serial6.print("TYPE : ") ;
    if ( c[i][counter[i]].type == 1 )
      Serial6.print("BIKE") ;
    else if ( c[i][counter[i]].type == 2 )
      Serial6.print("CAR") ;
    Serial6.println("");
    Serial6.print("ENTRY TIME : ");
    DS3231_get(&t); //get the value and pass to the function the pointer to t, that make an lower memory fingerprint and faster execution than use return
    Serial6.print(t.hour);
    Serial6.print(":");
    Serial6.print(t.min) ;
    Serial6.print(":");
    Serial6.print(t.sec);
    Serial6.println("") ;
    Serial6.print("DATE : ") ;
    Serial6.print(t.mday) ;
    Serial6.print("/");
    Serial6.print(t.mon) ;
    Serial6.print("/");
    Serial6.print((t.year + 100));
    Serial6.println("");
    delay(100);
    Serial6.println((char)26);
    delay(100);
    //     // //Serial.println("DUMPING DATA WHICH WILL BE GOING TO SERIAL6 GSM") ;
    //     // //Serial.println("AT+CMGF=1") ;
    //    Serial.print("AT+CMGS=\"+91") ;
    //    Serial.print(c[i][counter[i]].ph_number[0]) ;
    //    Serial.print(c[i][counter[i]].ph_number[1]) ;
    //    Serial.print(c[i][counter[i]].ph_number[2]) ;
    //    Serial.print(c[i][counter[i]].ph_number[3]) ;
    //    Serial.print(c[i][counter[i]].ph_number[4]) ;
    //    Serial.print(c[i][counter[i]].ph_number[5]) ;
    //    Serial.print(c[i][counter[i]].ph_number[6]) ;
    //    Serial.print(c[i][counter[i]].ph_number[7]) ;
    //    Serial.print(c[i][counter[i]].ph_number[8]) ;
    //    Serial.print(c[i][counter[i]].ph_number[9]) ;
    //    Serial.print("\"\r") ;
    //     // //Serial.println() ;
    //     // //Serial.println("--- E-RECEIPT ---") ;
    //     // //Serial.println("") ;
    //     // //Serial.println("PARKING CORTEX") ;
    //     // //Serial.println("VEHICLE ENTRY") ;
    //     // //Serial.println("") ;
    //    Serial.print("PIN : ") ;
    //    Serial.print(c[i][counter[i]].number[0]);
    //    Serial.print(c[i][counter[i]].number[1]);
    //    Serial.print(c[i][counter[i]].number[2]);
    //    Serial.print(c[i][counter[i]].number[3]);
    //     // //Serial.println("") ;
    //    Serial.print("FLOOR : ") ;
    //    if ( c[i][counter[i]].slot == 0 )
    //      Serial.print("GROUND FLOOR") ;
    //    else if ( c[i][counter[i]].slot == 1 )
    //      Serial.print("1st FLOOR") ;
    //    else if ( c[i][counter[i]].slot == 2 )
    //      Serial.print("2nd FLOOR") ;
    //    else if ( c[i][counter[i]].slot == 3 )
    //      Serial.print("3rd FLOOR") ;
    //     // //Serial.println("") ;
    //    Serial.print("TYPE : ") ;
    //    if ( c[i][counter[i]].type == 1 )
    //      Serial.print("BIKE") ;
    //    else if ( c[i][counter[i]].type == 2 )
    //      Serial.print("CAR") ;
    //     // //Serial.println("");
    //    Serial.print("ENTRY TIME : ");
    //    DS3231_get(&t); //get the value and pass to the function the pointer to t, that make an lower memory fingerprint and faster execution than use return
    //    Serial.print(t.hour);
    //    Serial.print(":");
    //    Serial.print(t.min) ;
    //    Serial.print(":");
    //    Serial.print(t.sec);
    //     // //Serial.println("") ;
    //    Serial.print("DATE : ") ;
    //    Serial.print(t.mday) ;
    //    Serial.print("/");
    //    Serial.print(t.mon) ;
    //    Serial.print("/");
    //    Serial.print((t.year + 100));
    //     // //Serial.println("");
    //     // //Serial.println((char)26);

    //     // //Serial.println("SENDING DATA TO GSM VIA SERIAL6") ;
    //
    //     // //Serial.println("DATA SUCCESSFULLY SENT TO GSM VIA SERIAL6");
    //     // //Serial.println("JOB OF SCREEN1111 IS DONE, LEAVING SCREEN1111 AND JUMPING TO SCREEN 5 - CONFIRMATION SCREEN WHERE THE USER HAS TO PRESS FINISH IN ORDER TO KEEP VEHICLE INSIDE") ;
    screen5() ;
  }

  if ( screen == 145 ) {
    // //Serial.println("SETUP OF SCREEN 145") ;
    // //Serial.println("NOW ENTERING SCREEN 145 - ASKING FOR AN E-RECEIPT , IF THE USER DECLINES THIS , THEN THE CONFIRMATION SCREEN WILL COME AND IF THE USER ACCEPTS IT , THEN PH. NO. SCREEN WILL COME") ;

    tft.fillScreen(BLACK);

    showmsgXYM(1, 50, 3, &FreeSans9pt7b, "E-Receipt");
    showmsgXY(1 , 50 + 40 , 2 , &FreeSans9pt7b, "Do you want \nE-receipt ?");
    tft.setFont(NULL);
    yes.initButton(&tft,  60 + 30, 200, 100, 50, GREEN, GREEN, WHITE, "Yes", 3);
    no.initButton(&tft,  60 + 170, 200, 100, 50, RED, RED, BLACK, "No", 3);
    showmsgXYG(1 , 260 , 1 , &FreeSans9pt7b, "If you click yes , you will be prompted to give your phone number and your \nphone number will be stored to provide an e-receipt now and also you will get \nan e-receipt while taking your car out") ;
    showmsgXY(1 , 260 + 120 + 20, 1 , &FreeSans9pt7b, "If you click no , then your entry will be \nconfirmed and you can keep your car \nyou will get no e-receipt");
    yes.drawButton(false);
    no.drawButton(false);

    // //Serial.println("SETUP DONE, MOVING TO LOOP FOR SCREEN 145") ;
  }

  if ( screen == 8341 ) {

    //     // //Serial.println("NOW ENTERING SETUP OF SCREEN 8341") ;
    //     // //Serial.println("SCREEN 8341 - SENDING MESSAGE STATUS WHILE THE MESSAGE IS BEING SENT TO THE OWNER OF THE PARKING LOT");
    //     // //Serial.println("THIS SCREEN HAS NO SETUP SO IT WILL JUMP INTO A SETUP OF ANOTHER SCREEN DIRECTLY") ;

    tft.fillScreen(BLACK);

    showmsgXY(1, 50 + 100, 3, &FreeSans9pt7b, "  SENDING");
    showmsgXY(15, 50 + 100, 3, &FreeSans9pt7b, "\n  MESSAGE");
    showmsgXY(15, 50 + 65 + 100, 2, &FreeSans9pt7b, "\n      Please Wait");
    showmsgXYM(15, 50 + 65 + 60 + 100, 1, &FreeSans9pt7b, "\nSending Message to : +91-7908848159");

    //     // //Serial.println("DUMPING DATA WHICH WILL BE GOING TO SERIAL6 GSM") ;
    //     // //Serial.println("AT+CMGF=1");
    //
    //     // //Serial.println("AT+CMGS=\"+917908848159\"\r");
    //    DS3231_get(&t); //get the value and pass to the function the pointer to t, that make an lower memory fingerprint and faster execution than use return
    //    Serial.print(t.hour);
    //    Serial.print(":");
    //    Serial.print(t.min) ;
    //    Serial.print(":");
    //    Serial.print(t.sec);
    //     // //Serial.println("") ;
    //    Serial.print("DATE : ") ;
    //    Serial.print(t.mday) ;
    //    Serial.print("/");
    //    Serial.print(t.mon) ;
    //    Serial.print("/");
    //    Serial.print((t.year + 100));
    //     // //Serial.println("");
    //    Serial.print("CARS WENT OUT OF PARKING SPACE : ");
    //    Serial.print(C_OUT) ;
    //     // //Serial.println("");
    //    Serial.print("TOTAL AMOUNT COLLECTED : ");
    //    Serial.print(COST) ;
    //     // //Serial.println("");
    //    Serial.print("CARS STILL IN PARKING SPACE : ");
    //    Serial.print(C_IN) ;
    //     // //Serial.println("");
    //
    //     // //Serial.println("SENDING DATA TO GSM VIA SERIAL6") ;
    delay(1000);
    Serial6.println("AT+CMGF=1");
    delay(1000);
    Serial6.println("AT+CMGS=\"+917908848159\"\r");
    delay(1000);
    DS3231_get(&t); //get the value and pass to the function the pointer to t, that make an lower memory fingerprint and faster execution than use return
    Serial6.print(t.hour);
    Serial6.print(":");
    Serial6.print(t.min) ;
    Serial6.print(":");
    Serial6.print(t.sec);
    Serial6.println("") ;
    Serial6.print("DATE : ") ;
    Serial6.print(t.mday) ;
    Serial6.print("/");
    Serial6.print(t.mon) ;
    Serial6.print("/");
    Serial6.print((t.year + 100));
    Serial6.println("");
    Serial6.print("CARS WENT OUT OF PARKING SPACE : ");
    Serial6.print(C_OUT) ;
    Serial6.println("");
    Serial6.print("TOTAL AMOUNT COLLECTED : ");
    Serial6.print(COST) ;
    Serial6.println("");
    Serial6.print("CARS STILL IN PARKING SPACE : ");
    Serial6.print(C_IN) ;
    Serial6.println("");

    delay(100);
    Serial6.println((char)26);
    delay(100);
    screen = 1 ;
    // //Serial.println("DATA SUCCESSFULLY SENT TO GSM VIA SERIAL6");
    // //Serial.println("JOB OF SCREEN1111 IS DONE, LEAVING SCREEN8341 AND JUMPING TO SETUP FUNCTION AS THIS IS NOT CONNECTED TO ANYTHING") ;
    setup() ;
  }

  if ( screen == 1 ) {

    tft.fillScreen(BLACK);
    // //Serial.println("NOW ENTERING SETUP OF SCREEN 1");
    // //Serial.println("SCREEN 1 - VEHICLE PARKING MAIN MENU SCREEN FOR TAKING USER INPUT OF WANT TO KEEP VEHICLE OR TAKE OUT VEHICLE") ;
    // //Serial.println("THIS IS THE SCREEN 1 FOR GSM VERSION") ;

    showmsgXY(1 + 35, 50 + 15, 5, &FreeSans9pt7b, "ePark");
    showmsgXYM(15 + 12, 115, 3, &FreeSans9pt7b, "Cortex  S5");
    showmsgXYG(15 + 95, 148 + 10, 2, &FreeSans9pt7b, "GSM");
    showmsgXYG(12, 162 + 10, 2, NULL, "SIM900A [900/1800 MHz] 2G");
    tft.setFont(NULL);
    one.initButton(&tft,  60, 150 + 100 + 55, 100, 50, MAGENTA, MAGENTA, BLACK, "1", 3);
    two.initButton(&tft,  60, 150 + 100 + 55 + 75, 100, 50, AZURE, AZURE, BLACK, "2", 3);
    Back.initButton(&tft,  41 - 7, 460 + 5, 80, 30, BLACK, BLACK , BLACK, "", 2);

    tft.setCursor(120, 130 + 100 + 55);
    tft.setTextColor(WHITE);
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
    ph_n = -1 ;

    one.drawButton(false);
    two.drawButton(false);
    Back.drawButton(false);
    // //Serial.println("GRAPHICS, VARIABLES INITIALIZED JUMPING TO SCREEN 1 LOOP") ;

  }

  if ( screen == 2 ) {
    tft.fillScreen(BLACK);
    // //Serial.println("NOW ENTRING SETUP OF SCREEN 2");
    // //Serial.println("SCREEN 2 - AVAILABLE SLOTS SCREEN WHERE THE AVAILABLE SLOTS ARE SHOWN IF ANY") ;

    showmsgXY(40, 30, 2, &FreeSans9pt7b, "Available Slots");
    showmsgXY(1, 42, 1, NULL, "The Following slots are only occupied by users based on their preference of time they want to keep thier  Vehicles, this has nothing to do with the amount that has to be paid at the time of exit , the user's \npreference helps the parking space to be in a sorted condition !");
    tft.setFont(NULL);

    Ok.initButton(&tft,  280 + 5, 460 + 5, 80, 30, ILI9481_GREEN, ILI9481_GREEN , WHITE, "Ok", 2);
    Back.initButton(&tft,  41 - 7, 460 + 5, 80, 30, ILI9481_RED, ILI9481_RED, BLACK, "Back", 2);

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

    // //Serial.println("GRAPHICS DRAWING DONE JUMPING TO LOOP FOR SCREEN 2") ;

  }

  if ( screen == 23 ) {
    tft.fillScreen(BLACK);
    // //Serial.println("NOW ENTERING SETUP OF SCREEN 23") ;
    // //Serial.println("SCREEN 23 - FOR SELECTING THE TYPE OF VEHILCE WHICH THE USER WANTS TO PARK AS PER THAT COST IS DIVIDED") ;

    showmsgXY(45, 30, 2, &FreeSans9pt7b, "Vehicle Type");
    showmsgXYM(1, 58, 1, &FreeSans9pt7b, "Choose the type of vehicle \non the basis of that the rate is divided") ;
    tft.setFont(NULL);

    TwoThreeOne.initButton(&tft,  50, 150 - 15, 75, 50, AZURE, AZURE, BLACK, "1", 3);
    TwoThreeTwo.initButton(&tft,  50, 150 + 50 + 30 - 15, 75, 50, AZURE, AZURE, BLACK, "2", 3);

    Ok.initButton(&tft,  280 + 5, 460 + 5, 80, 30, ILI9481_GREEN, ILI9481_GREEN , WHITE, "Ok", 2);
    Back.initButton(&tft,  41 - 7, 460 + 5, 80, 30, ILI9481_RED, ILI9481_RED, BLACK, "Back", 2);

    TwoThreeOne.drawButton(false);
    TwoThreeTwo.drawButton(false);
    Ok.drawButton(false);
    Back.drawButton(false);
    showmsgXY(98, 140 - 15, 1, &FreeSans9pt7b, "Bike \n                    Rs.25 for 1 hour\n") ;
    showmsgXY(98, 140 + 80 - 15, 1, &FreeSans9pt7b, "Car \n                    Rs.30 for 1 hour\n") ;
    showmsgXY(1, 280 - 15, 1, &FreeSans9pt7b, "These are the rates for 1 hour,however you have to pay as per time passed and hence if you have kept the vehicle for \nhalf hour you have to pay half \nthe amount , the time elapsed is \npresicely calculated and for after every \n11 hours the rate per hour is increased \nby Rs.5") ;
    // //Serial.println("SETUP DONE NOW MOVING TO LOOP OF SCREEN 23") ;
  }

  if ( screen == 3 ) {
    tft.fillScreen(BLACK);
    // //Serial.println("NOW ENTERING SCREEN 3") ;
    // //Serial.println("SCREEN 3 - SLOT SELECTION SCREEN WHERE THE SLOT WHICH IS TO BE KEPT IS TAKEN FROM THE USER") ;

    showmsgXY(40, 30, 2, &FreeSans9pt7b, "Slot Selection");
    showmsgXYM(1, 55, 1, &FreeSans9pt7b, "These Slots are just for keeping the      space sorted , you have to pay as per      time kept !") ;
    tft.setFont(NULL);

    One.initButton(&tft,  50, 150, 75, 50, MAGENTA, MAGENTA, BLACK, "1", 3);
    Two.initButton(&tft,  50, 150 + 50 + 30, 75, 50, MAGENTA, MAGENTA, BLACK, "2", 3);
    Three.initButton(&tft, 50, 150 + 50 + 30 + 50 + 30, 75, 50, MAGENTA, MAGENTA, BLACK, "3", 3);
    Four.initButton(&tft,  50, 150 + 50 + 30 + 50 + 30 + 50 + 30, 75, 50, MAGENTA, MAGENTA, BLACK, "4", 3);
    Ok.initButton(&tft,  280 + 5, 460 + 5, 80, 30, ILI9481_GREEN, ILI9481_GREEN , WHITE, "Ok", 2);
    Back.initButton(&tft,  41 - 7, 460 + 5, 80, 30, ILI9481_RED, ILI9481_RED, BLACK, "Back", 2);

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
    // //Serial.println("SETTING DONE NOW MOVING TO LOOP FOR SCREEN 3") ;
  }

  if ( screen == 4 ) {
    tft.fillScreen(BLACK);

    // //Serial.println("NOW ENTERING SCREEN 4") ;
    // //Serial.println("SCREEN 4 - UNIQUE IDENTIFICATION SCREEN WHERE THE USER PRESSES NUMPAD TO ENTER THE VEHICLE'S NUMBER");
    showmsgXY(75, 40, 2, &FreeSans12pt7b, "Unique \n  Identification");
    tft.setFont(NULL);
    Ok.initButton(&tft,  260, 460, 150, 40, ILI9481_GREEN, ILI9481_GREEN , WHITE, "Confirm", 2);
    Back.initButton(&tft,  41 - 7, 460 + 5, 80, 30, ILI9481_RED, ILI9481_RED, BLACK, "Back", 2);

    E.initButton(&tft,  160 , 210 + 20, 110, 50, MAGENTA, MAGENTA, BLACK, "Numpad", 2);


    Back.drawButton(false);
    E.drawButton(false);
    // //Serial.println("THE CONFIRM BUTTON WILL NOT BE DRAWN RIGHT NOW") ;
    /* -- showmsgXYM(1, 133, 1, &FreeSans9pt7b, "Enter your Vehicle's Registration no.     (from number plate) for our records") ; -- */
    showmsgXYM(1, 133, 1, &FreeSans9pt7b, "Enter 4 digit PIN to make it unique , it \nshould consist of last 2 digits of your \nvehicle number and two secret digits of your choice") ;
    /*  EXECUTE THESE STATEMENTS AFTER RETURNING FROM NUMPAD SCREEN */
    if ( n == 1 ) {
      // //Serial.println("USER HAS ENTERED PROPER DIGITS FOR PIN");
      // //Serial.println("DRAW THE CONFIRM BUTTON") ;
      showmsgXY(50 + 8, 260 + 20 + 16, 2 , NULL , textfield) ;
      tft.drawRect(50, 260 + 20, 220, 50, ILI9481_DARKGREY );
      showmsgXY(17, 400, 1, &FreeSans9pt7b, "Press Confirm to continue");

      Ok.drawButton(false);
    }
    // //Serial.println("DONE NOW MOVING TO LOOP FOR SCREEN 4") ;
  }

  if ( screen == 45 ) {
    tft.fillScreen(BLACK);
    // //Serial.println("NOW ENTERING SETUP FOR SCREEN 45") ;
    // //Serial.println("SCREEN 45 - PHONE NUMBER SCREEN WHERE THE USER HAS TO ENTER PHONE NUMBER , IN ORDER TO RECEIVE AN E-RECEIPT AND IT WOULD BE STORED IN THE STRUCTURE FOR THE USER , SO AS THE USER WOULD GET AN E-RECEIPT WHILE TAKING THE CAR OUT ALSO");


    showmsgXY(75, 40, 2, &FreeSans12pt7b, "Phone  \n     Number");
    tft.setFont(NULL);


    Ok.initButton(&tft,  260, 460, 150, 40, ILI9481_GREEN, ILI9481_GREEN , WHITE, "Confirm", 2);
    Back.initButton(&tft,  41 - 7, 460 + 5, 80, 30, ILI9481_RED, ILI9481_RED, BLACK, "Back", 2);

    E.initButton(&tft,  160 , 210 + 20, 110, 50, MAGENTA, MAGENTA, BLACK, "Numpad", 2);

    Back.drawButton(false);
    E.drawButton(false);
    // //Serial.println("DON'T DRAW THE CONFIRM BUTTON NOW") ;

    /* -- showmsgXYM(1, 133, 1, &FreeSans9pt7b, "Enter your Vehicle's Registration no.     (from number plate) for our records") ; -- */
    showmsgXYM(1, 133, 1, &FreeSans9pt7b, "Enter your 10 DIGIT phone number \nwhich you have right now") ;
    /*  EXECUTE THESE STATEMENTS AFTER RETURNING FROM NUMPAD SCREEN */
    if ( ph_n == 1 ) {
      // //Serial.println("DRAW THE CONFIRM BUTTON BECAUSE THE USER HAS ENTERED THE CORRECT NO. OF DIGITS") ;
      showmsgXY(50 + 8, 260 + 14, 2 , NULL , ph_textfield) ;
      tft.drawRect(50, 260, 220, 50, ILI9481_DARKGREY );
      showmsgXY(17, 400, 1, &FreeSans9pt7b, "Press Confirm to keep your vehicle");

      Ok.drawButton(false);
    }
    // //Serial.println("DONE NOW MOVING TO LOOP FOR SCREEN 45") ;
  }

  if ( screen == 5 ) {


    if ( c[i][counter[i]].yes == 9 )
      C_IN = C_IN  + 1;

    tft.fillScreen(BLACK);

    showmsgXYM(1, 50, 3, &FreeSans9pt7b, "Successful");
    showmsgXY(1, 95, 1, &FreeSans9pt7b, "You can now just keep your vehicle at \nthe prefered floor as per your choice of no. of hours , at the time of exit just \nchoose the option 2 and enter vehicle's number again , pay and take your \nVehicle back , now press Finish Button") ;
    showmsgXY(65, 400, 2, &FreeSans9pt7b, "Thank You !") ;
    tft.setFont(NULL);

    Finish.initButton(&tft,  160 , 300, 150, 50, MAGENTA, MAGENTA, BLACK, "Finish", 3);
    Finish.drawButton(false);
    // //Serial.println("DONE SETUP FOR KEEPING A VEHICLE") ;
    // //Serial.println("NOW MOVING TO LOOP FOR SCREEN 5 WHICH DOES NOT HAS MANY SUCH THINGS AND HENCE WILL SET SCREEN 1 AND CALL SETUP EVENTUALLY") ;
  }

  if ( screen == 9 ) {
    // //Serial.println("NOW ENTERING THE SETUP FOR NUMPAD SCREEN 9") ;
    // //Serial.println("NUMPAD - 9 - THE NUMPAD SCREEN WHERE THERE IS A MATRIX INPUT AVAILABLE AND INPUT IS DRAWN TO SCREEN 4") ;

    tft.fillScreen(BLACK);
    for (uint8_t row = 0; row < 5; row++) {
      for (uint8_t col = 0; col < 3; col++) {
        buttons[col + row * 3].initButton(&tft, BUTTON_X + col * (BUTTON_W + BUTTON_SPACING_X),
                                          BUTTON_Y + row * (BUTTON_H + BUTTON_SPACING_Y), // x, y, w, h, outline, fill, text
                                          BUTTON_W, BUTTON_H, BLACK, buttoncolors[col + row * 3], ILI9481_WHITE,
                                          buttonlabels[col + row * 3], BUTTON_TEXTSIZE);
        buttons[0 + 0 * 3].initButton(&tft, BUTTON_X + 0 * (BUTTON_W + BUTTON_SPACING_X),
                                      BUTTON_Y + 0 * (BUTTON_H + BUTTON_SPACING_Y), // x, y, w, h, outline, fill, text
                                      BUTTON_W, BUTTON_H, BLACK, buttoncolors[0 + 0 * 3], WHITE,
                                      buttonlabels[0 + 0 * 3], BUTTON_TEXTSIZE);

        buttons[col + row * 3].drawButton();
      }
    }

    // create 'text field'
    tft.drawRect(TEXT_X, TEXT_Y, TEXT_W, TEXT_H, ILI9481_DARKGREY );
  }

  if ( screen == 991 ) {
    tft.fillScreen(BLACK);
    // //Serial.println("NOW MOVING TO SETUP FOR SCREEN 991 WHICH IS ANOTHER NUMPAD") ;
    // //Serial.println("NUMPAD_PH - 991 - THE NUMPAD SCREEN FOR ENTERING THE 10 DIGIT PHONE NUMBER") ;
    for (uint8_t row = 0; row < 5; row++) {
      for (uint8_t col = 0; col < 3; col++) {
        buttons[col + row * 3].initButton(&tft, BUTTON_X + col * (BUTTON_W + BUTTON_SPACING_X),
                                          BUTTON_Y + row * (BUTTON_H + BUTTON_SPACING_Y), // x, y, w, h, outline, fill, text
                                          BUTTON_W, BUTTON_H, BLACK, buttoncolors[col + row * 3], ILI9481_WHITE,
                                          buttonlabels[col + row * 3], BUTTON_TEXTSIZE);
        buttons[0 + 0 * 3].initButton(&tft, BUTTON_X + 0 * (BUTTON_W + BUTTON_SPACING_X),
                                      BUTTON_Y + 0 * (BUTTON_H + BUTTON_SPACING_Y), // x, y, w, h, outline, fill, text
                                      BUTTON_W, BUTTON_H, BLACK, buttoncolors[0 + 0 * 3], WHITE,
                                      buttonlabels[0 + 0 * 3], BUTTON_TEXTSIZE);

        buttons[col + row * 3].drawButton();
      }
    }

    // create 'text field'
    tft.drawRect(TEXT_X, TEXT_Y, TEXT_W, TEXT_H, ILI9481_DARKGREY );
    // //Serial.println("SETUP DONE NOW MOVING TO LOOP FOR SCREEN 991") ;
  }

  if ( screen == 91 ) {
    tft.fillScreen(BLACK);
    // //Serial.println("NOW MOVING TO SETUP FOR SCREEN 91 WHICH IS ANOTHER NUMPAD") ;
    // //Serial.println(" NUMPAD1 - 91 - THE NUMPAD SCREEN WHERE THERE IS A MATRIX INPUT AVAILABLE AND INPUT IS DRAWN TO SCREEN 21") ;
    for (uint8_t row = 0; row < 5; row++) {
      for (uint8_t col = 0; col < 3; col++) {
        buttons[col + row * 3].initButton(&tft, BUTTON_X + col * (BUTTON_W + BUTTON_SPACING_X),
                                          BUTTON_Y + row * (BUTTON_H + BUTTON_SPACING_Y), // x, y, w, h, outline, fill, text
                                          BUTTON_W, BUTTON_H, BLACK, buttoncolors[col + row * 3], ILI9481_WHITE,
                                          buttonlabels[col + row * 3], BUTTON_TEXTSIZE);
        buttons[0 + 0 * 3].initButton(&tft, BUTTON_X + 0 * (BUTTON_W + BUTTON_SPACING_X),
                                      BUTTON_Y + 0 * (BUTTON_H + BUTTON_SPACING_Y), // x, y, w, h, outline, fill, text
                                      BUTTON_W, BUTTON_H, BLACK, buttoncolors[0 + 0 * 3], WHITE,
                                      buttonlabels[0 + 0 * 3], BUTTON_TEXTSIZE);
        buttons[col + row * 3].drawButton();
      }
    }

    // create 'text field'
    tft.drawRect(TEXT_X, TEXT_Y, TEXT_W, TEXT_H, ILI9481_DARKGREY );
    // //Serial.println("SETUP DONE NOW MOVING TO LOOP FOR SCREEN 91") ;
  }

  if ( screen == 21) {
    tft.fillScreen(BLACK);
    // //Serial.println("NOW ENTERING SCREEN 21") ;
    // //Serial.println("SCREEN 21 - UNIQUE IDENTIFICATION SCREEN FOR TAKING THE VEHICLE OUT THE USER ENTERS THE VEHICLE'S NUMBER AND TAKES THE VEHICLE OUT") ;

    showmsgXY(75, 40, 2, &FreeSans12pt7b, "Unique \n  Identification");
    tft.setFont(NULL);

    Ok.initButton(&tft,  260, 460, 150, 40, ILI9481_GREEN, ILI9481_GREEN , WHITE, "Confirm", 2);
    Back.initButton(&tft,  41 - 7, 460 + 5, 80, 30, ILI9481_RED, ILI9481_RED, BLACK, "Back", 2);

    E.initButton(&tft,  160 , 210 + 20, 110, 50, MAGENTA, MAGENTA, BLACK, "Numpad", 2);

    Back.drawButton(false);
    E.drawButton(false);
    // //Serial.println("DON'T DRAW THE CONFIRM BUTTON AS THE LOGIC IS NOT SATISFIED") ;
    /* -- showmsgXYM(1, 133, 1, &FreeSans9pt7b, "Enter your Vehicle's Registration no.     (from number plate) to take your Vehicle out") ; -- */
    showmsgXYM(1, 133, 1, &FreeSans9pt7b, "Enter the 4-digit PIN, to take your \nvehicle out") ;

    /*  EXECUTE THESE STATEMENTS AFTER RETURNING FROM NUMPAD SCREEN */
    if ( nr == 1 ) {
      // //Serial.println("NOW DRAW THE CONFIRM BUTTON AS THE USER HAS ENTERED THE CORRECT NO. OF DIGITS") ;
      showmsgXY(50 + 8, 260 + 14, 2 , NULL , textfieldr) ;
      tft.drawRect(50, 260, 220, 50, ILI9481_DARKGREY );
      showmsgXY(5, 400, 1, &FreeSans9pt7b, "Press Confirm to take out your Vehicle");
      Ok.drawButton(false);
    }
    // //Serial.println("SETUP DONE NOW MOVING TO LOOP FOR SCREEN 21") ;
  }

  if ( screen == 22) {
    tft.fillScreen(BLACK);
    // //Serial.println("NOW ENTERING SCREEN 22") ;
    // //Serial.println("SCREEN 22 - FINAL CONFIRMATION SCREEN WHERE THE USER PRESSES FINISH AND TAKES THE VEHICLE OUT") ;

    DS3231_get(&t); //get the value and pass to the function the pointer to t, that make an lower memory fingerprint and faster execution than use return
    timeTemp = ((t.unixtime + 3154000000) % 10000) ;
    showmsgXYM(1, 50, 3, &FreeSans9pt7b, "Successful");
    showmsgXY(1, 95, 1, &FreeSans9pt7b, "You can now just take your Vehicle out by paying the correct amount and press \nthe Finish button") ;
    showmsgXY(65, 190, 2, &FreeSans9pt7b, "Thank You !") ;
    C_OUT = C_OUT + 1 ;
    C_IN = C_IN - 1 ;
    tft.setFont(NULL);

    /*  EXECUTE THESE STATEMENTS AFTER SUCCESSFUL SEARCH  */
    // //Serial.println("EXECUTE THESE STATEMENTS AFTER SUCCESSFUL SEARCH") ;

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
      COST = COST + 30 ;

    }
    else if ( c[i_temp][j_temp].type == 1 ) {

      tft.setFont(&FreeSans12pt7b);
      tft.setCursor(1 + 120, 250 + 25 + 40 + 40 + 20);
      tft.setTextColor(WHITE);
      tft.setTextSize(1);
      T = ( timeTemp - c[i_temp][j_temp].sTime) * bcm ;
      tft.print(25);
      tft.setFont(NULL);
      COST = COST + 25 ;
    }

    if (c[i_temp][j_temp].yes == 1 ) {
      //       // //Serial.println("THE USER HAS ENTERED A PHONE NUMBER") ;
      //       // //Serial.println("SO DUMPING THE DATA TO BE GOING TO GSM VIA SERIAL6") ;
      //       // //Serial.println("AT+CMGF=1") ;
      //
      //      Serial.print("AT+CMGS=\"+91") ;
      //      Serial.print(c[i_temp][j_temp].ph_number[0]) ;
      //      Serial.print(c[i_temp][j_temp].ph_number[1]) ;
      //      Serial.print(c[i_temp][j_temp].ph_number[2]) ;
      //      Serial.print(c[i_temp][j_temp].ph_number[3]) ;
      //      Serial.print(c[i_temp][j_temp].ph_number[4]) ;
      //      Serial.print(c[i_temp][j_temp].ph_number[5]) ;
      //      Serial.print(c[i_temp][j_temp].ph_number[6]) ;
      //      Serial.print(c[i_temp][j_temp].ph_number[7]) ;
      //      Serial.print(c[i_temp][j_temp].ph_number[8]) ;
      //      Serial.print(c[i_temp][j_temp].ph_number[9]) ;
      //      Serial.print("\"\r") ;
      //       // //Serial.println() ;
      //
      //       // //Serial.println("--- E-RECEIPT ---") ;
      //       // //Serial.println("") ;
      //       // //Serial.println("PARKING CORTEX") ;
      //       // //Serial.println("VEHICLE EXIT") ;
      //       // //Serial.println("") ;
      //      Serial.print("TIME KEPT : ") ;
      //      Serial.print(T1) ;
      //       // //Serial.println("") ;
      //      Serial.print("AMOUNT TO BE PAID : ") ;
      //      if ( c[i_temp][j_temp].type == 1 )
      //        Serial.print("Rs. 25") ;
      //      else if ( c[i_temp][j_temp].type == 2 )
      //        Serial.print("Rs. 30") ;
      //       // //Serial.println("");
      //
      //      Serial.print("EXIT TIME : ");
      //      DS3231_get(&t); //get the value and pass to the function the pointer to t, that make an lower memory fingerprint and faster execution than use return
      //      Serial.print(t.hour);
      //      Serial.print(":");
      //      Serial.print(t.min) ;
      //      Serial.print(":");
      //      Serial.print(t.sec);
      //       // //Serial.println("") ;
      //      Serial.print("DATE : ") ;
      //      Serial.print(t.mday) ;
      //      Serial.print("/");
      //      Serial.print(t.mon) ;
      //      Serial.print("/");
      //      Serial.print((t.year + 100));
      //       // //Serial.println("");
      //
      //       // //Serial.println((char)26);
      //
      //       // //Serial.println("DUMPING OF SERIAL6 DONE NOW MOVING THE DATA TO SERIAL6");
      delay(1000) ;
      Serial6.println("AT+CMGF=1") ;
      delay(1000) ;
      Serial6.print("AT+CMGS=\"+91") ;
      Serial6.print(c[i_temp][j_temp].ph_number[0]) ;
      Serial6.print(c[i_temp][j_temp].ph_number[1]) ;
      Serial6.print(c[i_temp][j_temp].ph_number[2]) ;
      Serial6.print(c[i_temp][j_temp].ph_number[3]) ;
      Serial6.print(c[i_temp][j_temp].ph_number[4]) ;
      Serial6.print(c[i_temp][j_temp].ph_number[5]) ;
      Serial6.print(c[i_temp][j_temp].ph_number[6]) ;
      Serial6.print(c[i_temp][j_temp].ph_number[7]) ;
      Serial6.print(c[i_temp][j_temp].ph_number[8]) ;
      Serial6.print(c[i_temp][j_temp].ph_number[9]) ;
      Serial6.print("\"\r") ;
      Serial6.println() ;
      delay(1000) ;
      Serial6.println("--- E-RECEIPT ---") ;
      Serial6.println("") ;
      Serial6.println("PARKING CORTEX") ;
      Serial6.println("VEHICLE EXIT") ;
      Serial6.println("") ;
      Serial6.print("TIME KEPT : ") ;
      Serial6.print(T1) ;
      Serial6.println("") ;
      Serial6.print("AMOUNT TO BE PAID : ") ;
      if ( c[i_temp][j_temp].type == 1 )
        Serial6.print("Rs. 25") ;
      else if ( c[i_temp][j_temp].type == 2 )
        Serial6.print("Rs. 30") ;
      Serial6.println("");

      Serial6.print("EXIT TIME : ");
      DS3231_get(&t); //get the value and pass to the function the pointer to t, that make an lower memory fingerprint and faster execution than use return
      Serial6.print(t.hour);
      Serial6.print(":");
      Serial6.print(t.min) ;
      Serial6.print(":");
      Serial6.print(t.sec);
      Serial6.println("") ;
      Serial6.print("DATE : ") ;
      Serial6.print(t.mday) ;
      Serial6.print("/");
      Serial6.print(t.mon) ;
      Serial6.print("/");
      Serial6.print((t.year + 100));
      Serial6.println("");
      delay(100);
      Serial6.println((char)26);

      delay(100) ;
      // //Serial.println("SENDING OF DATA TO GSM DONE VIA SERIAL6");
      Finish.initButton(&tft,  160 , 450, 150, 50, MAGENTA, MAGENTA, BLACK, "Finish", 3);
      Finish.drawButton(false);
    } else if (c[i_temp][j_temp].yes == 9 ) {
      Finish.initButton(&tft,  160 , 450, 150, 50, MAGENTA, MAGENTA, BLACK , "Finish", 3);
      Finish.drawButton(false);
    }

    for ( k = 0 ; k < TEXT_LEN  ; k++)
      textfieldr[k] = ' ' ;
    textfieldr_i = 0 ;
    i_temp = -1 ;
    j_temp = -1 ;

    // //Serial.println("RESETTING VARIABLES AND MOVING TO LOOP FOR SCREEN 21 WHICH WILL RESET AND CALL SETUP AGAINST SCREEN 1");
  }

  if ( screen == 220) {
    // //Serial.println("NOW ENTERING THE SCREEN 220");
    // //Serial.println("SCREEN 22_0 - 220 - THE ERROR SCREEN WHERE THE USER WILL GET WHEN ENTERED THE WRONG VEHICLE'S NUMBER OR WHICH IS NOT IN THE DATABASE");
    tft.fillScreen(BLACK);
    showmsgXY(1, 100, 2, &FreeSans9pt7b, "The number you \nentered does not \nmatch our records \nplease go back and \nenter the correct \nnumber") ;
    tft.setFont(NULL);
    Back.initButton(&tft,  41 - 7, 460 + 5, 80, 30, ILI9481_RED, ILI9481_RED, BLACK, "Back", 2);
    Back.drawButton(false);
    nr = 0 ;
    // //Serial.println("SETUP DONE NOW MOVING TO LOOP AND FURTHER LOOP") ;
  }

  /*--------------MINI V1---------------*/


  if ( screen == 1001 ) {

    tft.fillScreen(BLACK);
    // //Serial.println("NOW ENTERING SETUP OF SCREEN 1");
    // //Serial.println("SCREEN 1 - VEHICLE PARKING MAIN MENU SCREEN FOR TAKING USER INPUT OF WANT TO KEEP VEHICLE OR TAKE OUT VEHICLE") ;
    // //Serial.println("THIS IS THE SCREEN 1 FOR GSM VERSION") ;

    showmsgXY(1 + 35, 50 + 15, 5, &FreeSans9pt7b, "ePark");
    showmsgXYM(15 + 12, 115, 3, &FreeSans9pt7b, "Cortex  S5");
    showmsgXYG(15 + 100, 148 + 10, 2, &FreeSans9pt7b, "MINI");
    showmsgXYG(12, 162 + 10, 2, NULL, "RTC SIMPLE MINI VERSION 1");
    tft.setFont(NULL);
    one.initButton(&tft,  60, 150 + 100 + 55, 100, 50, MAGENTA, MAGENTA, BLACK, "1", 3);
    two.initButton(&tft,  60, 150 + 100 + 55 + 75, 100, 50, AZURE, AZURE, BLACK, "2", 3);


    tft.setCursor(120, 130 + 100 + 55);
    tft.setTextColor(WHITE);
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
    ph_n = -1 ;

    one.drawButton(false);
    two.drawButton(false);
    // //Serial.println("GRAPHICS, VARIABLES INITIALIZED JUMPING TO SCREEN 1 LOOP") ;

  }

  if ( screen == 1002 ) {
    tft.fillScreen(BLACK);
    // //Serial.println("NOW ENTRING SETUP OF SCREEN 2");
    // //Serial.println("SCREEN 2 - AVAILABLE SLOTS SCREEN WHERE THE AVAILABLE SLOTS ARE SHOWN IF ANY") ;

    showmsgXY(40, 30, 2, &FreeSans9pt7b, "Available Slots");
    showmsgXY(1, 42, 1, NULL, "The Following slots are only occupied by users based on their preference of time they want to keep thier  Vehicles, this has nothing to do with the amount that has to be paid at the time of exit , the user's \npreference helps the parking space to be in a sorted condition !");
    tft.setFont(NULL);

    Ok.initButton(&tft,  280 + 5, 460 + 5, 80, 30, ILI9481_GREEN, ILI9481_GREEN , WHITE, "Ok", 2);
    Back.initButton(&tft,  41 - 7, 460 + 5, 80, 30, ILI9481_RED, ILI9481_RED, BLACK, "Back", 2);

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

    // //Serial.println("GRAPHICS DRAWING DONE JUMPING TO LOOP FOR SCREEN 2") ;

  }

  if ( screen == 1003 ) {
    tft.fillScreen(BLACK);
    // //Serial.println("NOW ENTERING SCREEN 3") ;
    // //Serial.println("SCREEN 3 - SLOT SELECTION SCREEN WHERE THE SLOT WHICH IS TO BE KEPT IS TAKEN FROM THE USER") ;

    showmsgXY(40, 30, 2, &FreeSans9pt7b, "Slot Selection");
    showmsgXYM(1, 55, 1, &FreeSans9pt7b, "These Slots are just for keeping the      space sorted , you have to pay as per      time kept !") ;
    tft.setFont(NULL);

    One.initButton(&tft,  50, 150, 75, 50, MAGENTA, MAGENTA, BLACK, "1", 3);
    Two.initButton(&tft,  50, 150 + 50 + 30, 75, 50, MAGENTA, MAGENTA, BLACK, "2", 3);
    Three.initButton(&tft, 50, 150 + 50 + 30 + 50 + 30, 75, 50, MAGENTA, MAGENTA, BLACK, "3", 3);
    Four.initButton(&tft,  50, 150 + 50 + 30 + 50 + 30 + 50 + 30, 75, 50, MAGENTA, MAGENTA, BLACK, "4", 3);
    Ok.initButton(&tft,  280 + 5, 460 + 5, 80, 30, ILI9481_GREEN, ILI9481_GREEN , WHITE, "Ok", 2);
    Back.initButton(&tft,  41 - 7, 460 + 5, 80, 30, ILI9481_RED, ILI9481_RED, BLACK, "Back", 2);

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
    // //Serial.println("SETTING DONE NOW MOVING TO LOOP FOR SCREEN 3") ;
  }

  if ( screen == 10023 ) {
    tft.fillScreen(BLACK);
    // //Serial.println("NOW ENTERING SETUP OF SCREEN 23") ;
    // //Serial.println("SCREEN 23 - FOR SELECTING THE TYPE OF VEHILCE WHICH THE USER WANTS TO PARK AS PER THAT COST IS DIVIDED") ;

    showmsgXY(45, 30, 2, &FreeSans9pt7b, "Vehicle Type");
    showmsgXYM(1, 58, 1, &FreeSans9pt7b, "Choose the type of vehicle \non the basis of that the rate is divided") ;
    tft.setFont(NULL);

    TwoThreeOne.initButton(&tft,  50, 150 - 15, 75, 50, AZURE, AZURE, BLACK, "1", 3);
    TwoThreeTwo.initButton(&tft,  50, 150 + 50 + 30 - 15, 75, 50, AZURE, AZURE, BLACK, "2", 3);

    Ok.initButton(&tft,  280 + 5, 460 + 5, 80, 30, ILI9481_GREEN, ILI9481_GREEN , WHITE, "Ok", 2);
    Back.initButton(&tft,  41 - 7, 460 + 5, 80, 30, ILI9481_RED, ILI9481_RED, BLACK, "Back", 2);

    TwoThreeOne.drawButton(false);
    TwoThreeTwo.drawButton(false);
    Ok.drawButton(false);
    Back.drawButton(false);
    showmsgXY(98, 140 - 15, 1, &FreeSans9pt7b, "Bike \n                    Rs.25 for 1 hour\n") ;
    showmsgXY(98, 140 + 80 - 15, 1, &FreeSans9pt7b, "Car \n                    Rs.30 for 1 hour\n") ;
    showmsgXY(1, 280 - 15, 1, &FreeSans9pt7b, "These are the rates for 1 hour,however you have to pay as per time passed and hence if you have kept the vehicle for \nhalf hour you have to pay half \nthe amount , the time elapsed is \npresicely calculated and for after every \n11 hours the rate per hour is increased \nby Rs.5") ;
    // //Serial.println("SETUP DONE NOW MOVING TO LOOP OF SCREEN 23") ;
  }

  if ( screen == 1004 ) {
    tft.fillScreen(BLACK);

    // //Serial.println("NOW ENTERING SCREEN 4") ;
    // //Serial.println("SCREEN 4 - UNIQUE IDENTIFICATION SCREEN WHERE THE USER PRESSES NUMPAD TO ENTER THE VEHICLE'S NUMBER");
    showmsgXY(75, 40, 2, &FreeSans12pt7b, "Unique \n  Identification");
    tft.setFont(NULL);
    Ok.initButton(&tft,  260, 460, 150, 40, ILI9481_GREEN, ILI9481_GREEN , WHITE, "Confirm", 2);
    Back.initButton(&tft,  41 - 7, 460 + 5, 80, 30, ILI9481_RED, ILI9481_RED, BLACK, "Back", 2);

    E.initButton(&tft,  160 , 210 + 20, 110, 50, MAGENTA, MAGENTA, BLACK, "Numpad", 2);


    Back.drawButton(false);
    E.drawButton(false);
    // //Serial.println("THE CONFIRM BUTTON WILL NOT BE DRAWN RIGHT NOW") ;
    /* -- showmsgXYM(1, 133, 1, &FreeSans9pt7b, "Enter your Vehicle's Registration no.     (from number plate) for our records") ; -- */
    showmsgXYM(1, 133, 1, &FreeSans9pt7b, "Enter 4 digit PIN to make it unique , it \nshould consist of last 2 digits of your \nvehicle number and two secret digits of your choice") ;
    /*  EXECUTE THESE STATEMENTS AFTER RETURNING FROM NUMPAD SCREEN */
    if ( n == 1 ) {
      // //Serial.println("USER HAS ENTERED PROPER DIGITS FOR PIN");
      // //Serial.println("DRAW THE CONFIRM BUTTON") ;
      showmsgXY(50 + 8, 260 + 20 + 16, 2 , NULL , textfield) ;
      tft.drawRect(50, 260 + 20, 220, 50, ILI9481_DARKGREY );
      showmsgXY(17, 400, 1, &FreeSans9pt7b, "Press Confirm to continue");

      Ok.drawButton(false);
    }
    // //Serial.println("DONE NOW MOVING TO LOOP FOR SCREEN 4") ;
  }

  if ( screen == 1009 ) {
    // //Serial.println("NOW ENTERING THE SETUP FOR NUMPAD SCREEN 9") ;
    // //Serial.println("NUMPAD - 9 - THE NUMPAD SCREEN WHERE THERE IS A MATRIX INPUT AVAILABLE AND INPUT IS DRAWN TO SCREEN 4") ;

    tft.fillScreen(BLACK);
    for (uint8_t row = 0; row < 5; row++) {
      for (uint8_t col = 0; col < 3; col++) {
        buttons[col + row * 3].initButton(&tft, BUTTON_X + col * (BUTTON_W + BUTTON_SPACING_X),
                                          BUTTON_Y + row * (BUTTON_H + BUTTON_SPACING_Y), // x, y, w, h, outline, fill, text
                                          BUTTON_W, BUTTON_H, BLACK, buttoncolors[col + row * 3], ILI9481_WHITE,
                                          buttonlabels[col + row * 3], BUTTON_TEXTSIZE);
        buttons[0 + 0 * 3].initButton(&tft, BUTTON_X + 0 * (BUTTON_W + BUTTON_SPACING_X),
                                      BUTTON_Y + 0 * (BUTTON_H + BUTTON_SPACING_Y), // x, y, w, h, outline, fill, text
                                      BUTTON_W, BUTTON_H, BLACK, buttoncolors[0 + 0 * 3], WHITE,
                                      buttonlabels[0 + 0 * 3], BUTTON_TEXTSIZE);

        buttons[col + row * 3].drawButton();
      }
    }

    // create 'text field'
    tft.drawRect(TEXT_X, TEXT_Y, TEXT_W, TEXT_H, ILI9481_DARKGREY );
  }

  if ( screen == 10091 ) {
    tft.fillScreen(BLACK);
    // //Serial.println("NOW MOVING TO SETUP FOR SCREEN 91 WHICH IS ANOTHER NUMPAD") ;
    // //Serial.println(" NUMPAD1 - 91 - THE NUMPAD SCREEN WHERE THERE IS A MATRIX INPUT AVAILABLE AND INPUT IS DRAWN TO SCREEN 21") ;
    for (uint8_t row = 0; row < 5; row++) {
      for (uint8_t col = 0; col < 3; col++) {
        buttons[col + row * 3].initButton(&tft, BUTTON_X + col * (BUTTON_W + BUTTON_SPACING_X),
                                          BUTTON_Y + row * (BUTTON_H + BUTTON_SPACING_Y), // x, y, w, h, outline, fill, text
                                          BUTTON_W, BUTTON_H, BLACK, buttoncolors[col + row * 3], ILI9481_WHITE,
                                          buttonlabels[col + row * 3], BUTTON_TEXTSIZE);
        buttons[0 + 0 * 3].initButton(&tft, BUTTON_X + 0 * (BUTTON_W + BUTTON_SPACING_X),
                                      BUTTON_Y + 0 * (BUTTON_H + BUTTON_SPACING_Y), // x, y, w, h, outline, fill, text
                                      BUTTON_W, BUTTON_H, BLACK, buttoncolors[0 + 0 * 3], WHITE,
                                      buttonlabels[0 + 0 * 3], BUTTON_TEXTSIZE);
        buttons[col + row * 3].drawButton();
      }
    }

    // create 'text field'
    tft.drawRect(TEXT_X, TEXT_Y, TEXT_W, TEXT_H, ILI9481_DARKGREY );
    // //Serial.println("SETUP DONE NOW MOVING TO LOOP FOR SCREEN 91") ;
  }

  if ( screen == 1005 ) {


    if ( c[i][counter[i]].yes == 9 )
      C_IN = C_IN  + 1;

    tft.fillScreen(BLACK);

    showmsgXYM(1, 50, 3, &FreeSans9pt7b, "Successful");
    showmsgXY(1, 95, 1, &FreeSans9pt7b, "You can now just keep your vehicle at \nthe prefered floor as per your choice of no. of hours , at the time of exit just \nchoose the option 2 and enter vehicle's number again , pay and take your \nVehicle back , now press Finish Button") ;
    showmsgXY(65, 400, 2, &FreeSans9pt7b, "Thank You !") ;
    tft.setFont(NULL);

    Finish.initButton(&tft,  160 , 300, 150, 50, MAGENTA, MAGENTA, BLACK, "Finish", 3);
    Finish.drawButton(false);
    // //Serial.println("DONE SETUP FOR KEEPING A VEHICLE") ;
    // //Serial.println("NOW MOVING TO LOOP FOR SCREEN 5 WHICH DOES NOT HAS MANY SUCH THINGS AND HENCE WILL SET SCREEN 1 AND CALL SETUP EVENTUALLY") ;
  }

  if ( screen == 10021) {
    tft.fillScreen(BLACK);
    // //Serial.println("NOW ENTERING SCREEN 21") ;
    // //Serial.println("SCREEN 21 - UNIQUE IDENTIFICATION SCREEN FOR TAKING THE VEHICLE OUT THE USER ENTERS THE VEHICLE'S NUMBER AND TAKES THE VEHICLE OUT") ;

    showmsgXY(75, 40, 2, &FreeSans12pt7b, "Unique \n  Identification");
    tft.setFont(NULL);

    Ok.initButton(&tft,  260, 460, 150, 40, ILI9481_GREEN, ILI9481_GREEN , WHITE, "Confirm", 2);
    Back.initButton(&tft,  41 - 7, 460 + 5, 80, 30, ILI9481_RED, ILI9481_RED, BLACK, "Back", 2);

    E.initButton(&tft,  160 , 210 + 20, 110, 50, MAGENTA, MAGENTA, BLACK, "Numpad", 2);

    Back.drawButton(false);
    E.drawButton(false);
    // //Serial.println("DON'T DRAW THE CONFIRM BUTTON AS THE LOGIC IS NOT SATISFIED") ;
    /* -- showmsgXYM(1, 133, 1, &FreeSans9pt7b, "Enter your Vehicle's Registration no.     (from number plate) to take your Vehicle out") ; -- */
    showmsgXYM(1, 133, 1, &FreeSans9pt7b, "Enter the 4-digit PIN, to take your \nvehicle out") ;

    /*  EXECUTE THESE STATEMENTS AFTER RETURNING FROM NUMPAD SCREEN */
    if ( nr == 1 ) {
      // //Serial.println("NOW DRAW THE CONFIRM BUTTON AS THE USER HAS ENTERED THE CORRECT NO. OF DIGITS") ;
      showmsgXY(50 + 8, 260 + 14, 2 , NULL , textfieldr) ;
      tft.drawRect(50, 260, 220, 50, ILI9481_DARKGREY );
      showmsgXY(5, 400, 1, &FreeSans9pt7b, "Press Confirm to take out your Vehicle");
      Ok.drawButton(false);
    }
    // //Serial.println("SETUP DONE NOW MOVING TO LOOP FOR SCREEN 21") ;
  }

  if ( screen == 10022) {
    tft.fillScreen(BLACK);
    // //Serial.println("NOW ENTERING SCREEN 22") ;
    // //Serial.println("SCREEN 22 - FINAL CONFIRMATION SCREEN WHERE THE USER PRESSES FINISH AND TAKES THE VEHICLE OUT") ;

    DS3231_get(&t); //get the value and pass to the function the pointer to t, that make an lower memory fingerprint and faster execution than use return
    timeTemp = ((t.unixtime + 3154000000) % 10000) ;
    showmsgXYM(1, 50, 3, &FreeSans9pt7b, "Successful");
    showmsgXY(1, 95, 1, &FreeSans9pt7b, "You can now just take your Vehicle out by paying the correct amount and press \nthe Finish button") ;
    showmsgXY(65, 190, 2, &FreeSans9pt7b, "Thank You !") ;
    C_OUT = C_OUT + 1 ;
    C_IN = C_IN - 1 ;
    tft.setFont(NULL);

    /*  EXECUTE THESE STATEMENTS AFTER SUCCESSFUL SEARCH  */
    // //Serial.println("EXECUTE THESE STATEMENTS AFTER SUCCESSFUL SEARCH") ;

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
      COST = COST + 30 ;

    }
    else if ( c[i_temp][j_temp].type == 1 ) {

      tft.setFont(&FreeSans12pt7b);
      tft.setCursor(1 + 120, 250 + 25 + 40 + 40 + 20);
      tft.setTextColor(WHITE);
      tft.setTextSize(1);
      T = ( timeTemp - c[i_temp][j_temp].sTime) * bcm ;
      tft.print(25);
      tft.setFont(NULL);
      COST = COST + 25 ;
    }
    //       // //Serial.println() ;
    //
    //       // //Serial.println("--- E-RECEIPT ---") ;
    //       // //Serial.println("") ;
    //       // //Serial.println("PARKING CORTEX") ;
    //       // //Serial.println("VEHICLE EXIT") ;
    //       // //Serial.println("") ;
    //      Serial.print("TIME KEPT : ") ;
    //      Serial.print(T1) ;
    //       // //Serial.println("") ;
    //      Serial.print("AMOUNT TO BE PAID : ") ;
    //      if ( c[i_temp][j_temp].type == 1 )
    //        Serial.print("Rs. 25") ;
    //      else if ( c[i_temp][j_temp].type == 2 )
    //        Serial.print("Rs. 30") ;
    //       // //Serial.println("");
    //
    //      Serial.print("EXIT TIME : ");
    //      DS3231_get(&t); //get the value and pass to the function the pointer to t, that make an lower memory fingerprint and faster execution than use return
    //      Serial.print(t.hour);
    //      Serial.print(":");
    //      Serial.print(t.min) ;
    //      Serial.print(":");
    //      Serial.print(t.sec);
    //       // //Serial.println("") ;
    //      Serial.print("DATE : ") ;
    //      Serial.print(t.mday) ;
    //      Serial.print("/");
    //      Serial.print(t.mon) ;
    //      Serial.print("/");
    //      Serial.print((t.year + 100));
    //       // //Serial.println("");
    Finish.initButton(&tft,  160 , 450, 150, 50, MAGENTA, MAGENTA, BLACK , "Finish", 3);
    Finish.drawButton(false);


    for ( k = 0 ; k < TEXT_LEN  ; k++)
      textfieldr[k] = ' ' ;
    textfieldr_i = 0 ;
    i_temp = -1 ;
    j_temp = -1 ;

    // //Serial.println("RESETTING VARIABLES AND MOVING TO LOOP FOR SCREEN 21 WHICH WILL RESET AND CALL SETUP AGAINST SCREEN 1");
  }

  if ( screen == 100220) {
    // //Serial.println("NOW ENTERING THE SCREEN 220");
    // //Serial.println("SCREEN 22_0 - 220 - THE ERROR SCREEN WHERE THE USER WILL GET WHEN ENTERED THE WRONG VEHICLE'S NUMBER OR WHICH IS NOT IN THE DATABASE");
    tft.fillScreen(BLACK);
    showmsgXY(1, 100, 2, &FreeSans9pt7b, "The number you \nentered does not \nmatch our records \nplease go back and \nenter the correct \nnumber") ;
    tft.setFont(NULL);
    Back.initButton(&tft,  41 - 7, 460 + 5, 80, 30, ILI9481_RED, ILI9481_RED, BLACK, "Back", 2);
    Back.drawButton(false);
    nr = 0 ;
    // //Serial.println("SETUP DONE NOW MOVING TO LOOP AND FURTHER LOOP") ;
  }

}

/*   THE MAIN LOOP FOR THE ARDUINO
     ALL THE CODES FOR REDRAWING THE THINGS ARE DECLARED HERE
*/


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
      c[i][counter[i]].yes = 1 ;
      screen45() ;
    }
    if (no.justPressed()) {
      no.drawButton(true);
      c[i][counter[i]].yes = 9 ;

      screen5() ;
    }
  }

  if (screen == 1) {

    buttonState = digitalRead(buttonPin);

    if (buttonState == LOW) {
      // //Serial.println("OWNER BUTTON PRESSED # SEND MESSAGE TO HARD CODED ONWER'S MOBILE NUMBER") ;
      /*----START SENDING THE MESSAGE BY CALLING A FUNCTION OR SOMETHING AND THEN RE-ROUTE THE FUNCTION TO SETUP-----*/
      /*-----MESSAGE------*/
      screen8341() ;
      // //Serial.println("MESSAGE SENT NOW CONTINUE RUNNING LOOP FOR SCREEN 1") ;
    }
    bool down = Touch_getXY();
    Back.press(down && Back.contains(pixel_x, pixel_y));
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
    if (Back.justReleased())
      Back.drawButton();
    if (Back.justPressed()) {

      Back.drawButton(true);
      tft.fillScreen(WHITE);
      delay(2000) ;
      screen = 1001 ;
      setup();
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
        c[i][counter[i]].slot = i ;
        screen4() ;
      }

      else if (tempT1 == 0 && tempT2 == 2 ) {
        c[i][counter[i]].type = tempT2 ;
        c[i][counter[i]].slot = i ;
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

        screen145() ;
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

  if (screen == 45 ) {
    bool down = Touch_getXY();

    Ok.press(down && Ok.contains(pixel_x, pixel_y));
    Back.press(down && Back.contains(pixel_x, pixel_y));
    E.press(down && E.contains(pixel_x, pixel_y));


    if (Back.justReleased())
      Back.drawButton();
    if ( ph_n == 1 ) {
      if (Ok.justReleased())
        Ok.drawButton();
      if (Ok.justPressed()) {
        Ok.drawButton(true);
        for ( k = 0 ; k < ph_TEXT_LEN ; k++)
          c[i][counter[i]].ph_number[k] = ph_textfield[k];
        for ( k = 0 ; k < ph_TEXT_LEN  ; k++)
          ph_textfield[k] = ' ' ;
        ph_textfield_i = 0 ;
        screen1111() ;
      }
    }
    if (Back.justPressed()) {
      Back.drawButton(true);

      for ( k = 0 ; k < ph_TEXT_LEN  ; k++)
        ph_textfield[k] = ' ' ;
      ph_textfield_i = 0 ;
      ph_n = 0 ;

      ph_tempT1 = -1 ;
      ph_tempT2 = -1 ;

      screen145() ;
    }
    if (E.justReleased())
      E.drawButton();
    if (E.justPressed()) {
      E.drawButton(true);
      ph_numpad();
      ph_n = 1 ;
    }
  }

  if (screen == 5) {
    bool down = Touch_getXY();
    Finish.press(down && Finish.contains(pixel_x, pixel_y));

    if (Finish.justReleased())
      Finish.drawButton();

    if (Finish.justPressed()) {
      Finish.drawButton(true);
      DS3231_get(&t); //get the value and pass to the function the pointer to t, that make an lower memory fingerprint and faster execution than use return
      c[i][counter[i]].sTime = ((t.unixtime + 3154000000) % 10000) ;
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
        //Serial.print("Pressing: ");  // //Serial.println(b);
        buttons[b].press(true);  // tell the button it is pressed
      } else {
        buttons[b].press(false);  // tell the button it is NOT pressed
      }
    }

    // now we can ask the buttons if their state has changed
    for (uint8_t b = 0; b < 15; b++) {
      if (buttons[b].justReleased()) {
        // Serial.print("Released: ");  // //Serial.println(b);
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
        // //Serial.println(textfield);
        tft.setCursor(TEXT_X + 8, TEXT_Y + 14);
        tft.setTextColor(TEXT_TCOLOR, BLACK);
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
          if ( textfield_i != 4 ) {
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

  if ( screen == 991 ) {
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
        //Serial.print("Pressing: ");  // //Serial.println(b);
        buttons[b].press(true);  // tell the button it is pressed
      } else {
        buttons[b].press(false);  // tell the button it is NOT pressed
      }
    }

    // now we can ask the buttons if their state has changed
    for (uint8_t b = 0; b < 15; b++) {
      if (buttons[b].justReleased()) {
        // Serial.print("Released: ");  // //Serial.println(b);
        buttons[b].drawButton();  // draw normal
      }

      if (buttons[b].justPressed()) {
        buttons[b].drawButton(true);  // draw invert!

        // if a numberpad button, append the relevant # to the textfield
        if (b >= 3) {
          if (ph_textfield_i < ph_TEXT_LEN) {
            ph_textfield[ph_textfield_i] = buttonlabels[b][0];
            ph_textfield_i++;
            ph_textfield[ph_textfield_i] = 0; // zero terminate
          }
        }

        // clr button! delete char
        if (b == 1) {

          ph_textfield[ph_textfield_i] = 0;
          if (ph_textfield > 0) {
            ph_textfield_i--;
            ph_textfield[ph_textfield_i] = ' ';
          }
        }

        // update the current text field
        // //Serial.println(ph_textfield);
        tft.setCursor(TEXT_X + 8, TEXT_Y + 14);
        tft.setTextColor(TEXT_TCOLOR, BLACK);
        tft.setTextSize(TEXT_TSIZE);
        tft.print(ph_textfield);

        if (b == 2) {
          status(F("Back"));
          n = 0 ;
          for ( k = 0 ; k < ph_TEXT_LEN  ; k++) {
            ph_textfield[k] = ' ';

          }
          ph_textfield_i = 0 ;
          screen45() ;
        }

        if (b == 0) {
          status(F("Ok"));
          if ( ph_textfield_i != 10 ) {
            for ( k = 0 ; k < ph_TEXT_LEN  ; k++)
              ph_textfield[k] = ' ';
            ph_textfield_i = 0 ;
            ph_n = 0 ;
            screen45();
          } else {
            ph_n = 1 ;
            screen45() ;
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
        //Serial.print("Pressing: ");  // //Serial.println(b);
        buttons[b].press(true);  // tell the button it is pressed
      } else {
        buttons[b].press(false);  // tell the button it is NOT pressed
      }
    }

    // now we can ask the buttons if their state has changed
    for (uint8_t b = 0; b < 15; b++) {
      if (buttons[b].justReleased()) {
        // Serial.print("Released: ");  // //Serial.println(b);
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
        // //Serial.println(textfieldr);
        tft.setCursor(TEXT_X + 8, TEXT_Y + 14);
        tft.setTextColor(TEXT_TCOLOR, BLACK);
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
          if ( textfieldr_i != 4 ) {
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
              if (c[i][j].number[0] == textfieldr[0] && c[i][j].number[1] == textfieldr[1] && c[i][j].number[2] == textfieldr[2] && c[i][j].number[3] == textfieldr[3]) {

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

  /*-------- MINI VERSION --------------*/


  if (screen == 1001) {

    bool down = Touch_getXY();
    one.press(down && one.contains(pixel_x, pixel_y));
    two.press(down && two.contains(pixel_x, pixel_y));
    if (one.justReleased())
      one.drawButton();
    if (two.justReleased())
      two.drawButton();
    if (one.justPressed()) {
      one.drawButton(true);

      screen1002() ;
    }
    if (two.justPressed()) {
      two.drawButton(true);

      screen10021() ;
    }
  }

  if (screen == 1002) {


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
        screen1003() ;
      }
    }

    if (Back.justReleased())
      Back.drawButton();

    if (Back.justPressed()) {

      Back.drawButton(true);
      screen1001() ;
    }
  }

  if (screen == 1003 ) {

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

        screen10023() ;
      }

      else if (temp1 == 9 && temp2 == 1 && temp3 == 9 && temp4 == 9 ) {
        i = 1 ;
        screen10023() ;
      }
      else if (temp1 == 9 && temp2 == 9 && temp3 == 2 && temp4 == 9 ) {
        i = 2 ;
        screen10023() ;
      }
      else if (temp1 == 9 && temp2 == 9 && temp3 == 9 && temp4 == 3 ) {
        i = 3 ;
        screen10023() ;
      }

    }
    if (Back.justPressed()) {
      Back.drawButton(true);
      temp1 = -1 ;
      temp2 = -1 ;
      temp3 = -1 ;
      temp4 = -1 ;

      i = -1 ;

      screen1002() ;
    }
  }

  if (screen == 10023) {

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
        c[i][counter[i]].slot = i ;
        screen1004() ;
      }

      else if (tempT1 == 0 && tempT2 == 2 ) {
        c[i][counter[i]].type = tempT2 ;
        c[i][counter[i]].slot = i ;
        screen1004() ;
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


      screen1003() ;
    }

  }

  if (screen == 1004) {

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

        screen1005() ;
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

      screen10023() ;
    }
    if (E.justReleased())
      E.drawButton();
    if (E.justPressed()) {
      E.drawButton(true);
      numpad100();
      n = 1 ;
    }
  }

  if (screen == 1005) {
    bool down = Touch_getXY();
    Finish.press(down && Finish.contains(pixel_x, pixel_y));

    if (Finish.justReleased())
      Finish.drawButton();

    if (Finish.justPressed()) {
      Finish.drawButton(true);
      DS3231_get(&t); //get the value and pass to the function the pointer to t, that make an lower memory fingerprint and faster execution than use return
      c[i][counter[i]].sTime = ((t.unixtime + 3154000000) % 10000) ;
      counter[i] = counter[i] + 1 ;
      n = 0 ;

      temp1 = -1 ;
      temp2 = -1 ;
      temp3 = -1 ;
      temp4 = -1 ;

      i = -1 ;


      tempT1 = -1 ;
      tempT2 = -1 ;

      screen1001() ;
    }

  }

  if (screen == 1009) {
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
        //Serial.print("Pressing: ");  // //Serial.println(b);
        buttons[b].press(true);  // tell the button it is pressed
      } else {
        buttons[b].press(false);  // tell the button it is NOT pressed
      }
    }

    // now we can ask the buttons if their state has changed
    for (uint8_t b = 0; b < 15; b++) {
      if (buttons[b].justReleased()) {
        // Serial.print("Released: ");  // //Serial.println(b);
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
        // //Serial.println(textfield);
        tft.setCursor(TEXT_X + 8, TEXT_Y + 14);
        tft.setTextColor(TEXT_TCOLOR, BLACK);
        tft.setTextSize(TEXT_TSIZE);
        tft.print(textfield);

        if (b == 2) {
          status(F("Back"));
          n = 0 ;
          for ( k = 0 ; k < TEXT_LEN  ; k++) {
            textfield[k] = ' ';

          }
          textfield_i = 0 ;
          screen1004() ;
        }

        if (b == 0) {
          status(F("Ok"));
          if ( textfield_i != 4 ) {
            for ( k = 0 ; k < TEXT_LEN  ; k++)
              textfield[k] = ' ';
            textfield_i = 0 ;
            n = 0 ;
            screen1004();
          } else {
            n = 1 ;
            screen1004() ;
          }
        }

        delay(100); // UI debouncing
      }
    }
  }

  if (screen == 10021) {
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
              if (c[i][j].number[0] == textfieldr[0] && c[i][j].number[1] == textfieldr[1] && c[i][j].number[2] == textfieldr[2] && c[i][j].number[3] == textfieldr[3]) {

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
            screen10022() ;

          } else if (found == 0) {
            for ( k = 0 ; k < TEXT_LEN  ; k++)
              textfieldr[k] = ' ' ;
            textfieldr_i = 0 ;
            screen10022_0() ;
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
      screen1001() ;
    }
    if (E.justReleased())
      E.drawButton();
    if (E.justPressed()) {
      E.drawButton(true);
      numpad1001() ;
      nr = 1;
    }

  }

  if (screen == 10091) {
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
        //Serial.print("Pressing: ");  // //Serial.println(b);
        buttons[b].press(true);  // tell the button it is pressed
      } else {
        buttons[b].press(false);  // tell the button it is NOT pressed
      }
    }

    // now we can ask the buttons if their state has changed
    for (uint8_t b = 0; b < 15; b++) {
      if (buttons[b].justReleased()) {
        // Serial.print("Released: ");  // //Serial.println(b);
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
        // //Serial.println(textfieldr);
        tft.setCursor(TEXT_X + 8, TEXT_Y + 14);
        tft.setTextColor(TEXT_TCOLOR, BLACK);
        tft.setTextSize(TEXT_TSIZE);
        tft.print(textfieldr);

        if (b == 2) {
          mfound = 0 ;

          nr = 0 ;
          for ( k = 0 ; k < TEXT_LEN  ; k++)
            textfieldr[k] = ' ' ;

          textfieldr_i = 0 ;
          screen10021() ;
        }

        if (b == 0) {
          if ( textfieldr_i != 4 ) {
            for ( k = 0 ; k < TEXT_LEN  ; k++)
              textfieldr[k] = ' ';
            textfieldr_i = 0 ;

            mfound = 0 ;
            nr = 0 ;
            screen10021();
          } else {
            mfound = 1 ;
            nr = 1 ;
            screen10021() ;
          }
        }
        delay(100); // UI debouncing
      }
    }
  }

  if (screen == 10022) {
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
      screen1001();
    }

  }

  if (screen == 100220) {
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
      screen10021() ;
    }
  }

}
