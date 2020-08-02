   /*******************************************************************
    Using a 64 * 64 RGB Matrix to display YT Subscriber stats
 *                                                                 *
    Read YouTube Channel statistics from the YouTube API on
    an ESP8266 and print them to the serial monitor
                                                                  
    Parts:
    D1 Mini ESP8266 (or any ESP8266) * - http://s.click.aliexpress.com/e/uzFUnIe
    * = Affilate
   
    If you find what I do useful and would like to support me,
    please consider becoming a sponsor on Github
    https://github.com/sponsors/witnessmenow/
    Written by Brian Lough
    YouTube: https://www.youtube.com/brianlough
    Tindie: https://www.tindie.com/stores/brianlough/
    Twitter: https://twitter.com/witnessmenow
 *******************************************************************/

// ----------------------------
// Standard Libraries
// ----------------------------
//Youtube API
#include <ESP8266WiFi.h>
#include <WiFiClientSecure.h>
//LED MATRIX
#include <Ticker.h>

// ----------------------------
// Additional Libraries - each one of these will need to be installed.
// ----------------------------

//LED MATRIX
#include <PxMatrix.h>
// The library for controlling the LED Matrix
// Needs to be manually downloaded and installed
// https://github.com/2dom/PxMatrix

//Youtube API
#include <YoutubeApi.h>
// Library for connecting to the Youtube API
// Search for "youtube" in the Arduino Library Manager
// https://github.com/witnessmenow/arduino-youtube-api

#include <ArduinoJson.h>
// Library used for parsing Json from the API responses
// Search for "Arduino Json" in the Arduino Library manager
// https://github.com/bblanchon/ArduinoJson

 
//------- Replace the following! ------
char ssid[] = "yourssid";       // your network SSID (name)
char password[] = "key";  // your network key
//Youtube API
#define API_KEY "your_google_apps_API_Token"  // your google apps API Token 
#define CHANNEL_ID "your_YT_CHANNEL_ID" // makes up the url of channel

//------------------------------

Ticker display_ticker;

WiFiClientSecure client;
YoutubeApi api(API_KEY, client);

// Youtube API
unsigned long timeBetweenRequests = 60000;
unsigned long nextRunTime;

long subs = 0;

// Pins for LED MATRIX
#define P_LAT 16
#define P_A 5
#define P_B 4
#define P_C 15
#define P_OE 2
#define P_D 12
#define P_E 0

// PxMATRIX display(64,16,P_LAT, P_OE,P_A,P_B,P_C);
// PxMATRIX display(64,32,P_LAT, P_OE,P_A,P_B,P_C,P_D);
PxMATRIX display(64, 64, P_LAT, P_OE, P_A, P_B, P_C, P_D, P_E);

// Some standard colors
uint16_t myRED = display.color565(255, 0, 0);
uint16_t myGREEN = display.color565(0, 255, 0);
uint16_t myBLUE = display.color565(0, 0, 255);
uint16_t myWHITE = display.color565(255, 255, 255);
uint16_t myYELLOW = display.color565(255, 255, 0);
uint16_t myCYAN = display.color565(0, 255, 255);
uint16_t myMAGENTA = display.color565(255, 0, 255);
uint16_t myBLACK = display.color565(0, 0, 0);

uint16 myCOLORS[8] = {myRED, myGREEN, myBLUE, myWHITE, myYELLOW, myCYAN, myMAGENTA, myBLACK};

