# RGB-LED-Matrix-YouTube-Sub-Display
Displaying live YouTube subscriber count using an LED Matrix and and ESP8266 (Arduino)

Always hope to create a unique YouTube subscriber counter, 
When I found the Adafruit GFX compatible graphics driver for LED matrix panels library & Arduino YouTube API written by Brian Lough, I knew I wanted my YouTube subscriber counter to look like this

Thanks to Brian Lough for the inspiration and the original sketch.

Here is a note of my production process. For more detailed instructions, please go to [Brian Lough's GitHub](https://github.com/witnessmenow)



# Arduino YouTube API
## Getting a Google Apps API key (Required!)
* Create an application [here](https://console.developers.google.com/)
* On the API Manager section, go to "Credentials" and create a new API key
* Enable your application to communicate the YouTube Api [here](https://console.developers.google.com/apis/api/youtube)
* Make sure the following URL works for you in your browser (Change the key at the end!): <https://www.googleapis.com/youtube/v3/channels?part=statistics&id=UCezJOfu7OtqGzd5xrP3q6WA&key=PutYourNewlyGeneratedKeyHere>


## Installing
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

# PxMatrix - LED matrix panel driver for ESP8266, ESP32 and ATMEL

detailed instructions, please go to [Dominic Buchstaller](https://github.com/2dom/PxMatrix)



