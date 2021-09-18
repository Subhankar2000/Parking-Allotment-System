# 1 "C:\\Users\\Subhankar Karmakar\\Documents\\Arduino\\libraries\\TFT_eSPI\\examples\\Generic\\Animated_Eyes_1\\Animated_Eyes_1.ino"
// An adaption of the "UncannyEyes" sketch (see eye_functions tab)
// for the TFT_eSPI library. As written the sketch is for driving
// one (240x320 minimum) TFT display, showing 2 eyes. See example
// Animated_Eyes_2 for a dual 128x128 TFT display configued sketch.

// Configuration settings for the eye, eye style, display count,
// chip selects and x offsets can be defined in the sketch "config.h" tab.

// Performance (frames per second = fps) can be improved by using
// DMA (for SPI displays only) on ESP32 and STM32 processors. Use
// as high a SPI clock rate as is supported by the display. 27MHz
// minimum, some diplays can be operated at higher clock rates in
// the range 40-80MHz.

// Single defaultEye performance for different processors
//                                  No DMA   With DMA
// ESP8266 (160MHz CPU) 40MHz SPI   36 fps
// ESP32 27MHz SPI                  53 fps     85 fps
// ESP32 40MHz SPI                  67 fps    102 fps
// ESP32 80MHz SPI                  82 fps    116 fps // Note: Few displays work reliably at 80MHz
// STM32F401 55MHz SPI              44 fps     90 fps
// STM32F446 55MHz SPI              83 fps    155 fps
// STM32F767 55MHz SPI             136 fps    197 fps

// DMA can be used with STM32 and ESP32 processors when the interface
// is SPI, uncomment the next line:
//#define USE_DMA

// Load TFT driver library
# 31 "C:\\Users\\Subhankar Karmakar\\Documents\\Arduino\\libraries\\TFT_eSPI\\examples\\Generic\\Animated_Eyes_1\\Animated_Eyes_1.ino" 2
# 32 "C:\\Users\\Subhankar Karmakar\\Documents\\Arduino\\libraries\\TFT_eSPI\\examples\\Generic\\Animated_Eyes_1\\Animated_Eyes_1.ino" 2
TFT_eSPI tft; // A single instance is used for 1 or 2 displays

// A pixel buffer is used during eye rendering
# 43 "C:\\Users\\Subhankar Karmakar\\Documents\\Arduino\\libraries\\TFT_eSPI\\examples\\Generic\\Animated_Eyes_1\\Animated_Eyes_1.ino"
uint16_t pbuffer[1 /* 1 buffer for no DMA*/][1024 /* 128 to 1024 seems optimum*/]; // Pixel rendering buffer
bool dmaBuf = 0; // DMA buffer selection

// This struct is populated in config.h
typedef struct { // Struct is defined before including config.h --
  int8_t select; // pin numbers for each eye's screen select line
  int8_t wink; // and wink button (or -1 if none) specified there,
  uint8_t rotation; // also display rotation and the x offset
  int16_t xposition; // position of eye on the screen
} eyeInfo_t;

# 55 "C:\\Users\\Subhankar Karmakar\\Documents\\Arduino\\libraries\\TFT_eSPI\\examples\\Generic\\Animated_Eyes_1\\Animated_Eyes_1.ino" 2

extern void user_setup(void); // Functions in the user*.cpp files
extern void user_loop(void);






// A simple state machine is used to control eye blinks/winks:



typedef struct {
  uint8_t state; // NOBLINK/ENBLINK/DEBLINK
  uint32_t duration; // Duration of blink state (micros)
  uint32_t startTime; // Time (micros) of last state change
} eyeBlink;

struct { // One-per-eye structure
  int16_t tft_cs; // Chip select pin for each display
  eyeBlink blink; // Current blink/wink state
  int16_t xposition; // x position of eye image
} eye[2 /* Number of eyes to display (1 or 2)*/];

uint32_t startTime; // For FPS indicator

