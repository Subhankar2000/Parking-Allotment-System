#include <Arduino.h>
#line 1 "D:\\Arduino-STM32-ARM-M4\\portable\\sketchbook\\V5.8_b_\\V5.8_b_.ino"
#line 1 "D:\\Arduino-STM32-ARM-M4\\portable\\sketchbook\\V5.8_b_\\V5.8_b_.ino"
/*   EPARK CORTEX S5 [ MINI / GSM / SERVER(b) ] <--------------------------------------------------------------------------------------> [ v1 / v2 / v5 ]

     [VERSIONS****************CHANGELOG]
     -> STARTED WITH THE NAME OF "CAR PARKING MANAGEMENT" IN FEB 2018 WITH ONLY ONE VARIANT OF IT WHICH HAD RFID AND HAD VERY POOR CODE FLEXIBILITY[v0.1]
     -> MODIFIED A LITTLE EXTENT BUT WITH FAILURE
     -> STARTED AGAIN WITH COMPLETELY DIFFERENT APPROACH WITH COMPUTING IN MIND, ALL THE THINGS WILL BE COMPUTED IN MCU AND A BETTER MCU AND THE
     DISPLAY WILL BE EASY, THE CODE SHOULD BE FLEXIBLE AND EASY TO MODIFY AND MOST IMPORTANTLY BUG FREE, STARTED IN 21 DECEMBER,2018 NAMED IT
     "PARKING ALLOTMENT SYSTEM"
     -> JANUARY 2019 , FIRST VERSION OF THE CODE COMPLETED WITH NO BUGS ABSOLUTELY, HAD ARDUINO MEGA 2560, DS3231 RTC AND 3.5" ILI9841 TFT DISPLAY [v1]
     -> FEBRUARY 2019 , SECOND VERSION OF THE CODE COMPLETED WITH NO BUGS, HAD ARDUINO MEGA 2560 , 3.5" TFT RESISTIVE TOUCH DISPLAY , DS3231 RTC   [v2]
     MODULE , GSM-SIM900A MODULE
     -> MORE TWEAKS TO THE SOFTAWRE DONE IN MARCH 2019 AND PROJECT STALLED FOR 4 MONTHS                                                            [v2.1]
     -> JULY 2019 , MOVED THE WHOLE PROGRAM TO RUN IN NUCLEO-STM32F401RE AN ARM CORTEX M4 BASED DEVELOPMENT BOARD, BUT THE GSM AND RTC HAD TO BE
     DISCARDED AS VERY LOW SUPPORT OF THE LIBRARY FOR RTC AND NO PROPER SUPPORT FOR SERIAL                                                         [v3]
     -> AUGUST 2019 , CHANGED THE WHOLE PROJECT'S UI WITH SIMILARITY TO NUCLEO BOARD, SHIFTED AND INVERTED COLOURS TO WHITE AND BLUE               [v4]
     -> SEPTEMBER 2019 , MOVED THE WHOLE [V2.1] TO NUCLEO-STM32F401RET6 AND MODIFIED TOUCH SCREEN LIBRARY AND RTC LIBRARY & MODIFIED THE HARDWARE  [v5]
     FOR RTC TO SAVE THE NON-RECHARGABLE BATTERY LR2032
     -> SEPTEMBER 2019 , MODIFIED MORE TO FIT IN 3 VERSIONS IN ONE WITH A CONCEPT OF LINKED LIST AND DIFFERENT STARTING POINTERS, ALSO ADDED       [v5.1]
     MICRO SD CARD SUPPORT OF THE TFT SHIELD WITH THE HELP OF SPI PROTOCOL AND ADDED A SLPASH SCREEN THAT IS DRAWN BY THE LCD AND TAKEN FROM MSD
     CARD.
     -> ADDED HIDDEN BUTTONS FOR TESTING AND SERIAL DEBUGGING LINES FOR TRACING BUGS IN THE CODE                                                   [v5.2]
     -> ADDED SUPPORT FOR SERVER [BETA] VERSION AND ADDED ESP8266 FOR NETWORK CONNECTIVITY AND UPLOADING METRICS TO MQTT SERVER AND INTEGRATE
     WITH AN ANDROID APP FOR PRE-BOOKING AND VIEWING OF SLOTS.                                                                                     [v5.3]
     -> ADDED COMMUNICATION WITH ESP8266 WITH I2C BUS AND READ MEANING FULL DATA FOR THE COUNTER ARRAY DENOTING THE NUMBER OF FREE SPACES          [v5.4]
     -> ADDED COMMUNICATION BOTHWAYS FROM ESP TO ARM AND FROM ARM TO ESP WITH DATA TRANSFER ONLY POSSIBLE IN SCREEN 1 NOT SO RAPIDLY               [v5.5]
     -> ADDED COMMUNICATION WITH MQTT SERVER WITH ESP8266 FROM ADAFRUIT I/O  WITH LIMITED UPDATE FUNCTIONALITY                                     [v5.6]
     -> FIXED BUGS --->--->--->
        -> TWO SAME PINS IF ENTERED DID NOT REPORTED ANY ERROR THAT ONE PIN IS ALREADY TAKEN------------------------------------------------------[FIXED]
        -> IF ONE OF SLOTS WAS FILLED, THE USER COULD PROCEED AND BOOK THAT FILLED SLOT-----------------------------------------------------------[FIXED]
        -> IF THE USER TAKES THE CAR AND ENTERED THE 2ND MENU FOR TAKING THE CAR, AFTER TAKING ALSO THE PIN MATCHED-------------------------------[FIXED]
        -> THE NUMPAD OF PH NUMBER SCREEN HAD A PROPAGATED BUG FROM v2 THAT IF THE BACK BUTTON IS PRESSED ONE CAN PRESS THE CONFIRM BUTTON--------[FIXED]
     -> MOVED THE AVAILABLE SLOTS SCREEN COMPLETELY AND KEPT THE SLOT SEKLECTION SCREEN IN OPTION 1 PARK YOUR CAR [FEATURE] [MAJOR IMPROVEMENT]
     -> CHANGED THE 4-DIGIT PIN TO 7-DIGIT PIN FOR EXTRA COMBINATIONS AND LESS REPEATATIONS [FEATURE] 
     -> TURNED ON SERIAL DEBUGGING AND ADDED LINES IN THE GSM VERSION FOR ADVANCED SERIAL DEBUGGING WITH A VERY HIGH BAUD RATE
     -> ADDED SECRET BUTTONS FOR TRANSITION OF ONE VERSION TO ANOTHER AND ADDED A LOADING SCREEN FOR THEM 
     -> THE BUGS WERE FIXED ONLY IN GSM VERSION                                                                                                    [v5.7]
     -> CHANGES WERE REFLECTED IN OTHER MINI AND SERVER BETA VERSIONS WITH I2C IN ESP AND OTHER BUG FIXES IN BOTH THE VERSIONS                     [v5.8]
     -> ADDED SERIAL DEBUGGING PRINT LINES ACROSS ALL VERSIONS                                                                                     [v5.8(b)]

     -> THIS IS A PROJECT WITH THE AIM TO SOLVE THE CHAOS IN A PARKING LOT AND RECORD ALL THE DATAS ELECTRONICALLY
     THIS HAS 3 VARIANTS PLUS MORE CUSTOMIZING OPTIONS, THE SOFTWARE HAS TO BE TAYLOR MADE FOR EACH PARKING SPACE WHICH IS VERY ESSENTIAL BUT
     WILL NOT TAKE MORE TIME FOR DEVELOPMENT, THE MAIN 3 VARIANTS STRAIGHT FORWARD ARE ALL IN THIS PROGRAM AND ONE CAN BE CHOOSEN AT A TIME
     MOST IMPORTANTLY AS THIS IS THE DEVELOPMENT VERSION, THE GSM IS THE MOST COMPLETED OF THEM ALL AND HENCE THERE ARE HIDDEN BUTTONS TO SWITCH TO
     MINI VERSION AND SERVER VERSION FOR DEMONSTRATION PURPOSES, THEY ALL USE THE SAME STRUCTURE AND SAME FORWARD BACKWARD PRINCIPLES FOR SMOOTH UI
     -> THE MOST COMPLETE VERSION IS THE GSM WHICH IS EQUIPPED FOR SENDING MESSAGES -> SENDS MESSAGE TO THE OWNER THAT IS A SUMMARY SENDS MESSAGE TO THE USER
     THAT IS AN E-RECEIPT AND ALSO IF THE USER GIVES IN HIS/HER PHONE NUMBER OR OPTS IN FOR E-RECIPT THEN ALSO THEY WILL GET AN E-RECEIPT BOTH DURING
     ENTRY AND EXIT.

     THIS IS A NEW VERSION AND THIS PROJECT TRIES TO SOLVE THE VEHICLE PARKING ALLOTMENT PROBLEM BY SORTING THE PLACES OF VEHICLE TO BE KEPT ON SO
     THAT THERE WOULD BE LESS CHAOS SO THIS TAKES INPUT ON BASIS OF TIME , CALCULATES ELAPSED TIME AND THEN CHARGES AS PER THE TIME THE VEHICLE
     WAS KEPT AND BECAUSE OF THIS A USER HAS TO PAY ONLY OF THE TIME KEPT INSIDE AND NOT ANY EXTRA AND ALSO THE PARKING SPACE IS LITTLE MORE SORTED
     BECAUSE THE VEHICLES ARE KEPT IN A FLOOR - TIME DEPENDENT TYPE THAT IS EACH FLOOR IS ENTITLED TO A SPECIFIC AMOUNT OF TIME. THIS PROJECT
     IS MADE BY USING AN NUCLEO STM32FR01RET6 , 3.5" TFT RESISTIVE TOUCH DISPLAY , DS3231 RTC MODULE , GSM-SIM900A MODULE , ESP8266 , ILI9341 SCREEN

     ALL THE LIBRARIES USED , ARE IN PUBLIC DOMAIN
     #TOUCHSCREEN.H HAS BEEN MODIFIED A LOT
     #DS3231FS LIBRAY IS TO BE USED FOR STM32-F401RE
     #SPI/I2C SHOULD BE CARRIED IN A LOW SPEED ~ 18 MHz

     ONLY DIS-ADVANTAGE - VOLATILE MEMORY MEMORY IS SRAM AND ITS LOST WHEN RESET !
*/

/*--------------------------------------------------------------------------------------------------------------------------------------------------------*/
/*---------------------------- CODE ----------------------------------------------------------------------------------------------------------------------*/
/*--------------------------------------------------------------------------------------------------------------------------------------------------------*/

/*  START OF PRE PROCESSOR DIRECTIVES */
/*  3.5" TFT DISPLAY WITH DRIVER ILI9481 */

#include <MCUFRIEND_kbv.h>
#include <Adafruit_GFX.h>
#include <TouchScreen.h>

/*   DS3231 RTC MODULE */
#include <Wire.h>
#include <ds3231.h>

#include <SPI.h>            // f.k. for Arduino-1.5.2
#include <SD.h>             // Use the official SD library on hardware pins
#if defined(ESP32)
#define SD_CS     5
#else
#define SD_CS     10
#endif
#define NAMEMATCH "1"        // "" matches any name
#define PALETTEDEPTH   8     // support 256-colour Palette

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
#define TEXT_LEN 7
#define TEXT_LEN200 4
#define ph_TEXT_LEN 10
#define OTP_TEXT_LEN 4
char otp_textfield[OTP_TEXT_LEN + 1] = "" ;
char ph_textfield[ph_TEXT_LEN + 1] = "";

uint8_t otp_textfield_i = 0 ;
uint8_t ph_textfield_i = 0;

char textfield[TEXT_LEN + 1] = "";
uint8_t textfield_i = 0;
char textfieldr[TEXT_LEN + 1] = "";
uint8_t textfieldr_i = 0;

char textfieldr200[TEXT_LEN200 + 1] = "";
uint8_t textfieldr_i200 = 0;

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

char namebuf[32] = "/";   //BMP files in root directory
File root;
File root1;
int pathlen;
int pathlen1;

struct car {
  int yes = 0 ;
  int slot ;
  char ph_number[10] ;
  char number[7] ;
  long int sTime ;
  int type ;

  char otp[4] ;

} c[4][5] ;

int i = 0 , j , k  ;
int iii , jjj , jjjj , iiii , jjjjj , iiiii ;

String textFT  , textFrt ;

int n = 0 , nr = 0 , nr200 = 0 ,  tempT1 = -1 , tempT2 = -2 , counter[4] , temp1 = -1 , temp2 = -2 , temp3 = -3 , temp4 = -4 , found = 0 , found200 = 0 , mfound = -1, mfound200 = -1 ;

double bcm = 0.006944 , ccm = 0.00833 ;
long int a ;
long int timeTemp , T1;
double T ;
int l , m  , o , p , i_temp , j_temp, i_temp200 , j_temp200 ;
int C_OUT = 0 ,  COST = 0 ;

long int a1 = 0 , b1 = 0 ;

const int buttonPin = PC13;
const int buttonPositive = 30 ;
const int buttonNegative = 31 ;
int buttonState = 0;

int tft_firstscreen = 1 ;
int tft_firstscreentr = 1 ;

int C_IN = 0 ;

int ph_n , ph_tempT1 , ph_tempT2 ;

ts t; //ts is a struct findable in ds3231.h
long long int unixtime1 ;

HardwareSerial Serial6(PA12, PA11);

/*  DATA VARIABLES DECLATION ENDED */

MCUFRIEND_kbv tft;    /* CREATION OF OBJECT FOR TFT */

