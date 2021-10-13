# RGB-LED-Matrix-YouTube-Sub-Display
Displaying live YouTube subscriber count using an LED Matrix and and ESP8266 (Arduino)

Always hope to create a unique YouTube subscriber counter, 
When I found the Adafruit GFX compatible graphics driver for LED matrix panels library & Arduino YouTube API written by Brian Lough, I knew I wanted my YouTube subscriber counter to look like this

Thanks to Brian Lough for the inspiration and the original sketch.

Here is a note of my production process. For more detailed instructions, please go to [Brian Lough's GitHub](https://github.com/witnessmenow)

![github](https://github.com/James-workshop/RGB-LED-Matrix-YouTube-Sub-Display/blob/master/RGB-LED-Matrix-YouTube-Sub-Display.jpg "RGB LED Matrix YouTube Sub Display")

# Hardware
* D1 Mini
* 220uF 25V Capacitor
* 220k Ohm Resistor
* 1N4001 Diode
* 3 pin male header
* 1 Jumper block
* 16 pin female header (2x8)
* 16 pin right angle male header (2x8)
* Large Green screw terminals (KF8500-2P-8.4MM)
* 3 Line Dip Switch (VDG-03HG-R)
* 5.0mm Screw Terminals 2Pin *2
* D1 Mini Matrix Shield PCB
* RGB LED Matrix Panel that is compatible with the PXMatrix library wiring [Described Here](https://github.com/2dom/PxMatrix#set-up-and-cabling)

![github](https://github.com/James-workshop/RGB-LED-Matrix-YouTube-Sub-Display/blob/master/Schematic.png "Schematic")


## D1 Mini Matrix Shield PCB
I have made a PCB at JLCPCB.com that makes using these displays really easy! It makes use of the wires than come with the displays for easier connections.

![github](https://github.com/James-workshop/RGB-LED-Matrix-YouTube-Sub-Display/blob/master/PCB_V2.1.png "PCB V2.1")


### ![github](https://jlcpcb.com/client/svg/nv_logo.svg "JLCPCB") Make hardware development easier, Higher Quality & Lower Cost
### New registered users offer , **Order here https://jlcpcb.com/HAR**
### You can use my Gerber file to place an order at JLCPCB.com
<BR><BR><BR>
### Change log of Version
V2.2
* Adjust PCB size
![github](https://github.com/James-workshop/RGB-LED-Matrix-YouTube-Sub-Display/blob/master/PCB_V2.2.jpg "PCB V2.2")

V2.1
* Reduce PCB size, suitable on some smaller displays


V1.1
* First version

  
## How to make<BR>
  <a href="https://youtu.be/3v2Arlc7Ogg">https://youtu.be/3v2Arlc7Ogg</a>
      ![github](https://github.com/James-workshop/RGB-LED-Matrix-YouTube-Sub-Display/blob/master/Cover_photo.jpg "Youtube Cover Photo")

# Install & config Libraries
## Arduino YouTube API
### Getting a Google Apps API key (Required!)
* Create an application [here](https://console.developers.google.com/)
* On the API Manager section, go to "Credentials" and create a new API key
* Enable your application to communicate the YouTube Api [here](https://console.developers.google.com/apis/api/youtube)
* Make sure the following URL works for you in your browser (Change the key at the end!): <https://www.googleapis.com/youtube/v3/channels?part=statistics&id=UCezJOfu7OtqGzd5xrP3q6WA&key=PutYourNewlyGeneratedKeyHere>


### Installing
The easiest way to install this library is through the aduino library manager, just search for "Youtube"

You also have to install the ArduinoJson library written by [Benoît Blanchon](https://github.com/bblanchon). Search for it on the Arduino Library manager or get it from [here](https://github.com/bblanchon/ArduinoJson).

Include YoutubeApi in your project:

> #include <YoutubeApi.h>

and pass it a Bot token and a SSL Client (See the examples for more details)

>#define API_KEY "XXXXXXXXX:XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX"
>
>WiFiClientSecure client; //For ESP8266 boards
>
>YoutubeApi bot(API_KEY, client);


## PxMatrix - LED matrix panel driver for ESP8266, ESP32 and ATMEL

detailed instructions, please go to [Dominic Buchstaller](https://github.com/2dom/PxMatrix)



