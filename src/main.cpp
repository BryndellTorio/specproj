#include <Arduino.h>

/* Definitions for HC-05 BT module. */

#include <SoftwareSerial.h>

const byte txPin = 3;
const byte rxPin = 2;

SoftwareSerial BTSerial(rxPin, txPin);

// NeoPixel Ring simple sketch (c) 2013 Shae Erisson
// Released under the GPLv3 license to match the rest of the
// Adafruit NeoPixel library

#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
#include <avr/power.h> // Required for 16 MHz Adafruit Trinket
#endif

// Which pin on the Arduino is connected to the NeoPixels?
#define PIN        6 // On Trinket or Gemma, suggest changing this to 1

// How many NeoPixels are attached to the Arduino?
#define NUMPIXELS 16 // Popular NeoPixel ring size

// When setting up the NeoPixel library, we tell it how many pixels,
// and which pin to use to send signals. Note that for older NeoPixel
// strips you might need to change the third parameter -- see the
// strandtest example for more information on possible values.
Adafruit_NeoPixel pixels(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

#define DELAYVAL 500 // Time (in milliseconds) to pause between pixels

void setup() {
    // These lines are specifically to support the Adafruit Trinket 5V 16 MHz.
    // Any other board, you can remove this part (but no harm leaving it):
#if defined(__AVR_ATtiny85__) && (F_CPU == 16000000)
    clock_prescale_set(clock_div_1);
#endif
    // END of Trinket-specific code.

    pixels.begin(); // INITIALIZE NeoPixel strip object (REQUIRED)

    Serial.begin(115200);

    /* Setup for BT module */
    BTSerial.begin(9600);
    pinMode(txPin, OUTPUT);
    pinMode(rxPin, INPUT);
    
}

char dataByte;

void loop() {
    /* BT module code definitions */
    while(BTSerial.available()) {
        dataByte = BTSerial.read();
        Serial.write(dataByte);
    }

    while(Serial.available()) {
        dataByte = Serial.read();
        BTSerial.write(dataByte);
    }

    if(Serial.available() == 0) {
        String Command = Serial.readStringUntil('#');
        if (Command == "ON") {
            for(int i = 0; i<NUMPIXELS; i++) {
                pixels.setPixelColor(i, pixels.Color(155,38,182));
                pixels.show();
            }
            Serial.println("ON Command initiated.");
        } else if(Command == "OFF") {
            pixels.clear();
            pixels.show();
            Serial.println("OFF Command initiated.");
        } else if (Command == "SEQ1") {
            for(int i = 0;i<NUMPIXELS; i++) {
                pixels.setPixelColor(i, pixels.Color(155,38,182));
                pixels.show();
                delay(DELAYVAL);
            }
            Serial.println("Sequence 1 initiated.");
        } else if(Command == "GREEN") {
            for(int i = 0; i<NUMPIXELS; i++) {
                pixels.setPixelColor(i, pixels.Color(0,255,0));
                pixels.show();
            }
            Serial.println("Color set to green.");
        } else if(Command == "RED") {
            for(int i = 0; i<NUMPIXELS; i++) {
                pixels.setPixelColor(i, pixels.Color(255,0,0));
                pixels.show();
            }
            Serial.println("Color set to red.");
        } else if(Command == "BLUE") {
            for(int i = 0; i<NUMPIXELS; i++) {
                pixels.setPixelColor(i, pixels.Color(0,0,255));
                pixels.show();
            }
            Serial.println("Color set to blue.");
        } else if (Command == "TIGEREYE") {
            for(int i = 0; i<NUMPIXELS; i++) {
                pixels.setPixelColor(i, pixels.Color(224,141,60));
                pixels.show();
            }
            Serial.println("Color set to TIRGEREYE.");
        }
    }
}
