# 1 "C:\\Users\\SUBHAN~2\\AppData\\Local\\Temp\\arduino_modified_sketch_748615\\TouchScreen_Calibr_native.ino"
# 1 "C:\\Users\\SUBHAN~2\\AppData\\Local\\Temp\\arduino_modified_sketch_748615\\TouchScreen_Calibr_native.ino"
// TouchScreen_Calibr_native for MCUFRIEND UNO Display Shields
// adapted by David Prentice
// for Adafruit's <TouchScreen.h> Resistive Touch Screen Library
// from Henning Karlsen's original UTouch_Calibration program.
// Many Thanks.







# 14 "C:\\Users\\SUBHAN~2\\AppData\\Local\\Temp\\arduino_modified_sketch_748615\\TouchScreen_Calibr_native.ino" 2
# 15 "C:\\Users\\SUBHAN~2\\AppData\\Local\\Temp\\arduino_modified_sketch_748615\\TouchScreen_Calibr_native.ino" 2
MCUFRIEND_kbv tft;
HardwareSerial Serial6(36, 37);
//#include <TouchScreen.h>         //Adafruit Library
//TouchScreen ts(XP, YP, XM, YM, 300);   //re-initialised after diagnose
//TSPoint tp;                            //global point
const int XP = 8, XM = A2, YP = A3, YM = 9; /* FOR TOUCH INPUT*/
const int TS_LEFT = 155, TS_RT = 885, TS_TOP = 931, TS_BOT = 100; /*CALIBERATED VALUES*/





# 28 "C:\\Users\\SUBHAN~2\\AppData\\Local\\Temp\\arduino_modified_sketch_748615\\TouchScreen_Calibr_native.ino" 2
TouchScreen_kbv ts(XP, YP, XM, YM, 300); //re-initialised after diagnose
TSPoint_kbv tp; //global point






void readResistiveTouch(void)
{
  tp = ts.getPoint();
  pinMode(YP, 0x1); //restore shared pins
  pinMode(XM, 0x1);
  digitalWrite(YP, 0x1); //because TFT control pins
  digitalWrite(XM, 0x1);
  //    Serial6.println("tp.x=" + String(tp.x) + ", tp.y=" + String(tp.y) + ", tp.z =" + String(tp.z));
}

bool ISPRESSED(void)
{
  // .kbv this was too sensitive !!
  // now touch has to be stable for 50ms
  int count = 0;
  bool state, oldstate;
  while (count < 10) {
    readResistiveTouch();
    state = tp.z > 200; //ADJUST THIS VALUE TO SUIT YOUR SCREEN e.g. 20 ... 250
    if (state == oldstate) count++;
    else count = 0;
    oldstate = state;
    delay(5);
  }
  return oldstate;
}

uint32_t cx, cy, cz;
uint32_t rx[8], ry[8];
int32_t clx, crx, cty, cby;
float px, py;
int dispx, dispy, text_y_center, swapxy;
uint32_t calx, caly, cals;

char *Aval(int pin)
{
  static char buf[2][10], cnt;
  cnt = !cnt;



  sprintf(buf[cnt], "A%d", pin - A0);

  return buf[cnt];
}

void showpins(int A, int D, int value, const char *msg)
{
  char buf[40];
  sprintf(buf, "%s (%s, D%d) = %d", msg, Aval(A), D, value);
  Serial6.println(buf);
}

boolean diagnose_pins()
{
  int i, j, value, Apins[2], Dpins[2], Values[2], found = 0;
  Serial6.println((reinterpret_cast<const __FlashStringHelper *>(("Making all control and bus pins INPUT_PULLUP"))));
  Serial6.println((reinterpret_cast<const __FlashStringHelper *>(("Typical 30k Analog pullup with corresponding pin"))));
  Serial6.println((reinterpret_cast<const __FlashStringHelper *>(("would read low when digital is written LOW"))));
  Serial6.println((reinterpret_cast<const __FlashStringHelper *>(("e.g. reads ~25 for 300R X direction"))));
  Serial6.println((reinterpret_cast<const __FlashStringHelper *>(("e.g. reads ~30 for 500R Y direction"))));
  Serial6.println((reinterpret_cast<const __FlashStringHelper *>((""))));
  for (i = A0; i < A5; i++) pinMode(i, 0x2);
  for (i = 2; i < 10; i++) pinMode(i, 0x2);
  for (i = A0; i < A4; i++) {
    pinMode(i, 0x2);
    for (j = 5; j < 10; j++) {
      pinMode(j, 0x1);
      digitalWrite(j, 0x0);
      value = analogRead(i); // ignore first reading
      value = analogRead(i);
      if (value < 100 && value > 0) {
        showpins(i, j, value, "Testing :");
        if (found < 2) {
          Apins[found] = i;
          Dpins[found] = j;
          Values[found] = value;
        }
        found++;
      }
      pinMode(j, 0x2);
    }
    pinMode(i, 0x2);
  }
  if (found == 2) {
    Serial6.println((reinterpret_cast<const __FlashStringHelper *>(("Diagnosing as:-"))));
    int idx = Values[0] < Values[1];
    for (i = 0; i < 2; i++) {
      showpins(Apins[i], Dpins[i], Values[i],
               (Values[i] < Values[!i]) ? "XM,XP: " : "YP,YM: ");
    }
    //        XM = Apins[!idx]; XP = Dpins[!idx]; YP = Apins[idx]; YM = Dpins[idx];
    //        ts = TouchScreen(XP, YP, XM, YM, 300);    //re-initialise with pins
    ts = TouchScreen_kbv(XP, YP, XM, YM, 300); //re-initialise with pins
    return true; //success
  }
  Serial6.println((reinterpret_cast<const __FlashStringHelper *>(("BROKEN TOUCHSCREEN"))));
  return false;
}