int screen = 111110 ;
/*  THE MAIN VARIABLE USED FOR SWITCHING IN BETWEEN SCREENS , THAT IS BASED ON THIS VALUE THE PARTS OF SETUP AND LOOP WILL BE EXECUTED  */
int prog = -1 ;
int found_pin = -1 ;
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
#line 270 "D:\\Arduino-STM32-ARM-M4\\portable\\sketchbook\\V5.8_b_\\V5.8_b_.ino"
void status(const __FlashStringHelper *msg);
#line 274 "D:\\Arduino-STM32-ARM-M4\\portable\\sketchbook\\V5.8_b_\\V5.8_b_.ino"
void status(char *msg);
#line 278 "D:\\Arduino-STM32-ARM-M4\\portable\\sketchbook\\V5.8_b_\\V5.8_b_.ino"
bool Touch_getXY(void);
#line 293 "D:\\Arduino-STM32-ARM-M4\\portable\\sketchbook\\V5.8_b_\\V5.8_b_.ino"
void showmsgXYGR(int x, int y, int sz, const GFXfont *f, const char *msg);
#line 307 "D:\\Arduino-STM32-ARM-M4\\portable\\sketchbook\\V5.8_b_\\V5.8_b_.ino"
void showmsgXY(int x, int y, int sz, const GFXfont *f, const char *msg);
#line 320 "D:\\Arduino-STM32-ARM-M4\\portable\\sketchbook\\V5.8_b_\\V5.8_b_.ino"
void showmsgXYM(int x, int y, int sz, const GFXfont *f, const char *msg);
#line 333 "D:\\Arduino-STM32-ARM-M4\\portable\\sketchbook\\V5.8_b_\\V5.8_b_.ino"
void showmsgXYR(int x, int y, int sz, const GFXfont *f, const char *msg);
#line 346 "D:\\Arduino-STM32-ARM-M4\\portable\\sketchbook\\V5.8_b_\\V5.8_b_.ino"
void showmsgXYG(int x, int y, int sz, const GFXfont *f, const char *msg);
#line 358 "D:\\Arduino-STM32-ARM-M4\\portable\\sketchbook\\V5.8_b_\\V5.8_b_.ino"
void showmsgXYB(int x, int y, int sz, const GFXfont *f, const char *msg);
#line 371 "D:\\Arduino-STM32-ARM-M4\\portable\\sketchbook\\V5.8_b_\\V5.8_b_.ino"
void showmsgXYG1(int x, int y, int sz, const GFXfont *f, const char *msg);
#line 450 "D:\\Arduino-STM32-ARM-M4\\portable\\sketchbook\\V5.8_b_\\V5.8_b_.ino"
void screen1();
#line 454 "D:\\Arduino-STM32-ARM-M4\\portable\\sketchbook\\V5.8_b_\\V5.8_b_.ino"
void screen2();
#line 458 "D:\\Arduino-STM32-ARM-M4\\portable\\sketchbook\\V5.8_b_\\V5.8_b_.ino"
void screen23();
#line 462 "D:\\Arduino-STM32-ARM-M4\\portable\\sketchbook\\V5.8_b_\\V5.8_b_.ino"
void screen3();
#line 466 "D:\\Arduino-STM32-ARM-M4\\portable\\sketchbook\\V5.8_b_\\V5.8_b_.ino"
void screen4();
#line 470 "D:\\Arduino-STM32-ARM-M4\\portable\\sketchbook\\V5.8_b_\\V5.8_b_.ino"
void screen40();
#line 474 "D:\\Arduino-STM32-ARM-M4\\portable\\sketchbook\\V5.8_b_\\V5.8_b_.ino"
void screen5();
#line 478 "D:\\Arduino-STM32-ARM-M4\\portable\\sketchbook\\V5.8_b_\\V5.8_b_.ino"
void numpad();
#line 482 "D:\\Arduino-STM32-ARM-M4\\portable\\sketchbook\\V5.8_b_\\V5.8_b_.ino"
void numpad1();
#line 486 "D:\\Arduino-STM32-ARM-M4\\portable\\sketchbook\\V5.8_b_\\V5.8_b_.ino"
void screen21();
#line 490 "D:\\Arduino-STM32-ARM-M4\\portable\\sketchbook\\V5.8_b_\\V5.8_b_.ino"
void screen22();
#line 494 "D:\\Arduino-STM32-ARM-M4\\portable\\sketchbook\\V5.8_b_\\V5.8_b_.ino"
void screen22_0();
#line 498 "D:\\Arduino-STM32-ARM-M4\\portable\\sketchbook\\V5.8_b_\\V5.8_b_.ino"
void screen8341();
#line 502 "D:\\Arduino-STM32-ARM-M4\\portable\\sketchbook\\V5.8_b_\\V5.8_b_.ino"
void screen145();
#line 506 "D:\\Arduino-STM32-ARM-M4\\portable\\sketchbook\\V5.8_b_\\V5.8_b_.ino"
void screen45();
#line 510 "D:\\Arduino-STM32-ARM-M4\\portable\\sketchbook\\V5.8_b_\\V5.8_b_.ino"
void ph_numpad();
#line 514 "D:\\Arduino-STM32-ARM-M4\\portable\\sketchbook\\V5.8_b_\\V5.8_b_.ino"
void screen1111();
#line 521 "D:\\Arduino-STM32-ARM-M4\\portable\\sketchbook\\V5.8_b_\\V5.8_b_.ino"
void screen2001();
#line 525 "D:\\Arduino-STM32-ARM-M4\\portable\\sketchbook\\V5.8_b_\\V5.8_b_.ino"
void screen2002();
#line 529 "D:\\Arduino-STM32-ARM-M4\\portable\\sketchbook\\V5.8_b_\\V5.8_b_.ino"
void screen20023();
#line 533 "D:\\Arduino-STM32-ARM-M4\\portable\\sketchbook\\V5.8_b_\\V5.8_b_.ino"
void screen2003();
#line 537 "D:\\Arduino-STM32-ARM-M4\\portable\\sketchbook\\V5.8_b_\\V5.8_b_.ino"
void screen2004();
#line 541 "D:\\Arduino-STM32-ARM-M4\\portable\\sketchbook\\V5.8_b_\\V5.8_b_.ino"
void screen2005();
#line 545 "D:\\Arduino-STM32-ARM-M4\\portable\\sketchbook\\V5.8_b_\\V5.8_b_.ino"
void numpad200();
#line 549 "D:\\Arduino-STM32-ARM-M4\\portable\\sketchbook\\V5.8_b_\\V5.8_b_.ino"
void numpad2001();
#line 553 "D:\\Arduino-STM32-ARM-M4\\portable\\sketchbook\\V5.8_b_\\V5.8_b_.ino"
void screen20021();
#line 557 "D:\\Arduino-STM32-ARM-M4\\portable\\sketchbook\\V5.8_b_\\V5.8_b_.ino"
void screen20022();
#line 561 "D:\\Arduino-STM32-ARM-M4\\portable\\sketchbook\\V5.8_b_\\V5.8_b_.ino"
void screen20022_0();
#line 565 "D:\\Arduino-STM32-ARM-M4\\portable\\sketchbook\\V5.8_b_\\V5.8_b_.ino"
void screen2008341();
#line 569 "D:\\Arduino-STM32-ARM-M4\\portable\\sketchbook\\V5.8_b_\\V5.8_b_.ino"
void screen200145();
#line 573 "D:\\Arduino-STM32-ARM-M4\\portable\\sketchbook\\V5.8_b_\\V5.8_b_.ino"
void screen20045();
#line 577 "D:\\Arduino-STM32-ARM-M4\\portable\\sketchbook\\V5.8_b_\\V5.8_b_.ino"
void ph_numpad200();
#line 581 "D:\\Arduino-STM32-ARM-M4\\portable\\sketchbook\\V5.8_b_\\V5.8_b_.ino"
void screen2001111();
#line 585 "D:\\Arduino-STM32-ARM-M4\\portable\\sketchbook\\V5.8_b_\\V5.8_b_.ino"
void screen20031();
#line 589 "D:\\Arduino-STM32-ARM-M4\\portable\\sketchbook\\V5.8_b_\\V5.8_b_.ino"
void numpad20013();
#line 593 "D:\\Arduino-STM32-ARM-M4\\portable\\sketchbook\\V5.8_b_\\V5.8_b_.ino"
void screen20022_03();
#line 597 "D:\\Arduino-STM32-ARM-M4\\portable\\sketchbook\\V5.8_b_\\V5.8_b_.ino"
void screen20040();
#line 603 "D:\\Arduino-STM32-ARM-M4\\portable\\sketchbook\\V5.8_b_\\V5.8_b_.ino"
void screen1001();
#line 607 "D:\\Arduino-STM32-ARM-M4\\portable\\sketchbook\\V5.8_b_\\V5.8_b_.ino"
void screen1002();
#line 611 "D:\\Arduino-STM32-ARM-M4\\portable\\sketchbook\\V5.8_b_\\V5.8_b_.ino"
void screen10023();
#line 615 "D:\\Arduino-STM32-ARM-M4\\portable\\sketchbook\\V5.8_b_\\V5.8_b_.ino"
void screen1003();
#line 619 "D:\\Arduino-STM32-ARM-M4\\portable\\sketchbook\\V5.8_b_\\V5.8_b_.ino"
void screen1004();
#line 623 "D:\\Arduino-STM32-ARM-M4\\portable\\sketchbook\\V5.8_b_\\V5.8_b_.ino"
void screen1005();
#line 627 "D:\\Arduino-STM32-ARM-M4\\portable\\sketchbook\\V5.8_b_\\V5.8_b_.ino"
void numpad100();
#line 631 "D:\\Arduino-STM32-ARM-M4\\portable\\sketchbook\\V5.8_b_\\V5.8_b_.ino"
void numpad1001();
#line 635 "D:\\Arduino-STM32-ARM-M4\\portable\\sketchbook\\V5.8_b_\\V5.8_b_.ino"
void screen10021();
#line 639 "D:\\Arduino-STM32-ARM-M4\\portable\\sketchbook\\V5.8_b_\\V5.8_b_.ino"
void screen10022();
#line 643 "D:\\Arduino-STM32-ARM-M4\\portable\\sketchbook\\V5.8_b_\\V5.8_b_.ino"
void screen10022_0();
#line 647 "D:\\Arduino-STM32-ARM-M4\\portable\\sketchbook\\V5.8_b_\\V5.8_b_.ino"
void screen10040();
#line 659 "D:\\Arduino-STM32-ARM-M4\\portable\\sketchbook\\V5.8_b_\\V5.8_b_.ino"
void setup(void);
#line 2985 "D:\\Arduino-STM32-ARM-M4\\portable\\sketchbook\\V5.8_b_\\V5.8_b_.ino"
void loop(void);
#line 5640 "D:\\Arduino-STM32-ARM-M4\\portable\\sketchbook\\V5.8_b_\\V5.8_b_.ino"
uint16_t read16(File & f);
#line 5646 "D:\\Arduino-STM32-ARM-M4\\portable\\sketchbook\\V5.8_b_\\V5.8_b_.ino"
uint32_t read32(File & f);
#line 5652 "D:\\Arduino-STM32-ARM-M4\\portable\\sketchbook\\V5.8_b_\\V5.8_b_.ino"
uint8_t showBMP(char *nm, int x, int y);
#line 5792 "D:\\Arduino-STM32-ARM-M4\\portable\\sketchbook\\V5.8_b_\\V5.8_b_.ino"
void receiveEvent(int howMany);
#line 5804 "D:\\Arduino-STM32-ARM-M4\\portable\\sketchbook\\V5.8_b_\\V5.8_b_.ino"
void requestEvent();
#line 270 "D:\\Arduino-STM32-ARM-M4\\portable\\sketchbook\\V5.8_b_\\V5.8_b_.ino"
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
void showmsgXYGR(int x, int y, int sz, const GFXfont *f, const char *msg)
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

      [SCREEN LEGEND]

      [v1 - MINI]---------------------------------------------------------------------------[ADD 200 WITH THE CONTROLLERS]
      SCREEN 1001 - VEHICLE PARKING MAIN MENU SCREEN FOR TAKING USER INPUT OF WANT TO KEEP VEHICLE OR TAKE OUT VEHICLE
      SCREEN 1002 - AVAILABLE SLOTS SCREEN WHERE THE AVAILABLE SLOTS ARE SHOWN IF ANY
      SCREEN 1003 - SLOT SELECTION SCREEN WHERE THE SLOT WHICH IS TO BE KEPT IS TAKEN FROM THE USER
      SCREEN 10023 - FOR SELECTING THE TYPE OF VEHILCE WHICH THE USER WANTS TO PARK AS PER THAT COST IS DIVIDED
      SCREEN 1004 - UNIQUE IDENTIFICATION SCREEN WHERE THE USER PRESSES NUMPAD TO ENTER THE VEHICLE'S NUMBER
      NUMPAD - 1009 - THE NUMPAD SCREEN WHERE THERE IS A MATRIX INPUT AVAILABLE AND INPUT IS DRAWN TO SCREEN 1004
      SCREEN 1005 - CONFIRMATION SCREEN WHERE THE USER HAS TO PRESS FINISH IN ORDER TO KEEP VEHICLE INSIDE
      SCREEN 10021 - UNIQUE IDENTIFICATION SCREEN FOR TAKING THE VEHICLE OUT THE USER ENTERS THE VEHICLE'S NUMBER AND TAKES THE VEHICLE OUT
      NUMPAD1 - 10091 - THE NUMPAD SCREEN WHERE THERE IS A MATRIX INPUT AVAILABLE AND INPUT IS DRAWN TO SCREEN 10021
      SCREEN 10022 - FINAL CONFIRMATION SCREEN WHERE THE USER PRESSES FINISH AND TAKES THE VEHICLE OUT
      SCREEN 10022_0 - 220 - THE ERROR SCREEN WHERE THE USER WILL GET WHEN ENTERED THE WRONG VEHICLE'S NUMBER OR WHICH IS NOT IN THE DATABASE
      SCREEN 1004_0 - 10040 - THE ERROR SCREEN WHICH WILL COME IF THE USER HAS ENTERED A PIN WHICH ANOTHER USER HAS ALRADY ENTERED BEFORE

      [v2 - GSM]-----------------------------------------------------------------------------[ADD NULL WITH CONTROLLERS] - [BASE OF ALL VERSION]
      SCREEN 11110 - SPLASH SCREEN DISPLAYED FOR 7 SECONDS WITH THE NAME EPARK [ NO SETUP ONLY LOOP ]
      BY DEFAULT THE SPLASH SCREEN IS LOADED AND IT MOVES ON TO SCREEN 1
      ..................................................................................................
      SCREEN 1 - VEHICLE PARKING MAIN MENU SCREEN FOR TAKING USER INPUT OF WANT TO KEEP VEHICLE OR TAKE OUT VEHICLE
      SCREEN 8341 - SENDING MESSAGE STATUS WHILE THE MESSAGE IS BEING SENT TO THE OWNER OF THE PARKING LOT
      SCREEN 2 - AVAILABLE SLOTS SCREEN WHERE THE AVAILABLE SLOTS ARE SHOWN IF ANY
      SCREEN 3 - SLOT SELECTION SCREEN WHERE THE SLOT WHICH IS TO BE KEPT IS TAKEN FROM THE USER
      SCREEN 23 - FOR SELECTING THE TYPE OF VEHILCE WHICH THE USER WANTS TO PARK AS PER THAT COST IS DIVIDED
      SCREEN 4 - UNIQUE IDENTIFICATION SCREEN WHERE THE USER PRESSES NUMPAD TO ENTER THE VEHICLE'S NUMBER
      NUMPAD - 9 - THE NUMPAD SCREEN WHERE THERE IS A MATRIX INPUT AVAILABLE AND INPUT IS DRAWN TO SCREEN 4
      SCREEN 145 - ASKING FOR AN E-RECEIPT , IF THE USER DECLINES THIS , THEN THE CONFIRMATION SCREEN WILL COME AND IF THE USER ACCEPTS IT , THEN PH. NO. SCREEN WILL COME
      SCREEN 45 - PHONE NUMBER SCREEN WHERE THE USER HAS TO ENTER PHONE NUMBER , IN ORDER TO RECEIVE AN E-RECEIPT AND IT WOULD BE STORED IN THE STRUCTURE FOR THE USER , SO AS THE USER WOULD GET AN
                  E-RECEIPT WHILE TAKING THE CAR OUT ALSO
      NUMPAD_PH - 991 - THE NUMPAD SCREEN FOR ENTERING THE 10 DIGIT PHONE NUMBER
      SCREEN 1111 - SENDING E-RECEIPT SCREEN AFTER THE USER HAS ENTERED ALL THE DETAILS
      SCREEN 5 - CONFIRMATION SCREEN WHERE THE USER HAS TO PRESS FINISH IN ORDER TO KEEP VEHICLE INSIDE
      SCREEN 21 - UNIQUE IDENTIFICATION SCREEN FOR TAKING THE VEHICLE OUT THE USER ENTERS THE VEHICLE'S NUMBER AND TAKES THE VEHICLE OUT
      NUMPAD1 - 91 - THE NUMPAD SCREEN WHERE THERE IS A MATRIX INPUT AVAILABLE AND INPUT IS DRAWN TO SCREEN 21
      SCREEN 22 - FINAL CONFIRMATION SCREEN WHERE THE USER PRESSES FINISH AND TAKES THE VEHICLE OUT
      SCREEN 22_0 - 220 - THE ERROR SCREEN WHERE THE USER WILL GET WHEN ENTERED THE WRONG VEHICLE'S NUMBER OR WHICH IS NOT IN THE DATABASE
      SCREEN 4_0 - 40 - THE ERROR SCREEN WHICH WILL COME IF THE USER HAS ENTERED A PIN WHICH ANOTHER USER HAS ALRADY ENTERED BEFORE

      [v5 - SERVER(b)]------------------------------------------------------------------------[ADD 200 WITH CONTROLLERS] - [IN VERY DEVELOPMENT STAGE]
      SCREEN 2001 - VEHICLE PARKING MAIN MENU SCREEN FOR TAKING USER INPUT OF WANT TO KEEP VEHICLE OR TAKE OUT VEHICLE
      SCREEN 2008341 - SENDING MESSAGE STATUS WHILE THE MESSAGE IS BEING SENT TO THE OWNER OF THE PARKING LOT
      SCREEN 2002 - AVAILABLE SLOTS SCREEN WHERE THE AVAILABLE SLOTS ARE SHOWN IF ANY
      SCREEN 2003 - SLOT SELECTION SCREEN WHERE THE SLOT WHICH IS TO BE KEPT IS TAKEN FROM THE USER
      SCREEN 20023 - FOR SELECTING THE TYPE OF VEHILCE WHICH THE USER WANTS TO PARK AS PER THAT COST IS DIVIDED
      SCREEN 2004 - UNIQUE IDENTIFICATION SCREEN WHERE THE USER PRESSES NUMPAD TO ENTER THE VEHICLE'S NUMBER
      NUMPAD - 2009 - THE NUMPAD SCREEN WHERE THERE IS A MATRIX INPUT AVAILABLE AND INPUT IS DRAWN TO SCREEN 4
      SCREEN 200145 - ASKING FOR AN E-RECEIPT , IF THE USER DECLINES THIS , THEN THE CONFIRMATION SCREEN WILL COME AND IF THE USER ACCEPTS IT , THEN PH. NO. SCREEN WILL COME
      SCREEN 20045 - PHONE NUMBER SCREEN WHERE THE USER HAS TO ENTER PHONE NUMBER , IN ORDER TO RECEIVE AN E-RECEIPT AND IT WOULD BE STORED IN THE STRUCTURE FOR THE USER , SO AS THE USER WOULD GET AN
                  E-RECEIPT WHILE TAKING THE CAR OUT ALSO
      NUMPAD_PH - 200991 - THE NUMPAD SCREEN FOR ENTERING THE 10 DIGIT PHONE NUMBER
      SCREEN 2001111 - SENDING E-RECEIPT SCREEN AFTER THE USER HAS ENTERED ALL THE DETAILS
      SCREEN 2005 - CONFIRMATION SCREEN WHERE THE USER HAS TO PRESS FINISH IN ORDER TO KEEP VEHICLE INSIDE
      SCREEN 20021 - UNIQUE IDENTIFICATION SCREEN FOR TAKING THE VEHICLE OUT THE USER ENTERS THE VEHICLE'S NUMBER AND TAKES THE VEHICLE OUT
      NUMPAD1 - 20091 - THE NUMPAD SCREEN WHERE THERE IS A MATRIX INPUT AVAILABLE AND INPUT IS DRAWN TO SCREEN 21
      SCREEN 20022 - FINAL CONFIRMATION SCREEN WHERE THE USER PRESSES FINISH AND TAKES THE VEHICLE OUT
      SCREEN 20022_0 - 220 - THE ERROR SCREEN WHERE THE USER WILL GET WHEN ENTERED THE WRONG VEHICLE'S NUMBER OR WHICH IS NOT IN THE DATABASE
      SCREEN 20031 - IN VERY DEVELOPMENT STAGE JUST FOR DEMONSTRATION THE OTP SCREEN WHICH WILL TAKE OTP AND JUMP TO ASKING PIN SCREEN
      SCREEN 200913 - NUMPAD SCREEN FOR OTP THIS IS A SEPERATE SCREEN FOR NUMPAD FOR THE OTP SCREEN 
      SCREEN 20022_03 - 2002203 - NOT FOUND SCREEN FOR OTP IF THE ENTERED OTP DOES NOT MATCH WITH OUR RECORDS
      SCREEN 2004_0 - 20040 - THE ERROR SCREEN WHICH WILL COME IF THE USER HAS ENTERED A PIN WHICH ANOTHER USER HAS ALRADY ENTERED BEFORE

*/