// INITIALIZATION -- runs once at startup ----------------------------------
void setup(void) {
  Serial.begin(115200);
  //while (!Serial);
  Serial.println("Starting");
# 95 "C:\\Users\\Subhankar Karmakar\\Documents\\Arduino\\libraries\\TFT_eSPI\\examples\\Generic\\Animated_Eyes_1\\Animated_Eyes_1.ino"
  // User call for additional features
  user_setup();

  // Initialiase the eye(s), this will set all chip selects low for the tft.init()
  initEyes();

  // Initialise TFT
  Serial.println("Initialising displays");
  tft.init();





  // Raise chip select(s) so that displays can be individually configured
  digitalWrite(eye[0].tft_cs, 0x1);
  if (2 /* Number of eyes to display (1 or 2)*/ > 1) digitalWrite(eye[1].tft_cs, 0x1);

  for (uint8_t e = 0; e < 2 /* Number of eyes to display (1 or 2)*/; e++) {
    digitalWrite(eye[e].tft_cs, 0x0);
    tft.setRotation(eyeInfo[e].rotation);
    tft.fillScreen(0x0000 /*   0,   0,   0 */);
    digitalWrite(eye[e].tft_cs, 0x1);
  }






  startTime = millis(); // For frame-rate calculation
}

// MAIN LOOP -- runs continuously after setup() ----------------------------
void loop() {
  updateEye();
}
# 1 "C:\\Users\\Subhankar Karmakar\\Documents\\Arduino\\libraries\\TFT_eSPI\\examples\\Generic\\Animated_Eyes_1\\eye_functions.ino"
//
// Code adapted by Bodmer as an example for TFT_eSPI, this runs on any
// TFT_eSPI compatible processor so ignore the technical limitations
// detailed in the original header below. Assorted changes have been
// made including removal of the display mirror kludge.

//--------------------------------------------------------------------------
// Uncanny eyes for Adafruit 1.5" OLED (product #1431) or 1.44" TFT LCD
// (#2088).  Works on PJRC Teensy 3.x and on Adafruit M0 and M4 boards
// (Feather, Metro, etc.).  This code uses features specific to these
// boards and WILL NOT work on normal Arduino or other boards!
//
// SEE FILE "config.h" FOR MOST CONFIGURATION (graphics, pins, display type,
// etc).  Probably won't need to edit THIS file unless you're doing some
// extremely custom modifications.
//
// Adafruit invests time and resources providing this open source code,
// please support Adafruit and open-source hardware by purchasing products
// from Adafruit!
//
// Written by Phil Burgess / Paint Your Dragon for Adafruit Industries.
// MIT license.  SPI FIFO insight from Paul Stoffregen's ILI9341_t3 library.
// Inspired by David Boccabella's (Marcwolf) hybrid servo/OLED eye concept.
//--------------------------------------------------------------------------


// Autonomous iris motion uses a fractal behavior to similate both the major
// reaction of the eye plus the continuous smaller adjustments that occur.
uint16_t oldIris = (90 /* Iris size (0-1023) in brightest light*/ + 130 /* Iris size (0-1023) in darkest light*/) / 2, newIris;


// Initialise eyes ---------------------------------------------------------
void initEyes(void)
{
  Serial.println("Initialise eye objects");

  // Initialise eye objects based on eyeInfo list in config.h:
  for (uint8_t e = 0; e < 2 /* Number of eyes to display (1 or 2)*/; e++) {
    Serial.print("Create display #"); Serial.println(e);

    eye[e].tft_cs = eyeInfo[e].select;
    eye[e].blink.state = 0 /* Not currently engaged in a blink*/;
    eye[e].xposition = eyeInfo[e].xposition;

    pinMode(eye[e].tft_cs, 0x01);
    digitalWrite(eye[e].tft_cs, 0x0);

    // Also set up an individual eye-wink pin if defined:
    if (eyeInfo[e].wink >= 0) pinMode(eyeInfo[e].wink, 0x02);
  }




}

