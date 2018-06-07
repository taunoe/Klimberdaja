//
const int volumePin = 7;
//Pin connected to latch pin (ST_CP) of 74HC595
const int latchPin = 8;
//Pin connected to clock pin (SH_CP) of 74HC595
const int clockPin = 12;
//Pin connected to Data in (DS) of 74HC595
const int dataPin = 11;

/*
  note  frequency
  c     262 Hz
  d     294 Hz
  e     330 Hz
  f     349 Hz
  g     392 Hz
  a     440 Hz
  b     494 Hz
  C     523 Hz
 */
int notes[] = {262, 294, 330, 349, 392, 440, 494, 523};

int sensorValue;//potsentsiomeeter

void setup() {
  //set pins to output because they are addressed in the main loop
  pinMode(latchPin, OUTPUT);
  pinMode(dataPin, OUTPUT);  
  pinMode(clockPin, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  sensorValue = analogRead(A0);
   // random number from 48 to 57
  int bitToSet = random(0, 8);
  
  Serial.println(bitToSet);
  registerWrite(bitToSet, HIGH);
  
  tone(volumePin, notes[bitToSet]);
  
  if (sensorValue < 40){
    sensorValue = 40;
    }
    delay(sensorValue);

}


// This method sends bits to the shift register:

void registerWrite(int whichPin, int whichState) {
  byte bitsToSend = 0;

  // turn off the output so the pins don't light up
  // while you're shifting bits:
  digitalWrite(latchPin, LOW);

  // turn on the next highest bit in bitsToSend:
  bitWrite(bitsToSend, whichPin, whichState);

  // shift the bits out:
  shiftOut(dataPin, clockPin, MSBFIRST, bitsToSend);

    // turn on the output so the LEDs can light up:
  digitalWrite(latchPin, HIGH);

}


