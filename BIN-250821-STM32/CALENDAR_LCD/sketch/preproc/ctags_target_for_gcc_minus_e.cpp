# 1 "C:\\Users\\Subhankar Karmakar\\Documents\\Arduino_old\\CALENDAR_LCD\\CALENDAR_LCD.ino"
# 1 "C:\\Users\\Subhankar Karmakar\\Documents\\Arduino_old\\CALENDAR_LCD\\CALENDAR_LCD.ino"
/*   CALENDAR IN LCD [ DRIVER ILI9481 ] 
     BY - SUBHANKAR KARMAKAR
     TIME - 3 : 38 PM 
     28 SEPTEMBER , THURSDAY , 2017
     ASANSOL ENGINEERING COLLEGE 
     ELECTRONICS AND COMMUNICATION DEPT. */

# 9 "C:\\Users\\Subhankar Karmakar\\Documents\\Arduino_old\\CALENDAR_LCD\\CALENDAR_LCD.ino" 2
# 10 "C:\\Users\\Subhankar Karmakar\\Documents\\Arduino_old\\CALENDAR_LCD\\CALENDAR_LCD.ino" 2





MCUFRIEND_kbv tft; /* CREATION OF OBJECT FOR TFT */
# 35 "C:\\Users\\Subhankar Karmakar\\Documents\\Arduino_old\\CALENDAR_LCD\\CALENDAR_LCD.ino"
# 36 "C:\\Users\\Subhankar Karmakar\\Documents\\Arduino_old\\CALENDAR_LCD\\CALENDAR_LCD.ino" 2

# 36 "C:\\Users\\Subhankar Karmakar\\Documents\\Arduino_old\\CALENDAR_LCD\\CALENDAR_LCD.ino"
char mystr[5];
void setup()
{
  Serial2.begin(9600);
  tft.reset();
  tft.begin(0x9481);
  tft.setRotation(-1);

  tft.fillScreen(0xFFE0);
  delay(1000);

  tft.fillRect(7,17,75,5,0x0000);
  tft.setCursor(97,10);
  tft.setTextColor(0x0000);
  tft.setTextSize(3);
  tft.print("CALENDAR");
  tft.fillRect(250,17,220,5,0x0000);

  tft.setCursor(75,50);
  tft.setTextColor(0x0000);
  tft.setTextSize(2);
  tft.print("Thursday - 28 September 2017");

  tft.fillRect(10,75,120,25,0x0000);
  tft.setCursor(22,80);
  tft.setTextColor((((255&0xF8)<<8)|((255&0xFC)<<3)|(255>>3)));
  tft.print("CALENDAR");

  tft.fillRect(45,98,430,2,0x0000);
  tft.fillRect(473,98,2,185,0x0000);
  tft.fillRect(45,98,2,185,0x0000);
  tft.fillRect(45,283,430,2,0x0000);
  tft.setCursor(65,110);
  tft.setTextColor(0x0000);
  tft.setTextSize(2);
  tft.print("SUN  MON  TUE  WED  THU  FRI  SAT") ;
  tft.fillRect(45,130,430,1,0x0000);

  tft.setCursor(65,140);
  tft.setTextColor(0x0000);
  tft.setTextSize(2);
  tft.print("                          1    2 ") ;
  tft.setCursor(65,170);
  tft.setTextColor(0x0000);
  tft.setTextSize(2);
  tft.print(" 3    4    5    6    7    8    9 ") ;
  tft.setCursor(68,200);
  tft.setTextColor(0x0000);
  tft.setTextSize(2);
  tft.print("10   11   12   13   14   15   16 ") ;
  tft.setCursor(57,230);
  tft.setTextColor(0x0000);
  tft.setTextSize(2);
  tft.print(" 17   18   19   20   21   22   23") ;
  tft.setCursor(57,260);
  tft.setTextColor(0x0000);
  tft.setTextSize(2);
  tft.print(" 24   25   26   27        29   30") ;
  tft.fillRect(300,255,40,25,0x0000);
  tft.setCursor(310,260);
  tft.setTextColor((((255&0xF8)<<8)|((255&0xFC)<<3)|(255>>3)));
  tft.setTextSize(2);
  tft.print("28") ;

}

void loop()
{

}
