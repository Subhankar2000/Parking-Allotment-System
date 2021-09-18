# 1 "C:\\Users\\SUBHAN~2\\AppData\\Local\\Temp\\arduino_modified_sketch_448279\\button_simple.ino"
# 1 "C:\\Users\\SUBHAN~2\\AppData\\Local\\Temp\\arduino_modified_sketch_448279\\button_simple.ino"


# 4 "C:\\Users\\SUBHAN~2\\AppData\\Local\\Temp\\arduino_modified_sketch_448279\\button_simple.ino" 2
# 5 "C:\\Users\\SUBHAN~2\\AppData\\Local\\Temp\\arduino_modified_sketch_448279\\button_simple.ino" 2
MCUFRIEND_kbv tft;
# 7 "C:\\Users\\SUBHAN~2\\AppData\\Local\\Temp\\arduino_modified_sketch_448279\\button_simple.ino" 2


HardwareSerial Serial6(36, 37);
// ALL Touch panels and wiring is DIFFERENT
// copy-paste results from TouchScreen_Calibr_native.ino
const int XP = 8, XM = A2, YP = A3, YM = 9; /* FOR TOUCH INPUT*/
const int TS_LEFT = 155, TS_RT = 885, TS_TOP = 931, TS_BOT = 100; /*CALIBERATED VALUES*/

TouchScreen ts = TouchScreen(XP, YP, XM, YM, 300); /*TOUCH INPUT INITIALIZATION*/

Adafruit_GFX_Button on_btn, off_btn;

int pixel_x, pixel_y; //Touch_getXY() updates global vars
bool Touch_getXY(void)
{
    TSPoint p = ts.getPoint();
    pinMode(YP, 0x1); //restore shared pins
    pinMode(XM, 0x1);
    digitalWrite(YP, 0x1); //because TFT control pins
    digitalWrite(XM, 0x1);
    bool pressed = (p.z > 200 && p.z < 1000);
    if (pressed) {
        pixel_x = map(p.x, TS_LEFT, TS_RT, 0, tft.width()); //.kbv makes sense to me
        pixel_y = map(p.y, TS_TOP, TS_BOT, 0, tft.height());
    }
    return pressed;
}
# 44 "C:\\Users\\SUBHAN~2\\AppData\\Local\\Temp\\arduino_modified_sketch_448279\\button_simple.ino"
void setup(void)
{
    Serial6.begin(9600);
    uint16_t ID = tft.readID();
    Serial6.print("TFT ID = 0x");
    Serial6.println(ID, 16);
    Serial6.println("Calibrate for your Touch Panel");
    if (ID == 0xD3D3) ID = 0x9486; // write-only shield
    tft.begin(ID);
    tft.setRotation(0); //PORTRAIT
    tft.fillScreen(0x0000);
    on_btn.initButton(&tft, 60, 200, 100, 40, 0xFFFF, 0x07FF, 0x0000, "ON", 2);
    off_btn.initButton(&tft, 180, 200, 100, 40, 0xFFFF, 0x07FF, 0x0000, "OFF", 2);
    on_btn.drawButton(false);
    off_btn.drawButton(false);
    tft.fillRect(40, 80, 160, 80, 0xF800);
}

/* two buttons are quite simple
 */
void loop(void)
{
    bool down = Touch_getXY();
    on_btn.press(down && on_btn.contains(pixel_x, pixel_y));
    off_btn.press(down && off_btn.contains(pixel_x, pixel_y));
    if (on_btn.justReleased())
        on_btn.drawButton();
    if (off_btn.justReleased())
        off_btn.drawButton();
    if (on_btn.justPressed()) {
        on_btn.drawButton(true);
        tft.fillRect(40, 80, 160, 80, 0x07E0);
    }
    if (off_btn.justPressed()) {
        off_btn.drawButton(true);
        tft.fillRect(40, 80, 160, 80, 0xF800);
    }
}
# 1 "C:\\Users\\SUBHAN~2\\AppData\\Local\\Temp\\arduino_modified_sketch_448279\\button_list.ino"
/* an alternative approach.   swap the #if 1 / 0 values to try it
 * 
 */
