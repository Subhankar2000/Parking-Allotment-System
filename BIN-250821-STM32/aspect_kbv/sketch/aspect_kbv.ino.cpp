#include <Arduino.h>
#line 1 "D:\\Arduino-STM32-ARM-M4\\portable\\sketchbook\\libraries\\MCUFRIEND_kbv\\examples\\aspect_kbv\\aspect_kbv.ino"
#line 1 "D:\\Arduino-STM32-ARM-M4\\portable\\sketchbook\\libraries\\MCUFRIEND_kbv\\examples\\aspect_kbv\\aspect_kbv.ino"
#include <Adafruit_GFX.h> // Hardware-specific library
#include <MCUFRIEND_kbv.h>
MCUFRIEND_kbv tft;

#line 5 "D:\\Arduino-STM32-ARM-M4\\portable\\sketchbook\\libraries\\MCUFRIEND_kbv\\examples\\aspect_kbv\\aspect_kbv.ino"
void setup();
#line 21 "D:\\Arduino-STM32-ARM-M4\\portable\\sketchbook\\libraries\\MCUFRIEND_kbv\\examples\\aspect_kbv\\aspect_kbv.ino"
void loop();
#line 5 "D:\\Arduino-STM32-ARM-M4\\portable\\sketchbook\\libraries\\MCUFRIEND_kbv\\examples\\aspect_kbv\\aspect_kbv.ino"
void setup()
{
    // put your setup code here, to run once:
    Serial.begin(9600);
    tft.reset();
    uint16_t identifier = tft.readID();
    Serial.print("ID = 0x");
    Serial.println(identifier, HEX);
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

