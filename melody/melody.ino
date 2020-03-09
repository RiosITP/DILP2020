/*

David Rios
NYU IMA - Designing Interfaces for Live Performance 2020

Resources:
https://itp.nyu.edu/physcomp/labs/labs-arduino-digital-and-analog/tone-output-using-an-arduino/

*/

int y = 13;
int b = 12;
int speaker = 3;
int del = 200;

void setup() {
  pinMode(speaker, OUTPUT);
  pinMode(y, INPUT);
  pinMode(b, INPUT);
}

void loop() {
del = map(analogRead(A0),0,1023,500,50);
  
  if (digitalRead(y) == 0 && digitalRead(b) == 0 ) {
    tone(speaker, 440); // A
    delay(del);
    tone(speaker, 330); // E
    delay(del);
    tone(speaker, 392); // G
    delay(del);
    noTone(speaker);
  }
  if (digitalRead(y) == 1 && digitalRead(b) == 0) {

    tone(speaker, 587); // D
    delay(del);
    tone(speaker, 392); // G
    delay(del);

    tone(speaker, 880); // A
    delay(del);
    noTone(speaker);
  }

  if (digitalRead(b) && digitalRead(y) == 0) {
    tone(speaker, 523); // C
    delay(del);
    tone(speaker, 87); // D
    delay(del);
    tone(speaker, 784); // G
    delay(del);
    noTone(speaker);
  }

  if (digitalRead(b) && digitalRead(y)) {
    tone(speaker, 40); // C
    delay(del);
    noTone(speaker); // D
    delay(del);
    tone(speaker, 40); // G
    delay(del);
    noTone(speaker);
    delay(del);
  }

}