/* [v2 - GSM]-----------------------------------------------------------------------------[ADD NULL WITH CONTROLLERS] - [BASE OF ALL VERSION] */
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
void screen40() {
  screen = 40 ;
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


/*[v5 - SERVER(b)]------------------------------------------------------------------------[ADD 200 WITH CONTROLLERS] - [IN VERY DEVELOPMENT STAGE]*/
void screen2001() {
  screen = 2001 ;
  setup() ;
}
void screen2002() {
  screen = 2002 ;
  setup() ;
}
void screen20023() {
  screen = 20023 ;
  setup() ;
}
void screen2003() {
  screen = 2003 ;
  setup() ;
}
void screen2004() {
  screen = 2004 ;
  setup() ;
}
void screen2005() {
  screen = 2005 ;
  setup() ;
}
void numpad200() {
  screen = 2009 ;
  setup() ;
}
void numpad2001() {
  screen = 20091 ;
  setup() ;
}
void screen20021() {
  screen = 20021 ;
  setup() ;
}
void screen20022() {
  screen = 20022 ;
  setup() ;
}
void screen20022_0() {
  screen = 200220 ;
  setup() ;
}
void screen2008341() {
  screen = 2008341 ;
  setup() ;
}
void screen200145 () {
  screen = 200145 ;
  setup() ;
}
void screen20045 () {
  screen = 20045 ;
  setup() ;
}
void ph_numpad200()  {
  screen = 200991 ;
  setup() ;
}
void screen2001111() {
  screen = 2001111 ;
  setup() ;
}
void screen20031() {
  screen = 20031 ;
  setup() ;
}
void numpad20013() {
  screen = 200913 ;
  setup() ;
}
void screen20022_03() {
  screen = 2002203 ;
  setup() ;
}
void screen20040() {
  screen = 20040 ;
  setup() ;
}

/*[v1 - MINI]---------------------------------------------------------------------------[ADD 200 WITH THE CONTROLLERS]*/
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
void screen10040() {
  screen = 10040 ;
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
  Serial.begin(230400);   /* FOR DEBUGGING PURPOSES */
  bool good = SD.begin(SD_CS);
  if (!good) {
    Serial.print(F("cannot start SD"));
    while (1);
  }
  root = SD.open(namebuf);
  pathlen = strlen(namebuf);
  root1 = SD.open(namebuf);
  pathlen1 = strlen(namebuf);

  if ( tft_first == 1 ) {
    Serial.println("FIRMWARE VERSION v5.8(b)");
    Serial.println("EPARK CORTEX S5 [ MINI / GSM / SERVER(b) ] <----------------------------------------------------------------------> [ v1 / v2 / v5 ]") ;
    Serial.println("ENTERING DEBUGGING MODE") ;
    Serial.println("PRINTING EVENTS IN THIS SERIAL MONITOR") ;
    Serial.println("ALL INITIALIZATION COMPLETE") ;
    Serial.println("PROCEDING TO DRAWING GRAPHICS") ;
    Serial.println("TINITILIZING WITH SCREEN 1 - VEHICLE PARKING MAIN MENU SCREEN FOR TAKING USER INPUT OF WANT TO KEEP VEHICLE OR TAKE OUT VEHICLE") ;
    Serial.println("FIRST TIME INITILIZATION #THIS WILL NOT BE PRINTED AGAIN#") ;
    uint16_t ID = tft.readID(); /* COMMAND TO FIND OUT THE LCD DRIVER AUTOMATICALLY */
    Serial.print("STARTING SCREEN FOR THE FIRST TIME WITH TFT ID = 0x") ;

    Serial.print(ID, HEX);
    Serial.println("") ;
    tft.begin(ID);
    tft.setRotation(0);            /* PORTRAIT */

    tft_firstscreen = -1 ;

    tft_first = -1 ;
    Serial.println("FIRST INITILIZATION DONE") ;
  }
  Serial.println("SETUP------->-------->") ;

  pinMode(buttonPin, INPUT);

  /*----BUTTON LOGIC-----*/

  /*   HERE THE MAIN TRICK LIES OF HOW TO SETUP ALL BUTTONS WITHOUT WRITING ALL THEM IN ONE PLACE
       THE VALUES MENTIONED IN THE PREVIOUS COMMENT SIMPLY REPRESENT THE VALUES OF DIFFERENT SCREEN
       AND THE SCREEN THATS NEEDED THAT VALUE IS JUST SET IN THE FUNCTIONS FOR THAT SCREENS AND THE
       SETUP FUNCTION IS CALLED SO THAT THE PARTICULAR SECTION OF THE SETUP AND LOOP ONLY GETS EXECUTED
  */


/* [v2 - GSM]-----------------------------------------------------------------------------[ADD NULL WITH CONTROLLERS] - [BASE OF ALL VERSION] */
  if ( screen == 1111 ) {

    Serial.println("NOW ENTERING SETUP OF SCREEN 1111 - SENDING E-RECEIPT SCREEN AFTER THE USER HAS ENTERED ALL THE DETAILS") ;
    Serial.println("THIS SCREEN HAS NO LOOP PART, SO THIS WILL JUMP TO ANOTHER SETUP OF SCREEN") ;

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
    Serial6.println("EPARK CORTEX S5") ;
    Serial6.println("VEHICLE ENTRY") ;
    Serial6.println("") ;
    Serial6.print("PIN : ") ;
    Serial6.print(c[i][counter[i]].number[0]);
    Serial6.print(c[i][counter[i]].number[1]);
    Serial6.print(c[i][counter[i]].number[2]);
    Serial6.print(c[i][counter[i]].number[3]);
    Serial6.print(c[i][counter[i]].number[4]);
    Serial6.print(c[i][counter[i]].number[5]);
    Serial6.print(c[i][counter[i]].number[6]);

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
    Serial.println("DUMPING DATA WHICH WILL BE GOING TO SERIAL6 GSM") ;
    Serial.println("AT+CMGF=1") ;
    Serial.print("AT+CMGS=\"+91") ;
    Serial.print(c[i][counter[i]].ph_number[0]) ;
    Serial.print(c[i][counter[i]].ph_number[1]) ;
    Serial.print(c[i][counter[i]].ph_number[2]) ;
    Serial.print(c[i][counter[i]].ph_number[3]) ;
    Serial.print(c[i][counter[i]].ph_number[4]) ;
    Serial.print(c[i][counter[i]].ph_number[5]) ;
    Serial.print(c[i][counter[i]].ph_number[6]) ;
    Serial.print(c[i][counter[i]].ph_number[7]) ;
    Serial.print(c[i][counter[i]].ph_number[8]) ;
    Serial.print(c[i][counter[i]].ph_number[9]) ;
    Serial.print("\"\r") ;
    Serial.println() ;
    Serial.println("--- SERIAL-RECEIPT ---") ;
    Serial.println("") ;
    Serial.println("EPARK CORTEX S5") ;
    Serial.println("VEHICLE ENTRY") ;
    Serial.println("") ;
    Serial.print("PIN : ") ;
    Serial.print(c[i][counter[i]].number[0]);
    Serial.print(c[i][counter[i]].number[1]);
    Serial.print(c[i][counter[i]].number[2]);
    Serial.print(c[i][counter[i]].number[3]);
    Serial.print(c[i][counter[i]].number[4]);
    Serial.print(c[i][counter[i]].number[5]);
    Serial.print(c[i][counter[i]].number[6]);
    Serial.println("") ;
    Serial.print("FLOOR : ") ;
    if ( c[i][counter[i]].slot == 0 )
      Serial.print("GROUND FLOOR") ;
    else if ( c[i][counter[i]].slot == 1 )
      Serial.print("1st FLOOR") ;
    else if ( c[i][counter[i]].slot == 2 )
      Serial.print("2nd FLOOR") ;
    else if ( c[i][counter[i]].slot == 3 )
      Serial.print("3rd FLOOR") ;
    Serial.println("") ;
    Serial.print("TYPE : ") ;
    if ( c[i][counter[i]].type == 1 )
      Serial.print("BIKE") ;
    else if ( c[i][counter[i]].type == 2 )
      Serial.print("CAR") ;
    Serial.println("");
    Serial.print("ENTRY TIME : ");
    DS3231_get(&t); //get the value and pass to the function the pointer to t, that make an lower memory fingerprint and faster execution than use return
    Serial.print(t.hour);
    Serial.print(":");
    Serial.print(t.min) ;
    Serial.print(":");
    Serial.print(t.sec);
    Serial.println("") ;
    Serial.print("DATE : ") ;
    Serial.print(t.mday) ;
    Serial.print("/");
    Serial.print(t.mon) ;
    Serial.print("/");
    Serial.print((t.year + 100));
    Serial.println("");
    Serial.println((char)26);

    Serial.println("SENDING DATA TO GSM VIA SERIAL6") ;
    Serial.println("DATA SUCCESSFULLY SENT TO GSM VIA SERIAL6");
    Serial.println("JOB OF SCREEN1111 IS DONE, LEAVING SCREEN1111 AND JUMPING TO SCREEN 5 - CONFIRMATION SCREEN WHERE THE USER HAS TO PRESS FINISH IN ORDER TO KEEP VEHICLE INSIDE") ;
    screen5() ;
  }

  if ( screen == 145 ) {
    Serial.println("SETUP OF SCREEN 145") ;
    Serial.println("NOW ENTERING SCREEN 145 - ASKING FOR AN E-RECEIPT , IF THE USER DECLINES THIS , THEN THE CONFIRMATION SCREEN WILL COME AND IF THE USER ACCEPTS IT , THEN PH. NO. SCREEN WILL COME") ;

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

    Serial.println("SETUP DONE, MOVING TO LOOP FOR SCREEN 145") ;
  }

  if ( screen == 8341 ) {

    Serial.println("NOW ENTERING SETUP OF SCREEN 8341") ;
    Serial.println("SCREEN 8341 - SENDING MESSAGE STATUS WHILE THE MESSAGE IS BEING SENT TO THE OWNER OF THE PARKING LOT");
    Serial.println("THIS SCREEN HAS NO SETUP SO IT WILL JUMP INTO A SETUP OF ANOTHER SCREEN DIRECTLY") ;

    tft.fillScreen(BLACK);

    showmsgXY(1, 50 + 100, 3, &FreeSans9pt7b, "  SENDING");
    showmsgXY(15, 50 + 100, 3, &FreeSans9pt7b, "\n  MESSAGE");
    showmsgXY(15, 50 + 65 + 100, 2, &FreeSans9pt7b, "\n      Please Wait");
    showmsgXYM(15, 50 + 65 + 60 + 100, 1, &FreeSans9pt7b, "\nSending Message to : +91-8967068772");

    Serial.println("DUMPING DATA WHICH WILL BE GOING TO SERIAL6 GSM") ;
    Serial.println("AT+CMGF=1");

    Serial.println("AT+CMGS=\"+918967068772\"\r");
    DS3231_get(&t); //get the value and pass to the function the pointer to t, that make an lower memory fingerprint and faster execution than use return
    Serial.print(t.hour);
    Serial.print(":");
    Serial.print(t.min) ;
    Serial.print(":");
    Serial.print(t.sec);
    Serial.println("") ;
    Serial.print("DATE : ") ;
    Serial.print(t.mday) ;
    Serial.print("/");
    Serial.print(t.mon) ;
    Serial.print("/");
    Serial.print((t.year + 100));
    Serial.println("");
    Serial.print("CARS WENT OUT OF PARKING SPACE : ");
    Serial.print(C_OUT) ;
    Serial.println("");
    Serial.print("TOTAL AMOUNT COLLECTED : ");
    Serial.print(COST) ;
    Serial.println("");
    Serial.print("CARS STILL IN PARKING SPACE : ");
    Serial.print(C_IN) ;
    Serial.println("");

    Serial.println("SENDING DATA TO GSM VIA SERIAL6") ;
    delay(1000);
    Serial6.println("AT+CMGF=1");
    delay(1000);
    Serial6.println("AT+CMGS=\"+918967068772\"\r");
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
    Serial.println("DATA SUCCESSFULLY SENT TO GSM VIA SERIAL6");
    Serial.println("JOB OF SCREEN1111 IS DONE, LEAVING SCREEN8341 AND JUMPING TO SETUP FUNCTION AS THIS IS NOT CONNECTED TO ANYTHING") ;
    setup() ;
  }

  if ( screen == 1 ) {
    /* I2C COMMUNICATION WITH ESP8266 BEGINS WITH 8 AND STM32 AS A SLAVE ONLY THIS SCREEN WILL FETCH THE DATA AND SEND DATA
        FOR NOW V5.3 ONLY SENDING OF DATA IS NECESSARY AND RECEIVING AND PARSING OF DATA WILL BE DONE IN LATER VERSIONS
        REQESTEVENT IS THE REQUEST FROM THE MASTER AND RECEIVEEVENT IS FOR THE SLAVE THAT RECEIVED THE DATA THAT IS STM32
    */
    Wire.begin(8);
    Wire.onReceive(receiveEvent);
    Wire.onRequest(requestEvent);


    tft.fillScreen(BLACK);
    Serial.println("NOW ENTERING SETUP OF SCREEN 1");
    Serial.println("SCREEN 1 - VEHICLE PARKING MAIN MENU SCREEN FOR TAKING USER INPUT OF WANT TO KEEP VEHICLE OR TAKE OUT VEHICLE") ;
    Serial.println("THIS IS THE SCREEN 1 FOR GSM VERSION") ;

    showmsgXYM(1 + 9, 50 + 15, 5, &FreeSans9pt7b, "EPARK");
    showmsgXY(15 + 12, 115, 3, &FreeSans9pt7b, "Cortex  S5");
    showmsgXYG(15 + 95, 148 + 10, 2, &FreeSans9pt7b, "GSM");
    showmsgXYG(12, 162 + 10, 2, NULL, "SIM900A [900/1800 MHz] 2G");
    tft.setFont(NULL);
    one.initButton(&tft,  60, 150 + 100 + 55, 100, 50, MAGENTA, MAGENTA, BLACK, "1", 3);
    two.initButton(&tft,  60, 150 + 100 + 55 + 75, 100, 50, AZURE, AZURE, BLACK, "2", 3);
    Ok.initButton(&tft,  280 + 5, 460 + 5, 80, 30, BLACK, BLACK , BLACK, "", 2);
    Back.initButton(&tft,  280 + 5, 420 + 5, 80, 30, BLACK, BLACK , BLACK, "", 2);

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
    Ok.drawButton(false);
    Back.drawButton(false);
    Serial.println("GRAPHICS, VARIABLES INITIALIZED JUMPING TO SCREEN 1 LOOP") ;

  }

  if ( screen == 2 ) {
    /* I2C COMMUNICATION WITH ESP8266 BEGINS WITH 8 AND STM32 AS A SLAVE ONLY THIS SCREEN WILL FETCH THE DATA AND SEND DATA
        FOR NOW V5.3 ONLY SENDING OF DATA IS NECESSARY AND RECEIVING AND PARSING OF DATA WILL BE DONE IN LATER VERSIONS
        REQESTEVENT IS THE REQUEST FROM THE MASTER AND RECEIVEEVENT IS FOR THE SLAVE THAT RECEIVED THE DATA THAT IS STM32
    */
    Wire.begin(8);
    Wire.onReceive(receiveEvent);
    Wire.onRequest(requestEvent);

    tft.fillScreen(BLACK);
    Serial.println("NOW ENTRING SETUP OF SCREEN 2");
    Serial.println("SCREEN 2 - AVAILABLE SLOTS SCREEN WHERE THE AVAILABLE SLOTS ARE SHOWN IF ANY") ;

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
    showmsgXY(10 + 60 + 15, 110 + 13, 1, &FreeSans9pt7b, "Ground Floor \n                 For parking time :\n                 less than 3 hours") ;
    showmsgXY(10 + 60 + 15, 110 + 60 + 20 + 13, 1, &FreeSans9pt7b, "1st Floor \n                 For parking time :\n                 more than 3 hours") ;
    showmsgXY(10 + 60 + 15,  110 + 60 + 20 + 60 + 20 + 13, 1, &FreeSans9pt7b, "2nd Floor \n                 For parking time :\n                 more than 6 hours") ;
    showmsgXY(10 + 60 + 15,  110 + 60 + 20 + 60 + 20 + 60 + 20 + 13, 1, &FreeSans9pt7b, "3rd Floor \n                 For parking time :\n                 more than 10 hours") ;

    Serial.println("GRAPHICS DRAWING DONE JUMPING TO LOOP FOR SCREEN 2") ;

  }

  if ( screen == 23 ) {


    tft.fillScreen(BLACK);
    Serial.println("NOW ENTERING SETUP OF SCREEN 23") ;
    Serial.println("SCREEN 23 - FOR SELECTING THE TYPE OF VEHILCE WHICH THE USER WANTS TO PARK AS PER THAT COST IS DIVIDED") ;

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
    Serial.println("SETUP DONE NOW MOVING TO LOOP OF SCREEN 23") ;
  }

  if ( screen == 3 ) {
    tft.fillScreen(BLACK);
    Serial.println("NOW ENTERING SCREEN 3") ;
    Serial.println("SCREEN 3 - SLOT SELECTION SCREEN WHERE THE SLOT WHICH IS TO BE KEPT IS TAKEN FROM THE USER") ;

    showmsgXY(40, 30, 2, &FreeSans9pt7b, "Slot Selection");
    showmsgXYM(1, 55, 1, &FreeSans9pt7b, "These Slots are just for keeping the      space sorted , you have to pay as per      time kept !") ;
    tft.setFont(NULL);

    if ( counter[0] != 5 ) {
      showmsgXY(98, 133, 1, &FreeSans9pt7b, "Ground Floor \n                    For parking time :\n                    less than 3 hours") ;
      One.initButton(&tft,  50, 150, 75, 50, GREEN, GREEN, WHITE, "1", 3);
    }

    else if ( counter[0] == 5 ) {
      One.initButton(&tft,  50, 150, 75, 50, RED, RED, BLACK, "1", 3);
      showmsgXYGR(98, 133, 1, &FreeSans9pt7b, "Ground Floor \n                    For parking time :\n                    less than 3 hours") ;
    }

    if ( counter[1] != 5 ) {
      Two.initButton(&tft,  50, 150 + 50 + 30, 75, 50, GREEN, GREEN, WHITE, "2", 3);
      showmsgXY(98, 133 + 80, 1, &FreeSans9pt7b, "1st Floor \n                    For parking time :\n                    more than 3 hours") ;
    }

    else if ( counter[1] == 5 ) {
      Two.initButton(&tft,  50, 150 + 50 + 30, 75, 50, RED, RED, BLACK, "2", 3);
      showmsgXYGR(98, 133 + 80, 1, &FreeSans9pt7b, "1st Floor \n                    For parking time :\n                    more than 3 hours") ;
    }

    if ( counter[2] != 5 ) {
      showmsgXY(98, 133 + 80 + 80, 1, &FreeSans9pt7b, "2nd Floor \n                    For parking time :\n                    more than 6 hours") ;
      Three.initButton(&tft, 50, 150 + 50 + 30 + 50 + 30, 75, 50, GREEN, GREEN, WHITE, "3", 3);
    }

    else if ( counter[2] == 5 ) {
      Three.initButton(&tft, 50, 150 + 50 + 30 + 50 + 30, 75, 50, RED, RED, BLACK, "3", 3);
      showmsgXYGR(98, 133 + 80 + 80, 1, &FreeSans9pt7b, "2nd Floor \n                    For parking time :\n                    more than 6 hours") ;
    }

    if ( counter[3] != 5 ) {
      showmsgXY(98, 133 + 80 + 80 + 80, 1, &FreeSans9pt7b, "3rd Floor \n                    For parking time :\n                    more than 10 hours") ;
      Four.initButton(&tft,  50, 150 + 50 + 30 + 50 + 30 + 50 + 30, 75, 50, GREEN, GREEN, WHITE, "4", 3);
    }

    else if ( counter[3] == 5 ) {
      Four.initButton(&tft,  50, 150 + 50 + 30 + 50 + 30 + 50 + 30, 75, 50, RED, RED, BLACK, "4", 3);
      showmsgXYGR(98, 133 + 80 + 80 + 80, 1, &FreeSans9pt7b, "3rd Floor \n                    For parking time :\n                    more than 10 hours") ;
    }

    Ok.initButton(&tft,  280 + 5, 460 + 5, 80, 30, ILI9481_GREEN, ILI9481_GREEN , WHITE, "Ok", 2);
    Back.initButton(&tft,  41 - 7, 460 + 5, 80, 30, ILI9481_RED, ILI9481_RED, BLACK, "Back", 2);

    if (!( counter[0] == 5 && counter[1] == 5 && counter[2] == 5 && counter[3] == 5 ))
      Ok.drawButton(false);

    Back.drawButton(false);


    One.drawButton(false);



    Two.drawButton(false);



    Three.drawButton(false);



    Four.drawButton(false);


    Serial.println("SETTING DONE NOW MOVING TO LOOP FOR SCREEN 3") ;
  }

  if ( screen == 4 ) {


    tft.fillScreen(BLACK);

    Serial.println("NOW ENTERING SCREEN 4") ;
    Serial.println("SCREEN 4 - UNIQUE IDENTIFICATION SCREEN WHERE THE USER PRESSES NUMPAD TO ENTER THE VEHICLE'S NUMBER");
    showmsgXY(75, 40, 2, &FreeSans12pt7b, "Unique \n  Identification");
    tft.setFont(NULL);
    Ok.initButton(&tft,  260, 460, 150, 40, ILI9481_GREEN, ILI9481_GREEN , WHITE, "Confirm", 2);
    Back.initButton(&tft,  41 - 7, 460 + 5, 80, 30, ILI9481_RED, ILI9481_RED, BLACK, "Back", 2);

    E.initButton(&tft,  160 , 210 + 20, 110, 50, MAGENTA, MAGENTA, BLACK, "Numpad", 2);


    Back.drawButton(false);
    E.drawButton(false);
    Serial.println("THE CONFIRM BUTTON WILL NOT BE DRAWN RIGHT NOW") ;
    /* -- showmsgXYM(1, 133, 1, &FreeSans9pt7b, "Enter your Vehicle's Registration no.     (from number plate) for our records") ; -- */
    showmsgXYM(1, 133, 1, &FreeSans9pt7b, "Enter 7 digit PIN to make it unique , it \nshould consist of last 4 digits of your \nvehicle number & 3 secret digits of your choice") ;
    /*  EXECUTE THESE STATEMENTS AFTER RETURNING FROM NUMPAD SCREEN */
    if ( n == 1 ) {
      Serial.println("USER HAS ENTERED PROPER DIGITS FOR PIN");
      Serial.println("DRAW THE CONFIRM BUTTON") ;
      showmsgXY(50 + 8, 260 + 20 + 16, 2 , NULL , textfield) ;
      tft.drawRect(50, 260 + 20, 220, 50, ILI9481_DARKGREY );
      showmsgXY(17, 400, 1, &FreeSans9pt7b, "Press Confirm to continue");

      Ok.drawButton(false);
    }
    Serial.println("DONE NOW MOVING TO LOOP FOR SCREEN 4") ;
  }

  if ( screen == 45 ) {

    tft.fillScreen(BLACK);
    Serial.println("NOW ENTERING SETUP FOR SCREEN 45") ;
    Serial.println("SCREEN 45 - PHONE NUMBER SCREEN WHERE THE USER HAS TO ENTER PHONE NUMBER , IN ORDER TO RECEIVE AN E-RECEIPT AND IT WOULD BE STORED IN THE STRUCTURE FOR THE USER , SO AS THE USER WOULD GET AN E-RECEIPT WHILE TAKING THE CAR OUT ALSO");


    showmsgXY(75, 40, 2, &FreeSans12pt7b, "Phone  \n     Number");
    tft.setFont(NULL);


    Ok.initButton(&tft,  260, 460, 150, 40, ILI9481_GREEN, ILI9481_GREEN , WHITE, "Confirm", 2);
    Back.initButton(&tft,  41 - 7, 460 + 5, 80, 30, ILI9481_RED, ILI9481_RED, BLACK, "Back", 2);

    E.initButton(&tft,  160 , 210 + 20, 110, 50, MAGENTA, MAGENTA, BLACK, "Numpad", 2);

    Back.drawButton(false);
    E.drawButton(false);
    Serial.println("DON'T DRAW THE CONFIRM BUTTON NOW") ;

    /* -- showmsgXYM(1, 133, 1, &FreeSans9pt7b, "Enter your Vehicle's Registration no.     (from number plate) for our records") ; -- */
    showmsgXYM(1, 133, 1, &FreeSans9pt7b, "Enter your 10 DIGIT phone number \nwhich you have right now") ;
    /*  EXECUTE THESE STATEMENTS AFTER RETURNING FROM NUMPAD SCREEN */
    if ( ph_n == 1 ) {
      Serial.println("DRAW THE CONFIRM BUTTON BECAUSE THE USER HAS ENTERED THE CORRECT NO. OF DIGITS") ;
      showmsgXY(50 + 8, 260 + 14, 2 , NULL , ph_textfield) ;
      tft.drawRect(50, 260, 220, 50, ILI9481_DARKGREY );
      showmsgXY(17, 400, 1, &FreeSans9pt7b, "Press Confirm to keep your vehicle");

      Ok.drawButton(false);
    }
    Serial.println("DONE NOW MOVING TO LOOP FOR SCREEN 45") ;
  }

  if ( screen == 5 ) {

    tft.fillScreen(BLACK);
    if ( c[i][counter[i]].yes == 9 )
      C_IN = C_IN  + 1;

    showmsgXYM(1, 50, 3, &FreeSans9pt7b, "Successful");
    showmsgXY(1, 95, 1, &FreeSans9pt7b, "You can now just keep your vehicle at \nthe prefered floor as per your choice of no. of hours , at the time of exit just \nchoose the option 2 and enter vehicle's number again , pay and take your \nVehicle back , now press Finish Button") ;
    showmsgXY(65, 400, 2, &FreeSans9pt7b, "Thank You !") ;
    tft.setFont(NULL);

    Finish.initButton(&tft,  160 , 300, 150, 50, MAGENTA, MAGENTA, BLACK, "Finish", 3);
    Finish.drawButton(false);
    Serial.println("DONE SETUP FOR KEEPING A VEHICLE") ;
    Serial.println("NOW MOVING TO LOOP FOR SCREEN 5 WHICH DOES NOT HAS MANY SUCH THINGS AND HENCE WILL SET SCREEN 1 AND CALL SETUP EVENTUALLY") ;
  }

  if ( screen == 9 ) {


    Serial.println("NOW ENTERING THE SETUP FOR NUMPAD SCREEN 9") ;
    Serial.println("NUMPAD - 9 - THE NUMPAD SCREEN WHERE THERE IS A MATRIX INPUT AVAILABLE AND INPUT IS DRAWN TO SCREEN 4") ;

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
    Serial.println("NOW MOVING TO SETUP FOR SCREEN 991 WHICH IS ANOTHER NUMPAD") ;
    Serial.println("NUMPAD_PH - 991 - THE NUMPAD SCREEN FOR ENTERING THE 10 DIGIT PHONE NUMBER") ;
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
    Serial.println("SETUP DONE NOW MOVING TO LOOP FOR SCREEN 991") ;
  }

  if ( screen == 91 ) {


    tft.fillScreen(BLACK);
    Serial.println("NOW MOVING TO SETUP FOR SCREEN 91 WHICH IS ANOTHER NUMPAD") ;
    Serial.println(" NUMPAD1 - 91 - THE NUMPAD SCREEN WHERE THERE IS A MATRIX INPUT AVAILABLE AND INPUT IS DRAWN TO SCREEN 21") ;
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
    Serial.println("SETUP DONE NOW MOVING TO LOOP FOR SCREEN 91") ;
  }

  if ( screen == 21) {
    tft.fillScreen(BLACK);
    Serial.println("NOW ENTERING SCREEN 21") ;
    Serial.println("SCREEN 21 - UNIQUE IDENTIFICATION SCREEN FOR TAKING THE VEHICLE OUT THE USER ENTERS THE VEHICLE'S NUMBER AND TAKES THE VEHICLE OUT") ;

    showmsgXY(75, 40, 2, &FreeSans12pt7b, "Unique \n  Identification");
    tft.setFont(NULL);

    Ok.initButton(&tft,  260, 460, 150, 40, ILI9481_GREEN, ILI9481_GREEN , WHITE, "Confirm", 2);
    Back.initButton(&tft,  41 - 7, 460 + 5, 80, 30, ILI9481_RED, ILI9481_RED, BLACK, "Back", 2);

    E.initButton(&tft,  160 , 210 + 20, 110, 50, MAGENTA, MAGENTA, BLACK, "Numpad", 2);

    Back.drawButton(false);
    E.drawButton(false);
    Serial.println("DON'T DRAW THE CONFIRM BUTTON AS THE LOGIC IS NOT SATISFIED") ;
    /* -- showmsgXYM(1, 133, 1, &FreeSans9pt7b, "Enter your Vehicle's Registration no.     (from number plate) to take your Vehicle out") ; -- */
    showmsgXYM(1, 133, 1, &FreeSans9pt7b, "Enter the 7-digit PIN, to take your \nvehicle out") ;

    /*  EXECUTE THESE STATEMENTS AFTER RETURNING FROM NUMPAD SCREEN */
    if ( nr == 1 ) {
      Serial.println("NOW DRAW THE CONFIRM BUTTON AS THE USER HAS ENTERED THE CORRECT NO. OF DIGITS") ;
      showmsgXY(50 + 8, 260 + 14, 2 , NULL , textfieldr) ;
      tft.drawRect(50, 260, 220, 50, ILI9481_DARKGREY );
      showmsgXY(5, 400, 1, &FreeSans9pt7b, "Press Confirm to take out your Vehicle");
      Ok.drawButton(false);
    }
    Serial.println("SETUP DONE NOW MOVING TO LOOP FOR SCREEN 21") ;
  }

  if ( screen == 22) {
    tft.fillScreen(BLACK);
    Serial.println("NOW ENTERING SCREEN 22") ;
    Serial.println("SCREEN 22 - FINAL CONFIRMATION SCREEN WHERE THE USER PRESSES FINISH AND TAKES THE VEHICLE OUT") ;

    DS3231_get(&t); //get the value and pass to the function the pointer to t, that make an lower memory fingerprint and faster execution than use return
    timeTemp = ((t.unixtime + 3154000000) % 10000) ;
    showmsgXYM(1, 50, 3, &FreeSans9pt7b, "Successful");
    showmsgXY(1, 95, 1, &FreeSans9pt7b, "You can now just take your Vehicle out by paying the correct amount and press \nthe Finish button") ;
    showmsgXY(65, 190, 2, &FreeSans9pt7b, "Thank You !") ;
    C_OUT = C_OUT + 1 ;
    C_IN = C_IN - 1 ;
    tft.setFont(NULL);

    /*  EXECUTE THESE STATEMENTS AFTER SUCCESSFUL SEARCH  */
    Serial.println("EXECUTE THESE STATEMENTS AFTER SUCCESSFUL SEARCH") ;

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
    c[i_temp][j_temp].number[0] = '$' ;
    c[i_temp][j_temp].number[1] = '$' ;
    c[i_temp][j_temp].number[2] = '$' ;
    c[i_temp][j_temp].number[3] = '$' ;
    c[i_temp][j_temp].number[4] = '$' ;
    c[i_temp][j_temp].number[5] = '$' ;
    c[i_temp][j_temp].number[6] = '$' ;
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
    Serial.println("--- SERIAL-RECEIPT ---") ;
    Serial.println("") ;
    Serial.println("EPARK CORTEX S5") ;
    Serial.println("VEHICLE EXIT") ;
    Serial.println("") ;
    Serial.print("TIME KEPT : ") ;
    Serial.print(T1) ;
    Serial.println("") ;
    Serial.print("AMOUNT TO BE PAID : ") ;
    if ( c[i_temp][j_temp].type == 1 )
      Serial.print("Rs. 25") ;
    else if ( c[i_temp][j_temp].type == 2 )
      Serial.print("Rs. 30") ;
    Serial.println("");

    Serial.print("EXIT TIME : ");
    DS3231_get(&t); //get the value and pass to the function the pointer to t, that make an lower memory fingerprint and faster execution than use return
    Serial.print(t.hour);
    Serial.print(":");
    Serial.print(t.min) ;
    Serial.print(":");
    Serial.print(t.sec);
    Serial.println("") ;
    Serial.print("DATE : ") ;
    Serial.print(t.mday) ;
    Serial.print("/");
    Serial.print(t.mon) ;
    Serial.print("/");
    Serial.print((t.year + 100));
    Serial.println("");

    Serial.println((char)26);
    if (c[i_temp][j_temp].yes == 1 ) {
      Serial.println("THE USER HAS ENTERED A PHONE NUMBER") ;
      Serial.println("SO DUMPING THE DATA TO BE GOING TO GSM VIA SERIAL6") ;
      Serial.println("AT+CMGF=1") ;
      Serial.print("AT+CMGS=\"+91") ;
      Serial.print(c[i_temp][j_temp].ph_number[0]) ;
      Serial.print(c[i_temp][j_temp].ph_number[1]) ;
      Serial.print(c[i_temp][j_temp].ph_number[2]) ;
      Serial.print(c[i_temp][j_temp].ph_number[3]) ;
      Serial.print(c[i_temp][j_temp].ph_number[4]) ;
      Serial.print(c[i_temp][j_temp].ph_number[5]) ;
      Serial.print(c[i_temp][j_temp].ph_number[6]) ;
      Serial.print(c[i_temp][j_temp].ph_number[7]) ;
      Serial.print(c[i_temp][j_temp].ph_number[8]) ;
      Serial.print(c[i_temp][j_temp].ph_number[9]) ;
      Serial.print("\"\r") ;
      Serial.println() ;

      Serial.println("--- E-RECEIPT ---") ;
      Serial.println("") ;
      Serial.println("EPARK CORTEX S5") ;
      Serial.println("VEHICLE EXIT") ;
      Serial.println("") ;
      Serial.print("TIME KEPT : ") ;
      Serial.print(T1) ;
      Serial.println("") ;
      Serial.print("AMOUNT TO BE PAID : ") ;
      if ( c[i_temp][j_temp].type == 1 )
        Serial.print("Rs. 25") ;
      else if ( c[i_temp][j_temp].type == 2 )
        Serial.print("Rs. 30") ;
      Serial.println("");

      Serial.print("EXIT TIME : ");
      DS3231_get(&t); //get the value and pass to the function the pointer to t, that make an lower memory fingerprint and faster execution than use return
      Serial.print(t.hour);
      Serial.print(":");
      Serial.print(t.min) ;
      Serial.print(":");
      Serial.print(t.sec);
      Serial.println("") ;
      Serial.print("DATE : ") ;
      Serial.print(t.mday) ;
      Serial.print("/");
      Serial.print(t.mon) ;
      Serial.print("/");
      Serial.print((t.year + 100));
      Serial.println("");

      Serial.println((char)26);

      Serial.println("DUMPING OF SERIAL6 DONE NOW MOVING THE DATA TO SERIAL6");
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
      Serial6.println("EPARK CORTEX S5") ;
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
      Serial.println("SENDING OF DATA TO GSM DONE VIA SERIAL6");
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

    Serial.println("RESETTING VARIABLES AND MOVING TO LOOP FOR SCREEN 21 WHICH WILL RESET AND CALL SETUP AGAINST SCREEN 1");
    /* I2C COMMUNICATION WITH ESP8266 BEGINS WITH 8 AND STM32 AS A SLAVE ONLY THIS SCREEN WILL FETCH THE DATA AND SEND DATA
        FOR NOW V5.3 ONLY SENDING OF DATA IS NECESSARY AND RECEIVING AND PARSING OF DATA WILL BE DONE IN LATER VERSIONS
        REQESTEVENT IS THE REQUEST FROM THE MASTER AND RECEIVEEVENT IS FOR THE SLAVE THAT RECEIVED THE DATA THAT IS STM32
    */

  }

  if ( screen == 220) {
    Serial.println("NOW ENTERING THE SCREEN 220");
    Serial.println("SCREEN 22_0 - 220 - THE ERROR SCREEN WHERE THE USER WILL GET WHEN ENTERED THE WRONG VEHICLE'S NUMBER OR WHICH IS NOT IN THE DATABASE");
    tft.fillScreen(BLACK);
    showmsgXY(1, 100, 2, &FreeSans9pt7b, "The number you \nentered does not \nmatch our records \nplease go back and \nenter the correct \nnumber") ;
    tft.setFont(NULL);
    Back.initButton(&tft,  41 - 7, 460 + 5, 80, 30, ILI9481_RED, ILI9481_RED, BLACK, "Back", 2);
    Back.drawButton(false);
    nr = 0 ;

  }

  if ( screen == 40) {
    Serial.println("NOW ENTERING THE SCREEN 40");
    Serial.println("SCREEN 4_0 - 40 - THE ERROR SCREEN WHERE THE USER WILL GET WHEN ENTERED THE SAME PIN");
    tft.fillScreen(BLACK);
    showmsgXY(1, 100, 2, &FreeSans9pt7b, "The number you \nentered cannot be \nused as PIN for you please go back and enter different \nnumber again") ;
    tft.setFont(NULL);
    Back.initButton(&tft,  41 - 7, 460 + 5, 80, 30, ILI9481_RED, ILI9481_RED, BLACK, "Back", 2);
    Back.drawButton(false);
    Serial.println("SETUP DONE NOW MOVING TO LOOP AND FURTHER LOOP") ;
    found_pin = -1;



  }



/*[v5 - SERVER(b)]------------------------------------------------------------------------[ADD 200 WITH CONTROLLERS] - [IN VERY DEVELOPMENT STAGE]*/
  if ( screen == 2001111 ) {

    Serial.println("NOW ENTERING SETUP OF SCREEN 1111 - SENDING E-RECEIPT SCREEN AFTER THE USER HAS ENTERED ALL THE DETAILS") ;
    Serial.println("THIS SCREEN HAS NO LOOP PART, SO THIS WILL JUMP TO ANOTHER SETUP OF SCREEN") ;

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
    Serial6.println("EPARK CORTEX S5") ;
    Serial6.println("VEHICLE ENTRY") ;
    Serial6.println("") ;
    Serial6.print("PIN : ") ;
    Serial6.print(c[i][counter[i]].number[0]);
    Serial6.print(c[i][counter[i]].number[1]);
    Serial6.print(c[i][counter[i]].number[2]);
    Serial6.print(c[i][counter[i]].number[3]);
    Serial6.print(c[i][counter[i]].number[4]);
    Serial6.print(c[i][counter[i]].number[5]);
    Serial6.print(c[i][counter[i]].number[6]);
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
    Serial.println("DUMPING DATA WHICH WILL BE GOING TO SERIAL6 GSM") ;
    Serial.println("AT+CMGF=1") ;
    Serial.print("AT+CMGS=\"+91") ;
    Serial.print(c[i][counter[i]].ph_number[0]) ;
    Serial.print(c[i][counter[i]].ph_number[1]) ;
    Serial.print(c[i][counter[i]].ph_number[2]) ;
    Serial.print(c[i][counter[i]].ph_number[3]) ;
    Serial.print(c[i][counter[i]].ph_number[4]) ;
    Serial.print(c[i][counter[i]].ph_number[5]) ;
    Serial.print(c[i][counter[i]].ph_number[6]) ;
    Serial.print(c[i][counter[i]].ph_number[7]) ;
    Serial.print(c[i][counter[i]].ph_number[8]) ;
    Serial.print(c[i][counter[i]].ph_number[9]) ;
    Serial.print("\"\r") ;
    Serial.println() ;
    Serial.println("--- E-RECEIPT ---") ;
    Serial.println("") ;
    Serial.println("EPARK CORTEX S5") ;
    Serial.println("VEHICLE ENTRY") ;
    Serial.println("") ;
    Serial.print("PIN : ") ;
    Serial.print(c[i][counter[i]].number[0]);
    Serial.print(c[i][counter[i]].number[1]);
    Serial.print(c[i][counter[i]].number[2]);
    Serial.print(c[i][counter[i]].number[3]);
    Serial.print(c[i][counter[i]].number[4]);
    Serial.print(c[i][counter[i]].number[5]);
    Serial.print(c[i][counter[i]].number[6]);

    Serial.println("") ;
    Serial.print("FLOOR : ") ;
    if ( c[i][counter[i]].slot == 0 )
      Serial.print("GROUND FLOOR") ;
    else if ( c[i][counter[i]].slot == 1 )
      Serial.print("1st FLOOR") ;
    else if ( c[i][counter[i]].slot == 2 )
      Serial.print("2nd FLOOR") ;
    else if ( c[i][counter[i]].slot == 3 )
      Serial.print("3rd FLOOR") ;
    Serial.println("") ;
    Serial.print("TYPE : ") ;
    if ( c[i][counter[i]].type == 1 )
      Serial.print("BIKE") ;
    else if ( c[i][counter[i]].type == 2 )
      Serial.print("CAR") ;
    Serial.println("");
    Serial.print("ENTRY TIME : ");
    DS3231_get(&t); //get the value and pass to the function the pointer to t, that make an lower memory fingerprint and faster execution than use return
    Serial.print(t.hour);
    Serial.print(":");
    Serial.print(t.min) ;
    Serial.print(":");
    Serial.print(t.sec);
    Serial.println("") ;
    Serial.print("DATE : ") ;
    Serial.print(t.mday) ;
    Serial.print("/");
    Serial.print(t.mon) ;
    Serial.print("/");
    Serial.print((t.year + 100));
    Serial.println("");
    Serial.println((char)26);

    Serial.println("SENDING DATA TO GSM VIA SERIAL6") ;

    Serial.println("DATA SUCCESSFULLY SENT TO GSM VIA SERIAL6");
    Serial.println("JOB OF SCREEN1111 IS DONE, LEAVING SCREEN1111 AND JUMPING TO SCREEN 5 - CONFIRMATION SCREEN WHERE THE USER HAS TO PRESS FINISH IN ORDER TO KEEP VEHICLE INSIDE") ;
    screen2005() ;
  }

  if ( screen == 200145 ) {
    Serial.println("SETUP OF SCREEN 145") ;
    Serial.println("NOW ENTERING SCREEN 145 - ASKING FOR AN E-RECEIPT , IF THE USER DECLINES THIS , THEN THE CONFIRMATION SCREEN WILL COME AND IF THE USER ACCEPTS IT , THEN PH. NO. SCREEN WILL COME") ;

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

    Serial.println("SETUP DONE, MOVING TO LOOP FOR SCREEN 145") ;
  }

  if ( screen == 2008341 ) {

    Serial.println("NOW ENTERING SETUP OF SCREEN 8341") ;
    Serial.println("SCREEN 8341 - SENDING MESSAGE STATUS WHILE THE MESSAGE IS BEING SENT TO THE OWNER OF THE PARKING LOT");
    Serial.println("THIS SCREEN HAS NO SETUP SO IT WILL JUMP INTO A SETUP OF ANOTHER SCREEN DIRECTLY") ;

    tft.fillScreen(BLACK);

    showmsgXY(1, 50 + 100, 3, &FreeSans9pt7b, "  SENDING");
    showmsgXY(15, 50 + 100, 3, &FreeSans9pt7b, "\n  MESSAGE");
    showmsgXY(15, 50 + 65 + 100, 2, &FreeSans9pt7b, "\n      Please Wait");
    showmsgXYM(15, 50 + 65 + 60 + 100, 1, &FreeSans9pt7b, "\nSending Message to : +91-8967068772");

    Serial.println("DUMPING DATA WHICH WILL BE GOING TO SERIAL6 GSM") ;
    Serial.println("AT+CMGF=1");

    Serial.println("AT+CMGS=\"+918967068772\"\r");
    DS3231_get(&t); //get the value and pass to the function the pointer to t, that make an lower memory fingerprint and faster execution than use return
    Serial.print(t.hour);
    Serial.print(":");
    Serial.print(t.min) ;
    Serial.print(":");
    Serial.print(t.sec);
    Serial.println("") ;
    Serial.print("DATE : ") ;
    Serial.print(t.mday) ;
    Serial.print("/");
    Serial.print(t.mon) ;
    Serial.print("/");
    Serial.print((t.year + 100));
    Serial.println("");
    Serial.print("CARS WENT OUT OF PARKING SPACE : ");
    Serial.print(C_OUT) ;
    Serial.println("");
    Serial.print("TOTAL AMOUNT COLLECTED : ");
    Serial.print(COST) ;
    Serial.println("");
    Serial.print("CARS STILL IN PARKING SPACE : ");
    Serial.print(C_IN) ;
    Serial.println("");

    Serial.println("SENDING DATA TO GSM VIA SERIAL6") ;
    delay(1000);
    Serial6.println("AT+CMGF=1");
    delay(1000);
    Serial6.println("AT+CMGS=\"+918967068772\"\r");
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
    screen = 2001 ;
    Serial.println("DATA SUCCESSFULLY SENT TO GSM VIA SERIAL6");
    Serial.println("JOB OF SCREEN1111 IS DONE, LEAVING SCREEN8341 AND JUMPING TO SETUP FUNCTION AS THIS IS NOT CONNECTED TO ANYTHING") ;
    setup() ;
  }

  if ( screen == 2001 ) {

    /* I2C COMMUNICATION WITH ESP8266 BEGINS WITH 8 AND STM32 AS A SLAVE ONLY THIS SCREEN WILL FETCH THE DATA AND SEND DATA
        FOR NOW V5.3 ONLY SENDING OF DATA IS NECESSARY AND RECEIVING AND PARSING OF DATA WILL BE DONE IN LATER VERSIONS
        REQESTEVENT IS THE REQUEST FROM THE MASTER AND RECEIVEEVENT IS FOR THE SLAVE THAT RECEIVED THE DATA THAT IS STM32
    */
    Wire.begin(8);
    Wire.onReceive(receiveEvent);
    Wire.onRequest(requestEvent);

    tft.fillScreen(BLACK);
    Serial.println("NOW ENTERING SETUP OF SCREEN 1");
    Serial.println("SCREEN 1 - VEHICLE PARKING MAIN MENU SCREEN FOR TAKING USER INPUT OF WANT TO KEEP VEHICLE OR TAKE OUT VEHICLE") ;
    Serial.println("THIS IS THE SCREEN 1 FOR GSM VERSION") ;

    showmsgXYM(1 + 9, 50 + 15, 5, &FreeSans9pt7b, "EPARK");
    showmsgXY(15 + 12, 115, 3, &FreeSans9pt7b, "Cortex  S5");
    showmsgXYG(15 + 30, 148 + 10, 2, &FreeSans9pt7b, "SERVER beta");
    showmsgXY(12, 162 + 10, 2, NULL, "ESP8266 IEEE 802.11 b/g/n\n EXPERIMENTAL FEATURES\n SERVER - APP INTEGRATION\n PRE-BOOKING OF SLOTS");
    tft.setFont(NULL);
    one.initButton(&tft,  60, 150 + 100 + 55, 100, 50, MAGENTA, MAGENTA, BLACK, "1", 3);
    two.initButton(&tft,  60, 150 + 100 + 55 + 75 - 5, 100, 50, AZURE, AZURE, BLACK, "2", 3);
    Three.initButton(&tft,  60, 150 + 100 + 55 + 75 + 65, 100, 50, PURPLE, PURPLE, BLACK, "3", 3);

    tft.setCursor(120, 130 + 100 + 55);
    tft.setTextColor(WHITE);
    tft.setTextSize(2);
    tft.print("Keep your");
    tft.setCursor(120, 150 + 100 + 57);
    tft.print("Vehicle inside");

    tft.setCursor(120, 242 + 100 + 20 - 5);
    tft.setTextColor(WHITE);
    tft.setTextSize(2);
    tft.print("Take your");
    tft.setCursor(120, 262 + 100 + 22 - 5);
    tft.print("Vehicle");

    tft.setCursor(120, 242 + 100 + 20 - 5 + 69);
    tft.setTextColor(RED);
    tft.setTextSize(2);
    tft.print("Finish");
    tft.setCursor(120, 262 + 100 + 22 - 5 + 69 );
    tft.print("Pre-Booking");

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
    Three.drawButton(false);
    Serial.println("GRAPHICS, VARIABLES INITIALIZED JUMPING TO SCREEN 1 LOOP") ;

  }

  if ( screen == 2002 ) {
    tft.fillScreen(BLACK);
    Serial.println("NOW ENTRING SETUP OF SCREEN 2");
    Serial.println("SCREEN 2 - AVAILABLE SLOTS SCREEN WHERE THE AVAILABLE SLOTS ARE SHOWN IF ANY") ;

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

    Serial.println("GRAPHICS DRAWING DONE JUMPING TO LOOP FOR SCREEN 2") ;

  }

  if ( screen == 20023 ) {
    tft.fillScreen(BLACK);
    Serial.println("NOW ENTERING SETUP OF SCREEN 23") ;
    Serial.println("SCREEN 23 - FOR SELECTING THE TYPE OF VEHILCE WHICH THE USER WANTS TO PARK AS PER THAT COST IS DIVIDED") ;

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
    Serial.println("SETUP DONE NOW MOVING TO LOOP OF SCREEN 23") ;
  }

  if ( screen == 2003 ) {

    tft.fillScreen(BLACK);
    Serial.println("NOW ENTERING SCREEN 3") ;
    Serial.println("SCREEN 3 - SLOT SELECTION SCREEN WHERE THE SLOT WHICH IS TO BE KEPT IS TAKEN FROM THE USER") ;

    showmsgXY(40, 30, 2, &FreeSans9pt7b, "Slot Selection");
    showmsgXYM(1, 55, 1, &FreeSans9pt7b, "These Slots are just for keeping the      space sorted , you have to pay as per      time kept !") ;
    tft.setFont(NULL);

    if ( counter[0] != 5 ) {
      showmsgXY(98, 133, 1, &FreeSans9pt7b, "Ground Floor \n                    For parking time :\n                    less than 3 hours") ;
      One.initButton(&tft,  50, 150, 75, 50, GREEN, GREEN, WHITE, "1", 3);
    }

    else if ( counter[0] == 5 ) {
      One.initButton(&tft,  50, 150, 75, 50, RED, RED, BLACK, "1", 3);
      showmsgXYGR(98, 133, 1, &FreeSans9pt7b, "Ground Floor \n                    For parking time :\n                    less than 3 hours") ;
    }

    if ( counter[1] != 5 ) {
      Two.initButton(&tft,  50, 150 + 50 + 30, 75, 50, GREEN, GREEN, WHITE, "2", 3);
      showmsgXY(98, 133 + 80, 1, &FreeSans9pt7b, "1st Floor \n                    For parking time :\n                    more than 3 hours") ;
    }

    else if ( counter[1] == 5 ) {
      Two.initButton(&tft,  50, 150 + 50 + 30, 75, 50, RED, RED, BLACK, "2", 3);
      showmsgXYGR(98, 133 + 80, 1, &FreeSans9pt7b, "1st Floor \n                    For parking time :\n                    more than 3 hours") ;
    }

    if ( counter[2] != 5 ) {
      showmsgXY(98, 133 + 80 + 80, 1, &FreeSans9pt7b, "2nd Floor \n                    For parking time :\n                    more than 6 hours") ;
      Three.initButton(&tft, 50, 150 + 50 + 30 + 50 + 30, 75, 50, GREEN, GREEN, WHITE, "3", 3);
    }

    else if ( counter[2] == 5 ) {
      Three.initButton(&tft, 50, 150 + 50 + 30 + 50 + 30, 75, 50, RED, RED, BLACK, "3", 3);
      showmsgXYGR(98, 133 + 80 + 80, 1, &FreeSans9pt7b, "2nd Floor \n                    For parking time :\n                    more than 6 hours") ;
    }

    if ( counter[3] != 5 ) {
      showmsgXY(98, 133 + 80 + 80 + 80, 1, &FreeSans9pt7b, "3rd Floor \n                    For parking time :\n                    more than 10 hours") ;
      Four.initButton(&tft,  50, 150 + 50 + 30 + 50 + 30 + 50 + 30, 75, 50, GREEN, GREEN, WHITE, "4", 3);
    }

    else if ( counter[3] == 5 ) {
      Four.initButton(&tft,  50, 150 + 50 + 30 + 50 + 30 + 50 + 30, 75, 50, RED, RED, BLACK, "4", 3);
      showmsgXYGR(98, 133 + 80 + 80 + 80, 1, &FreeSans9pt7b, "3rd Floor \n                    For parking time :\n                    more than 10 hours") ;
    }

    Ok.initButton(&tft,  280 + 5, 460 + 5, 80, 30, ILI9481_GREEN, ILI9481_GREEN , WHITE, "Ok", 2);
    Back.initButton(&tft,  41 - 7, 460 + 5, 80, 30, ILI9481_RED, ILI9481_RED, BLACK, "Back", 2);

    if (!( counter[0] == 5 && counter[1] == 5 && counter[2] == 5 && counter[3] == 5 ))
      Ok.drawButton(false);

    Back.drawButton(false);


    One.drawButton(false);



    Two.drawButton(false);



    Three.drawButton(false);



    Four.drawButton(false);


    Serial.println("SETTING DONE NOW MOVING TO LOOP FOR SCREEN 3") ;
  }

  if ( screen == 2004 ) {
    tft.fillScreen(BLACK);

    Serial.println("NOW ENTERING SCREEN 4") ;
    Serial.println("SCREEN 4 - UNIQUE IDENTIFICATION SCREEN WHERE THE USER PRESSES NUMPAD TO ENTER THE VEHICLE'S NUMBER");
    showmsgXY(75, 40, 2, &FreeSans12pt7b, "Unique \n  Identification");
    tft.setFont(NULL);
    Ok.initButton(&tft,  260, 460, 150, 40, ILI9481_GREEN, ILI9481_GREEN , WHITE, "Confirm", 2);
    Back.initButton(&tft,  41 - 7, 460 + 5, 80, 30, ILI9481_RED, ILI9481_RED, BLACK, "Back", 2);

    E.initButton(&tft,  160 , 210 + 20, 110, 50, MAGENTA, MAGENTA, BLACK, "Numpad", 2);


    Back.drawButton(false);
    E.drawButton(false);
    Serial.println("THE CONFIRM BUTTON WILL NOT BE DRAWN RIGHT NOW") ;
    /* -- showmsgXYM(1, 133, 1, &FreeSans9pt7b, "Enter your Vehicle's Registration no.     (from number plate) for our records") ; -- */
    showmsgXYM(1, 133, 1, &FreeSans9pt7b, "Enter 7 digit PIN to make it unique , it \nshould consist of last 4 digits of your \nvehicle number & 3 secret digits of your choice") ;
    /*  EXECUTE THESE STATEMENTS AFTER RETURNING FROM NUMPAD SCREEN */
    if ( n == 1 ) {
      Serial.println("USER HAS ENTERED PROPER DIGITS FOR PIN");
      Serial.println("DRAW THE CONFIRM BUTTON") ;
      showmsgXY(50 + 8, 260 + 20 + 16, 2 , NULL , textfield) ;
      tft.drawRect(50, 260 + 20, 220, 50, ILI9481_DARKGREY );
      showmsgXY(17, 400, 1, &FreeSans9pt7b, "Press Confirm to continue");

      Ok.drawButton(false);
    }
    Serial.println("DONE NOW MOVING TO LOOP FOR SCREEN 4") ;
  }

  if ( screen == 20045 ) {
    tft.fillScreen(BLACK);
    Serial.println("NOW ENTERING SETUP FOR SCREEN 45") ;
    Serial.println("SCREEN 45 - PHONE NUMBER SCREEN WHERE THE USER HAS TO ENTER PHONE NUMBER , IN ORDER TO RECEIVE AN E-RECEIPT AND IT WOULD BE STORED IN THE STRUCTURE FOR THE USER , SO AS THE USER WOULD GET AN E-RECEIPT WHILE TAKING THE CAR OUT ALSO");


    showmsgXY(75, 40, 2, &FreeSans12pt7b, "Phone  \n     Number");
    tft.setFont(NULL);


    Ok.initButton(&tft,  260, 460, 150, 40, ILI9481_GREEN, ILI9481_GREEN , WHITE, "Confirm", 2);
    Back.initButton(&tft,  41 - 7, 460 + 5, 80, 30, ILI9481_RED, ILI9481_RED, BLACK, "Back", 2);

    E.initButton(&tft,  160 , 210 + 20, 110, 50, MAGENTA, MAGENTA, BLACK, "Numpad", 2);

    Back.drawButton(false);
    E.drawButton(false);
    Serial.println("DON'T DRAW THE CONFIRM BUTTON NOW") ;

    /* -- showmsgXYM(1, 133, 1, &FreeSans9pt7b, "Enter your Vehicle's Registration no.     (from number plate) for our records") ; -- */
    showmsgXYM(1, 133, 1, &FreeSans9pt7b, "Enter your 10 DIGIT phone number \nwhich you have right now") ;
    /*  EXECUTE THESE STATEMENTS AFTER RETURNING FROM NUMPAD SCREEN */
    if ( ph_n == 1 ) {
      Serial.println("DRAW THE CONFIRM BUTTON BECAUSE THE USER HAS ENTERED THE CORRECT NO. OF DIGITS") ;
      showmsgXY(50 + 8, 260 + 14, 2 , NULL , ph_textfield) ;
      tft.drawRect(50, 260, 220, 50, ILI9481_DARKGREY );
      showmsgXY(17, 400, 1, &FreeSans9pt7b, "Press Confirm to keep your vehicle");

      Ok.drawButton(false);
    }
    Serial.println("DONE NOW MOVING TO LOOP FOR SCREEN 45") ;
  }

  if ( screen == 2005 ) {

    if ( c[i][counter[i]].yes == 9 )
      C_IN = C_IN  + 1;

    tft.fillScreen(BLACK);

    showmsgXYM(1, 50, 3, &FreeSans9pt7b, "Successful");
    showmsgXY(1, 95, 1, &FreeSans9pt7b, "You can now just keep your vehicle at \nthe prefered floor as per your choice of no. of hours , at the time of exit just \nchoose the option 2 and enter vehicle's number again , pay and take your \nVehicle back , now press Finish Button") ;
    showmsgXY(65, 400, 2, &FreeSans9pt7b, "Thank You !") ;
    tft.setFont(NULL);

    Finish.initButton(&tft,  160 , 300, 150, 50, MAGENTA, MAGENTA, BLACK, "Finish", 3);
    Finish.drawButton(false);
    Serial.println("DONE SETUP FOR KEEPING A VEHICLE") ;
    Serial.println("NOW MOVING TO LOOP FOR SCREEN 5 WHICH DOES NOT HAS MANY SUCH THINGS AND HENCE WILL SET SCREEN 1 AND CALL SETUP EVENTUALLY") ;
  }

  if ( screen == 2009 ) {
    Serial.println("NOW ENTERING THE SETUP FOR NUMPAD SCREEN 9") ;
    Serial.println("NUMPAD - 9 - THE NUMPAD SCREEN WHERE THERE IS A MATRIX INPUT AVAILABLE AND INPUT IS DRAWN TO SCREEN 4") ;

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

  if ( screen == 200991 ) {
    tft.fillScreen(BLACK);
    Serial.println("NOW MOVING TO SETUP FOR SCREEN 991 WHICH IS ANOTHER NUMPAD") ;
    Serial.println("NUMPAD_PH - 991 - THE NUMPAD SCREEN FOR ENTERING THE 10 DIGIT PHONE NUMBER") ;
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
    Serial.println("SETUP DONE NOW MOVING TO LOOP FOR SCREEN 991") ;
  }

  if ( screen == 20091 ) {
    tft.fillScreen(BLACK);
    Serial.println("NOW MOVING TO SETUP FOR SCREEN 91 WHICH IS ANOTHER NUMPAD") ;
    Serial.println(" NUMPAD1 - 91 - THE NUMPAD SCREEN WHERE THERE IS A MATRIX INPUT AVAILABLE AND INPUT IS DRAWN TO SCREEN 21") ;
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
    Serial.println("SETUP DONE NOW MOVING TO LOOP FOR SCREEN 91") ;
  }

  if ( screen == 20021) {
    tft.fillScreen(BLACK);
    Serial.println("NOW ENTERING SCREEN 21") ;
    Serial.println("SCREEN 21 - UNIQUE IDENTIFICATION SCREEN FOR TAKING THE VEHICLE OUT THE USER ENTERS THE VEHICLE'S NUMBER AND TAKES THE VEHICLE OUT") ;

    showmsgXY(75, 40, 2, &FreeSans12pt7b, "Unique \n  Identification");
    tft.setFont(NULL);

    Ok.initButton(&tft,  260, 460, 150, 40, ILI9481_GREEN, ILI9481_GREEN , WHITE, "Confirm", 2);
    Back.initButton(&tft,  41 - 7, 460 + 5, 80, 30, ILI9481_RED, ILI9481_RED, BLACK, "Back", 2);

    E.initButton(&tft,  160 , 210 + 20, 110, 50, MAGENTA, MAGENTA, BLACK, "Numpad", 2);

    Back.drawButton(false);
    E.drawButton(false);
    Serial.println("DON'T DRAW THE CONFIRM BUTTON AS THE LOGIC IS NOT SATISFIED") ;
    /* -- showmsgXYM(1, 133, 1, &FreeSans9pt7b, "Enter your Vehicle's Registration no.     (from number plate) to take your Vehicle out") ; -- */
    showmsgXYM(1, 133, 1, &FreeSans9pt7b, "Enter the 7-digit PIN, to take your \nvehicle out") ;

    /*  EXECUTE THESE STATEMENTS AFTER RETURNING FROM NUMPAD SCREEN */
    if ( nr == 1 ) {
      Serial.println("NOW DRAW THE CONFIRM BUTTON AS THE USER HAS ENTERED THE CORRECT NO. OF DIGITS") ;
      showmsgXY(50 + 8, 260 + 14, 2 , NULL , textfieldr) ;
      tft.drawRect(50, 260, 220, 50, ILI9481_DARKGREY );
      showmsgXY(5, 400, 1, &FreeSans9pt7b, "Press Confirm to take out your Vehicle");
      Ok.drawButton(false);
    }
    Serial.println("SETUP DONE NOW MOVING TO LOOP FOR SCREEN 21") ;
  }

  if ( screen == 20022) {
    tft.fillScreen(BLACK);
    Serial.println("NOW ENTERING SCREEN 22") ;
    Serial.println("SCREEN 22 - FINAL CONFIRMATION SCREEN WHERE THE USER PRESSES FINISH AND TAKES THE VEHICLE OUT") ;

    DS3231_get(&t); //get the value and pass to the function the pointer to t, that make an lower memory fingerprint and faster execution than use return
    timeTemp = ((t.unixtime + 3154000000) % 10000) ;
    showmsgXYM(1, 50, 3, &FreeSans9pt7b, "Successful");
    showmsgXY(1, 95, 1, &FreeSans9pt7b, "You can now just take your Vehicle out by paying the correct amount and press \nthe Finish button") ;
    showmsgXY(65, 190, 2, &FreeSans9pt7b, "Thank You !") ;
    C_OUT = C_OUT + 1 ;
    C_IN = C_IN - 1 ;
    tft.setFont(NULL);

    /*  EXECUTE THESE STATEMENTS AFTER SUCCESSFUL SEARCH  */
    Serial.println("EXECUTE THESE STATEMENTS AFTER SUCCESSFUL SEARCH") ;

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
    c[i_temp][j_temp].number[0] = '$' ;
    c[i_temp][j_temp].number[1] = '$' ;
    c[i_temp][j_temp].number[2] = '$' ;
    c[i_temp][j_temp].number[3] = '$' ;
    c[i_temp][j_temp].number[4] = '$' ;
    c[i_temp][j_temp].number[5] = '$' ;
    c[i_temp][j_temp].number[6] = '$' ;
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
      //       Serial.println("THE USER HAS ENTERED A PHONE NUMBER") ;
      //       Serial.println("SO DUMPING THE DATA TO BE GOING TO GSM VIA SERIAL6") ;
      //       Serial.println("AT+CMGF=1") ;
      //
      Serial.print("AT+CMGS=\"+91") ;
      Serial.print(c[i_temp][j_temp].ph_number[0]) ;
      Serial.print(c[i_temp][j_temp].ph_number[1]) ;
      Serial.print(c[i_temp][j_temp].ph_number[2]) ;
      Serial.print(c[i_temp][j_temp].ph_number[3]) ;
      Serial.print(c[i_temp][j_temp].ph_number[4]) ;
      Serial.print(c[i_temp][j_temp].ph_number[5]) ;
      Serial.print(c[i_temp][j_temp].ph_number[6]) ;
      Serial.print(c[i_temp][j_temp].ph_number[7]) ;
      Serial.print(c[i_temp][j_temp].ph_number[8]) ;
      Serial.print(c[i_temp][j_temp].ph_number[9]) ;
      Serial.print("\"\r") ;
      Serial.println() ;

      Serial.println("--- E-RECEIPT ---") ;
      Serial.println("") ;
      Serial.println("EPARK CORTEX S5") ;
      Serial.println("VEHICLE EXIT") ;
      Serial.println("") ;
      Serial.print("TIME KEPT : ") ;
      Serial.print(T1) ;
      Serial.println("") ;
      Serial.print("AMOUNT TO BE PAID : ") ;
      if ( c[i_temp][j_temp].type == 1 )
        Serial.print("Rs. 25") ;
      else if ( c[i_temp][j_temp].type == 2 )
        Serial.print("Rs. 30") ;
      Serial.println("");

      Serial.print("EXIT TIME : ");
      DS3231_get(&t); //get the value and pass to the function the pointer to t, that make an lower memory fingerprint and faster execution than use return
      Serial.print(t.hour);
      Serial.print(":");
      Serial.print(t.min) ;
      Serial.print(":");
      Serial.print(t.sec);
      Serial.println("") ;
      Serial.print("DATE : ") ;
      Serial.print(t.mday) ;
      Serial.print("/");
      Serial.print(t.mon) ;
      Serial.print("/");
      Serial.print((t.year + 100));
      Serial.println("");

      Serial.println((char)26);

      Serial.println("DUMPING OF SERIAL6 DONE NOW MOVING THE DATA TO SERIAL6");
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
      Serial6.println("EPARK CORTEX S5") ;
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
      Serial.println("SENDING OF DATA TO GSM DONE VIA SERIAL6");
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

    Serial.println("RESETTING VARIABLES AND MOVING TO LOOP FOR SCREEN 21 WHICH WILL RESET AND CALL SETUP AGAINST SCREEN 1");
  }

  if ( screen == 200220) {
    Serial.println("NOW ENTERING THE SCREEN 220");
    Serial.println("SCREEN 22_0 - 220 - THE ERROR SCREEN WHERE THE USER WILL GET WHEN ENTERED THE WRONG VEHICLE'S NUMBER OR WHICH IS NOT IN THE DATABASE");
    tft.fillScreen(BLACK);
    showmsgXY(1, 100, 2, &FreeSans9pt7b, "The number you \nentered does not \nmatch our records \nplease go back and \nenter the correct \nnumber") ;
    tft.setFont(NULL);
    Back.initButton(&tft,  41 - 7, 460 + 5, 80, 30, ILI9481_RED, ILI9481_RED, BLACK, "Back", 2);
    Back.drawButton(false);
    nr = 0 ;
    Serial.println("SETUP DONE NOW MOVING TO LOOP AND FURTHER LOOP") ;
  }

  if ( screen == 20031) {
    tft.fillScreen(BLACK);
    Serial.println("NOW ENTERING SCREEN 21") ;
    Serial.println("SCREEN 21 - UNIQUE IDENTIFICATION SCREEN FOR TAKING THE VEHICLE OUT THE USER ENTERS THE VEHICLE'S NUMBER AND TAKES THE VEHICLE OUT") ;

    showmsgXY(75, 40, 2, &FreeSans12pt7b, "  Finish \n   Pre-booking");
    tft.setFont(NULL);

    Ok.initButton(&tft,  260, 460, 150, 40, ILI9481_GREEN, ILI9481_GREEN , WHITE, "Confirm", 2);
    Back.initButton(&tft,  41 - 7, 460 + 5, 80, 30, ILI9481_RED, ILI9481_RED, BLACK, "Back", 2);

    E.initButton(&tft,  160 , 210 + 20, 110, 50, MAGENTA, MAGENTA, BLACK, "Numpad", 2);

    Back.drawButton(false);
    E.drawButton(false);
    Serial.println("DON'T DRAW THE CONFIRM BUTTON AS THE LOGIC IS NOT SATISFIED") ;
    /* -- showmsgXYM(1, 133, 1, &FreeSans9pt7b, "Enter your Vehicle's Registration no.     (from number plate) to take your Vehicle out") ; -- */
    showmsgXYM(1, 133, 1, &FreeSans9pt7b, "Enter the 4-digit OTP to finish your pre-booking. As you have finilized slots \nduring pre-booking you will have to give minimal data") ;

    /*  EXECUTE THESE STATEMENTS AFTER RETURNING FROM NUMPAD SCREEN */
    if ( nr200 == 1 ) {
      Serial.println("NOW DRAW THE CONFIRM BUTTON AS THE USER HAS ENTERED THE CORRECT NO. OF DIGITS") ;
      showmsgXY(50 + 8, 260 + 14, 2 , NULL , textfieldr200) ;
      tft.drawRect(50, 260, 220, 50, ILI9481_DARKGREY );
      showmsgXY(5, 400, 1, &FreeSans9pt7b, "Press Confirm to take out your Vehicle");
      Ok.drawButton(false);
    }
    Serial.println("SETUP DONE NOW MOVING TO LOOP FOR SCREEN 21") ;
  }

  if ( screen == 200913 ) {
    tft.fillScreen(BLACK);
    Serial.println("NOW MOVING TO SETUP FOR SCREEN 91 WHICH IS ANOTHER NUMPAD") ;
    Serial.println(" NUMPAD1 - 913 - THE NUMPAD SCREEN WHERE THERE IS A MATRIX INPUT AVAILABLE AND INPUT IS DRAWN TO SCREEN 21") ;
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
    Serial.println("SETUP DONE NOW MOVING TO LOOP FOR SCREEN 913") ;
  }

  if ( screen == 2002203) {
    Serial.println("NOW ENTERING THE SCREEN 220");
    Serial.println("SCREEN 22_0 - 220 - THE ERROR SCREEN WHERE THE USER WILL GET WHEN ENTERED THE WRONG VEHICLE'S NUMBER OR WHICH IS NOT IN THE DATABASE");
    tft.fillScreen(BLACK);
    showmsgXY(1, 100, 2, &FreeSans9pt7b, "The number you \nentered does not \nmatch our records \nplease go back and \nenter the correct \nnumber") ;
    tft.setFont(NULL);
    Back.initButton(&tft,  41 - 7, 460 + 5, 80, 30, ILI9481_RED, ILI9481_RED, BLACK, "Back", 2);
    Back.drawButton(false);
    nr200 = 0 ;
    Serial.println("SETUP DONE NOW MOVING TO LOOP AND FURTHER LOOP") ;
  }

  if ( screen == 20040) {
    Serial.println("NOW ENTERING THE SCREEN 40");
    Serial.println("SCREEN 4_0 - 40 - THE ERROR SCREEN WHERE THE USER WILL GET WHEN ENTERED THE SAME PIN");
    tft.fillScreen(BLACK);
    showmsgXY(1, 100, 2, &FreeSans9pt7b, "The number you \nentered cannot be \nused as PIN for you please go back and enter different \nnumber again") ;
    tft.setFont(NULL);
    Back.initButton(&tft,  41 - 7, 460 + 5, 80, 30, ILI9481_RED, ILI9481_RED, BLACK, "Back", 2);
    Back.drawButton(false);
    Serial.println("SETUP DONE NOW MOVING TO LOOP AND FURTHER LOOP") ;
    found_pin = -1;



  }



/*[v1 - MINI]---------------------------------------------------------------------------[ADD 200 WITH THE CONTROLLERS]*/
  if ( screen == 1001 ) {

    tft.fillScreen(BLACK);
    Serial.println("NOW ENTERING SETUP OF SCREEN 1");
    Serial.println("SCREEN 1 - VEHICLE PARKING MAIN MENU SCREEN FOR TAKING USER INPUT OF WANT TO KEEP VEHICLE OR TAKE OUT VEHICLE") ;
    Serial.println("THIS IS THE SCREEN 1 FOR GSM VERSION") ;

    showmsgXYM(1 + 9, 50 + 15, 5, &FreeSans9pt7b, "EPARK");
    showmsgXY(15 + 12, 115, 3, &FreeSans9pt7b, "Cortex  S5");
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
    Serial.println("GRAPHICS, VARIABLES INITIALIZED JUMPING TO SCREEN 1 LOOP") ;

  }

  if ( screen == 1002 ) {
    tft.fillScreen(BLACK);
    Serial.println("NOW ENTRING SETUP OF SCREEN 2");
    Serial.println("SCREEN 2 - AVAILABLE SLOTS SCREEN WHERE THE AVAILABLE SLOTS ARE SHOWN IF ANY") ;

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

    Serial.println("GRAPHICS DRAWING DONE JUMPING TO LOOP FOR SCREEN 2") ;

  }

  if ( screen == 1003 ) {
    tft.fillScreen(BLACK);
    Serial.println("NOW ENTERING SCREEN 3") ;
    Serial.println("SCREEN 3 - SLOT SELECTION SCREEN WHERE THE SLOT WHICH IS TO BE KEPT IS TAKEN FROM THE USER") ;

    showmsgXY(40, 30, 2, &FreeSans9pt7b, "Slot Selection");
    showmsgXYM(1, 55, 1, &FreeSans9pt7b, "These Slots are just for keeping the      space sorted , you have to pay as per      time kept !") ;
    tft.setFont(NULL);

    if ( counter[0] != 5 ) {
      showmsgXY(98, 133, 1, &FreeSans9pt7b, "Ground Floor \n                    For parking time :\n                    less than 3 hours") ;
      One.initButton(&tft,  50, 150, 75, 50, GREEN, GREEN, WHITE, "1", 3);
    }

    else if ( counter[0] == 5 ) {
      One.initButton(&tft,  50, 150, 75, 50, RED, RED, BLACK, "1", 3);
      showmsgXYGR(98, 133, 1, &FreeSans9pt7b, "Ground Floor \n                    For parking time :\n                    less than 3 hours") ;
    }

    if ( counter[1] != 5 ) {
      Two.initButton(&tft,  50, 150 + 50 + 30, 75, 50, GREEN, GREEN, WHITE, "2", 3);
      showmsgXY(98, 133 + 80, 1, &FreeSans9pt7b, "1st Floor \n                    For parking time :\n                    more than 3 hours") ;
    }

    else if ( counter[1] == 5 ) {
      Two.initButton(&tft,  50, 150 + 50 + 30, 75, 50, RED, RED, BLACK, "2", 3);
      showmsgXYGR(98, 133 + 80, 1, &FreeSans9pt7b, "1st Floor \n                    For parking time :\n                    more than 3 hours") ;
    }

    if ( counter[2] != 5 ) {
      showmsgXY(98, 133 + 80 + 80, 1, &FreeSans9pt7b, "2nd Floor \n                    For parking time :\n                    more than 6 hours") ;
      Three.initButton(&tft, 50, 150 + 50 + 30 + 50 + 30, 75, 50, GREEN, GREEN, WHITE, "3", 3);
    }

    else if ( counter[2] == 5 ) {
      Three.initButton(&tft, 50, 150 + 50 + 30 + 50 + 30, 75, 50, RED, RED, BLACK, "3", 3);
      showmsgXYGR(98, 133 + 80 + 80, 1, &FreeSans9pt7b, "2nd Floor \n                    For parking time :\n                    more than 6 hours") ;
    }

    if ( counter[3] != 5 ) {
      showmsgXY(98, 133 + 80 + 80 + 80, 1, &FreeSans9pt7b, "3rd Floor \n                    For parking time :\n                    more than 10 hours") ;
      Four.initButton(&tft,  50, 150 + 50 + 30 + 50 + 30 + 50 + 30, 75, 50, GREEN, GREEN, WHITE, "4", 3);
    }

    else if ( counter[3] == 5 ) {
      Four.initButton(&tft,  50, 150 + 50 + 30 + 50 + 30 + 50 + 30, 75, 50, RED, RED, BLACK, "4", 3);
      showmsgXYGR(98, 133 + 80 + 80 + 80, 1, &FreeSans9pt7b, "3rd Floor \n                    For parking time :\n                    more than 10 hours") ;
    }

    Ok.initButton(&tft,  280 + 5, 460 + 5, 80, 30, ILI9481_GREEN, ILI9481_GREEN , WHITE, "Ok", 2);
    Back.initButton(&tft,  41 - 7, 460 + 5, 80, 30, ILI9481_RED, ILI9481_RED, BLACK, "Back", 2);

    if (!( counter[0] == 5 && counter[1] == 5 && counter[2] == 5 && counter[3] == 5 ))
      Ok.drawButton(false);

    Back.drawButton(false);


    One.drawButton(false);



    Two.drawButton(false);



    Three.drawButton(false);



    Four.drawButton(false);


    Serial.println("SETTING DONE NOW MOVING TO LOOP FOR SCREEN 3") ;
  }

  if ( screen == 10023 ) {
    tft.fillScreen(BLACK);
    Serial.println("NOW ENTERING SETUP OF SCREEN 23") ;
    Serial.println("SCREEN 23 - FOR SELECTING THE TYPE OF VEHILCE WHICH THE USER WANTS TO PARK AS PER THAT COST IS DIVIDED") ;

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
    Serial.println("SETUP DONE NOW MOVING TO LOOP OF SCREEN 23") ;
  }

  if ( screen == 1004 ) {
    tft.fillScreen(BLACK);

    Serial.println("NOW ENTERING SCREEN 4") ;
    Serial.println("SCREEN 4 - UNIQUE IDENTIFICATION SCREEN WHERE THE USER PRESSES NUMPAD TO ENTER THE VEHICLE'S NUMBER");
    showmsgXY(75, 40, 2, &FreeSans12pt7b, "Unique \n  Identification");
    tft.setFont(NULL);
    Ok.initButton(&tft,  260, 460, 150, 40, ILI9481_GREEN, ILI9481_GREEN , WHITE, "Confirm", 2);
    Back.initButton(&tft,  41 - 7, 460 + 5, 80, 30, ILI9481_RED, ILI9481_RED, BLACK, "Back", 2);

    E.initButton(&tft,  160 , 210 + 20, 110, 50, MAGENTA, MAGENTA, BLACK, "Numpad", 2);


    Back.drawButton(false);
    E.drawButton(false);
    Serial.println("THE CONFIRM BUTTON WILL NOT BE DRAWN RIGHT NOW") ;
    /* -- showmsgXYM(1, 133, 1, &FreeSans9pt7b, "Enter your Vehicle's Registration no.     (from number plate) for our records") ; -- */
    showmsgXYM(1, 133, 1, &FreeSans9pt7b, "Enter 7 digit PIN to make it unique , it \nshould consist of last 4 digits of your \nvehicle number & 3 secret digits of your choice") ;
    /*  EXECUTE THESE STATEMENTS AFTER RETURNING FROM NUMPAD SCREEN */
    if ( n == 1 ) {
      Serial.println("USER HAS ENTERED PROPER DIGITS FOR PIN");
      Serial.println("DRAW THE CONFIRM BUTTON") ;
      showmsgXY(50 + 8, 260 + 20 + 16, 2 , NULL , textfield) ;
      tft.drawRect(50, 260 + 20, 220, 50, ILI9481_DARKGREY );
      showmsgXY(17, 400, 1, &FreeSans9pt7b, "Press Confirm to continue");

      Ok.drawButton(false);
    }
    Serial.println("DONE NOW MOVING TO LOOP FOR SCREEN 4") ;
  }

  if ( screen == 1009 ) {
    Serial.println("NOW ENTERING THE SETUP FOR NUMPAD SCREEN 9") ;
    Serial.println("NUMPAD - 9 - THE NUMPAD SCREEN WHERE THERE IS A MATRIX INPUT AVAILABLE AND INPUT IS DRAWN TO SCREEN 4") ;

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
    Serial.println("NOW MOVING TO SETUP FOR SCREEN 91 WHICH IS ANOTHER NUMPAD") ;
    Serial.println(" NUMPAD1 - 91 - THE NUMPAD SCREEN WHERE THERE IS A MATRIX INPUT AVAILABLE AND INPUT IS DRAWN TO SCREEN 21") ;
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
    Serial.println("SETUP DONE NOW MOVING TO LOOP FOR SCREEN 91") ;
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
    Serial.println("DONE SETUP FOR KEEPING A VEHICLE") ;
    Serial.println("NOW MOVING TO LOOP FOR SCREEN 5 WHICH DOES NOT HAS MANY SUCH THINGS AND HENCE WILL SET SCREEN 1 AND CALL SETUP EVENTUALLY") ;
  }

  if ( screen == 10021) {
    tft.fillScreen(BLACK);
    Serial.println("NOW ENTERING SCREEN 21") ;
    Serial.println("SCREEN 21 - UNIQUE IDENTIFICATION SCREEN FOR TAKING THE VEHICLE OUT THE USER ENTERS THE VEHICLE'S NUMBER AND TAKES THE VEHICLE OUT") ;

    showmsgXY(75, 40, 2, &FreeSans12pt7b, "Unique \n  Identification");
    tft.setFont(NULL);

    Ok.initButton(&tft,  260, 460, 150, 40, ILI9481_GREEN, ILI9481_GREEN , WHITE, "Confirm", 2);
    Back.initButton(&tft,  41 - 7, 460 + 5, 80, 30, ILI9481_RED, ILI9481_RED, BLACK, "Back", 2);

    E.initButton(&tft,  160 , 210 + 20, 110, 50, MAGENTA, MAGENTA, BLACK, "Numpad", 2);

    Back.drawButton(false);
    E.drawButton(false);
    Serial.println("DON'T DRAW THE CONFIRM BUTTON AS THE LOGIC IS NOT SATISFIED") ;
    /* -- showmsgXYM(1, 133, 1, &FreeSans9pt7b, "Enter your Vehicle's Registration no.     (from number plate) to take your Vehicle out") ; -- */
    showmsgXYM(1, 133, 1, &FreeSans9pt7b, "Enter the 7-digit PIN, to take your \nvehicle out") ;

    /*  EXECUTE THESE STATEMENTS AFTER RETURNING FROM NUMPAD SCREEN */
    if ( nr == 1 ) {
      Serial.println("NOW DRAW THE CONFIRM BUTTON AS THE USER HAS ENTERED THE CORRECT NO. OF DIGITS") ;
      showmsgXY(50 + 8, 260 + 14, 2 , NULL , textfieldr) ;
      tft.drawRect(50, 260, 220, 50, ILI9481_DARKGREY );
      showmsgXY(5, 400, 1, &FreeSans9pt7b, "Press Confirm to take out your Vehicle");
      Ok.drawButton(false);
    }
    Serial.println("SETUP DONE NOW MOVING TO LOOP FOR SCREEN 21") ;
  }

  if ( screen == 10022) {
    tft.fillScreen(BLACK);
    Serial.println("NOW ENTERING SCREEN 22") ;
    Serial.println("SCREEN 22 - FINAL CONFIRMATION SCREEN WHERE THE USER PRESSES FINISH AND TAKES THE VEHICLE OUT") ;

    DS3231_get(&t); //get the value and pass to the function the pointer to t, that make an lower memory fingerprint and faster execution than use return
    timeTemp = ((t.unixtime + 3154000000) % 10000) ;
    showmsgXYM(1, 50, 3, &FreeSans9pt7b, "Successful");
    showmsgXY(1, 95, 1, &FreeSans9pt7b, "You can now just take your Vehicle out by paying the correct amount and press \nthe Finish button") ;
    showmsgXY(65, 190, 2, &FreeSans9pt7b, "Thank You !") ;
    C_OUT = C_OUT + 1 ;
    C_IN = C_IN - 1 ;
    tft.setFont(NULL);

    /*  EXECUTE THESE STATEMENTS AFTER SUCCESSFUL SEARCH  */
    Serial.println("EXECUTE THESE STATEMENTS AFTER SUCCESSFUL SEARCH") ;

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
    c[i_temp][j_temp].number[0] = '$' ;
    c[i_temp][j_temp].number[1] = '$' ;
    c[i_temp][j_temp].number[2] = '$' ;
    c[i_temp][j_temp].number[3] = '$' ;
    c[i_temp][j_temp].number[4] = '$' ;
    c[i_temp][j_temp].number[5] = '$' ;
    c[i_temp][j_temp].number[6] = '$' ;
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
    Serial.println() ;

    Serial.println("--- E-RECEIPT ---") ;
    Serial.println("") ;
    Serial.println("EPARK CORTEX S5") ;
    Serial.println("VEHICLE EXIT") ;
    Serial.println("") ;
    Serial.print("TIME KEPT : ") ;
    Serial.print(T1) ;
    Serial.println("") ;
    Serial.print("AMOUNT TO BE PAID : ") ;
    if ( c[i_temp][j_temp].type == 1 )
      Serial.print("Rs. 25") ;
    else if ( c[i_temp][j_temp].type == 2 )
      Serial.print("Rs. 30") ;
    Serial.println("");

    Serial.print("EXIT TIME : ");
    DS3231_get(&t); //get the value and pass to the function the pointer to t, that make an lower memory fingerprint and faster execution than use return
    Serial.print(t.hour);
    Serial.print(":");
    Serial.print(t.min) ;
    Serial.print(":");
    Serial.print(t.sec);
    Serial.println("") ;
    Serial.print("DATE : ") ;
    Serial.print(t.mday) ;
    Serial.print("/");
    Serial.print(t.mon) ;
    Serial.print("/");
    Serial.print((t.year + 100));
    Serial.println("");
    Finish.initButton(&tft,  160 , 450, 150, 50, MAGENTA, MAGENTA, BLACK , "Finish", 3);
    Finish.drawButton(false);


    for ( k = 0 ; k < TEXT_LEN  ; k++)
      textfieldr[k] = ' ' ;
    textfieldr_i = 0 ;
    i_temp = -1 ;
    j_temp = -1 ;

    Serial.println("RESETTING VARIABLES AND MOVING TO LOOP FOR SCREEN 21 WHICH WILL RESET AND CALL SETUP AGAINST SCREEN 1");
  }

  if ( screen == 100220) {
    Serial.println("NOW ENTERING THE SCREEN 220");
    Serial.println("SCREEN 22_0 - 220 - THE ERROR SCREEN WHERE THE USER WILL GET WHEN ENTERED THE WRONG VEHICLE'S NUMBER OR WHICH IS NOT IN THE DATABASE");
    tft.fillScreen(BLACK);
    showmsgXY(1, 100, 2, &FreeSans9pt7b, "The number you \nentered does not \nmatch our records \nplease go back and \nenter the correct \nnumber") ;
    tft.setFont(NULL);
    Back.initButton(&tft,  41 - 7, 460 + 5, 80, 30, ILI9481_RED, ILI9481_RED, BLACK, "Back", 2);
    Back.drawButton(false);
    nr = 0 ;
    Serial.println("SETUP DONE NOW MOVING TO LOOP AND FURTHER LOOP") ;
  }


  if ( screen == 10040) {
    Serial.println("NOW ENTERING THE SCREEN 40");
    Serial.println("SCREEN 4_0 - 40 - THE ERROR SCREEN WHERE THE USER WILL GET WHEN ENTERED THE SAME PIN");
    tft.fillScreen(BLACK);
    showmsgXY(1, 100, 2, &FreeSans9pt7b, "The number you \nentered cannot be \nused as PIN for you please go back and enter different \nnumber again") ;
    tft.setFont(NULL);
    Back.initButton(&tft,  41 - 7, 460 + 5, 80, 30, ILI9481_RED, ILI9481_RED, BLACK, "Back", 2);
    Back.drawButton(false);
    Serial.println("SETUP DONE NOW MOVING TO LOOP AND FURTHER LOOP") ;
    found_pin = -1;



  }



}

/*   THE MAIN LOOP FOR THE ARDUINO
     ALL THE CODES FOR REDRAWING THE THINGS ARE DECLARED HERE
*/


void loop(void)
{
/* [v2 - GSM]-----------------------------------------------------------------------------[ADD NULL WITH CONTROLLERS] - [BASE OF ALL VERSION] */
  if (screen == 111110) {
    Serial.println("SPLASH SCREEN") ;
    char *nm = namebuf + pathlen;
    File f = root.openNextFile();
    uint8_t ret;
    uint32_t start;
    if (f != NULL && tft_firstscreentr == 1) {
#ifdef USE_SDFAT
      f.getName(nm, 32 - pathlen);
#else
      strcpy(nm, (char *)f.name());
#endif
      f.close();
      strlwr(nm);
      if (strstr(nm, ".bmp") != NULL && strstr(nm, NAMEMATCH) != NULL) {
        //            Serial.print(namebuf);
        //            Serial.print(F(" - "));
        tft.fillScreen(0);
        //start = millis();
        ret = showBMP(namebuf, 5, 5);
        switch (ret) {
          case 0:
            //                    Serial.print(millis() - start);
            //                    Serial.println(F("ms"));
            delay(1000);

            //                case 1:
            //                    Serial.println(F("bad position"));
            //                    break;
            //                case 2:
            //                    Serial.println(F("bad BMP ID"));
            //                    break;
            //                case 3:
            //                    Serial.println(F("wrong number of planes"));
            //                    break;
            //                case 4:
            //                    Serial.println(F("unsupported BMP format"));
            //                    break;
            //                case 5:
            //                    Serial.println(F("unsupported palette"));
            //                    break;
            //                default:
            //                    Serial.println(F("unknown"));
            //                    break;
        }
      }
    }
    else if (tft_firstscreentr == 1) {
      tft_firstscreentr = -1 ;
      screen1();
    }
  }

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
      Serial.println("OWNER BUTTON PRESSED # SEND MESSAGE TO HARD CODED ONWER'S MOBILE NUMBER") ;
      /*----START SENDING THE MESSAGE BY CALLING A FUNCTION OR SOMETHING AND THEN RE-ROUTE THE FUNCTION TO SETUP-----*/
      /*-----MESSAGE------*/
      screen8341() ;
      Serial.println("MESSAGE SENT NOW CONTINUE RUNNING LOOP FOR SCREEN 1") ;
    }
    bool down = Touch_getXY();

    Ok.press(down && Ok.contains(pixel_x, pixel_y));
    Back.press(down && Back.contains(pixel_x, pixel_y));
    one.press(down && one.contains(pixel_x, pixel_y));
    two.press(down && two.contains(pixel_x, pixel_y));
    if (one.justReleased())
      one.drawButton();
    if (two.justReleased())
      two.drawButton();
    if (one.justPressed()) {
      one.drawButton(true);

      screen3() ;
    }
    if (two.justPressed()) {
      two.drawButton(true);

      screen21() ;
    }
    if (Ok.justReleased())
      Ok.drawButton();
    if (Ok.justPressed()) {
      tft.fillScreen(WHITE);
      tft.setTextSize(2) ;
      tft.setCursor(1, 1) ;
      tft.setTextColor(BLACK) ;
      delay(100) ;
      tft.println("") ;      tft.setTextColor(RED) ;      tft.print("-") ; delay(300) ;      tft.setTextColor(BLACK) ;      tft.print("C") ; delay(100) ;      tft.print("O") ; delay(100) ;      tft.print("N") ; delay(100) ;      tft.print("N") ; delay(100) ;      tft.print("E") ; delay(100) ;      tft.print("C") ; delay(100) ;      tft.print("T") ; delay(100) ;      tft.print(" ") ; delay(100) ;      tft.print("T") ; delay(100) ;      tft.print("O") ; delay(100) ;      tft.print(" ") ; delay(100) ;      tft.print("C") ; delay(100) ;      tft.print("O") ; delay(100) ;      tft.print("R") ; delay(100) ;      tft.print("T") ; delay(100) ;      tft.print("E") ; delay(100) ;      tft.print("X") ; delay(100) ;      tft.print(".") ; delay(100) ;      tft.print(".") ; delay(100) ;      tft.print(".") ; delay(200) ;      tft.print(".") ; delay(300) ;     tft.print(".") ; delay(400) ;     tft.print(".") ; delay(100) ;     tft.print(".") ; delay(100) ;     tft.print(".") ; delay(100) ;      tft.println("") ;     tft.setTextColor(RED) ;     tft.print("-") ; delay(500) ;     tft.setTextColor(BLACK) ;     tft.print("C") ; delay(100) ;     tft.print("O") ; delay(100) ;     tft.print("N") ; delay(100) ;     tft.print("N") ; delay(100) ;    tft.print("E") ; delay(100) ;     tft.print("C") ; delay(100) ;     tft.print("T") ; delay(100) ;     tft.print("E") ; delay(100) ;     tft.print("D") ; delay(100) ;      tft.println("") ;     tft.setTextColor(RED) ;     tft.print("-") ; delay(500) ;     tft.setTextColor(BLACK) ;    tft.print("D") ; delay(100) ;     tft.print("E") ; delay(100) ;     tft.print("V") ; delay(100) ;      tft.print(".") ; delay(100) ;     tft.print(".") ; delay(100) ;
      tft.print(".") ; delay(100) ;
      tft.print(".") ; delay(100) ;      tft.print(".") ; delay(100) ;      tft.print(".") ; delay(100) ;      tft.print(".") ; delay(100) ;      tft.print("v") ; delay(200) ;      tft.print("5") ; delay(300) ;      tft.print(".") ; delay(400) ;      tft.print("8(b)") ; delay(100) ;      tft.println("") ; delay(100) ;      tft.setTextColor(RED) ;
      tft.print("-") ; delay(500) ;      tft.setTextColor(BLACK) ;      tft.print("J") ; delay(100) ;      tft.print("U") ; delay(100) ;      tft.print("M") ; delay(100) ;      tft.print("P") ; delay(100) ;      tft.print("I") ; delay(100) ;      tft.print("N") ; delay(100) ;      tft.print("G") ; delay(100) ;      tft.print(" -") ; delay(200) ;      tft.print(">") ; delay(100) ;      tft.print("v") ; delay(100) ;     tft.print("1") ; delay(100) ;      tft.println("") ; delay(100) ;      tft.setTextColor(RED) ;      tft.print("-") ; delay(300) ;      tft.setTextColor(BLACK) ;      tft.print("C") ; delay(100) ;      tft.print("O") ; delay(100) ;      tft.print("D") ; delay(100) ;      tft.print("E") ; delay(100) ;      tft.print(".") ; delay(100) ;      tft.print(".") ; delay(100) ;      tft.print(".") ; delay(100) ;      tft.print(".") ; delay(200) ;      tft.print(".") ; delay(100) ;      tft.print("O") ; delay(100) ;     tft.print("K") ; delay(100) ;     tft.println("") ;     tft.setTextColor(GREEN) ;     tft.setTextSize(3) ;     tft.print("JUMP NOW") ; delay(100) ;
      delay(3000) ;
      tft.fillScreen(RED); delay(400);
      //      tft.fillScreen(RED); delay(400);
      //      tft.fillScreen(YELLOW); delay(400);
      //      tft.fillScreen(GREEN); delay(600);
      //      tft.fillScreen(BLUE); delay(500);
      //      tft.fillScreen(MAGENTA); delay(400);
      //      tft.fillScreen(BLACK); delay(100);
      Serial.println("\n\nJUMPING TO v1 MINI") ;
      Serial.println("PUTTING SCREEN EQUALS 1001") ;
      Serial.println("NOW THE INDEXES IN SERIAL WILL BE OF MINI VERSION INSTEAD OF GSM - ADD 100 WITH EVERY INDEX TO DEBUG") ;
      screen = 1001 ;
      setup();
      //      Back.drawButton(true);
      //      prog = 1 ;
      //      tft_firstscreentr = 1 ;
      //      screen = 111110 ;
      //      setup() ;
    }

    if (Back.justReleased())
      Back.drawButton();
    if (Back.justPressed()) {

tft.fillScreen(WHITE);
      tft.setTextSize(2) ;
      tft.setCursor(1, 1) ;
      tft.setTextColor(BLACK) ;
      delay(100) ;
      tft.println("") ;      tft.setTextColor(RED) ;      tft.print("-") ; delay(300) ;      tft.setTextColor(BLACK) ;      tft.print("C") ; delay(100) ;      tft.print("O") ; delay(100) ;      tft.print("N") ; delay(100) ;      tft.print("N") ; delay(100) ;      tft.print("E") ; delay(100) ;      tft.print("C") ; delay(100) ;      tft.print("T") ; delay(100) ;      tft.print(" ") ; delay(100) ;      tft.print("T") ; delay(100) ;      tft.print("O") ; delay(100) ;      tft.print(" ") ; delay(100) ;      tft.print("C") ; delay(100) ;      tft.print("O") ; delay(100) ;      tft.print("R") ; delay(100) ;      tft.print("T") ; delay(100) ;      tft.print("E") ; delay(100) ;      tft.print("X") ; delay(100) ;      tft.print(".") ; delay(100) ;      tft.print(".") ; delay(100) ;      tft.print(".") ; delay(200) ;      tft.print(".") ; delay(300) ;     tft.print(".") ; delay(400) ;     tft.print(".") ; delay(100) ;     tft.print(".") ; delay(100) ;     tft.print(".") ; delay(100) ;      tft.println("") ;     tft.setTextColor(RED) ;     tft.print("-") ; delay(500) ;     tft.setTextColor(BLACK) ;     tft.print("C") ; delay(100) ;     tft.print("O") ; delay(100) ;     tft.print("N") ; delay(100) ;     tft.print("N") ; delay(100) ;    tft.print("E") ; delay(100) ;     tft.print("C") ; delay(100) ;     tft.print("T") ; delay(100) ;     tft.print("E") ; delay(100) ;     tft.print("D") ; delay(100) ;      tft.println("") ;     tft.setTextColor(RED) ;     tft.print("-") ; delay(500) ;     tft.setTextColor(BLACK) ;    tft.print("D") ; delay(100) ;     tft.print("E") ; delay(100) ;     tft.print("V") ; delay(100) ;      tft.print(".") ; delay(100) ;     tft.print(".") ; delay(100) ;
      tft.print(".") ; delay(100) ;
      tft.print(".") ; delay(100) ;      tft.print(".") ; delay(100) ;      tft.print(".") ; delay(100) ;      tft.print(".") ; delay(100) ;      tft.print("v") ; delay(200) ;      tft.print("5") ; delay(300) ;      tft.print(".") ; delay(400) ;      tft.print("8(b)") ; delay(100) ;      tft.println("") ; delay(100) ;      tft.setTextColor(RED) ;
      tft.print("-") ; delay(500) ;      tft.setTextColor(BLACK) ;      tft.print("J") ; delay(100) ;      tft.print("U") ; delay(100) ;      tft.print("M") ; delay(100) ;      tft.print("P") ; delay(100) ;      tft.print("I") ; delay(100) ;      tft.print("N") ; delay(100) ;      tft.print("G") ; delay(100) ;      tft.print(" -") ; delay(200) ;      tft.print(">") ; delay(100) ;      tft.print("v") ; delay(100) ;     tft.print("5(b)") ; delay(100) ;      tft.println("") ; delay(100) ;      tft.setTextColor(RED) ;      tft.print("-") ; delay(300) ;      tft.setTextColor(BLACK) ;      tft.print("C") ; delay(100) ;      tft.print("O") ; delay(100) ;      tft.print("D") ; delay(100) ;      tft.print("E") ; delay(100) ;      tft.print(".") ; delay(100) ;      tft.print(".") ; delay(100) ;      tft.print(".") ; delay(100) ;      tft.print(".") ; delay(200) ;      tft.print(".") ; delay(100) ;      tft.print("O") ; delay(100) ;     tft.print("K") ; delay(100) ;     tft.println("") ;     tft.setTextColor(GREEN) ;     tft.setTextSize(3) ;     tft.print("JUMP NOW") ; delay(100) ;
      delay(3000) ;
      tft.fillScreen(RED); delay(400);

      
//      tft.fillScreen(BLACK); delay(300);
//      tft.fillScreen(RED); delay(400);
//      tft.fillScreen(YELLOW); delay(400);
//      tft.fillScreen(GREEN); delay(600);
//      tft.fillScreen(BLUE); delay(500);
//      tft.fillScreen(MAGENTA); delay(400);
//      tft.fillScreen(BLACK); delay(100);

      Serial.println("\n\nJUMPING TO v5 SERVER(beta)") ;
      Serial.println("PUTTING SCREEN EQUALS 2001") ;
      Serial.println("NOW THE INDEXES IN SERAL WILL BE OF MINI VERSION INSTEAD OF GSM - ADD 200 WITH EVERY INDEX TO DEBUG") ;
      screen = 2001 ;
      setup();
      //      Back.drawButton(true);
      //      prog = 1 ;
      //      tft_firstscreentr = 1 ;
      //      screen = 111110 ;
      //      setup() ;
    }

  }

  if (screen == 2) {


    bool down = Touch_getXY();
    Ok.press(down && Ok.contains(pixel_x, pixel_y));
    Back.press(down && Back.contains(pixel_x, pixel_y));

    if ( counter[3] == 5 )
      tft.fillRect(10 , 110 + 60 + 20 + 60 + 20 + 60 + 20, 60, 60, RED);
    else
      tft.fillRect(10 , 110 + 60 + 20 + 60 + 20 + 60 + 20, 60, 60, GREEN);

    if (counter[2] == 5 )
      tft.fillRect(10 , 110 + 60 + 20 + 60 + 20, 60, 60, RED);
    else
      tft.fillRect(10 , 110 + 60 + 20 + 60 + 20, 60, 60, GREEN);

    if (counter[1] == 5 )
      tft.fillRect(10 , 110 + 60 + 20, 60, 60, RED);
    else
      tft.fillRect(10 , 110 + 60 + 20, 60, 60, GREEN);

    if (counter[0] == 5 )
      tft.fillRect(10 , 110, 60, 60, RED);
    else
      tft.fillRect(10 , 110, 60, 60, GREEN);


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
    if ( counter[0] != 5 )
      One.press(down && One.contains(pixel_x, pixel_y));
    if ( counter[1] != 5 )
      Two.press(down && Two.contains(pixel_x, pixel_y));
    if ( counter[2] != 5 )
      Three.press(down && Three.contains(pixel_x, pixel_y));
    if ( counter[3] != 5 )
      Four.press(down && Four.contains(pixel_x, pixel_y));

    if (One.justPressed()) {

      One.drawButton(true);

      Two.drawButton();

      Three.drawButton();

      Four.drawButton();
      temp1 = 0 ;
      temp2 = 9 ;
      temp3 = 9 ;
      temp4 = 9 ;
    }
    if (Two.justPressed()) {

      One.drawButton();

      Two.drawButton(true);

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

      One.drawButton();

      Two.drawButton();

      Three.drawButton(true);

      Four.drawButton();
      temp1 = 9 ;
      temp2 = 9 ;
      temp3 = 2 ;
      temp4 = 9 ;
    }
    if (Four.justPressed()) {

      One.drawButton();

      Two.drawButton();

      Three.drawButton();

      Four.drawButton(true);
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

      screen1() ;
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

      Serial.println("--- SERIAL-RECEIPT ---") ;
      Serial.println("") ;
      Serial.println("EPARK CORTEX S5") ;
      Serial.println("VEHICLE ENTRY") ;
      Serial.println("") ;
      Serial.print("PIN : ") ;
      Serial.print(c[i][counter[i]].number[0]);
      Serial.print(c[i][counter[i]].number[1]);
      Serial.print(c[i][counter[i]].number[2]);
      Serial.print(c[i][counter[i]].number[3]);
      Serial.print(c[i][counter[i]].number[4]);
      Serial.print(c[i][counter[i]].number[5]);
      Serial.print(c[i][counter[i]].number[6]);
      Serial.println("") ;
      Serial.print("FLOOR : ") ;
      if ( c[i][counter[i]].slot == 0 )
        Serial.print("GROUND FLOOR") ;
      else if ( c[i][counter[i]].slot == 1 )
        Serial.print("1st FLOOR") ;
      else if ( c[i][counter[i]].slot == 2 )
        Serial.print("2nd FLOOR") ;
      else if ( c[i][counter[i]].slot == 3 )
        Serial.print("3rd FLOOR") ;
      Serial.println("") ;
      Serial.print("TYPE : ") ;
      if ( c[i][counter[i]].type == 1 )
        Serial.print("BIKE") ;
      else if ( c[i][counter[i]].type == 2 )
        Serial.print("CAR") ;
      Serial.println("");
      Serial.print("ENTRY TIME : ");
      Serial.print(t.hour);
      Serial.print(":");
      Serial.print(t.min) ;
      Serial.print(":");
      Serial.print(t.sec);
      Serial.println("") ;
      Serial.print("DATE : ") ;
      Serial.print(t.mday) ;
      Serial.print("/");
      Serial.print(t.mon) ;
      Serial.print("/");
      Serial.print((t.year + 100));
      Serial.println("");
      Serial.println((char)26);

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
    //Serial.println(textfield);
    tft.setCursor(TEXT_X + 8, TEXT_Y + 14);
    tft.setTextColor(TEXT_TCOLOR, BLACK);
    tft.setTextSize(TEXT_TSIZE);
    tft.print(textfield);
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
        Serial.print("Pressing: ");  Serial.println(b);
        buttons[b].press(true);  // tell the button it is pressed
      } else {
        buttons[b].press(false);  // tell the button it is NOT pressed
      }
    }

    // now we can ask the buttons if their state has changed
    for (uint8_t b = 0; b < 15; b++) {
      if (buttons[b].justReleased()) {
        Serial.print("Released: ");  Serial.println(b);
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
          if ( textfield_i != TEXT_LEN ) {
            for ( k = 0 ; k < TEXT_LEN  ; k++)
              textfield[k] = ' ';
            textfield_i = 0 ;
            n = 0 ;
            screen4();
          } else {

            for ( iii = 0 ; iii < 4 ; iii++) {
              for ( jjj = 0 ; jjj < 5 ; jjj++) {
                if (c[iii][jjj].number[0] == textfield[0] && c[iii][jjj].number[1] == textfield[1] && c[iii][jjj].number[2] == textfield[2] && c[iii][jjj].number[3] == textfield[3] && c[iii][jjj].number[4] == textfield[4] && c[iii][jjj].number[5] == textfield[5] && c[iii][jjj].number[6] == textfield[6]) {

                  found_pin = 1 ;
                  break ;
                }
              }
            }
            if (found_pin == -1) {
              n = 1 ;
              screen4() ;
            } else if ( found_pin == 1) {
              for ( k = 0 ; k < TEXT_LEN  ; k++)
                textfield[k] = ' ';
              textfield_i = 0 ;
              n = 0 ;
              screen40() ;
            }
          }
        }
        delay(100); // UI debouncing
      }
    }
  }

  if ( screen == 991 ) {
    Serial.println(ph_textfield);
    tft.setCursor(TEXT_X + 8, TEXT_Y + 14);
    tft.setTextColor(TEXT_TCOLOR, BLACK);
    tft.setTextSize(TEXT_TSIZE);
    tft.print(ph_textfield);
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
        Serial.print("Pressing: ");  Serial.println(b);
        buttons[b].press(true);  // tell the button it is pressed
      } else {
        buttons[b].press(false);  // tell the button it is NOT pressed
      }
    }

    // now we can ask the buttons if their state has changed
    for (uint8_t b = 0; b < 15; b++) {
      if (buttons[b].justReleased()) {
        Serial.print("Released: ");  Serial.println(b);
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
        Serial.println(ph_textfield);
        tft.setCursor(TEXT_X + 8, TEXT_Y + 14);
        tft.setTextColor(TEXT_TCOLOR, BLACK);
        tft.setTextSize(TEXT_TSIZE);
        tft.print(ph_textfield);

        if (b == 2) {
          status(F("Back"));
          ph_n = 0 ;
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
    // update the current text field
    //Serial.println(textfieldr);
    tft.setCursor(TEXT_X + 8, TEXT_Y + 14);
    tft.setTextColor(TEXT_TCOLOR, BLACK);
    tft.setTextSize(TEXT_TSIZE);
    tft.print(textfieldr);
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
        Serial.print("Pressing: ");  Serial.println(b);
        buttons[b].press(true);  // tell the button it is pressed
      } else {
        buttons[b].press(false);  // tell the button it is NOT pressed
      }
    }

    // now we can ask the buttons if their state has changed
    for (uint8_t b = 0; b < 15; b++) {
      if (buttons[b].justReleased()) {
        Serial.print("Released: ");  Serial.println(b);
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
          if ( textfieldr_i != TEXT_LEN ) {
            for ( k = 0 ; k < TEXT_LEN  ; k++)
              textfieldr[k] = ' ';
            textfieldr_i = 0 ;

            mfound = 0 ;
            nr = 0 ;
            screen21();
          }
          else {
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
              if (c[i][j].number[0] == textfieldr[0] && c[i][j].number[1] == textfieldr[1] && c[i][j].number[2] == textfieldr[2] && c[i][j].number[3] == textfieldr[3] && c[i][j].number[4] == textfieldr[4] && c[i][j].number[5] == textfieldr[5] && c[i][j].number[6] == textfieldr[6]) {

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

  if (screen == 40) {
    bool down = Touch_getXY();
    Back.press(down && Back.contains(pixel_x, pixel_y));
    if (Back.justReleased())
      Back.drawButton();
    if (Back.justPressed()) {
      Back.drawButton(true);
      //      for ( k = 0 ; k < TEXT_LEN  ; k++)
      //        textfield[k] = ' ' ;
      //      textfield_i = 0 ;
      //      nr = 0 ;
      screen4() ;
    }
  }




/*[v5 - SERVER(b)]------------------------------------------------------------------------[ADD 200 WITH CONTROLLERS] - [IN VERY DEVELOPMENT STAGE]*/
  if (screen == 200145) {


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
      screen20045() ;
    }
    if (no.justPressed()) {
      no.drawButton(true);
      c[i][counter[i]].yes = 9 ;

      screen2005() ;
    }
  }

  if (screen == 2001) {
    buttonState = digitalRead(buttonPin);
    if (buttonState == LOW) {
      Serial.println("OWNER BUTTON PRESSED # SEND MESSAGE TO HARD CODED ONWER'S MOBILE NUMBER") ;
      /*----START SENDING THE MESSAGE BY CALLING A FUNCTION OR SOMETHING AND THEN RE-ROUTE THE FUNCTION TO SETUP-----*/
      /*-----MESSAGE------*/
      screen2008341() ;
      Serial.println("MESSAGE SENT NOW CONTINUE RUNNING LOOP FOR SCREEN 1") ;
    }
    bool down = Touch_getXY();
    one.press(down && one.contains(pixel_x, pixel_y));
    two.press(down && two.contains(pixel_x, pixel_y));
    Three.press(down && Three.contains(pixel_x, pixel_y));

    if (Three.justReleased())
      Three.drawButton();
    if (Three.justPressed()) {
      Three.drawButton(true);

      screen20031() ;
    }

    if (one.justReleased())
      one.drawButton();
    if (two.justReleased())
      two.drawButton();
    if (one.justPressed()) {
      one.drawButton(true);

      screen2003() ;
    }
    if (two.justPressed()) {
      two.drawButton(true);

      screen20021() ;
    }
  }

  if (screen == 2002) {


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
        screen2003() ;
      }
    }

    if (Back.justReleased())
      Back.drawButton();

    if (Back.justPressed()) {

      Back.drawButton(true);
      screen2001() ;
    }
  }

  if (screen == 20023) {

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
        screen2004() ;
      }

      else if (tempT1 == 0 && tempT2 == 2 ) {
        c[i][counter[i]].type = tempT2 ;
        c[i][counter[i]].slot = i ;
        screen2004() ;
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


      screen2003() ;
    }
  }

  if (screen == 2003 ) {

    bool down = Touch_getXY();
    Ok.press(down && Ok.contains(pixel_x, pixel_y));
    Back.press(down && Back.contains(pixel_x, pixel_y));
    if ( counter[0] != 5 )
      One.press(down && One.contains(pixel_x, pixel_y));
    if ( counter[1] != 5 )
      Two.press(down && Two.contains(pixel_x, pixel_y));
    if ( counter[2] != 5 )
      Three.press(down && Three.contains(pixel_x, pixel_y));
    if ( counter[3] != 5 )
      Four.press(down && Four.contains(pixel_x, pixel_y));

    if (One.justPressed()) {

      One.drawButton(true);

      Two.drawButton();

      Three.drawButton();

      Four.drawButton();
      temp1 = 0 ;
      temp2 = 9 ;
      temp3 = 9 ;
      temp4 = 9 ;
    }
    if (Two.justPressed()) {

      One.drawButton();

      Two.drawButton(true);

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

      One.drawButton();

      Two.drawButton();

      Three.drawButton(true);

      Four.drawButton();
      temp1 = 9 ;
      temp2 = 9 ;
      temp3 = 2 ;
      temp4 = 9 ;
    }
    if (Four.justPressed()) {

      One.drawButton();

      Two.drawButton();

      Three.drawButton();

      Four.drawButton(true);
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

        screen20023() ;
      }

      else if (temp1 == 9 && temp2 == 1 && temp3 == 9 && temp4 == 9 ) {
        i = 1 ;
        screen20023() ;
      }
      else if (temp1 == 9 && temp2 == 9 && temp3 == 2 && temp4 == 9 ) {
        i = 2 ;
        screen20023() ;
      }
      else if (temp1 == 9 && temp2 == 9 && temp3 == 9 && temp4 == 3 ) {
        i = 3 ;
        screen20023() ;
      }

    }
    if (Back.justPressed()) {
      Back.drawButton(true);
      temp1 = -1 ;
      temp2 = -1 ;
      temp3 = -1 ;
      temp4 = -1 ;

      i = -1 ;

      screen2001() ;
    }
  }

  if (screen == 2004) {

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

        screen200145() ;
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

      screen20023() ;
    }
    if (E.justReleased())
      E.drawButton();
    if (E.justPressed()) {
      E.drawButton(true);
      numpad200();
      n = 1 ;
    }
  }

  if (screen == 20045 ) {
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
        screen2001111() ;
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

      screen200145() ;
    }
    if (E.justReleased())
      E.drawButton();
    if (E.justPressed()) {
      E.drawButton(true);
      ph_numpad200();
      ph_n = 1 ;
    }
  }

  if (screen == 2005) {
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

      screen2001() ;
    }
  }

  if (screen == 2009) {
    //Serial.println(textfield);
    tft.setCursor(TEXT_X + 8, TEXT_Y + 14);
    tft.setTextColor(TEXT_TCOLOR, BLACK);
    tft.setTextSize(TEXT_TSIZE);
    tft.print(textfield);
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
        Serial.print("Pressing: ");  Serial.println(b);
        buttons[b].press(true);  // tell the button it is pressed
      } else {
        buttons[b].press(false);  // tell the button it is NOT pressed
      }
    }

    // now we can ask the buttons if their state has changed
    for (uint8_t b = 0; b < 15; b++) {
      if (buttons[b].justReleased()) {
        Serial.print("Released: ");  Serial.println(b);
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
          screen2004() ;
        }

        if (b == 0) {
          status(F("Ok"));
          if ( textfield_i != TEXT_LEN ) {
            for ( k = 0 ; k < TEXT_LEN  ; k++)
              textfield[k] = ' ';
            textfield_i = 0 ;
            n = 0 ;
            screen2004();
          } else {

            for ( iii = 0 ; iii < 4 ; iii++) {
              for ( jjj = 0 ; jjj < 5 ; jjj++) {
                if (c[iii][jjj].number[0] == textfield[0] && c[iii][jjj].number[1] == textfield[1] && c[iii][jjj].number[2] == textfield[2] && c[iii][jjj].number[3] == textfield[3] && c[iii][jjj].number[4] == textfield[4] && c[iii][jjj].number[5] == textfield[5] && c[iii][jjj].number[6] == textfield[6]) {

                  found_pin = 1 ;
                  break ;
                }
              }
            }
            if (found_pin == -1) {
              n = 1 ;
              screen2004() ;
            } else if ( found_pin == 1) {
              for ( k = 0 ; k < TEXT_LEN  ; k++)
                textfield[k] = ' ';
              textfield_i = 0 ;
              n = 0 ;
              screen20040() ;
            }
          }
        }
        delay(100); // UI debouncing
      }
    }
  }

  if ( screen == 200991 ) {
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
        Serial.print("Pressing: ");  Serial.println(b);
        buttons[b].press(true);  // tell the button it is pressed
      } else {
        buttons[b].press(false);  // tell the button it is NOT pressed
      }
    }

    // now we can ask the buttons if their state has changed
    for (uint8_t b = 0; b < 15; b++) {
      if (buttons[b].justReleased()) {
        Serial.print("Released: ");  Serial.println(b);
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
        Serial.println(ph_textfield);
        tft.setCursor(TEXT_X + 8, TEXT_Y + 14);
        tft.setTextColor(TEXT_TCOLOR, BLACK);
        tft.setTextSize(TEXT_TSIZE);
        tft.print(ph_textfield);

        if (b == 2) {
          status(F("Back"));
          ph_n = 0 ;
          for ( k = 0 ; k < ph_TEXT_LEN  ; k++) {
            ph_textfield[k] = ' ';

          }
          ph_textfield_i = 0 ;
          screen20045() ;
        }

        if (b == 0) {
          status(F("Ok"));
          if ( ph_textfield_i != 10 ) {
            for ( k = 0 ; k < ph_TEXT_LEN  ; k++)
              ph_textfield[k] = ' ';
            ph_textfield_i = 0 ;
            ph_n = 0 ;
            screen20045();
          } else {
            ph_n = 1 ;
            screen20045() ;
          }
        }
        delay(100); // UI debouncing
      }
    }
  }

  if (screen == 20091) {
    //Serial.println(textfieldr);
    tft.setCursor(TEXT_X + 8, TEXT_Y + 14);
    tft.setTextColor(TEXT_TCOLOR, BLACK);
    tft.setTextSize(TEXT_TSIZE);
    tft.print(textfieldr);
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
        Serial.print("Pressing: ");  Serial.println(b);
        buttons[b].press(true);  // tell the button it is pressed
      } else {
        buttons[b].press(false);  // tell the button it is NOT pressed
      }
    }

    // now we can ask the buttons if their state has changed
    for (uint8_t b = 0; b < 15; b++) {
      if (buttons[b].justReleased()) {
        Serial.print("Released: ");  Serial.println(b);
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
        tft.setTextColor(TEXT_TCOLOR, BLACK);
        tft.setTextSize(TEXT_TSIZE);
        tft.print(textfieldr);

        if (b == 2) {
          mfound = 0 ;

          nr = 0 ;
          for ( k = 0 ; k < TEXT_LEN  ; k++)
            textfieldr[k] = ' ' ;

          textfieldr_i = 0 ;
          screen20021() ;
        }

        if (b == 0) {
          if ( textfieldr_i != 4 ) {
            for ( k = 0 ; k < TEXT_LEN  ; k++)
              textfieldr[k] = ' ';
            textfieldr_i = 0 ;

            mfound = 0 ;
            nr = 0 ;
            screen20021();
          } else {
            mfound = 1 ;
            nr = 1 ;
            screen20021() ;
          }
        }
        delay(100); // UI debouncing
      }
    }
  }

  if (screen == 20021) {
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
            screen20022() ;

          } else if (found == 0) {
            for ( k = 0 ; k < TEXT_LEN  ; k++)
              textfieldr[k] = ' ' ;
            textfieldr_i = 0 ;
            screen20022_0() ;
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
      screen2001() ;
    }
    if (E.justReleased())
      E.drawButton();
    if (E.justPressed()) {
      E.drawButton(true);
      numpad2001() ;
      nr = 1;
    }
  }

  if (screen == 20022) {
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
      screen2001();
    }
  }

  if (screen == 200220) {
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
      screen20021() ;
    }
  }

  if (screen == 20031) {
    bool down = Touch_getXY();

    Ok.press(down && Ok.contains(pixel_x, pixel_y));
    Back.press(down && Back.contains(pixel_x, pixel_y));
    E.press(down && E.contains(pixel_x, pixel_y));


    if (Back.justReleased())
      Back.drawButton();

    if ( nr200 == 1 ) {
      if (Ok.justReleased())
        Ok.drawButton();
      if (Ok.justPressed()) {
        Ok.drawButton(true);



        if (mfound200 == 1) {
          for ( i = 0 ; i < 4 ; i++) {
            for ( j = 0 ; j < 5 ; j++) {
              if (c[i][j].otp[0] == textfieldr200[0] && c[i][j].otp[1] == textfieldr200[1] && c[i][j].otp[2] == textfieldr200[2] && c[i][j].otp[3] == textfieldr200[3]) {

                found200 = 1 ;
                i_temp200 = i ;
                j_temp200 = j ;
                break ;
              }
            }
          }

          if (found200 == 1) {
            //            counter[i_temp200] = counter[i_temp200] - 1 ;
            //            found = 0 ;
            screen2003() ;

          } else if (found200 == 0) {
            for ( k = 0 ; k < TEXT_LEN200  ; k++)
              textfieldr200[k] = ' ' ;
            textfieldr_i200 = 0 ;
            screen20022_03() ;
          }
        }
      }
    }
    if (Back.justPressed()) {
      Back.drawButton(true);

      for ( k = 0 ; k < TEXT_LEN200  ; k++)
        textfieldr200[k] = ' ' ;
      textfieldr_i200 = 0 ;
      nr200 = 0 ;
      screen2001() ;
    }
    if (E.justReleased())
      E.drawButton();
    if (E.justPressed()) {
      E.drawButton(true);
      numpad20013() ;
      nr200 = 1;
    }
  }

  if (screen == 200913) {
    //Serial.println(textfieldr);
    tft.setCursor(TEXT_X + 8, TEXT_Y + 14);
    tft.setTextColor(TEXT_TCOLOR, BLACK);
    tft.setTextSize(TEXT_TSIZE);
    tft.print(textfieldr200);

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
        Serial.print("Pressing: ");  Serial.println(b);
        buttons[b].press(true);  // tell the button it is pressed
      } else {
        buttons[b].press(false);  // tell the button it is NOT pressed
      }
    }

    // now we can ask the buttons if their state has changed
    for (uint8_t b = 0; b < 15; b++) {
      if (buttons[b].justReleased()) {
        Serial.print("Released: ");  Serial.println(b);
        buttons[b].drawButton();  // draw normal
      }

      if (buttons[b].justPressed()) {
        buttons[b].drawButton(true);  // draw invert!

        // if a numberpad button, append the relevant # to the textfieldr
        if (b >= 3) {
          if (textfieldr_i200 < TEXT_LEN200) {
            textfieldr200[textfieldr_i200] = buttonlabels[b][0];
            textfieldr_i200++;
            textfieldr200[textfieldr_i200] = 0; // zero terminate
          }
        }

        // clr button! delete char
        if (b == 1) {

          textfieldr200[textfieldr_i200] = 0;
          if (textfieldr200 > 0) {
            textfieldr_i200--;
            textfieldr200[textfieldr_i200] = ' ';
          }
        }

        // update the current text field
        Serial.println(textfieldr200);
        tft.setCursor(TEXT_X + 8, TEXT_Y + 14);
        tft.setTextColor(TEXT_TCOLOR, BLACK);
        tft.setTextSize(TEXT_TSIZE);
        tft.print(textfieldr200);

        if (b == 2) {
          mfound200 = 0 ;

          nr200 = 0 ;
          for ( k = 0 ; k < TEXT_LEN200  ; k++)
            textfieldr200[k] = ' ' ;

          textfieldr_i200 = 0 ;
          screen20031() ;
        }

        if (b == 0) {
          if ( textfieldr_i200 != 4 ) {
            for ( k = 0 ; k < TEXT_LEN200  ; k++)
              textfieldr200[k] = ' ';
            textfieldr_i200 = 0 ;

            mfound200 = 0 ;
            nr200 = 0 ;
            screen20031();
          } else {
            mfound200 = 1 ;
            nr200 = 1 ;
            screen20031() ;
          }
        }
        delay(100); // UI debouncing
      }
    }
  }

  if (screen == 2002203) {
    bool down = Touch_getXY();
    Back.press(down && Back.contains(pixel_x, pixel_y));
    if (Back.justReleased())
      Back.drawButton();
    if (Back.justPressed()) {
      Back.drawButton(true);
      for ( k = 0 ; k < TEXT_LEN200  ; k++)
        textfieldr200[k] = ' ' ;
      textfieldr_i200 = 0 ;
      nr200 = 0 ;
      screen20031() ;
    }
  }

  if (screen == 20040) {
    bool down = Touch_getXY();
    Back.press(down && Back.contains(pixel_x, pixel_y));
    if (Back.justReleased())
      Back.drawButton();
    if (Back.justPressed()) {
      Back.drawButton(true);
      //      for ( k = 0 ; k < TEXT_LEN  ; k++)
      //        textfield[k] = ' ' ;
      //      textfield_i = 0 ;
      //      nr = 0 ;
      screen2004() ;
    }
  }



