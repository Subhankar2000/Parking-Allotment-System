# 1 "C:\\Users\\Subhankar Karmakar\\Documents\\Arduino_old\\TIME_LCD\\TIME_LCD.ino"
# 1 "C:\\Users\\Subhankar Karmakar\\Documents\\Arduino_old\\TIME_LCD\\TIME_LCD.ino"
# 2 "C:\\Users\\Subhankar Karmakar\\Documents\\Arduino_old\\TIME_LCD\\TIME_LCD.ino" 2
# 3 "C:\\Users\\Subhankar Karmakar\\Documents\\Arduino_old\\TIME_LCD\\TIME_LCD.ino" 2
# 4 "C:\\Users\\Subhankar Karmakar\\Documents\\Arduino_old\\TIME_LCD\\TIME_LCD.ino" 2
# 19 "C:\\Users\\Subhankar Karmakar\\Documents\\Arduino_old\\TIME_LCD\\TIME_LCD.ino"
MCUFRIEND_kbv tft; /* CREATION OF OBJECT FOR TFT */
uint8_t hh, mm, ss;
uint8_t conv2d(const char* p)
{
    uint8_t v = 0;
    if ('0' <= *p && *p <= '9') v = *p - '0';
    return 10 * v + *++p - '0';
}
void setup() {
   Serial2.begin(9600);
  tft.reset();
  tft.begin(0x9481);
  tft.setRotation(1);

  tft.fillScreen(0x0000);
  delay(1000);
  tft.setCursor(40,100);
  tft.setTextColor(0xFFFF);
  tft.setTextSize(3);
  tft.print("28 Sep 2017 - Thursday");

  /*tft.setCursor(220,100);
  tft.setTextColor(GREEN);
  tft.setTextSize(4);
  tft.print("Everyone");*/

  /*tft.fillRect(80,200, 321, 60, GREEN);

  tft.setCursor(135,215);
  tft.setTextColor(BLACK);
  tft.setTextSize(4);
  tft.print("Subhankar");

  tft.drawRect(0,0,480,320,WHITE);
  delay(1000);*/
 tft.setCursor(110,170);
  tft.setTextColor(0xFFFF);
  tft.setTextSize(3);
  tft.print("Time ");

    tft.setFont(&FreeSans9pt7b);

    hh = conv2d("20:25:59");
    mm = conv2d("20:25:59" + 3);
    ss = conv2d("20:25:59" + 6);
}

void loop()
{
  //tft.fillRect(80,200,321,60,BLACK);


  /*tft.print(hh);
  tft.print(" : ") ;
  tft.print(mm);
  tft.print(" : " );
tft.print(ss);
tft.print("  AM") ;*/
while (1) {tft.fillRect(150,150,321,60,0x0000);
  tft.setCursor(150,170);
  tft.setTextColor(0xFFFF);
  tft.setTextSize(3);}}
     /*   if (++ss > 59) {
            ss = 0;
            mm++;
            if (mm > 59) {
                mm = 0;
                hh++;
                if (hh > 23) hh = 0;
            }
        }
        char buf[20];
        /*sprintf(buf, "%02d : %02d : %02d", hh, mm, ss);tft.print(buf);delay(1000);}
  */