// UPDATE EYE --------------------------------------------------------------
void updateEye (void)
{
# 85 "C:\\Users\\Subhankar Karmakar\\Documents\\Arduino\\libraries\\TFT_eSPI\\examples\\Generic\\Animated_Eyes_1\\eye_functions.ino"
  newIris = random(90 /* Iris size (0-1023) in brightest light*/, 130 /* Iris size (0-1023) in darkest light*/);
  split(oldIris, newIris, micros(), 10000000L, 130 /* Iris size (0-1023) in darkest light*/ - 90 /* Iris size (0-1023) in brightest light*/);
  oldIris = newIris;


}

// EYE-RENDERING FUNCTION --------------------------------------------------
void drawEye( // Renders one eye.  Inputs must be pre-clipped & valid.
  // Use native 32 bit variables where possible as this is 10% faster!
  uint8_t e, // Eye array index; 0 or 1 for left/right
  uint32_t iScale, // Scale factor for iris
  uint32_t scleraX, // First pixel X offset into sclera image
  uint32_t scleraY, // First pixel Y offset into sclera image
  uint32_t uT, // Upper eyelid threshold value
  uint32_t lT) { // Lower eyelid threshold value

  uint32_t screenX, screenY, scleraXsave;
  int32_t irisX, irisY;
  uint32_t p, a;
  uint32_t d;

  uint32_t pixels = 0;

  // Set up raw pixel dump to entire screen.  Although such writes can wrap
  // around automatically from end of rect back to beginning, the region is
  // reset on each frame here in case of an SPI glitch.
  digitalWrite(eye[e].tft_cs, 0x0);
  tft.startWrite();
  tft.setAddrWindow(eye[e].xposition, 0, 128, 128);

  // Now just issue raw 16-bit values for every pixel...

  scleraXsave = scleraX; // Save initial X value to reset on each line
  irisY = scleraY - (200 - 80) / 2;

  // Eyelid image is left<>right swapped for two displays
  uint16_t lidX = 0;
  uint16_t dlidX = -1;
  if (e) dlidX = 1;
  for (screenY = 0; screenY < 128; screenY++, scleraY++, irisY++) {
    scleraX = scleraXsave;
    irisX = scleraXsave - (200 - 80) / 2;
    if (e) lidX = 0; else lidX = 128 - 1;
    for (screenX = 0; screenX < 128; screenX++, scleraX++, irisX++, lidX += dlidX) {
      if ((
# 130 "C:\\Users\\Subhankar Karmakar\\Documents\\Arduino\\libraries\\TFT_eSPI\\examples\\Generic\\Animated_Eyes_1\\eye_functions.ino" 3
          pgm_read_byte_inlined(
# 130 "C:\\Users\\Subhankar Karmakar\\Documents\\Arduino\\libraries\\TFT_eSPI\\examples\\Generic\\Animated_Eyes_1\\eye_functions.ino"
          lower + screenY * 128 + lidX
# 130 "C:\\Users\\Subhankar Karmakar\\Documents\\Arduino\\libraries\\TFT_eSPI\\examples\\Generic\\Animated_Eyes_1\\eye_functions.ino" 3
          ) 
# 130 "C:\\Users\\Subhankar Karmakar\\Documents\\Arduino\\libraries\\TFT_eSPI\\examples\\Generic\\Animated_Eyes_1\\eye_functions.ino"
                                                               <= lT) ||
          (
# 131 "C:\\Users\\Subhankar Karmakar\\Documents\\Arduino\\libraries\\TFT_eSPI\\examples\\Generic\\Animated_Eyes_1\\eye_functions.ino" 3
          pgm_read_byte_inlined(
# 131 "C:\\Users\\Subhankar Karmakar\\Documents\\Arduino\\libraries\\TFT_eSPI\\examples\\Generic\\Animated_Eyes_1\\eye_functions.ino"
          upper + screenY * 128 + lidX
# 131 "C:\\Users\\Subhankar Karmakar\\Documents\\Arduino\\libraries\\TFT_eSPI\\examples\\Generic\\Animated_Eyes_1\\eye_functions.ino" 3
          ) 
# 131 "C:\\Users\\Subhankar Karmakar\\Documents\\Arduino\\libraries\\TFT_eSPI\\examples\\Generic\\Animated_Eyes_1\\eye_functions.ino"
                                                               <= uT)) { // Covered by eyelid
        p = 0;
      } else if ((irisY < 0) || (irisY >= 80) ||
                 (irisX < 0) || (irisX >= 80)) { // In sclera
        p = 
# 135 "C:\\Users\\Subhankar Karmakar\\Documents\\Arduino\\libraries\\TFT_eSPI\\examples\\Generic\\Animated_Eyes_1\\eye_functions.ino" 3
           ((uint16_t)pgm_read_dword_unaligned(
# 135 "C:\\Users\\Subhankar Karmakar\\Documents\\Arduino\\libraries\\TFT_eSPI\\examples\\Generic\\Animated_Eyes_1\\eye_functions.ino"
           sclera + scleraY * 200 + scleraX
# 135 "C:\\Users\\Subhankar Karmakar\\Documents\\Arduino\\libraries\\TFT_eSPI\\examples\\Generic\\Animated_Eyes_1\\eye_functions.ino" 3
           ))
# 135 "C:\\Users\\Subhankar Karmakar\\Documents\\Arduino\\libraries\\TFT_eSPI\\examples\\Generic\\Animated_Eyes_1\\eye_functions.ino"
                                                                   ;
      } else { // Maybe iris...
        p = 
# 137 "C:\\Users\\Subhankar Karmakar\\Documents\\Arduino\\libraries\\TFT_eSPI\\examples\\Generic\\Animated_Eyes_1\\eye_functions.ino" 3
           ((uint16_t)pgm_read_dword_unaligned(
# 137 "C:\\Users\\Subhankar Karmakar\\Documents\\Arduino\\libraries\\TFT_eSPI\\examples\\Generic\\Animated_Eyes_1\\eye_functions.ino"
           polar + irisY * 80 + irisX
# 137 "C:\\Users\\Subhankar Karmakar\\Documents\\Arduino\\libraries\\TFT_eSPI\\examples\\Generic\\Animated_Eyes_1\\eye_functions.ino" 3
           ))
# 137 "C:\\Users\\Subhankar Karmakar\\Documents\\Arduino\\libraries\\TFT_eSPI\\examples\\Generic\\Animated_Eyes_1\\eye_functions.ino"
                                                            ; // Polar angle/dist
        d = (iScale * (p & 0x7F)) / 128; // Distance (Y)
        if (d < 64) { // Within iris area
          a = (256 * (p >> 7)) / 512; // Angle (X)
          p = 
# 141 "C:\\Users\\Subhankar Karmakar\\Documents\\Arduino\\libraries\\TFT_eSPI\\examples\\Generic\\Animated_Eyes_1\\eye_functions.ino" 3
             ((uint16_t)pgm_read_dword_unaligned(
# 141 "C:\\Users\\Subhankar Karmakar\\Documents\\Arduino\\libraries\\TFT_eSPI\\examples\\Generic\\Animated_Eyes_1\\eye_functions.ino"
             iris + d * 256 + a
# 141 "C:\\Users\\Subhankar Karmakar\\Documents\\Arduino\\libraries\\TFT_eSPI\\examples\\Generic\\Animated_Eyes_1\\eye_functions.ino" 3
             ))
# 141 "C:\\Users\\Subhankar Karmakar\\Documents\\Arduino\\libraries\\TFT_eSPI\\examples\\Generic\\Animated_Eyes_1\\eye_functions.ino"
                                                         ; // Pixel = iris
        } else { // Not in iris
          p = 
# 143 "C:\\Users\\Subhankar Karmakar\\Documents\\Arduino\\libraries\\TFT_eSPI\\examples\\Generic\\Animated_Eyes_1\\eye_functions.ino" 3
             ((uint16_t)pgm_read_dword_unaligned(
# 143 "C:\\Users\\Subhankar Karmakar\\Documents\\Arduino\\libraries\\TFT_eSPI\\examples\\Generic\\Animated_Eyes_1\\eye_functions.ino"
             sclera + scleraY * 200 + scleraX
# 143 "C:\\Users\\Subhankar Karmakar\\Documents\\Arduino\\libraries\\TFT_eSPI\\examples\\Generic\\Animated_Eyes_1\\eye_functions.ino" 3
             ))
# 143 "C:\\Users\\Subhankar Karmakar\\Documents\\Arduino\\libraries\\TFT_eSPI\\examples\\Generic\\Animated_Eyes_1\\eye_functions.ino"
                                                                     ; // Pixel = sclera
        }
      }
      *(&pbuffer[dmaBuf][0] + pixels++) = p >> 8 | p << 8;

      if (pixels >= 1024 /* 128 to 1024 seems optimum*/) {
        yield();




        tft.pushPixels(pbuffer, pixels);

        pixels = 0;
      }
    }
  }

  if (pixels) {



    tft.pushPixels(pbuffer, pixels);

  }
  tft.endWrite();
  digitalWrite(eye[e].tft_cs, 0x1);
}