/*[v1 - MINI]---------------------------------------------------------------------------[ADD 200 WITH THE CONTROLLERS]*/
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

      screen1003() ;
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
    if ( counter[0] != 5 )
      One.press(down && One.contains(pixel_x, pixel_y));
    if ( counter[1] != 5 )
      Two.press(down && Two.contains(pixel_x, pixel_y));
    if ( counter[2] != 5 )
      Three.press(down && Three.contains(pixel_x, pixel_y));
    if ( counter[3] != 5 )
      Four.press(down && Four.contains(pixel_x, pixel_y));

    if (One.justPressed()) {

      One.drawButton(true);

      Two.drawButton();

      Three.drawButton();

      Four.drawButton();
      temp1 = 0 ;
      temp2 = 9 ;
      temp3 = 9 ;
      temp4 = 9 ;
    }
    if (Two.justPressed()) {

      One.drawButton();

      Two.drawButton(true);

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

      One.drawButton();

      Two.drawButton();

      Three.drawButton(true);

      Four.drawButton();
      temp1 = 9 ;
      temp2 = 9 ;
      temp3 = 2 ;
      temp4 = 9 ;
    }
    if (Four.justPressed()) {

      One.drawButton();

      Two.drawButton();

      Three.drawButton();

      Four.drawButton(true);
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

      screen1001() ;
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
    //Serial.println(textfield);
    tft.setCursor(TEXT_X + 8, TEXT_Y + 14);
    tft.setTextColor(TEXT_TCOLOR, BLACK);
    tft.setTextSize(TEXT_TSIZE);
    tft.print(textfield);
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
        Serial.print("Pressing: ");  Serial.println(b);
        buttons[b].press(true);  // tell the button it is pressed
      } else {
        buttons[b].press(false);  // tell the button it is NOT pressed
      }
    }

    // now we can ask the buttons if their state has changed
    for (uint8_t b = 0; b < 15; b++) {
      if (buttons[b].justReleased()) {
        Serial.print("Released: ");  Serial.println(b);
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
          if ( textfield_i != TEXT_LEN ) {
            for ( k = 0 ; k < TEXT_LEN  ; k++)
              textfield[k] = ' ';
            textfield_i = 0 ;
            n = 0 ;
            screen1004();
          } else {

            for ( iii = 0 ; iii < 4 ; iii++) {
              for ( jjj = 0 ; jjj < 5 ; jjj++) {
                if (c[iii][jjj].number[0] == textfield[0] && c[iii][jjj].number[1] == textfield[1] && c[iii][jjj].number[2] == textfield[2] && c[iii][jjj].number[3] == textfield[3] && c[iii][jjj].number[4] == textfield[4] && c[iii][jjj].number[5] == textfield[5] && c[iii][jjj].number[6] == textfield[6]) {

                  found_pin = 1 ;
                  break ;
                }
              }
            }
            if (found_pin == -1) {
              n = 1 ;
              screen1004() ;
            } else if ( found_pin == 1) {
              for ( k = 0 ; k < TEXT_LEN  ; k++)
                textfield[k] = ' ';
              textfield_i = 0 ;
              n = 0 ;
              screen10040() ;
            }
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
    //Serial.println(textfieldr);
    tft.setCursor(TEXT_X + 8, TEXT_Y + 14);
    tft.setTextColor(TEXT_TCOLOR, BLACK);
    tft.setTextSize(TEXT_TSIZE);
    tft.print(textfieldr);
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
        Serial.print("Pressing: ");  Serial.println(b);
        buttons[b].press(true);  // tell the button it is pressed
      } else {
        buttons[b].press(false);  // tell the button it is NOT pressed
      }
    }

    // now we can ask the buttons if their state has changed
    for (uint8_t b = 0; b < 15; b++) {
      if (buttons[b].justReleased()) {
        Serial.print("Released: ");  Serial.println(b);
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

  if (screen == 10040) {
    bool down = Touch_getXY();
    Back.press(down && Back.contains(pixel_x, pixel_y));
    if (Back.justReleased())
      Back.drawButton();
    if (Back.justPressed()) {
      Back.drawButton(true);
      //      for ( k = 0 ; k < TEXT_LEN  ; k++)
      //        textfield[k] = ' ' ;
      //      textfield_i = 0 ;
      //      nr = 0 ;
      screen1004() ;
    }
  }



}

#define BMPIMAGEOFFSET 54
#define BUFFPIXEL      20

uint16_t read16(File & f) {
  uint16_t result;         // read little-endian
  f.read((uint8_t*)&result, sizeof(result));
  return result;
}

uint32_t read32(File & f) {
  uint32_t result;
  f.read((uint8_t*)&result, sizeof(result));
  return result;
}

uint8_t showBMP(char *nm, int x, int y) // FUNCTION TO READ THE BMP FILE FROM SD CARD
{
  File bmpFile;
  int bmpWidth, bmpHeight;    // W+H in pixels
  uint8_t bmpDepth;           // Bit depth (currently must be 24, 16, 8, 4, 1)
  uint32_t bmpImageoffset;    // Start of image data in file
  uint32_t rowSize;           // Not always = bmpWidth; may have padding
  uint8_t sdbuffer[3 * BUFFPIXEL];    // pixel in buffer (R+G+B per pixel)
  uint16_t lcdbuffer[(1 << PALETTEDEPTH) + BUFFPIXEL], *palette = NULL;
  uint8_t bitmask, bitshift;
  boolean flip = true;        // BMP is stored bottom-to-top
  int w, h, row, col, lcdbufsiz = (1 << PALETTEDEPTH) + BUFFPIXEL, buffidx;
  uint32_t pos;               // seek position
  boolean is565 = false;      //

  uint16_t bmpID;
  uint16_t n;                 // blocks read
  uint8_t ret;

  if ((x >= tft.width()) || (y >= tft.height()))
    return 1;               // off screen

  bmpFile = SD.open(nm);      // Parse BMP header
  bmpID = read16(bmpFile);    // BMP signature
  (void) read32(bmpFile);     // Read & ignore file size
  (void) read32(bmpFile);     // Read & ignore creator bytes
  bmpImageoffset = read32(bmpFile);       // Start of image data
  (void) read32(bmpFile);     // Read & ignore DIB header size
  bmpWidth = read32(bmpFile);
  bmpHeight = read32(bmpFile);
  n = read16(bmpFile);        // # planes -- must be '1'
  bmpDepth = read16(bmpFile); // bits per pixel
  pos = read32(bmpFile);      // format
  if (bmpID != 0x4D42) ret = 2; // bad ID
  else if (n != 1) ret = 3;   // too many planes
  else if (pos != 0 && pos != 3) ret = 4; // format: 0 = uncompressed, 3 = 565
  else if (bmpDepth < 16 && bmpDepth > PALETTEDEPTH) ret = 5; // palette
  else {
    bool first = true;
    is565 = (pos == 3);               // ?already in 16-bit format
    // BMP rows are padded (if needed) to 4-byte boundary
    rowSize = (bmpWidth * bmpDepth / 8 + 3) & ~3;
    if (bmpHeight < 0) {              // If negative, image is in top-down order.
      bmpHeight = -bmpHeight;
      flip = false;
    }

    w = bmpWidth;
    h = bmpHeight;
    if ((x + w) >= tft.width())       // Crop area to be loaded
      w = tft.width() - x;
    if ((y + h) >= tft.height())      //
      h = tft.height() - y;

    if (bmpDepth <= PALETTEDEPTH) {   // these modes have separate palette
      bmpFile.seek(BMPIMAGEOFFSET); //palette is always @ 54
      bitmask = 0xFF;
      if (bmpDepth < 8)
        bitmask >>= bmpDepth;
      bitshift = 8 - bmpDepth;
      n = 1 << bmpDepth;
      lcdbufsiz -= n;
      palette = lcdbuffer + lcdbufsiz;
      for (col = 0; col < n; col++) {
        pos = read32(bmpFile);    //map palette to 5-6-5
        palette[col] = ((pos & 0x0000F8) >> 3) | ((pos & 0x00FC00) >> 5) | ((pos & 0xF80000) >> 8);
      }
    }

    // Set TFT address window to clipped image bounds
    tft.setAddrWindow(x, y, x + w - 1, y + h - 1);
    for (row = 0; row < h; row++) { // For each scanline...
      // Seek to start of scan line.  It might seem labor-
      // intensive to be doing this on every line, but this
      // method covers a lot of gritty details like cropping
      // and scanline padding.  Also, the seek only takes
      // place if the file position actually needs to change
      // (avoids a lot of cluster math in SD library).
      uint8_t r, g, b, *sdptr;
      int lcdidx, lcdleft;
      if (flip)   // Bitmap is stored bottom-to-top order (normal BMP)
        pos = bmpImageoffset + (bmpHeight - 1 - row) * rowSize;
      else        // Bitmap is stored top-to-bottom
        pos = bmpImageoffset + row * rowSize;
      if (bmpFile.position() != pos) { // Need seek?
        bmpFile.seek(pos);
        buffidx = sizeof(sdbuffer); // Force buffer reload
      }

      for (col = 0; col < w; ) {  //pixels in row
        lcdleft = w - col;
        if (lcdleft > lcdbufsiz) lcdleft = lcdbufsiz;
        for (lcdidx = 0; lcdidx < lcdleft; lcdidx++) { // buffer at a time
          uint16_t color;
          // Time to read more pixel data?
          if (buffidx >= sizeof(sdbuffer)) { // Indeed
            bmpFile.read(sdbuffer, sizeof(sdbuffer));
            buffidx = 0; // Set index to beginning
            r = 0;
          }
          switch (bmpDepth) {          // Convert pixel from BMP to TFT format
            case 24:
              b = sdbuffer[buffidx++];
              g = sdbuffer[buffidx++];
              r = sdbuffer[buffidx++];
              color = tft.color565(r, g, b);
              break;
            case 16:
              b = sdbuffer[buffidx++];
              r = sdbuffer[buffidx++];
              if (is565)
                color = (r << 8) | (b);
              else
                color = (r << 9) | ((b & 0xE0) << 1) | (b & 0x1F);
              break;
            case 1:
            case 4:
            case 8:
              if (r == 0)
                b = sdbuffer[buffidx++], r = 8;
              color = palette[(b >> bitshift) & bitmask];
              r -= bmpDepth;
              b <<= bmpDepth;
              break;
          }
          lcdbuffer[lcdidx] = color;

        }
        tft.pushColors(lcdbuffer, lcdidx, first);
        first = false;
        col += lcdidx;
      }           // end cols
    }               // end rows
    tft.setAddrWindow(0, 0, tft.width() - 1, tft.height() - 1); //restore full screen
    ret = 0;        // good render
  }
  bmpFile.close();
  return (ret);
}

void receiveEvent(int howMany) { // TO RECEIVE DATA FROM ESP8266
  while (0 < Wire.available())
  {
    char c = Wire.read();      /* receive byte as a character */
    Serial.print(c);           /* print the character */
  }
  Serial.println();             /* to newline */
}

char ccount[4] ; // CHAR ARRAY FOR I2C
int ij ; // COUNTER FOR I2C PROTOCOL

void requestEvent() {
  //Serial.println("SENDING DATA VIA I2C BUS TO ESP8266") ;
  for (  ij = 0 ; ij < 4 ; ij++) {
    ccount[ij] = (char(counter[ij] + 48)) ;
  }
  Wire.write(ccount) ; // WRITING THE WHOLE CHARACTER ARRAY OF CCOUNT

}

