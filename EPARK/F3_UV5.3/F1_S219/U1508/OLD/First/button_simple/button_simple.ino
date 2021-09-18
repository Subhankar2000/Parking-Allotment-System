#include <Adafruit_GFX.h>
#include <MCUFRIEND_kbv.h>
MCUFRIEND_kbv tft;
#include <TouchScreen.h>
#define MINPRESSURE 1
#define MAXPRESSURE 1000

// ALL Touch panels and wiring is DIFFERENT
// copy-paste results from TouchScreen_Calibr_native.ino
const int XP=8,XM=A2,YP=A3,YM=9; //320x480 ID=0x9481
const int TS_LEFT=155,TS_RT=885,TS_TOP=931,TS_BOT=100;

TouchScreen ts = TouchScreen(XP, YP, XM, YM, 300);

Adafruit_GFX_Button one_btn, two_btn;

int pixel_x, pixel_y;     //Touch_getXY() updates global vars
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

void setup(void)
{
    Serial.begin(9600);
    uint16_t ID = tft.readID();
    Serial.print("TFT ID = 0x");
    Serial.println(ID, HEX);
    Serial.println("Calibrate for your Touch Panel");
    if (ID == 0xD3D3) ID = 0x9486; // write-only shield
    tft.begin(ID);
    tft.setRotation(0);            //PORTRAIT
    tft.fillScreen(BLACK);
    one_btn.initButton(&tft,  60, 200, 100, 40, WHITE, YELLOW, BLACK, "1", 2);
    two_btn.initButton(&tft,  60, 250, 100, 40, WHITE, YELLOW, BLACK, "2", 2);
    one_btn.drawButton(false);
    two_btn.drawButton(false);
    tft.fillRect(40, 80, 160, 80, RED);
}

/* two buttons are quite simple
 */
void loop(void)
{
    bool down = Touch_getXY();
    one_btn.press(down && one_btn.contains(pixel_x, pixel_y));
    two_btn.press(down && two_btn.contains(pixel_x, pixel_y));
    if (one_btn.justReleased())
        one_btn.drawButton();
    if (two_btn.justReleased())
        two_btn.drawButton();
    if (one_btn.justPressed()) {
        one_btn.drawButton(true);
        tft.fillRect(40, 80, 160, 80, GREEN);
    }
    if (two_btn.justPressed()) {
        two_btn.drawButton(true);
        tft.fillRect(40, 80, 160, 80, RED);
    }
}