// EYE ANIMATION -----------------------------------------------------------

const uint8_t ease[] = { // Ease in/out curve for eye movements 3*t^2-2*t^3
  0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 2, 2, 2, 3, // T
  3, 3, 4, 4, 4, 5, 5, 6, 6, 7, 7, 8, 9, 9, 10, 10, // h
  11, 12, 12, 13, 14, 15, 15, 16, 17, 18, 18, 19, 20, 21, 22, 23, // x
  24, 25, 26, 27, 27, 28, 29, 30, 31, 33, 34, 35, 36, 37, 38, 39, // 2
  40, 41, 42, 44, 45, 46, 47, 48, 50, 51, 52, 53, 54, 56, 57, 58, // A
  60, 61, 62, 63, 65, 66, 67, 69, 70, 72, 73, 74, 76, 77, 78, 80, // l
  81, 83, 84, 85, 87, 88, 90, 91, 93, 94, 96, 97, 98, 100, 101, 103, // e
  104, 106, 107, 109, 110, 112, 113, 115, 116, 118, 119, 121, 122, 124, 125, 127, // c
  128, 130, 131, 133, 134, 136, 137, 139, 140, 142, 143, 145, 146, 148, 149, 151, // J
  152, 154, 155, 157, 158, 159, 161, 162, 164, 165, 167, 168, 170, 171, 172, 174, // a
  175, 177, 178, 179, 181, 182, 183, 185, 186, 188, 189, 190, 192, 193, 194, 195, // c
  197, 198, 199, 201, 202, 203, 204, 205, 207, 208, 209, 210, 211, 213, 214, 215, // o
  216, 217, 218, 219, 220, 221, 222, 224, 225, 226, 227, 228, 228, 229, 230, 231, // b
  232, 233, 234, 235, 236, 237, 237, 238, 239, 240, 240, 241, 242, 243, 243, 244, // s
  245, 245, 246, 246, 247, 248, 248, 249, 249, 250, 250, 251, 251, 251, 252, 252, // o
  252, 253, 253, 253, 254, 254, 254, 254, 254, 255, 255, 255, 255, 255, 255, 255
}; // n


