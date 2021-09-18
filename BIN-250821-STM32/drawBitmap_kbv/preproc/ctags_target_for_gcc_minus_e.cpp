# 1 "C:\\Users\\SUBHAN~2\\AppData\\Local\\Temp\\arduino_modified_sketch_789063\\drawBitmap_kbv.ino"
# 1 "C:\\Users\\SUBHAN~2\\AppData\\Local\\Temp\\arduino_modified_sketch_789063\\drawBitmap_kbv.ino"
# 2 "C:\\Users\\SUBHAN~2\\AppData\\Local\\Temp\\arduino_modified_sketch_789063\\drawBitmap_kbv.ino" 2
MCUFRIEND_kbv tft;
HardwareSerial Serial6(36, 37);


# 7 "C:\\Users\\SUBHAN~2\\AppData\\Local\\Temp\\arduino_modified_sketch_789063\\drawBitmap_kbv.ino" 2
# 8 "C:\\Users\\SUBHAN~2\\AppData\\Local\\Temp\\arduino_modified_sketch_789063\\drawBitmap_kbv.ino" 2
# 20 "C:\\Users\\SUBHAN~2\\AppData\\Local\\Temp\\arduino_modified_sketch_789063\\drawBitmap_kbv.ino"
void setup()
{
    Serial6.begin(9600);
    uint16_t ID = tft.readID();

    Serial6.print((reinterpret_cast<const __FlashStringHelper *>(("ID = 0x"))));
    Serial6.println(ID, 16);

    Serial6.println((reinterpret_cast<const __FlashStringHelper *>(("GFX drawBitmap() plots one mono pixel at a time"))));
    Serial6.println((reinterpret_cast<const __FlashStringHelper *>(("it defaults to transparent plotting"))));
    Serial6.println((reinterpret_cast<const __FlashStringHelper *>(("unless you specify foreground and background colours"))));
    Serial6.println((reinterpret_cast<const __FlashStringHelper *>(("it can plot a monochrome bitmap from Flash or SRAM"))));

    Serial6.println((reinterpret_cast<const __FlashStringHelper *>((""))));
    Serial6.println((reinterpret_cast<const __FlashStringHelper *>(("GFX drawGrayscaleBitmap() is not relevant for OLED, TFT"))));
    Serial6.println((reinterpret_cast<const __FlashStringHelper *>(("GFX drawRGBBitmap() plots one colour pixel at a time"))));
    Serial6.println((reinterpret_cast<const __FlashStringHelper *>(("from Flash or SRAM and with a monochrome transparent bitmask"))));
    Serial6.println((reinterpret_cast<const __FlashStringHelper *>((""))));
    Serial6.println((reinterpret_cast<const __FlashStringHelper *>(("Using the hardware pushColors() methods is faster"))));
    Serial6.println((reinterpret_cast<const __FlashStringHelper *>(("pushColors() expects uint16 array in SRAM"))));
    Serial6.println((reinterpret_cast<const __FlashStringHelper *>(("for any runtime generated images"))));
    Serial6.println((reinterpret_cast<const __FlashStringHelper *>(("but it expects uint8_t array of Serial6ised bytes in Flash"))));
    Serial6.println((reinterpret_cast<const __FlashStringHelper *>((""))));

    Serial6.println((reinterpret_cast<const __FlashStringHelper *>(("Colour TFTs are natively big-endian"))));
    Serial6.println((reinterpret_cast<const __FlashStringHelper *>(("Many microcontrollers and Tools are little-endian"))));
    Serial6.println((reinterpret_cast<const __FlashStringHelper *>(("you can use the optional argument to select big-end"))));
    tft.begin(ID);
    //    invertmap(betty_1_bmp + 62, 8960);
    //    while (1);
}

// GFX drawBitmap() expects each row to be on 8-bit boundary.  i.e. pad = 7
// Mono BMP rows are on 32-bit boundary. i.e. pad = 31,  rows are in RVS order.
// FreeFont bitmaps have no padding.  i.e. pad = 0.   e.g. 5x4 bitmap is in 3 bytes
void showbgd(int x, int y, const uint8_t *bmp, int w, int h, uint16_t color, uint16_t bg, uint8_t pad = 7)
{
    int yy, xx;
    uint8_t first = 1, RVS = pad & 0x80;
    uint16_t pixel;
    pad &= 31;
    uint16_t wid = (w + pad) & ~pad; //bits per row
    tft.setAddrWindow(x, y, x + w - 1, y + h - 1); //
    for (yy = 0; yy < h; yy++) {
        uint32_t ofs = (RVS ? (h - yy - 1) : yy) * wid; //bit offset
        const uint8_t *p = bmp + (ofs >> 3); //flash address
        uint8_t mask = 0x80 >> (ofs & 7); //bit mask
        uint8_t c = (*(const unsigned char *)(p++));
        for (xx = 0; xx < w; xx++) {
            if (mask == 0) {
                c = (*(const unsigned char *)(p++));
                mask = 0x80;
            }
            pixel = (c & mask) ? color : bg;
            tft.pushColors(&pixel, 1, first);
            first = 0;
            mask >>= 1;
        }
    }
    tft.setAddrWindow(0, 0, tft.width() - 1, tft.height() - 1);
}