void setup()
{
  Serial6.begin(9600);
  Serial6.println("TouchScreen.h GFX Calibration");
  bool ret = true;

  Serial6.println((reinterpret_cast<const __FlashStringHelper *>(("Not possible to diagnose Touch pins on ARM or ESP32"))));



  uint16_t ID = tft.readID();
  Serial6.print("ID = 0x");
  Serial6.println(ID, 16);
  tft.begin(ID);
  tft.setRotation(0);
  dispx = tft.width();
  dispy = tft.height();
  text_y_center = (dispy / 2) - 6;
  if (ret == false) {
    centerprint("BROKEN TOUCHSCREEN", text_y_center);
    while (true); //just tread water
  }
}

void loop()
{
  startup();

  tft.fillScreen(0x0000);
  drawCrossHair(dispx - 11, 10, 0x8410);
  drawCrossHair(dispx / 2, 10, 0x8410);
  drawCrossHair(10, 10, 0x8410);
  drawCrossHair(dispx - 11, dispy / 2, 0x8410);
  drawCrossHair(10, dispy / 2, 0x8410);
  drawCrossHair(dispx - 11, dispy - 11, 0x8410);
  drawCrossHair(dispx / 2, dispy - 11, 0x8410);
  drawCrossHair(10, dispy - 11, 0x8410);
  centerprint("***********", text_y_center - 12);
  centerprint("***********", text_y_center + 12);

  calibrate(10, 10, 0, (reinterpret_cast<const __FlashStringHelper *>((" LEFT, TOP, Pressure"))));
  calibrate(10, dispy / 2, 1, (reinterpret_cast<const __FlashStringHelper *>((" LEFT, MIDH, Pressure"))));
  calibrate(10, dispy - 11, 2, (reinterpret_cast<const __FlashStringHelper *>((" LEFT, BOT, Pressure"))));
  calibrate(dispx / 2, 10, 3, (reinterpret_cast<const __FlashStringHelper *>((" MIDW, TOP, Pressure"))));
  calibrate(dispx / 2, dispy - 11, 4, (reinterpret_cast<const __FlashStringHelper *>((" MIDW, BOT, Pressure"))));
  calibrate(dispx - 11, 10, 5, (reinterpret_cast<const __FlashStringHelper *>((" RT, TOP, Pressure"))));
  calibrate(dispx - 11, dispy / 2, 6, (reinterpret_cast<const __FlashStringHelper *>((" RT, MIDH, Pressure"))));
  calibrate(dispx - 11, dispy - 11, 7, (reinterpret_cast<const __FlashStringHelper *>((" RT, BOT, Pressure"))));

  cals = (long(dispx - 1) << 12) + (dispy - 1);
  if (0 == 0) swapxy = rx[2] - rx[0];
  else swapxy = ry[2] - ry[0];
  swapxy = (swapxy < -500 || swapxy > 500);
  if ((0 == 0) ^ (swapxy != 0)) {
    clx = (rx[0] + rx[1] + rx[2]) / 3;
    crx = (rx[5] + rx[6] + rx[7]) / 3;
    cty = (ry[0] + ry[3] + ry[5]) / 3;
    cby = (ry[2] + ry[4] + ry[7]) / 3;
  } else {
    clx = (ry[0] + ry[1] + ry[2]) / 3;
    crx = (ry[5] + ry[6] + ry[7]) / 3;
    cty = (rx[0] + rx[3] + rx[5]) / 3;
    cby = (rx[2] + rx[4] + rx[7]) / 3;
  }
  px = float(crx - clx) / (dispx - 20);
  py = float(cby - cty) / (dispy - 20);
  //  px = 0;
  clx -= px * 10;
  crx += px * 10;
  cty -= py * 10;
  cby += py * 10;

  calx = (long(clx) << 14) + long(crx);
  caly = (long(cty) << 14) + long(cby);
  if (swapxy)
    cals |= (1L << 31);

  report(); // report results
  while (true) {} // tread water
}

