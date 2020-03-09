/*

David Rios
NYU IMA - Designing Interfaces for Live Performance 2020
Code for DILP MIDI/ Arduino Class 2020

Code based off ArduinoZeroMidi Example:
https://github.com/arduino/tutorials/blob/master/ArduinoZeroMidi/ArduinoZeroMidi.ino
*/


#include <frequencyToNote.h>
#include <MIDIUSB.h>
#include <MIDIUSB_Defs.h>
#include <pitchToFrequency.h>
#include <pitchToNote.h>


// Variables:
byte note = 0;            // The MIDI note value to be played
byte note2 = 0;
int y = 12;
int b = 9;
boolean ywasPressed = false;
boolean bwasPressed = false;

void setup() {
  Serial.begin(9600);
  pinMode(y, INPUT);
  pinMode(b, INPUT);
}

void loop() {

  if (digitalRead(y) == 1 && !wasPressed) {
    // Channel, CC# , Value
    controlChange(0x00,21,0x05);
    // delay(100);
    ywasPressed = true;
  }

  if (digitalRead(y) == 0 && wasPressed) {
    ywasPressed = false;
  }
 
  if (digitalRead(b) == 1 && !wasPressed) {
    // Channel, CC# , Value
    controlChange(0x00,22,0x05);
    // delay(100);
    bwasPressed = true;
  }

  if (digitalRead(b) == 0 && wasPressed) {
    bwasPressed = false;
  }
}

void controlChange(byte channel, byte control, byte value) {
  midiEventPacket_t event = {0x0B, 0xB0 | channel, control, value};
  MidiUSB.sendMIDI(event);
}
