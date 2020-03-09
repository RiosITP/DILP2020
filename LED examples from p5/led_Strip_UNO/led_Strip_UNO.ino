

/*
  David Rios
  NYU IMA - Designing Interfaces for Live Performance 2020
  Class 06 - Feb 19
  Serial Communication
*/
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
#define NUMPIXELS 60 // Popular NeoPixel ring size

// When setting up the NeoPixel library, we tell it how many pixels,
// and which pin to use to send signals. Note that for older NeoPixel
// strips you might need to change the third parameter -- see the
// strandtest example for more information on possible values.
//Adafruit_NeoPixel pixels(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);
//Adafruit_NeoPixel strip =  Adafruit_NeoPixel_ZeroDMA(60, 6, NEO_GRB);

#define DELAYVAL 500 // Time (in milliseconds) to pause between pixels
int yellow = 12;
int blue = 11;
int led = 10;
int level = 2;
void setup() {
  // These lines are specifically to support the Adafruit Trinket 5V 16 MHz.
  // Any other board, you can remove this part (but no harm leaving it):
#if defined(__AVR_ATtiny85__) && (F_CPU == 16000000)
  clock_prescale_set(clock_div_1);
#endif
  // END of Trinket-specific code.

  strip.begin(); // INITIALIZE NeoPixel strip object (REQUIRED)
  strip.setBrightness(50);
  strip.show(); // Initialize all pixels to 'off'

  Serial.begin(9600);
  pinMode(yellow, INPUT);
  pinMode(blue, INPUT);
  pinMode(led, OUTPUT);
  digitalWrite(led, LOW);
  while (Serial.available() <= 0) {
    Serial.println("hello");
    delay(200);
  }
}

void loop() {

  int yel = digitalRead(yellow);
  int blu = digitalRead(blue);
  int pot = map(analogRead(A0), 0, 1023, 255, 0);


  if (Serial.available() > 0) {
    //int incoming = Serial.parseInt();
    int incoming = Serial.read();
    analogWrite(led, incoming);
    Serial.print(yel);
    Serial.print(",");
    Serial.print(blu);
    Serial.print(",");
    Serial.println(pot);

    level = map(incoming, 0, 255, 0, 60);
    for (int i = 0; i < NUMPIXELS ; i++) {
      if (i <= level) {
        strip.setPixelColor(i, strip.Color(255, 0, 125));
      } else {
        strip.setPixelColor(i, strip.Color(0, 0, 0));
      }
    }
    strip.show();
  }

}