void readCoordinates()
{
  int iter = 5000;
  int failcount = 0;
  int cnt = 0;
  uint32_t tx = 0;
  uint32_t ty = 0;
  boolean OK = false;

  while (OK == false)
  {
    centerprint("*  PRESS  *", text_y_center);
    while (ISPRESSED() == false) {}
    centerprint("*  HOLD!  *", text_y_center);
    cnt = 0;
    iter = 400;
    do
    {
      readResistiveTouch();
      if (tp.z > 20)
      {
        tx += tp.x;
        ty += tp.y;
        cnt++;
      }
      else
        failcount++;
    } while ((cnt < iter) && (failcount < 10000));
    if (cnt >= iter)
    {
      OK = true;
    }
    else
    {
      tx = 0;
      ty = 0;
      cnt = 0;
    }
    if (failcount >= 10000)
      fail();
  }

  cx = tx / iter;
  cy = ty / iter;
  cz = tp.z;
}

void calibrate(int x, int y, int i, String msg)
{
  drawCrossHair(x, y, 0xFFFF);
  readCoordinates();
  centerprint("* RELEASE *", text_y_center);
  drawCrossHair(x, y, 0x8410);
  rx[i] = cx;
  ry[i] = cy;
  Serial6.print("\r\ncx="); Serial6.print(cx);
  Serial6.print(" cy="); Serial6.print(cy);
  Serial6.print(" cz="); Serial6.print(cz);
  if (msg) Serial6.print(msg);
  while (ISPRESSED() == true) {}
}

void report()
{
  uint16_t TS_LEFT, TS_RT, TS_TOP, TS_BOT, TS_WID, TS_HT, TS_SWAP;
  int16_t tmp;
  char buf[60];
  centertitle("TouchScreen.h GFX Calibration");

  tft.println((reinterpret_cast<const __FlashStringHelper *>(("To use the new calibration"))));
  tft.println((reinterpret_cast<const __FlashStringHelper *>(("settings you must map the values"))));
  tft.println((reinterpret_cast<const __FlashStringHelper *>(("from Point p = ts.getPoint() e.g. "))));
  tft.println((reinterpret_cast<const __FlashStringHelper *>(("x = map(p.x, LEFT, RT, 0, tft.width());"))));
  tft.println((reinterpret_cast<const __FlashStringHelper *>(("y = map(p.y, TOP, BOT, 0, tft.height());"))));
  tft.println((reinterpret_cast<const __FlashStringHelper *>(("swap p.x and p.y if diff ORIENTATION"))));

  //.kbv show human values
  TS_LEFT = (calx >> 14) & 0x3FFF;
  TS_RT = (calx >> 0) & 0x3FFF;
  TS_TOP = (caly >> 14) & 0x3FFF;
  TS_BOT = (caly >> 0) & 0x3FFF;
  TS_WID = ((cals >> 12) & 0x0FFF) + 1;
  TS_HT = ((cals >> 0) & 0x0FFF) + 1;
  TS_SWAP = (cals >> 31);
  if (0 == 1) { //always show PORTRAIT first
    tmp = TS_LEFT, TS_LEFT = TS_BOT, TS_BOT = TS_RT, TS_RT = TS_TOP, TS_TOP = tmp;
    tmp = TS_WID, TS_WID = TS_HT, TS_HT = tmp;
  }
  tft.setCursor(0, 120);
  Serial6.println("");
  sprintf(buf, "MCUFRIEND_kbv ID=0x%04X  %d x %d",
          tft.readID(), TS_WID, TS_HT);
  tft.println(buf);
  Serial6.println(buf);
  sprintf(buf, "\nconst int XP=%d,XM=A%d,YP=A%d,YM=%d; //%dx%d ID=0x%04X",
          XP, XM - A0, YP - A0, YM, TS_WID, TS_HT, tft.readID());
  Serial6.println(buf);
  sprintf(buf, "const int TS_LEFT=%d,TS_RT=%d,TS_TOP=%d,TS_BOT=%d;",
          TS_LEFT, TS_RT, TS_TOP, TS_BOT);
  Serial6.println(buf);
  sprintf(buf, "PORTRAIT CALIBRATION     %d x %d", TS_WID, TS_HT);
  tft.println("");
  tft.println(buf);
  Serial6.println(buf);
  sprintf(buf, "x = map(p.x, LEFT=%d, RT=%d, 0, %d)", TS_LEFT, TS_RT, TS_WID);
  tft.println(buf);
  Serial6.println(buf);
  sprintf(buf, "y = map(p.y, TOP=%d, BOT=%d, 0, %d)", TS_TOP, TS_BOT, TS_HT);
  tft.println(buf);
  Serial6.println(buf);
  sprintf(buf, "Touch Pin Wiring XP=%d XM=%s YP=%s YM=%d",
          XP, Aval(XM), Aval(YP), YM);
  tft.println("");
  tft.println(buf);
  Serial6.println(buf);

  tmp = TS_LEFT, TS_LEFT = TS_TOP, TS_TOP = TS_RT, TS_RT = TS_BOT, TS_BOT = tmp;
  tmp = TS_WID, TS_WID = TS_HT, TS_HT = tmp;

  sprintf(buf, "LANDSCAPE CALIBRATION    %d x %d", TS_WID, TS_HT);
  tft.println("");
  tft.println(buf);
  Serial6.println(buf);
  sprintf(buf, "x = map(p.y, LEFT=%d, RT=%d, 0, %d)", TS_LEFT, TS_RT, TS_WID);
  tft.println(buf);
  Serial6.println(buf);
  sprintf(buf, "y = map(p.x, TOP=%d, BOT=%d, 0, %d)", TS_TOP, TS_BOT, TS_HT);
  tft.println(buf);
  Serial6.println(buf);
}

