//Final code for ESP8266 10th Sept...

#include <Arduino.h>
#include <SPI.h>
#include <ESP8266WiFi.h>
#include "Adafruit_MQTT.h"
#include "Adafruit_MQTT_Client.h"
#include <Wire.h>

#include "Adafruit_ILI9341esp.h"
#include "Adafruit_GFX.h"
//#include "XPT2046.h"

#define TFT_DC 2
#define TFT_CS 15

#define TEXT_X 10
#define TEXT_Y 10
#define TEXT_W 220
#define TEXT_H 40  //50
#define VAR_X 115
#define TEXT_TSIZE 3
#define TEXT_TCOLOR ILI9341_WHITE

Adafruit_ILI9341 tft = Adafruit_ILI9341(TFT_CS, TFT_DC);

/************************* WiFi Access Point *********************************/
#define WLAN_SSID       "Saqib"        //"Saqib" "iBall-Baton"
#define WLAN_PASS       "Saqib@123"    //"Saqib@123" "md9332328844"
/************************* Adafruit.io Setup *********************************/
#define AIO_SERVER      "io.adafruit.com"
#define AIO_SERVERPORT  1883           // use 8883 for SSL
#define AIO_USERNAME    "Saqibj"
#define AIO_KEY         "2fa9a134a4d94cbf98ebb46f41cd5cca"
/************ Global State (you don't need to change this!) ******************/
// Create an ESP8266 WiFiClient class to connect to the MQTT server.
WiFiClient client;
// or... use WiFiFlientSecure for SSL
//WiFiClientSecure client;

// Setup the MQTT client class by passing in the WiFi client and MQTT server and login details.
Adafruit_MQTT_Client mqtt(&client, AIO_SERVER, AIO_SERVERPORT, AIO_USERNAME, AIO_KEY);

/****************************** Feeds ***************************************/
// Setup a feed called 'ePark' for publishing.
Adafruit_MQTT_Publish f3 = Adafruit_MQTT_Publish(&mqtt, AIO_USERNAME "/feeds/3f");
Adafruit_MQTT_Publish f2 = Adafruit_MQTT_Publish(&mqtt, AIO_USERNAME "/feeds/2f");
Adafruit_MQTT_Publish f1 = Adafruit_MQTT_Publish(&mqtt, AIO_USERNAME "/feeds/1f");
Adafruit_MQTT_Publish f0 = Adafruit_MQTT_Publish(&mqtt, AIO_USERNAME "/feeds/gf");

//--------------------------------------------------------------------------------------------------//

/*************************** Sketch Code ************************************/

void MQTT_connect();

#define led D4
char arr1[4];
int arr[4];
int arrP[4] = {0, 0, 0, 0};
int flag[4] = {0, 0, 0, 0};
int flagR[4] = {0, 0, 0, 0};

