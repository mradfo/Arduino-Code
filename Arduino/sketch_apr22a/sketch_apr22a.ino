const int Glow = 392;
const int A = 440;
const int AsBf = 466;
const int B = 494;
const int C =523;
const int CsDf= 554;
const int DsEf =622;
const int E =659;
const int F =698;
const int FsGf = 740;
const int G =784;
const int GsAf =831;
const int D =588;

const int buzzer = 12;
const int buttonPin = 2;
int buttonState = 0;

int notes[] = 
{D,E,C,A,B,Glow,0,
D,E,C,A,B,Glow,0,
D,E,C,A,B,AsBf,A,Glow,0,
0,
D,DsEf,E,C,E,C,E,C,0,
C,D,DsEf,E,C,D,E,B,D,C,0,
D,DsEf,E,C,E,C,E,C,0,
A,G,FsGf,A,C,E,D,C,A,D,0,

D,DsEf,E,C,E,C,E,C,0,
C,D,DsEf,E,C,D,E,B,D,C,0,

C,D,E,C,D,E,
C,D,C,E,C,D,E,
C,D,C,E,C,D,E,
B,D,C
};

int durations[] =
{250,250,250,500,250,250,250,
250,250,250,500,250,250,250,
250,250,250,500,250,250,250,250,250,
1000,
250,250,250,500,250,500,250,500,1000,
250,250,250,250,250,250,500,250,500,500,1000,
250,250,250,500,250,500,250,500,1000,
250,250,250,250,250,500,250,250,250,500,1000,

250,250,250,500,250,500,250,500,1000,
250,250,250,250,250,250,500,250,500,500,1000,

250,250,250,250,250,500,
250,250,250,250,250,250,500,
250,250,250,250,250,250,500,
250,500,250
};

const float songSpeed = 1.0;

void setup() {
 pinMode(buttonPin, INPUT);
}

void loop() {
  buttonState = digitalRead(buttonPin);

  if (buttonState == HIGH){
    const int totalNotes = sizeof(notes) / sizeof(int);
    for (int i = 0; i < totalNotes; i++) {
      const int currentNote = notes[i];
      float wait = durations[i] / songSpeed;
      // Play tone if currentNote is not 0 frequency, otherwise pause (noTone)
      if (currentNote != 0){
        tone(buzzer, notes[i], wait); // tone(pin, frequency, duration)
      }
      else {
       noTone(buzzer);
      }
      // delay is used to wait for tone to finish playing before moving to next loop
      delay(wait);
    }
  }
}