void drawCrossHair(int x, int y, uint16_t color)
{
  tft.drawRect(x - 10, y - 10, 20, 20, color);
  tft.drawLine(x - 5, y, x + 5, y, color);
  tft.drawLine(x, y - 5, x, y + 5, color);
}

void centerprint(const char *s, int y)
{
  int len = strlen(s) * 6;
  tft.setTextColor(0xFFFF, 0xF800);
  tft.setCursor((dispx - len) / 2, y);
  tft.print(s);
}

void centertitle(const char *s)
{
  tft.fillScreen(0x0000);
  tft.fillRect(0, 0, dispx, 14, 0xF800);
  tft.fillRect(0, 14, dispx, 1, 0xFFFF);
  centerprint(s, 1);
  tft.setCursor(0, 30);
  tft.setTextColor(0xFFFF, 0x0000);
}

void startup()
{
  centertitle("TouchScreen.h GFX Calibration");

  tft.println((reinterpret_cast<const __FlashStringHelper *>(("#define NUMSAMPLES 3 in Library\n"))));
  tft.println((reinterpret_cast<const __FlashStringHelper *>(("Use a stylus or something"))));
  tft.println((reinterpret_cast<const __FlashStringHelper *>(("similar to touch as close"))));
  tft.println((reinterpret_cast<const __FlashStringHelper *>(("to the center of the"))));
  tft.println((reinterpret_cast<const __FlashStringHelper *>(("highlighted crosshair as"))));
  tft.println((reinterpret_cast<const __FlashStringHelper *>(("possible. Keep as still as"))));
  tft.println((reinterpret_cast<const __FlashStringHelper *>(("possible and keep holding"))));
  tft.println((reinterpret_cast<const __FlashStringHelper *>(("until the highlight is"))));
  tft.println((reinterpret_cast<const __FlashStringHelper *>(("removed. Repeat for all"))));
  tft.println((reinterpret_cast<const __FlashStringHelper *>(("crosshairs in sequence.\n"))));
  tft.println((reinterpret_cast<const __FlashStringHelper *>(("Report can be pasted from Serial\n"))));
  tft.println((reinterpret_cast<const __FlashStringHelper *>(("Touch screen to continue"))));

  while (ISPRESSED() == false) {}
  while (ISPRESSED() == true) {}
  //    waitForTouch();
}

void fail()
{
  centertitle("Touch Calibration FAILED");

  tft.println((reinterpret_cast<const __FlashStringHelper *>(("Unable to read the position"))));
  tft.println((reinterpret_cast<const __FlashStringHelper *>(("of the press. This is a"))));
  tft.println((reinterpret_cast<const __FlashStringHelper *>(("hardware issue and can"))));
  tft.println((reinterpret_cast<const __FlashStringHelper *>(("not be corrected in"))));
  tft.println((reinterpret_cast<const __FlashStringHelper *>(("software."))));
  tft.println((reinterpret_cast<const __FlashStringHelper *>(("check XP, XM pins with a multimeter"))));
  tft.println((reinterpret_cast<const __FlashStringHelper *>(("check YP, YM pins with a multimeter"))));
  tft.println((reinterpret_cast<const __FlashStringHelper *>(("should be about 300 ohms"))));

  while (true) {};
}
