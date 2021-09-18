# 1 "D:\\Arduino-STM32-ARM-M4\\portable\\sketchbook\\libraries\\MCUFRIEND_kbv\\examples\\aspect_kbv\\aspect_kbv.ino"
# 1 "D:\\Arduino-STM32-ARM-M4\\portable\\sketchbook\\libraries\\MCUFRIEND_kbv\\examples\\aspect_kbv\\aspect_kbv.ino"
# 2 "D:\\Arduino-STM32-ARM-M4\\portable\\sketchbook\\libraries\\MCUFRIEND_kbv\\examples\\aspect_kbv\\aspect_kbv.ino" 2
# 3 "D:\\Arduino-STM32-ARM-M4\\portable\\sketchbook\\libraries\\MCUFRIEND_kbv\\examples\\aspect_kbv\\aspect_kbv.ino" 2
MCUFRIEND_kbv tft;

void setup()
{
    // put your setup code here, to run once:
    Serial2.begin(9600);
    tft.reset();
    uint16_t identifier = tft.readID();
    Serial2.print("ID = 0x");
    Serial2.println(identifier, 16);
    if (identifier == 0xEFEF) identifier = 0x9486;
    tft.begin(identifier);
    //  tft.fillScreen(BLACK);
}

char *msg[] = { "PORTRAIT", "LANDSCAPE", "PORTRAIT_REV", "LANDSCAPE_REV" };
uint8_t aspect;

void loop()
{
    // put your main code here, to run repeatedly:
    uint16_t x = 50, y = 100;
    tft.setRotation(aspect);
    tft.fillScreen(0x0000);
    tft.setCursor(0, 0);
    tft.setTextSize(2);
    tft.println(msg[aspect]);
    tft.setCursor(x, y);
    tft.println("[x=" + String(x) + ",y=" + String(y) + "]");
    delay(5000);
    tft.println("INVERT ON");
    tft.invertDisplay(true);
    delay(1000);
    tft.invertDisplay(false);
    tft.println("INVERT OFF");
    delay(1000);
    if (++aspect >= 4) aspect = 0;
}
