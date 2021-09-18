# 1 "C:\\Users\\SUBHAN~2\\AppData\\Local\\Temp\\arduino_modified_sketch_193545\\Touch_shield_new.ino"
# 1 "C:\\Users\\SUBHAN~2\\AppData\\Local\\Temp\\arduino_modified_sketch_193545\\Touch_shield_new.ino"
// the regular Adafruit "TouchScreen.h" library only works on AVRs

// different mcufriend shields have Touchscreen on different pins
// and rotation.
// Run the TouchScreen_Calibr_native sketch for calibration of your shield

# 8 "C:\\Users\\SUBHAN~2\\AppData\\Local\\Temp\\arduino_modified_sketch_193545\\Touch_shield_new.ino" 2
MCUFRIEND_kbv tft; // hard-wired for UNO shields anyway.
# 10 "C:\\Users\\SUBHAN~2\\AppData\\Local\\Temp\\arduino_modified_sketch_193545\\Touch_shield_new.ino" 2
HardwareSerial Serial6(36, 37);
char *name = "Please Calibrate."; //edit name of shield
const int XP = 8, XM = A2, YP = A3, YM = 9; /* FOR TOUCH INPUT*/
const int TS_LEFT = 155, TS_RT = 885, TS_TOP = 931, TS_BOT = 100; /*CALIBERATED VALUES*/




TouchScreen ts = TouchScreen(XP, YP, XM, YM, 300); /*TOUCH INPUT INITIALIZATION*/
TSPoint tp;


int16_t BOXSIZE;
int16_t PENRADIUS = 1;
uint16_t ID, oldcolor, currentcolor;
uint8_t Orientation = 0; //PORTRAIT

// Assign human-readable names to some common 16-bit color values:
# 37 "C:\\Users\\SUBHAN~2\\AppData\\Local\\Temp\\arduino_modified_sketch_193545\\Touch_shield_new.ino"
void show_Serial(void)
{
    Serial6.println((reinterpret_cast<const __FlashStringHelper *>(("Most Touch Screens use pins 6, 7, A1, A2"))));
    Serial6.println((reinterpret_cast<const __FlashStringHelper *>(("But they can be in ANY order"))));
    Serial6.println((reinterpret_cast<const __FlashStringHelper *>(("e.g. right to left or bottom to top"))));
    Serial6.println((reinterpret_cast<const __FlashStringHelper *>(("or wrong direction"))));
    Serial6.println((reinterpret_cast<const __FlashStringHelper *>(("Edit name and calibration statements\n"))));
    Serial6.println(name);
    Serial6.print((reinterpret_cast<const __FlashStringHelper *>(("ID=0x"))));
    Serial6.println(ID, 16);
    Serial6.println("Screen is " + String(tft.width()) + "x" + String(tft.height()));
    Serial6.println("Calibration is: ");
    Serial6.println("LEFT = " + String(TS_LEFT) + " RT  = " + String(TS_RT));
    Serial6.println("TOP  = " + String(TS_TOP) + " BOT = " + String(TS_BOT));
    Serial6.println("Wiring is always PORTRAIT");
    Serial6.println("YP=" + String(YP) + " XM=" + String(XM));
    Serial6.println("YM=" + String(YM) + " XP=" + String(XP));
}

void show_tft(void)
{
    tft.setCursor(0, 0);
    tft.setTextSize(1);
    tft.print((reinterpret_cast<const __FlashStringHelper *>(("ID=0x"))));
    tft.println(ID, 16);
    tft.println("Screen is " + String(tft.width()) + "x" + String(tft.height()));
    tft.println("");
    tft.setTextSize(2);
    tft.println(name);
    tft.setTextSize(1);
    tft.println("PORTRAIT Values:");
    tft.println("LEFT = " + String(TS_LEFT) + " RT  = " + String(TS_RT));
    tft.println("TOP  = " + String(TS_TOP) + " BOT = " + String(TS_BOT));
    tft.println("\nWiring is: ");
    tft.println("YP=" + String(YP) + " XM=" + String(XM));
    tft.println("YM=" + String(YM) + " XP=" + String(XP));
    tft.setTextSize(2);
    tft.setTextColor(0xF800);
    tft.setCursor((tft.width() - 48) / 2, (tft.height() * 2) / 4);
    tft.print("EXIT");
    tft.setTextColor(0xFFE0, 0x0000);
    tft.setCursor(0, (tft.height() * 6) / 8);
    tft.print("Touch screen for loc");
    while (1) {
        tp = ts.getPoint();
        pinMode(XM, 0x1);
        pinMode(YP, 0x1);
        if (tp.z < 1 || tp.z > 1000) continue;
        if (tp.x > 450 && tp.x < 570 && tp.y > 450 && tp.y < 570) break;
        tft.setCursor(0, (tft.height() * 3) / 4);
        tft.print("tp.x=" + String(tp.x) + " tp.y=" + String(tp.y) + "   ");
    }
}


