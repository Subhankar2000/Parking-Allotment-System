# 1 "D:\\Arduino-STM32-ARM-M4\\portable\\sketchbook\\libraries\\TFT_eSPI\\examples\\320 x 240\\Cellular_Automata\\Cellular_Automata.ino"
# 1 "D:\\Arduino-STM32-ARM-M4\\portable\\sketchbook\\libraries\\TFT_eSPI\\examples\\320 x 240\\Cellular_Automata\\Cellular_Automata.ino"
//The Game of Life, also known simply as Life, is a cellular automaton
//devised by the British mathematician John Horton Conway in 1970.
// https://en.wikipedia.org/wiki/Conway's_Game_of_Life


# 7 "D:\\Arduino-STM32-ARM-M4\\portable\\sketchbook\\libraries\\TFT_eSPI\\examples\\320 x 240\\Cellular_Automata\\Cellular_Automata.ino" 2

# 9 "D:\\Arduino-STM32-ARM-M4\\portable\\sketchbook\\libraries\\TFT_eSPI\\examples\\320 x 240\\Cellular_Automata\\Cellular_Automata.ino" 2

TFT_eSPI tft = TFT_eSPI(); // Invoke custom library

//#define GRIDX 80
//#define GRIDY 60
//#define CELLXY 4







//Current grid
uint8_t grid[160][120];

//The new grid for the next generation
uint8_t newgrid[160][120];

//Number of generations


uint16_t genCount = 0;

void setup() {

  //Set up the display
  tft.init();
  tft.setRotation(3);
  tft.fillScreen(0x0000 /*   0,   0,   0 */);
  tft.setTextSize(1);
  tft.setTextColor(0xFFFF /* 255, 255, 255 */);
  tft.setCursor(0, 0);

}

void loop() {

  //Display a simple splash screen
  tft.fillScreen(0x0000 /*   0,   0,   0 */);
  tft.setTextSize(2);
  tft.setTextColor(0xFFFF /* 255, 255, 255 */);
  tft.setCursor(40, 5);
  tft.println(((reinterpret_cast<const __FlashStringHelper *>(
# 52 "D:\\Arduino-STM32-ARM-M4\\portable\\sketchbook\\libraries\\TFT_eSPI\\examples\\320 x 240\\Cellular_Automata\\Cellular_Automata.ino" 3
             (__extension__({static const char __pstr__[] __attribute__((__aligned__(4))) __attribute__((section( "\".irom0.pstr." "Cellular_Automata.ino" "." "52" "." "423" "\", \"aSM\", @progbits, 1 #"))) = (
# 52 "D:\\Arduino-STM32-ARM-M4\\portable\\sketchbook\\libraries\\TFT_eSPI\\examples\\320 x 240\\Cellular_Automata\\Cellular_Automata.ino"
             "Arduino"
# 52 "D:\\Arduino-STM32-ARM-M4\\portable\\sketchbook\\libraries\\TFT_eSPI\\examples\\320 x 240\\Cellular_Automata\\Cellular_Automata.ino" 3
             ); &__pstr__[0];}))
# 52 "D:\\Arduino-STM32-ARM-M4\\portable\\sketchbook\\libraries\\TFT_eSPI\\examples\\320 x 240\\Cellular_Automata\\Cellular_Automata.ino"
             ))));
  tft.setCursor(35, 25);
  tft.println(((reinterpret_cast<const __FlashStringHelper *>(
# 54 "D:\\Arduino-STM32-ARM-M4\\portable\\sketchbook\\libraries\\TFT_eSPI\\examples\\320 x 240\\Cellular_Automata\\Cellular_Automata.ino" 3
             (__extension__({static const char __pstr__[] __attribute__((__aligned__(4))) __attribute__((section( "\".irom0.pstr." "Cellular_Automata.ino" "." "54" "." "424" "\", \"aSM\", @progbits, 1 #"))) = (
# 54 "D:\\Arduino-STM32-ARM-M4\\portable\\sketchbook\\libraries\\TFT_eSPI\\examples\\320 x 240\\Cellular_Automata\\Cellular_Automata.ino"
             "Cellular"
# 54 "D:\\Arduino-STM32-ARM-M4\\portable\\sketchbook\\libraries\\TFT_eSPI\\examples\\320 x 240\\Cellular_Automata\\Cellular_Automata.ino" 3
             ); &__pstr__[0];}))
# 54 "D:\\Arduino-STM32-ARM-M4\\portable\\sketchbook\\libraries\\TFT_eSPI\\examples\\320 x 240\\Cellular_Automata\\Cellular_Automata.ino"
             ))));
  tft.setCursor(35, 45);
  tft.println(((reinterpret_cast<const __FlashStringHelper *>(
# 56 "D:\\Arduino-STM32-ARM-M4\\portable\\sketchbook\\libraries\\TFT_eSPI\\examples\\320 x 240\\Cellular_Automata\\Cellular_Automata.ino" 3
             (__extension__({static const char __pstr__[] __attribute__((__aligned__(4))) __attribute__((section( "\".irom0.pstr." "Cellular_Automata.ino" "." "56" "." "425" "\", \"aSM\", @progbits, 1 #"))) = (
# 56 "D:\\Arduino-STM32-ARM-M4\\portable\\sketchbook\\libraries\\TFT_eSPI\\examples\\320 x 240\\Cellular_Automata\\Cellular_Automata.ino"
             "Automata"
# 56 "D:\\Arduino-STM32-ARM-M4\\portable\\sketchbook\\libraries\\TFT_eSPI\\examples\\320 x 240\\Cellular_Automata\\Cellular_Automata.ino" 3
             ); &__pstr__[0];}))
# 56 "D:\\Arduino-STM32-ARM-M4\\portable\\sketchbook\\libraries\\TFT_eSPI\\examples\\320 x 240\\Cellular_Automata\\Cellular_Automata.ino"
             ))));

  delay(1000);

  tft.fillScreen(0x0000 /*   0,   0,   0 */);

  initGrid();

  genCount = 600;

  drawGrid();

  //Compute generations
  for (int gen = 0; gen < genCount; gen++)
  {
    computeCA();
    drawGrid();
    delay(0);
    for (int16_t x = 1; x < 160 -1; x++) {
      for (int16_t y = 1; y < 120 -1; y++) {
        grid[x][y] = newgrid[x][y];
      }
    }

  }
}