void setup()
{
  Serial.begin(9600);

  Wire.begin(D1, D2);
  SPI.setFrequency(ESP_SPI_FREQ);

  tft.begin();

  tft.fillScreen(ILI9341_BLACK);

  //Drawing the 1st Rectangle...
  tft.setCursor(10, 10);
  tft.setTextColor(TEXT_TCOLOR, ILI9341_BLACK);
  tft.setTextSize(2);
  tft.print("Ground Floor...");

  tft.drawRect(10, 35, TEXT_W, TEXT_H, ILI9341_WHITE);
  tft.fillRect(10 + 1, 35 + 1, TEXT_W - 2, TEXT_H - 2, ILI9341_DARKGREEN);

  tft.setCursor(VAR_X , 35 + 10);
  tft.setTextColor(TEXT_TCOLOR, ILI9341_DARKGREEN);
  tft.setTextSize(TEXT_TSIZE);
  tft.print("/  5");

  //Drawing the 2nd Rectangle...
  tft.setCursor(TEXT_X, 85);
  tft.setTextColor(TEXT_TCOLOR, ILI9341_BLACK);
  tft.setTextSize(2);
  tft.print("1st Floor...");

  tft.drawRect(TEXT_X, 110, TEXT_W, TEXT_H, ILI9341_WHITE);
  tft.fillRect(TEXT_X + 1, 110 + 1, TEXT_W - 2, TEXT_H - 2, ILI9341_DARKGREEN);

  tft.setCursor(TEXT_X + 105, 110 + 10);
  tft.setTextColor(TEXT_TCOLOR, ILI9341_DARKGREEN);
  tft.setTextSize(TEXT_TSIZE);
  tft.print("/  5");

  //Drawing the 3rd Rectangle...
  tft.setCursor(10, 160);
  tft.setTextColor(TEXT_TCOLOR, ILI9341_BLACK);
  tft.setTextSize(2);
  tft.print("2nd Floor...");

  tft.drawRect(TEXT_X, 185, TEXT_W, TEXT_H, ILI9341_WHITE);
  tft.fillRect(TEXT_X + 1, 185 + 1, TEXT_W - 2, TEXT_H - 2, ILI9341_DARKGREEN);

  tft.setCursor(TEXT_X + 105, 185 + 10);
  tft.setTextColor(TEXT_TCOLOR, ILI9341_DARKGREEN);
  tft.setTextSize(TEXT_TSIZE);
  tft.print("/  5");

  //Drawing the 4th Rectangle...
  tft.setCursor(TEXT_X, 235);
  tft.setTextColor(TEXT_TCOLOR, ILI9341_BLACK);
  tft.setTextSize(2);
  tft.print("3rd Floor...");

  tft.drawRect(TEXT_X, 260, TEXT_W, TEXT_H, ILI9341_WHITE);
  tft.fillRect(TEXT_X + 1, 260 + 1, TEXT_W - 2, TEXT_H - 2, ILI9341_DARKGREEN);

  tft.setCursor(TEXT_X + 105, 260 + 10);
  tft.setTextColor(TEXT_TCOLOR, ILI9341_DARKGREEN);
  tft.setTextSize(TEXT_TSIZE);
  tft.print("/  5");

  while (!Serial)
    continue;

  pinMode(led, OUTPUT);

  Serial.println(F("Adafruit MQTT demo"));

  // Connect to WiFi access point.
  Serial.println(); Serial.println();

  Serial.print("Connecting to ");
  Serial.println(WLAN_SSID);

  WiFi.begin(WLAN_SSID, WLAN_PASS);
  while (WiFi.status() != WL_CONNECTED) {
    delay(100);
    Serial.print(".");
  }
  Serial.println();

  Serial.println("WiFi connected");
  Serial.println("IP address: "); Serial.println(WiFi.localIP());
}

int sent = 0;

