int samples = 200;
float audioIn;
float audioPrevious;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  audioIn = 0;
  audioPrevious = 0;
  pinMode(3, OUTPUT);
}

void loop() {
  float vol = 0;
  //  sense = analogRead(A1);

  for (int i = 0 ; i < samples; i++) {
    int mic = analogRead(A0);
    audioIn = mic;
    vol = vol + abs(audioIn - audioPrevious);
    audioPrevious = audioIn;
  }
  vol = vol / samples;
  Serial.println(vol);
  if (vol > 10) {
    vol = map(vol,9.0,100.0,200.0,1000.0);
    tone(3, vol);
  }
  else {
    noTone(3);
  }
}