uint32_t timeOfLastBlink = 0L, timeToNextBlink = 0L;


// Process motion for a single frame of left or right eye
void frame(uint16_t iScale) // Iris scale (0-1023)
{
  static uint32_t frames = 0; // Used in frame rate calculation
  static uint8_t eyeIndex = 0; // eye[] array counter
  int16_t eyeX, eyeY;
  uint32_t t = micros(); // Time at start of function

  if (!(++frames & 255)) { // Every 256 frames...
    float elapsed = (millis() - startTime) / 1000.0;
    if (elapsed) Serial.println((uint16_t)(frames / elapsed)); // Print FPS
  }

  if (++eyeIndex >= 2 /* Number of eyes to display (1 or 2)*/) eyeIndex = 0; // Cycle through eyes, 1 per call

  // X/Y movement
# 237 "C:\\Users\\Subhankar Karmakar\\Documents\\Arduino\\libraries\\TFT_eSPI\\examples\\Generic\\Animated_Eyes_1\\eye_functions.ino"
  // Periodically initiates motion to a new random point, random speed,
  // holds there for random period until next motion.

  static bool eyeInMotion = false;
  static int16_t eyeOldX = 512, eyeOldY = 512, eyeNewX = 512, eyeNewY = 512;
  static uint32_t eyeMoveStartTime = 0L;
  static int32_t eyeMoveDuration = 0L;

  int32_t dt = t - eyeMoveStartTime; // uS elapsed since last eye event
  if (eyeInMotion) { // Currently moving?
    if (dt >= eyeMoveDuration) { // Time up?  Destination reached.
      eyeInMotion = false; // Stop moving
      eyeMoveDuration = random(3000000); // 0-3 sec stop
      eyeMoveStartTime = t; // Save initial time of stop
      eyeX = eyeOldX = eyeNewX; // Save position
      eyeY = eyeOldY = eyeNewY;
    } else { // Move time's not yet fully elapsed -- interpolate position
      int16_t e = ease[255 * dt / eyeMoveDuration] + 1; // Ease curve
      eyeX = eyeOldX + (((eyeNewX - eyeOldX) * e) / 256); // Interp X
      eyeY = eyeOldY + (((eyeNewY - eyeOldY) * e) / 256); // and Y
    }
  } else { // Eye stopped
    eyeX = eyeOldX;
    eyeY = eyeOldY;
    if (dt > eyeMoveDuration) { // Time up?  Begin new move.
      int16_t dx, dy;
      uint32_t d;
      do { // Pick new dest in circle
        eyeNewX = random(1024);
        eyeNewY = random(1024);
        dx = (eyeNewX * 2) - 1023;
        dy = (eyeNewY * 2) - 1023;
      } while ((d = (dx * dx + dy * dy)) > (1023 * 1023)); // Keep trying
      eyeMoveDuration = random(72000, 144000); // ~1/14 - ~1/7 sec
      eyeMoveStartTime = t; // Save initial time of move
      eyeInMotion = true; // Start move on next frame
    }
  }


  // Blinking

  // Similar to the autonomous eye movement above -- blink start times
  // and durations are random (within ranges).
  if ((t - timeOfLastBlink) >= timeToNextBlink) { // Start new blink?
    timeOfLastBlink = t;
    uint32_t blinkDuration = random(36000, 72000); // ~1/28 - ~1/14 sec
    // Set up durations for both eyes (if not already winking)
    for (uint8_t e = 0; e < 2 /* Number of eyes to display (1 or 2)*/; e++) {
      if (eye[e].blink.state == 0 /* Not currently engaged in a blink*/) {
        eye[e].blink.state = 1 /* Eyelid is currently closing*/;
        eye[e].blink.startTime = t;
        eye[e].blink.duration = blinkDuration;
      }
    }
    timeToNextBlink = blinkDuration * 3 + random(4000000);
  }


  if (eye[eyeIndex].blink.state) { // Eye currently blinking?
    // Check if current blink state time has elapsed
    if ((t - eye[eyeIndex].blink.startTime) >= eye[eyeIndex].blink.duration) {
      // Yes -- increment blink state, unless...
      if ((eye[eyeIndex].blink.state == 1 /* Eyelid is currently closing*/) && ( // Enblinking and...



            ((eyeInfo[eyeIndex].wink >= 0) &&
             digitalRead(eyeInfo[eyeIndex].wink) == 0x0) )) {
        // Don't advance state yet -- eye is held closed instead
      } else { // No buttons, or other state...
        if (++eye[eyeIndex].blink.state > 2 /* Eyelid is currently opening*/) { // Deblinking finished?
          eye[eyeIndex].blink.state = 0 /* Not currently engaged in a blink*/; // No longer blinking
        } else { // Advancing from ENBLINK to DEBLINK mode
          eye[eyeIndex].blink.duration *= 2; // DEBLINK is 1/2 ENBLINK speed
          eye[eyeIndex].blink.startTime = t;
        }
      }
    }
  } else { // Not currently blinking...check buttons!
# 330 "C:\\Users\\Subhankar Karmakar\\Documents\\Arduino\\libraries\\TFT_eSPI\\examples\\Generic\\Animated_Eyes_1\\eye_functions.ino"
      if ((eyeInfo[eyeIndex].wink >= 0) &&
          (digitalRead(eyeInfo[eyeIndex].wink) == 0x0)) { // Wink!
        eye[eyeIndex].blink.state = 1 /* Eyelid is currently closing*/;
        eye[eyeIndex].blink.startTime = t;
        eye[eyeIndex].blink.duration = random(45000, 90000);
      }
  }

  // Process motion, blinking and iris scale into renderable values

  // Scale eye X/Y positions (0-1023) to pixel units used by drawEye()
  eyeX = map(eyeX, 0, 1023, 0, 200 - 128);
  eyeY = map(eyeY, 0, 1023, 0, 200 - 128);

  // Horizontal position is offset so that eyes are very slightly crossed
  // to appear fixated (converged) at a conversational distance.  Number
  // here was extracted from my posterior and not mathematically based.
  // I suppose one could get all clever with a range sensor, but for now...
  if (2 /* Number of eyes to display (1 or 2)*/ > 1) {
    if (eyeIndex == 1) eyeX += 4;
    else eyeX -= 4;
  }
  if (eyeX > (200 - 128)) eyeX = (200 - 128);

  // Eyelids are rendered using a brightness threshold image.  This same
  // map can be used to simplify another problem: making the upper eyelid
  // track the pupil (eyes tend to open only as much as needed -- e.g. look
  // down and the upper eyelid drops).  Just sample a point in the upper
  // lid map slightly above the pupil to determine the rendering threshold.
  static uint8_t uThreshold = 128;
  uint8_t lThreshold, n;

  int16_t sampleX = 200 / 2 - (eyeX / 2), // Reduce X influence
          sampleY = 200 / 2 - (eyeY + 80 / 4);
  // Eyelid is slightly asymmetrical, so two readings are taken, averaged
  if (sampleY < 0) n = 0;
  else n = (
# 366 "C:\\Users\\Subhankar Karmakar\\Documents\\Arduino\\libraries\\TFT_eSPI\\examples\\Generic\\Animated_Eyes_1\\eye_functions.ino" 3
                      pgm_read_byte_inlined(
# 366 "C:\\Users\\Subhankar Karmakar\\Documents\\Arduino\\libraries\\TFT_eSPI\\examples\\Generic\\Animated_Eyes_1\\eye_functions.ino"
                      upper + sampleY * 128 + sampleX
# 366 "C:\\Users\\Subhankar Karmakar\\Documents\\Arduino\\libraries\\TFT_eSPI\\examples\\Generic\\Animated_Eyes_1\\eye_functions.ino" 3
                      ) 
# 366 "C:\\Users\\Subhankar Karmakar\\Documents\\Arduino\\libraries\\TFT_eSPI\\examples\\Generic\\Animated_Eyes_1\\eye_functions.ino"
                                                                              +
                         
# 367 "C:\\Users\\Subhankar Karmakar\\Documents\\Arduino\\libraries\\TFT_eSPI\\examples\\Generic\\Animated_Eyes_1\\eye_functions.ino" 3
                        pgm_read_byte_inlined(
# 367 "C:\\Users\\Subhankar Karmakar\\Documents\\Arduino\\libraries\\TFT_eSPI\\examples\\Generic\\Animated_Eyes_1\\eye_functions.ino"
                        upper + sampleY * 128 + (128 - 1 - sampleX)
# 367 "C:\\Users\\Subhankar Karmakar\\Documents\\Arduino\\libraries\\TFT_eSPI\\examples\\Generic\\Animated_Eyes_1\\eye_functions.ino" 3
                        )
# 367 "C:\\Users\\Subhankar Karmakar\\Documents\\Arduino\\libraries\\TFT_eSPI\\examples\\Generic\\Animated_Eyes_1\\eye_functions.ino"
                                                                                                    ) / 2;
  uThreshold = (uThreshold * 3 + n) / 4; // Filter/soften motion
  // Lower eyelid doesn't track the same way, but seems to be pulled upward
  // by tension from the upper lid.
  lThreshold = 254 - uThreshold;




  // The upper/lower thresholds are then scaled relative to the current
  // blink position so that blinks work together with pupil tracking.
  if (eye[eyeIndex].blink.state) { // Eye currently blinking?
    uint32_t s = (t - eye[eyeIndex].blink.startTime);
    if (s >= eye[eyeIndex].blink.duration) s = 255; // At or past blink end
    else s = 255 * s / eye[eyeIndex].blink.duration; // Mid-blink
    s = (eye[eyeIndex].blink.state == 2 /* Eyelid is currently opening*/) ? 1 + s : 256 - s;
    n = (uThreshold * s + 254 * (257 - s)) / 256;
    lThreshold = (lThreshold * s + 254 * (257 - s)) / 256;
  } else {
    n = uThreshold;
  }

  // Pass all the derived values to the eye-rendering function:
  drawEye(eyeIndex, iScale, eyeX, eyeY, n, lThreshold);

  if (eyeIndex == (2 /* Number of eyes to display (1 or 2)*/ - 1)) {
    user_loop(); // Call user code after rendering last eye
  }
}