void msg_time(int x, int y, String msg, uint32_t t)
{
    t = millis() - t;
    tft.setCursor(x, y);
    tft.print(msg);
    tft.print(t);
    tft.print((reinterpret_cast<const __FlashStringHelper *>(("ms"))));
}

void loop(void)
{
    int x = 5, y, w = 128, h = 64;
    uint32_t t;
    const int SZ = w * h / 8;
    uint8_t sram[SZ];
    memcpy((sram), (tractor_128x64), (SZ));

    tft.fillScreen(0x0000);
    y = 0; t = millis();
    tft.drawBitmap(x, y, tractor_128x64, 128, 64, 0x001F);
    msg_time(0, y + 66, (reinterpret_cast<const __FlashStringHelper *>(("drawBitmap() transparent flash "))), t);
    y = 80; t = millis();
    tft.drawBitmap(x, y, tractor_128x64, 128, 64, 0xF800, 0xFFE0);
    msg_time(0, y + 66, (reinterpret_cast<const __FlashStringHelper *>(("drawBitmap() background flash "))), t);
    y = 160; t = millis();
    tft.fillRect(x, y, w, h, 0x8410);
    tft.drawBitmap(x, y, sram, 128, 64, 0x07E0);
    msg_time(0, y + 66, (reinterpret_cast<const __FlashStringHelper *>(("drawBitmap() fill bgd SRAM "))), t);
    y = 240; t = millis();
    showbgd(x, y, tractor_128x64, 128, 64, 0xF81F, 0xFFE0);
    msg_time(0, y + 66, (reinterpret_cast<const __FlashStringHelper *>(("pushColors() background flash "))), t);
    delay(5000);

    tft.fillScreen(0x0000);
    y = 0; t = millis();
    tft.drawRGBBitmap(x, y, marilyn_64x64, 64, 64);
    msg_time(0, y + 66, "drawRGBBitmap() flash ", t);
    y = 80; t = millis();
    tft.setAddrWindow(x, y, x + 64 - 1, y + 64 - 1);
    tft.pushColors((const uint8_t*)marilyn_64x64, 64 * 64, 1, false);
    tft.setAddrWindow(0, 0, tft.width() - 1, tft.height() - 1);
    msg_time(0, y + 66, (reinterpret_cast<const __FlashStringHelper *>(("pushColors() flash "))), t);
    y = 160; t = millis();
    w = 64;
    tft.fillRect(x, y, w, h, 0x8410);
    tft.drawRGBBitmap(x, y, marilyn_64x64, magnify_64x64, 64, 64);
    msg_time(0, y + 66, (reinterpret_cast<const __FlashStringHelper *>(("drawRGBBitmap() with mask "))), t);
    y = 240; t = millis();
    w = 64;
    tft.fillRect(x, y, w, h, 0x8410);
    tft.drawRGBBitmap(x, y, marilyn_64x64, magnify_inv_64x64, 64, 64);
    msg_time(0, y + 66, (reinterpret_cast<const __FlashStringHelper *>(("drawRGBBitmap() with mask "))), t);
    delay(5000);


    tft.fillScreen(0x0000);
    y = 0; t = millis();
    tft.drawRGBBitmap(x, y, tractor10_96x64, 96, 64);
    msg_time(0, y + 66, "drawRGBBitmap() flash ", t);
    y = 80; t = millis();
    tft.setAddrWindow(x, y, x + 96 - 1, y + 64 - 1);
    tft.pushColors((const uint8_t*)tractor10_96x64, 96 * 64, 1, false);
    tft.setAddrWindow(0, 0, tft.width() - 1, tft.height() - 1);
    msg_time(0, y + 66, (reinterpret_cast<const __FlashStringHelper *>(("pushColors() flash "))), t);
    y = 160; t = millis();
    w = 96;
    tft.fillRect(x, y, w, h, 0x8410);
    tft.drawRGBBitmap(x, y, tractor10_96x64, camera_96x64, 96, 64);
    msg_time(0, y + 66, (reinterpret_cast<const __FlashStringHelper *>(("drawRGBBitmap() with mask "))), t);
    y = 240; t = millis();
    w = 96;
    tft.fillRect(x, y, w, h, 0x8410);
    tft.drawRGBBitmap(x, y, tractor10_96x64, camera_inv_96x64, 96, 64);
    msg_time(0, y + 66, (reinterpret_cast<const __FlashStringHelper *>(("drawRGBBitmap() with mask "))), t);
    delay(5000);

}