void loop() {
  digitalWrite(led, HIGH);

  MQTT_connect();

  //---------------------------------------------------//

  Wire.beginTransmission(8);
  Wire.write(char(sent) + 48);
  sent++;
  Wire.endTransmission();

  Wire.requestFrom(8, 4);

  int n = 0;
  while (Wire.available())
  {
    char c = Wire.read();
    Serial.print(c);
    arr1[n] = c;
    n++;
  }

  Serial.println();

  for (n = 0; n < 4; n++)
  {
    arr[n] = int(arr1[n]);
    arr[n] = arr[n] - 48;
  }

  //----------------------------------------------------//

  // Now we will publish stuff!
  if (arr[0] >= 0 && arr[0] <= 5 && arr[1] >= 0 && arr[1] <= 5 && arr[2] >= 0 && arr[2] <= 5 && arr[3] >= 0 && arr[3] <= 5)
  {
    //    Serial.println(F("\nSending Number of Vehicle "));

    //--------------------------------------------------------
    if (arr[0] != arrP[0])
    {
      Serial.println("Data for Ground Floor...");
      Serial.print("Gnd Floor = ");
      Serial.println(arr[0]);
      Serial.print("...");
      if (! f0.publish(arr[0]))
      {
        Serial.println(F("Failed"));
      }
      else
      {
        Serial.println(F("Published!"));
      }
      arrP[0] = arr[0];
      delay(500);
    }
    //-----------------------------------------------------------
    if (arr[1] != arrP[1])
    {
      Serial.println("Data for 1st Floor...");
      Serial.print("1st Floor = ");
      Serial.println(arr[1]);
      Serial.print("...");
      if (! f1.publish(arr[1]))
      {
        Serial.println(F("Failed"));
      }
      else
      {
        Serial.println(F("Published!"));
      }
      arrP[1] = arr[1];
      delay(500);
    }
    //-----------------------------------------------------------
    if (arr[2] != arrP[2])
    {
      Serial.println("Data for 2nd Floor...");
      Serial.print("2nd Floor = ");
      Serial.println(arr[2]);
      Serial.print("...");
      if (! f2.publish(arr[2]))
      {
        Serial.println(F("Failed"));
      }
      else
      {
        Serial.println(F("Published!"));
      }
      arrP[2] = arr[2];
      delay(500);
    }
    //-----------------------------------------------------------
    if (arr[3] != arrP[3]) //Checking if prev data is equal to the current data/not... In this case we'll not publish any data..
    {
      Serial.println("Data for 3rd Floor...");
      Serial.print("3rd Floor = ");
      Serial.println(arr[3]);
      Serial.print("...");
      if (! f3.publish(arr[3]))
      {
        Serial.println(F("Failed"));
      }
      else
      {
        Serial.println(F("Published!"));
      }
      arrP[3] = arr[3];
      delay(500);
    }
    delay(200);
    digitalWrite(led, LOW);
  }//End of BIG if condition...

  //Filling of DATA...

  if (arr[0] >= 0 && arr[0] <= 5 && arr[1] >= 0 && arr[1] <= 5 && arr[2] >= 0 && arr[2] <= 5 && arr[3] >= 0 && arr[3] <= 5)
  {
    for (int k = 0; k < 4; k++)
    {
      tft.setCursor(TEXT_X + 60, 45 + (75 * k));
      if (arr[k] == 5)
      {
        tft.setTextColor(TEXT_TCOLOR, ILI9341_RED);
        tft.setTextSize(TEXT_TSIZE);
        tft.print(arr[k]);
      }
      else
      {
        tft.setTextColor(TEXT_TCOLOR, ILI9341_DARKGREEN);
        tft.setTextSize(TEXT_TSIZE);
        tft.print(arr[k]);
      }
    }
  }
  //End of filling of DATA...


  //======================================================================//


  //Filling Rectangles RED...
  if (arr[0] == 5 && flagR[0] == 0)
  {
    tft.fillRect(TEXT_X + 1, 35 + 1, TEXT_W - 2, TEXT_H - 2, ILI9341_RED);

    tft.setCursor(TEXT_X + 105, 35 + 10);
    tft.setTextColor(TEXT_TCOLOR, ILI9341_RED);
    tft.setTextSize(TEXT_TSIZE);
    tft.print("/  5");
    flag[0] = 1;
    flagR[0] = 1;
  }
  //Filling Rectangles Green...
  if (arr[0] != 5 && flag[0] == 1)
  {
    tft.fillRect(TEXT_X + 1, 35 + 1, TEXT_W - 2, TEXT_H - 2, ILI9341_DARKGREEN);

    tft.setCursor(TEXT_X + 105, 35 + 10);
    tft.setTextColor(TEXT_TCOLOR, ILI9341_DARKGREEN);
    tft.setTextSize(TEXT_TSIZE);
    tft.print("/  5");
    flag[0] = 0;
    flagR[0] = 0;
  }


  //======================================================================//


  //Filling Rectangles RED...
  if (arr[1] == 5 && flagR[1] == 0)
  {
    tft.fillRect(TEXT_X + 1, 110 + 1, TEXT_W - 2, TEXT_H - 2, ILI9341_RED);

    tft.setCursor(TEXT_X + 105, 110 + 10);
    tft.setTextColor(TEXT_TCOLOR, ILI9341_RED);
    tft.setTextSize(TEXT_TSIZE);
    tft.print("/  5");
    flag[1] = 1;
    flagR[1] = 1;
  }
  //Filling Rectangles Green...
  if (arr[1] != 5 && flag[1] == 1)
  {
    tft.fillRect(TEXT_X + 1, 110 + 1, TEXT_W - 2, TEXT_H - 2, ILI9341_DARKGREEN);

    tft.setCursor(TEXT_X + 105, 110 + 10);
    tft.setTextColor(TEXT_TCOLOR, ILI9341_DARKGREEN);
    tft.setTextSize(TEXT_TSIZE);
    tft.print("/  5");
    flag[1] = 0;
    flagR[1] = 0;
  }


  //======================================================================//


  //Filling Rectangles RED...
  if (arr[2] == 5 && flagR[2] == 0)
  {
    tft.fillRect(TEXT_X + 1, 185 + 1, TEXT_W - 2, TEXT_H - 2, ILI9341_RED);

    tft.setCursor(TEXT_X + 105, 185 + 10);
    tft.setTextColor(TEXT_TCOLOR, ILI9341_RED);
    tft.setTextSize(TEXT_TSIZE);
    tft.print("/  5");
    flag[2] = 1;
    flagR[2] = 1;
  }
  //Filling Rectangles Green...
  if (arr[2] != 5 && flag[2] == 1)
  {
    tft.fillRect(TEXT_X + 1, 185 + 1, TEXT_W - 2, TEXT_H - 2, ILI9341_DARKGREEN);

    tft.setCursor(TEXT_X + 105, 185 + 10);
    tft.setTextColor(TEXT_TCOLOR, ILI9341_DARKGREEN);
    tft.setTextSize(TEXT_TSIZE);
    tft.print("/  5");
    flag[2] = 0;
    flagR[2] = 0;
  }


  //======================================================================//


  //Filling Rectangles RED...
  if (arr[3] == 5 && flagR[3] == 0)
  {
    tft.fillRect(TEXT_X + 1, 260 + 1, TEXT_W - 2, TEXT_H - 2, ILI9341_RED);

    tft.setCursor(TEXT_X + 105, 260 + 10);
    tft.setTextColor(TEXT_TCOLOR, ILI9341_RED);
    tft.setTextSize(TEXT_TSIZE);
    tft.print("/  5");
    flag[3] = 1;
    flagR[3] = 1;
  }
  //Filling Rectangles Green...
  if (arr[3] != 5 && flag[3] == 1)
  {
    tft.fillRect(TEXT_X + 1, 260 + 1, TEXT_W - 2, TEXT_H - 2, ILI9341_DARKGREEN);

    tft.setCursor(TEXT_X + 105, 260 + 10);
    tft.setTextColor(TEXT_TCOLOR, ILI9341_DARKGREEN);
    tft.setTextSize(TEXT_TSIZE);
    tft.print("/  5");
    flag[3] = 0;
    flagR[3] = 0;
  }  //End of 2nd BIG if loop....
} //End of void loop()....

//-------------------------------------------------------------------------------------//

// Function to connect and reconnect as necessary to the MQTT server.
// Should be called in the loop function and it will take care if connecting.

void MQTT_connect() {
  int8_t ret;

  // Stop if already connected.
  if (mqtt.connected()) {
    return;
  }

  Serial.print("Connecting to MQTT... ");

  uint8_t retries = 3;
  while ((ret = mqtt.connect()) != 0) { // connect will return 0 for connected
    Serial.println(mqtt.connectErrorString(ret));
    Serial.println("Retrying MQTT connection in 5 seconds...");
    mqtt.disconnect();
    delay(5000);  // wait 5 seconds
    retries--;
    if (retries == 0) {
      // basically die and wait for WDT to reset me
      while (1);
    }
  }
  Serial.println("MQTT Connected!");
}// End of MQTT Connet Function..
