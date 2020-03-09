
/*
  David Rios
  NYU IMA - Designing Interfaces for Live Performance 2020
  Class 07 - Feb 19
  Serial Communication

  Based on Adafruit examples:
  https://learn.adafruit.com/dma-driven-neopixels
  Written By: Phillip Burgess
*/

#include <Adafruit_NeoPixel_ZeroDMA.h>

// DMA NeoPixels work ONLY on SPECIFIC PINS.
// On Circuit Playground Express: 8, A2 and A7 (TX) are valid.
// On Feather M0, Arduino Zero, etc.: 5, 11, A5 and 23 (SPI MOSI).
// On GEMMA M0: pin 0.
// On Trinket M0: pin 4.
// On Metro M4: 3, 6, 8, 11, A3 and MOSI
#define PIN         11
#define NUM_PIXELS 60


Adafruit_NeoPixel_ZeroDMA strip(NUM_PIXELS, PIN, NEO_GRB);

int yellow = 12;
int blue = 9;
int led = 10;
int level = 2;
void setup() {

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
  for (int i = 0; i < NUM_PIXELS ; i++) {
    strip.setPixelColor(i, strip.Color(0, 0, 0));
  }
  strip.show();
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
    for (int i = 0; i < NUM_PIXELS ; i++) {
      if (i <= level) {
        strip.setPixelColor(i, strip.Color(255, 0, 125));
      } else {
        strip.setPixelColor(i, strip.Color(0, 0, 0));
      }
    }
    strip.show();
  }
}
