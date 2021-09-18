# 1 "C:\\Users\\Subhankar Karmakar\\Documents\\Arduino_old\\TIME_NEW\\TIME_NEW.ino"
# 1 "C:\\Users\\Subhankar Karmakar\\Documents\\Arduino_old\\TIME_NEW\\TIME_NEW.ino"
/*   MAGENTA
     TIME AND CALENDAR DISPLAYED IN LCD 
     BY - SUBHANKAR KARMAKAR
     ASANSOL ENGINEERING COLLEGE 
     ELECTRONICS AND COMMUNICATION DE{PT. */

# 8 "C:\\Users\\Subhankar Karmakar\\Documents\\Arduino_old\\TIME_NEW\\TIME_NEW.ino" 2
# 9 "C:\\Users\\Subhankar Karmakar\\Documents\\Arduino_old\\TIME_NEW\\TIME_NEW.ino" 2
# 10 "C:\\Users\\Subhankar Karmakar\\Documents\\Arduino_old\\TIME_NEW\\TIME_NEW.ino" 2





MCUFRIEND_kbv tft; /* CREATION OF OBJECT FOR TFT */
# 35 "C:\\Users\\Subhankar Karmakar\\Documents\\Arduino_old\\TIME_NEW\\TIME_NEW.ino"
# 36 "C:\\Users\\Subhankar Karmakar\\Documents\\Arduino_old\\TIME_NEW\\TIME_NEW.ino" 2


# 37 "C:\\Users\\Subhankar Karmakar\\Documents\\Arduino_old\\TIME_NEW\\TIME_NEW.ino"
uint16_t ID;
uint8_t hh, mm, ss;

uint8_t conv2d(const char* p)
{
    uint8_t v = 0;
    if ('0' <= *p && *p <= '9') v = *p - '0';
    return 10 * v + *++p - '0';
}

void setup()
{
  Serial2.begin(9600);
  tft.reset();
  tft.begin(0x9481);
  tft.setRotation(1);

  tft.fillScreen(0xF81F);
  delay(1000);

  tft.fillRect(7,17,75,5,0x0000);
  tft.setCursor(97,10);
  tft.setTextColor(0x0000);
  tft.setTextSize(3);
  tft.print("CALENDAR + CLOCK");
  tft.fillRect(395,17,80,5,0x0000);

  tft.setCursor(75,50);
  tft.setTextColor(0x0000);
  tft.setTextSize(2);
  tft.print("Thursday - 28 September 2017");

  tft.fillRect(10,75,120,25,0x0000);
  tft.setCursor(22,80);
  tft.setTextColor(0xF81F);
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
  tft.setTextColor(0xF81F);
  tft.setTextSize(2);
  tft.print("28") ;
  tft.fillRect(80,290,350,27,0x0000);
  tft.setCursor(87,295);
  tft.setTextColor(0xF81F);
  tft.setTextSize(2);
  tft.print("24 HOUR TIME") ;
  tft.fillRect(245,290,110,1,0x0000);
  tft.fillRect(355,290,1,25,0x0000);
  tft.fillRect(245,315,110,1,0x0000);

    tft.setFont(&FreeSans9pt7b);

    hh = conv2d("20:27:41");
    mm = conv2d("20:27:41" + 3);
    ss = conv2d("20:27:41" + 6);
}

void loop()
{ while (1)
  {
    tft.fillRect(246,291,150,24,0xF81F);
    tft.setCursor(250,296);
    tft.setTextColor(0x0000);
    tft.setTextSize(2);

    delay(50);
    if (++ss > 59) {
            ss = 0;
            mm++;
            if (mm > 59) {
                mm = 0;
                hh++;
                if (hh > 23) hh = 0;
            }
        }
    char buf[20];
    sprintf(buf, "%02d : %02d : %02d", hh, mm, ss);
    tft.print(buf);

delay(50);}

}