void setup(void)
{
    uint16_t tmp;

    tft.reset();
    ID = tft.readID();
    tft.begin(ID);
    Serial6.begin(9600);
    show_Serial();
    tft.setRotation(Orientation);
    tft.fillScreen(0x0000);
    show_tft();

    BOXSIZE = tft.width() / 6;
    tft.fillScreen(0x0000);

    tft.fillRect(0, 0, BOXSIZE, BOXSIZE, 0xF800);
    tft.fillRect(BOXSIZE, 0, BOXSIZE, BOXSIZE, 0xFFE0);
    tft.fillRect(BOXSIZE * 2, 0, BOXSIZE, BOXSIZE, 0x07E0);
    tft.fillRect(BOXSIZE * 3, 0, BOXSIZE, BOXSIZE, 0x07FF);
    tft.fillRect(BOXSIZE * 4, 0, BOXSIZE, BOXSIZE, 0x001F);
    tft.fillRect(BOXSIZE * 5, 0, BOXSIZE, BOXSIZE, 0xF81F);

    tft.drawRect(0, 0, BOXSIZE, BOXSIZE, 0xFFFF);
    currentcolor = 0xF800;
    delay(1000);
}

void loop()
{
    uint16_t xpos, ypos; //screen coordinates
    tp = ts.getPoint(); //tp.x, tp.y are ADC values

    // if sharing pins, you'll need to fix the directions of the touchscreen pins
    pinMode(XM, 0x1);
    pinMode(YP, 0x1);
    // we have some minimum pressure we consider 'valid'
    // pressure of 0 means no pressing!

    if (tp.z > 1 && tp.z < 1000) {
        // most mcufriend have touch (with icons) that extends below the TFT
        // screens without icons need to reserve a space for "erase"
        // scale the ADC values from ts.getPoint() to screen values e.g. 0-239
        //
        // Calibration is true for PORTRAIT. tp.y is always long dimension 
        // map to your current pixel orientation
        switch (Orientation) {
            case 0:
                xpos = map(tp.x, TS_LEFT, TS_RT, 0, tft.width());
                ypos = map(tp.y, TS_TOP, TS_BOT, 0, tft.height());
                break;
            case 1:
                xpos = map(tp.y, TS_TOP, TS_BOT, 0, tft.width());
                ypos = map(tp.x, TS_RT, TS_LEFT, 0, tft.height());
                break;
            case 2:
                xpos = map(tp.x, TS_RT, TS_LEFT, 0, tft.width());
                ypos = map(tp.y, TS_BOT, TS_TOP, 0, tft.height());
                break;
            case 3:
                xpos = map(tp.y, TS_BOT, TS_TOP, 0, tft.width());
                ypos = map(tp.y, TS_LEFT, TS_RT, 0, tft.height());
                break;
        }

        // are we in top color box area ?
        if (ypos < BOXSIZE) { //draw white border on selected color box
            oldcolor = currentcolor;

            if (xpos < BOXSIZE) {
                currentcolor = 0xF800;
                tft.drawRect(0, 0, BOXSIZE, BOXSIZE, 0xFFFF);
            } else if (xpos < BOXSIZE * 2) {
                currentcolor = 0xFFE0;
                tft.drawRect(BOXSIZE, 0, BOXSIZE, BOXSIZE, 0xFFFF);
            } else if (xpos < BOXSIZE * 3) {
                currentcolor = 0x07E0;
                tft.drawRect(BOXSIZE * 2, 0, BOXSIZE, BOXSIZE, 0xFFFF);
            } else if (xpos < BOXSIZE * 4) {
                currentcolor = 0x07FF;
                tft.drawRect(BOXSIZE * 3, 0, BOXSIZE, BOXSIZE, 0xFFFF);
            } else if (xpos < BOXSIZE * 5) {
                currentcolor = 0x001F;
                tft.drawRect(BOXSIZE * 4, 0, BOXSIZE, BOXSIZE, 0xFFFF);
            } else if (xpos < BOXSIZE * 6) {
                currentcolor = 0xF81F;
                tft.drawRect(BOXSIZE * 5, 0, BOXSIZE, BOXSIZE, 0xFFFF);
            }

            if (oldcolor != currentcolor) { //rub out the previous white border
                if (oldcolor == 0xF800) tft.fillRect(0, 0, BOXSIZE, BOXSIZE, 0xF800);
                if (oldcolor == 0xFFE0) tft.fillRect(BOXSIZE, 0, BOXSIZE, BOXSIZE, 0xFFE0);
                if (oldcolor == 0x07E0) tft.fillRect(BOXSIZE * 2, 0, BOXSIZE, BOXSIZE, 0x07E0);
                if (oldcolor == 0x07FF) tft.fillRect(BOXSIZE * 3, 0, BOXSIZE, BOXSIZE, 0x07FF);
                if (oldcolor == 0x001F) tft.fillRect(BOXSIZE * 4, 0, BOXSIZE, BOXSIZE, 0x001F);
                if (oldcolor == 0xF81F) tft.fillRect(BOXSIZE * 5, 0, BOXSIZE, BOXSIZE, 0xF81F);
            }
        }
        // are we in drawing area ?
        if (((ypos - PENRADIUS) > BOXSIZE) && ((ypos + PENRADIUS) < tft.height())) {
            tft.fillCircle(xpos, ypos, PENRADIUS, currentcolor);
        }
        // are we in erase area ?
        // Plain Touch panels use bottom 10 pixels e.g. > h - 10
        // Touch panels with icon area e.g. > h - 0
        if (ypos > tft.height() - 10) {
            // press the bottom of the screen to erase
            tft.fillRect(0, BOXSIZE, tft.width(), tft.height() - BOXSIZE, 0x0000);
        }
    }
}