// Converted using the following site: http://www.rinkydinkelectronics.com/t_imageconverter565.php
uint16_t static youTubeBigger[] = {
  0x0000, 0x0000, 0xF800, 0xF800, 0xF800, 0xF800, 0xF800, 0xF800, 0xF800, 0xF800, 0xF800, 0xF800, 0xF800, 0xF800, 0xF800, 0xF800,   // 0x0010 (16) pixels
  0xF800, 0xF800, 0xF800, 0x0000, 0x0000, 0x0000, 0xF800, 0xF800, 0xF800, 0xF800, 0xF800, 0xF800, 0xF800, 0xF800, 0xF800, 0xF800,   // 0x0020 (32) pixels
  0xF800, 0xF800, 0xF800, 0xF800, 0xF800, 0xF800, 0xF800, 0xF800, 0xF800, 0x0000, 0xF800, 0xF800, 0xF800, 0xF800, 0xF800, 0xF800,   // 0x0030 (48) pixels
  0xF800, 0xF800, 0xFFFF, 0xF800, 0xF800, 0xF800, 0xF800, 0xF800, 0xF800, 0xF800, 0xF800, 0xF800, 0xF800, 0xF800, 0xF800, 0xF800,   // 0x0040 (64) pixels
  0xF800, 0xF800, 0xF800, 0xF800, 0xF800, 0xF800, 0xF800, 0xFFFF, 0xFFFF, 0xF800, 0xF800, 0xF800, 0xF800, 0xF800, 0xF800, 0xF800,   // 0x0050 (80) pixels
  0xF800, 0xF800, 0xF800, 0xF800, 0xF800, 0xF800, 0xF800, 0xF800, 0xF800, 0xF800, 0xF800, 0xF800, 0xFFFF, 0xFFFF, 0xFFFF, 0xF800,   // 0x0060 (96) pixels
  0xF800, 0xF800, 0xF800, 0xF800, 0xF800, 0xF800, 0xF800, 0xF800, 0xF800, 0xF800, 0xF800, 0xF800, 0xF800, 0xF800, 0xF800, 0xF800,   // 0x0070 (112) pixels
  0xF800, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xF800, 0xF800, 0xF800, 0xF800, 0xF800, 0xF800, 0xF800, 0xF800, 0xF800, 0xF800, 0xF800,   // 0x0080 (128) pixels
  0xF800, 0xF800, 0xF800, 0xF800, 0xF800, 0xF800, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xF800, 0xF800, 0xF800, 0xF800, 0xF800,   // 0x0090 (144) pixels
  0xF800, 0xF800, 0xF800, 0xF800, 0xF800, 0xF800, 0xF800, 0xF800, 0xF800, 0xF800, 0xF800, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF,   // 0x00A0 (160) pixels
  0xFFFF, 0xF800, 0xF800, 0xF800, 0xF800, 0xF800, 0xF800, 0xF800, 0xF800, 0xF800, 0xF800, 0xF800, 0xF800, 0xF800, 0xF800, 0xF800,   // 0x00B0 (176) pixels
  0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0x0000, 0xF800, 0xF800, 0xF800, 0xF800, 0xF800, 0xF800, 0xF800, 0xF800, 0xF800, 0xF800,   // 0x00C0 (192) pixels
  0xF800, 0xF800, 0xF800, 0xF800, 0xF800, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0x0000, 0xF800, 0xF800, 0xF800, 0xF800, 0xF800, 0xF800,   // 0x00D0 (208) pixels
  0xF800, 0xF800, 0xF800, 0xF800, 0xF800, 0xF800, 0xF800, 0xF800, 0xF800, 0xF800, 0xFFFF, 0xFFFF, 0xFFFF, 0x0000, 0xF800, 0xF800,   // 0x00E0 (224) pixels
  0xF800, 0xF800, 0xF800, 0xF800, 0xF800, 0xF800, 0xF800, 0xF800, 0xF800, 0xF800, 0xF800, 0xF800, 0xF800, 0xF800, 0xF800, 0xFFFF,   // 0x00F0 (240) pixels
  0xFFFF, 0x0000, 0xF800, 0xF800, 0xF800, 0xF800, 0xF800, 0xF800, 0xF800, 0xF800, 0xF800, 0xF800, 0xF800, 0xF800, 0xF800, 0xF800,   // 0x0100 (256) pixels
  0xF800, 0xF800, 0xF800, 0xF800, 0xFFFF, 0x0000, 0xF800, 0xF800, 0xF800, 0xF800, 0xF800, 0xF800, 0xF800, 0xF800, 0xF800, 0xF800,   // 0x0110 (272) pixels
  0xF800, 0xF800, 0xF800, 0xF800, 0xF800, 0xF800, 0xF800, 0xF800, 0xF800, 0x0000, 0xF800, 0xF800, 0xF800, 0xF800, 0xF800, 0xF800,   // 0x0120 (288) pixels
  0xF800, 0xF800, 0xF800, 0xF800, 0xF800, 0xF800, 0x0000, 0xF800, 0xF800, 0xF800, 0xF800, 0xF800, 0xF800, 0xF800, 0xF800, 0xF800,   // 0x0130 (304) pixels
  0xF800, 0xF800, 0xF800, 0xF800, 0xF800, 0xF800, 0xF800, 0xF800, 0xF800, 0xF800, 0x0000, 0x0000, 0x0000, 0xF800, 0xF800, 0xF800,   // 0x0140 (320) pixels
  0xF800, 0xF800, 0xF800, 0xF800, 0xF800, 0xF800, 0xF800, 0xF800, 0xF800, 0xF800, 0xF800, 0xF800, 0xF800, 0xF800, 0x0000, 0x0000,   // 0x0150 (336) pixels
};


