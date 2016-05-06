#include <SPI.h>
#include <Adafruit_GFX.h>
#include <TFT_ILI9163C.h>
#include "DHT.h"

#define DHTPIN 2     // what digital pin we're connected to
#define DHTPIN2 4

// Uncomment whatever type you're using!
#define DHTTYPE DHT11   // DHT 11
//#define DHTTYPE DHT22   // DHT 22  (AM2302), AM2321
//#define DHTTYPE DHT21   // DHT 21 (AM2301)

// Connect pin 1 (on the left) of the sensor to +5V
// NOTE: If using a board with 3.3V logic like an Arduino Due connect pin 1
// to 3.3V instead of 5V!
// Connect pin 2 of the sensor to whatever your DHTPIN is
// Connect pin 4 (on the right) of the sensor to GROUND
// Connect a 10K resistor from pin 2 (data) to pin 1 (power) of the sensor

// Initialize DHT sensor.
// Note that older versions of this library took an optional third parameter to
// tweak the timings for faster processors.  This parameter is no longer needed
// as the current DHT reading algorithm adjusts itself to work on faster procs.
DHT dht(DHTPIN, DHTTYPE);
DHT dht2(DHTPIN2, DHTTYPE);

const int VAL_PROBE = 0; //Analog pin 0
const int MOISTURE_LEVEL = 250; // the value after the LED goes on

// Color definitions
#define	BLACK   0x0000
#define	BLUE    0x001F
#define	RED     0xF800
#define	GREEN   0x07E0
#define CYAN    0x07FF
#define MAGENTA 0xF81F
#define YELLOW  0xFFE0  
#define WHITE   0xFFFF

/*
Teensy3.x and Arduino's
You are using 4 wire SPI here, so:
 MOSI:  11//Teensy3.x/Arduino UNO (for MEGA/DUE refere to arduino site)
 MISO:  12//Teensy3.x/Arduino UNO (for MEGA/DUE refere to arduino site)
 SCK:   13//Teensy3.x/Arduino UNO (for MEGA/DUE refere to arduino site)
 the rest of pin below:
 */
#define __CS 10
#define __DC 9
/*
Teensy 3.x can use: 2,6,9,10,15,20,21,22,23
Arduino's 8 bit: any
DUE: check arduino site
If you do not use reset, tie it to +3V3
*/


TFT_ILI9163C tft = TFT_ILI9163C(__CS,8, __DC);

void setup() {
  Serial.begin(9600);
  tft.begin();
  dht.begin();
}

void loop(){   
  int moisture = analogRead(VAL_PROBE);
  String m=String(moisture);  
  String output="Umidità"+m;  
  Serial.print("Umidita: ");
  Serial.println(m);
  tft.fillScreen();
  tft.setCursor(0, 0);
  tft.setTextSize(1);
  tft.println(output);

  float h = dht.readHumidity();
  // Read temperature as Celsius (the default)
  float t = dht.readTemperature();
  String sT=String(t);
  String sH=String(h);
  tft.println("Temperatura: " + sT);
  tft.println("Umidita aria: "+sH);  
  
  float h2 = dht2.readHumidity();
  // Read temperature as Celsius (the default)
  float t2 = dht2.readTemperature();
  String sT2=String(t2);
  String sH2=String(h2);
  tft.println("Temperatura2: " + sT2);
  tft.println("Umidita aria2: "+sH2);  
  delay(2000); 
}


unsigned long testText(String text) {
  
  unsigned long start = micros();
  tft.setCursor(0, 0);
  tft.setTextColor(WHITE);  
  tft.setTextSize(1);
  tft.println(text);  
  return micros() - start;
}

