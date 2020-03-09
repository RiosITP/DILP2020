/*
  David Rios
  NYU IMA - Designing Interfaces for Live Performance 2020
  Code for DILP MIDI/ Arduino Class 2020

  Code based off Tom Igoe's Midi USB Examples
  https://tigoe.github.io/SoundExamples/midiusb.html
*/


#include <frequencyToNote.h>
#include <MIDIUSB.h>
#include <MIDIUSB_Defs.h>
#include <pitchToFrequency.h>
#include <pitchToNote.h>


// Variables:

int y = 12;
int b = 9;
boolean wasPressed = false;
void setup() {
  Serial.begin(9600);
  pinMode(y, INPUT);
  pinMode(b, INPUT);
}

void loop() {
  /* map a potentiometer reading to a midi value
     Full MIDI Range is 0-127
  */
  note = map(analogRead(A0), 0, 1023, 30, 100);
  if (digitalRead(y) == 1) {
    // noteOn(MIDI Status, MIDI Note, MIDI Velocity)
    noteOn(0x90, note, 0x45);
    delay(100);
  } else {
    for (int i = 0; i < 128; i++) {
      noteOn(0x90, i, 0x00);
    }
  }

  if (digitalRead(b) == 1 && !wasPressed) {
    note2 = map(analogRead(A1), 0, 1023, 0, 127);
    noteOn(0x99, note2, 0x45);
    // delay(100);
    wasPressed = true;
  }

  //Turn all the notes OFF
  if (digitalRead(b) == 0 && wasPressed) {
    for (int i = 0; i < 128; i++) {
      noteOn(0x99, i, 0x00);
    }
    wasPressed = false;
  }
}

// plays a MIDI note. Doesn't check to see that
// cmd is greater than 127, or that data values are less than 127:
void noteOn(byte cmd, byte data1, byte data2) {
  /* First parameter is the event type (top 4 bits of the command byte).
     Second parameter is command byte combined with the channel.
     Third parameter is the first data byte
     Fourth parameter second data byte, if there is one:
  */
  midiEventPacket_t midiMsg = {cmd >> 4, cmd, data1, data2};
  MidiUSB.sendMIDI(midiMsg);

  //prints the values in the serial monitor so we can see what note we're playing
  Serial.print("cmd: ");
  Serial.print(cmd);
  Serial.print(", data1: ");
  Serial.print(data1);
  Serial.print(", data2: ");
  Serial.println(data2);
}