// ISR for display refresh
void display_updater()
{

  display.display(100);

}
void setup() {

  // Define your display layout here, e.g. 1/8 step
  display.begin(32);
  display.setBrightness(5);
  //display.setMuxDelay(1,1,1,1,1);
  display.setPanelsWidth(1);
  display.clearDisplay();
  display.setTextColor(myWHITE);
  display.setCursor(2, 0);
  display.print("Connecting");
  //display.setTextColor(myMAGENTA);
  display.setCursor(2, 8);
  display.print("to the");
  //display.setTextColor(myGREEN);
  display.setCursor(2, 16);
  display.print("WiFi!");
  display.setCursor(2, 24);
  display.print("YouTubeSub");
  display.setCursor(2, 32);
  display.print("display V2");
  delay(30000);
  // Set WiFi to station mode and disconnect from an AP if it was Previously
  // connected
  WiFi.mode(WIFI_STA);
  WiFi.disconnect();
  delay(500);

  // Attempt to connect to Wifi network:
  Serial.print("Connecting Wifi: ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  IPAddress ip = WiFi.localIP();
  Serial.println(ip);

  Serial.begin(115200);
  client.setInsecure();

  Serial.print("Pixel draw latency in us: ");
  unsigned long start_timer = micros();
  display.drawPixel(1, 1, 0);
  unsigned long delta_timer = micros() - start_timer;
  Serial.println(delta_timer);

  Serial.print("Display update latency in us: ");
  start_timer = micros();
  display.display(0);
  delta_timer = micros() - start_timer;
  Serial.println(delta_timer);

  display_ticker.attach(0.002, display_updater);
  yield();
  delay(1000);
  display.clearDisplay();
  displayName("James","Work","Shop"); // seemed to crash when I used lower case letters at the bottom!
  delay(5000);
}

void drawYouTube(int x, int y)
{
  int counter = 0;
  for (int yy = 0; yy < 16; yy++)
  {
    for (int xx = 0; xx < 21; xx++)
    {
      display.drawPixel(xx + x , yy + y, youTubeBigger[counter]);
      counter++;
    }
  }
}

void displayText(String text, int yPos) {
  int16_t  x1, y1;
  uint16_t w, h;
  display.setTextSize(2);
  char charBuf[text.length() + 1];
  text.toCharArray(charBuf, text.length() + 1);
  display.getTextBounds(charBuf, 0, yPos, &x1, &y1, &w, &h);
  int startingX = 33 - (w / 2);
  if (startingX < 0) {
    display.setTextSize(1);
    display.getTextBounds(charBuf, 0, yPos, &x1, &y1, &w, &h);
    startingX = 33 - (w / 2);
  }
  display.setCursor(startingX, yPos);
  Serial.println(startingX);
  Serial.println(yPos);
  display.print(text);
}

void updateScreensubCount(long subCount) {
  display.clearDisplay();
  display.setTextSize(1);  
  display.setTextColor(myWHITE);
  display.setCursor(18, 3);
  display.print("James");
  display.setTextSize(1);  
  display.setTextColor(myWHITE);
  display.setCursor(8, 11);
  display.print("workshop");
  drawYouTube(21 , 20);
  display.setTextColor(myWHITE);
  displayText(String(subCount), 38);
  display.setTextSize(1);  
  display.setCursor(3, 53);
  display.print("Subscriber");

}

void updateScreenviewCount(long viewCount) {
  display.clearDisplay();
  display.setTextSize(1);  
  display.setTextColor(myWHITE);
  display.setCursor(18, 3);
  display.print("James");
  display.setTextSize(1);  
  display.setTextColor(myWHITE);
  display.setCursor(8, 11);
  display.print("workshop");
  drawYouTube(21 , 20);
  display.setTextColor(myWHITE);
  displayText(String(viewCount/1000)+ "K", 38);
  display.setTextSize(1);  
  display.setCursor(21, 52);
  display.print("view");

}

void displayName(String A, String B, String C)
{
  display.setTextColor(myCYAN);
  displayText(A, 1);
  display.setTextColor(myMAGENTA);
  displayText(B, 28);
  display.setTextColor(myMAGENTA);
  displayText(C, 45);  
}

void loop() {
    if(api.getChannelStatistics(CHANNEL_ID))
      {
        Serial.println("---------Update---------");
        for(int i = 0; i <= 9; i++){
          Serial.println("---------Stats---------");
          Serial.print("i = ");
          Serial.println(i);
          Serial.print("Subscriber Count: ");
          Serial.println(api.channelStats.subscriberCount);
          updateScreensubCount(api.channelStats.subscriberCount);
          delay(40000);      
          Serial.print("view Count: ");
          Serial.println(api.channelStats.viewCount);
          updateScreenviewCount(api.channelStats.viewCount);
          delay(20000);  
        }
      }
  }
