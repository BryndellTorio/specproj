#include <Arduino.h>

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
}

void loop() {
    // pixels.clear(); // Set all pixel colors to 'off'
    //
    // // The first NeoPixel in a strand is #0, second is 1, all the way up
    // // to the count of pixels minus one.
    // for(int i=0; i<NUMPIXELS; i++) { // For each pixel...
    //
    //   // pixels.Color() takes RGB values, from 0,0,0 up to 255,255,255
    //   // Here we're using a moderately bright green color:
    //   pixels.setPixelColor(i, pixels.Color(224, 141, 60));
    //
    //   pixels.show();   // Send the updated pixel colors to the hardware.
    //
    //   delay(DELAYVAL); // Pause before next pass through loop
    // }
    if(Serial.available() == 0) {
        String Command = Serial.readStringUntil('#');
        if (Command == "ON") {
            for(int i = 0; i<NUMPIXELS; i++) {
                pixels.setPixelColor(i, pixels.Color(155,38,182));
                // pixels.setPixelColor(i, pixels.Color(224, 141, 60));
                pixels.show();
            }
            Serial.println("ON Command initiated.");
        } else if(Command == "OFF") {
            pixels.clear();
            pixels.show();
            Serial.println("OFF Command initiated.");
        } else if (Command == "SEQ1") {
            for(int i = 0;i<NUMPIXELS; i++) {
                // pixels.setPixelColor(i, pixels.Color(224, 141, 60));
                pixels.setPixelColor(i, pixels.Color(155,38,182));
                pixels.show();
                delay(DELAYVAL);
            }
            Serial.println("Sequence 1 initiated.");
        } else if(Command == "GREEN") {
            for(int i = 0; i<NUMPIXELS; i++) {
                pixels.setPixelColor(i, pixels.Color(0,255,0));
                // pixels.setPixelColor(i, pixels.Color(224, 141, 60));
                pixels.show();
            }
            Serial.println("Color set to green.");
        } else if(Command == "RED") {
            for(int i = 0; i<NUMPIXELS; i++) {
                pixels.setPixelColor(i, pixels.Color(255,0,0));
                // pixels.setPixelColor(i, pixels.Color(224, 141, 60));
                pixels.show();
            }
            Serial.println("Color set to red.");
        } else if(Command == "BLUE") {
            for(int i = 0; i<NUMPIXELS; i++) {
                pixels.setPixelColor(i, pixels.Color(0,0,255));
                // pixels.setPixelColor(i, pixels.Color(224, 141, 60));
                pixels.show();
            }
            Serial.println("Color set to blue.");
        }
    }
}