// AUTONOMOUS IRIS SCALING (if no photocell or dial) -----------------------



// Autonomous iris motion uses a fractal behavior to similate both the major
// reaction of the eye plus the continuous smaller adjustments that occur.

void split( // Subdivides motion path into two sub-paths w/randimization
  int16_t startValue, // Iris scale value (IRIS_MIN to IRIS_MAX) at start
  int16_t endValue, // Iris scale value at end
  uint32_t startTime, // micros() at start
  int32_t duration, // Start-to-end time, in microseconds
  int16_t range) { // Allowable scale value variance when subdividing

  if (range >= 8) { // Limit subdvision count, because recursion
    range /= 2; // Split range & time in half for subdivision,
    duration /= 2; // then pick random center point within range:
    int16_t midValue = (startValue + endValue - range) / 2 + random(range);
    uint32_t midTime = startTime + duration;
    split(startValue, midValue, startTime, duration, range); // First half
    split(midValue , endValue, midTime , duration, range); // Second half
  } else { // No more subdivisons, do iris motion...
    int32_t dt; // Time (micros) since start of motion
    int16_t v; // Interim value
    while ((dt = (micros() - startTime)) < duration) {
      v = startValue + (((endValue - startValue) * dt) / duration);
      if (v < 90 /* Iris size (0-1023) in brightest light*/) v = 90 /* Iris size (0-1023) in brightest light*/; // Clip just in case
      else if (v > 130 /* Iris size (0-1023) in darkest light*/) v = 130 /* Iris size (0-1023) in darkest light*/;
      frame(v); // Draw frame w/interim iris scale value
    }
  }
}