//Draws the grid on the display
void drawGrid(void) {

  uint16_t color = 0xFFFF /* 255, 255, 255 */;
  for (int16_t x = 1; x < 160 - 1; x++) {
    for (int16_t y = 1; y < 120 - 1; y++) {
      if ((grid[x][y]) != (newgrid[x][y])) {
        if (newgrid[x][y] == 1) color = 0xFFFF; //random(0xFFFF);
        else color = 0;
        tft.fillRect(2 * x, 2 * y, 2, 2, color);
      }
    }
  }
}

//Initialise Grid
void initGrid(void) {
  for (int16_t x = 0; x < 160; x++) {
    for (int16_t y = 0; y < 120; y++) {
      newgrid[x][y] = 0;

      if (x == 0 || x == 160 - 1 || y == 0 || y == 120 - 1) {
        grid[x][y] = 0;
      }
      else {
        if (random(3) == 1)
          grid[x][y] = 1;
        else
          grid[x][y] = 0;
      }

    }
  }
}

//Compute the CA. Basically everything related to CA starts here
void computeCA() {
  for (int16_t x = 1; x < 160; x++) {
    for (int16_t y = 1; y < 120; y++) {
      int neighbors = getNumberOfNeighbors(x, y);
      if (grid[x][y] == 1 && (neighbors == 2 || neighbors == 3 ))
      {
        newgrid[x][y] = 1;
      }
      else if (grid[x][y] == 1) newgrid[x][y] = 0;
      if (grid[x][y] == 0 && (neighbors == 3))
      {
        newgrid[x][y] = 1;
      }
      else if (grid[x][y] == 0) newgrid[x][y] = 0;
    }
  }
}

// Check the Moore neighborhood
int getNumberOfNeighbors(int x, int y) {
  return grid[x - 1][y] + grid[x - 1][y - 1] + grid[x][y - 1] + grid[x + 1][y - 1] + grid[x + 1][y] + grid[x + 1][y + 1] + grid[x][y + 1] + grid[x - 1][y + 1];
}

/*
   The MIT License (MIT)

   Copyright (c) 2016 RuntimeProjects.com

   Permission is hereby granted, free of charge, to any person obtaining a copy
   of this software and associated documentation files (the "Software"), to deal
   in the Software without restriction, including without limitation the rights
   to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
   copies of the Software, and to permit persons to whom the Software is
   furnished to do so, subject to the following conditions:

   The above copyright notice and this permission notice shall be included in all
   copies or substantial portions of the Software.

   THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
   IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
   FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
   AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
   LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
   OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
   SOFTWARE.
*/
