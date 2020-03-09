/*
  David Rios
  NYU IMA - Designing Interfaces for Live Performance 2020
  Class 06 - Feb 19
  Serial Communication
  Handshake Setup with buttons
*/

int yellow = 12;
int blue = 11;
int led = 10;

void setup() {
  Serial.begin(9600);
  pinMode(yellow, INPUT);
  pinMode(blue, INPUT);
  pinMode(led, OUTPUT);
  digitalWrite(led,LOW);
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
    int incoming = Serial.read();
    digitalWrite(led,HIGH);
    Serial.print(yel);
    Serial.print(",");
    Serial.print(blu);
    Serial.print(",");
    Serial.println(pot);
  }
    digitalWrite(led,LOW);
}
