#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <string.h>

// Set the LCD address to 0x27 for a 16 chars and 2 line display
LiquidCrystal_I2C lcd(0x27, 16, 2);

const int buzzer = 9;
const int hot_to_go_length = 18;
const int double_life_length = 23;
const int bridget_song_length = 16;
const int god_save_the_queen_length = 41;
const int happy_birthday_length = 25;
const int trigPin = 10;  
const int echoPin = 11;
const int ledPin1 = 12;
const int ledPin2 = 13;
const int buttonPin = 2;
float duration, distance;
int buttonState = 0;
int idx = 0;
const int num_songs = 5;

// notes
const int Cs4 = 277;
const int D4 = 294;
const int Ef4 = 311;
const int E4 = 330;
const int Fs4 = 370;
const int G4 = 392;
const int Af4 = 415;
const int nA4 = 440;
const int Bf4 = 466;
const int B4 = 494;
const int C5 = 523;
const int Cs5= 554;
const int D5 = 588;
const int Ef5 = 622;
const int E5 = 659;
const int F5 = 698;
const int Fs5 = 740;
const int G5 = 784;
const int Af5 = 831;
const int Bf5 = 932;
const int rest = 0;

int ledState = HIGH;

// all songs and their durations
int hot_to_go_notes[hot_to_go_length] = {Bf4, Cs5, Cs5, Cs5, Ef5, 
                    Cs5, Ef5, Cs5, rest, Bf4, Cs5, 
                    Fs5, Af5, Af5, Bf5, Af5, Fs5};
double hot_to_go_durations[hot_to_go_length] = {1, 1, 1, 1,
                        1.5, 0.5, 0.5, 0.5, 1,
                        1, 1, 1, 1,
                        1.5, .5, .5, .5, 1};
int double_life_notes[double_life_length] = {Af4, Bf4, B4, Cs5, 
                        Ef5, Ef5, rest, Ef4, Ef4, Ef4, Ef4, 
                        Af4, Bf4, B4, Cs5, Ef5, Ef5, rest, Ef4, Ef4, Ef4, 
                        Ef4, rest};
double double_life_durations[double_life_length] = {1, 0.5, 1, 
                        0.5, 0.5, 0.5, 0.5, 1, 0.5, 1, 1, 1, 
                        0.5, 1, 0.5, 0.5, 0.5, 0.5, 1, 0.5, 1, 
                        1, 1};
int god_save_the_queen_notes[god_save_the_queen_length] = {D4, D4, E4, Cs4,
                        D4, E4, Fs4, Fs4, G4, Fs4, E4, D4, 
                        E4, D4, Cs4, D4, nA4, nA4, nA4, nA4, G4, Fs4, G4,
                        G4, G4, G4, Fs4, E4, Fs4, G4, Fs4,
                        E4, D4, Fs4, G4, nA4, B4, G4, Fs4, E4, D4};
double god_save_the_queen_durations[god_save_the_queen_length] = {1, 1, 1, 1.5, 0.5,
                        1, 1, 1, 1, 1.5, 0.5, 1, 1, 1, 1, 3, 1, 1, 1, 1.5, 0.5, 1,
                        1, 1, 1, 1.5, 0.5, 1, 1, 0.5, 0.5, 0.5, 0.5, 1.5, 0.5, 1, 0.5,
                        0.5, 1, 1, 3};
int bridget_song_notes[bridget_song_length] = {Bf5, Bf5, Bf5, 
                        G5, F5, Bf5, Bf5, rest, Bf5, Bf5, Bf5, 
                        G5, F5, Bf5, Bf5, rest};
double bridget_song_durations[bridget_song_length] = {1, 1, 0.5, 1, 0.5, 
                        1, 0.5, 2.5, 1, 1, 0.5, 1, 0.5, 1, 0.5, 2.5};
int happy_birthday_notes[happy_birthday_length] = {G4, G4, nA4, G4, C5, B4,
                        G4, G4, nA4, G4, D5, C5, G4, G4, G5, E5, C5, B4, nA4,
                        F5, F5, E5, C5, D5, C5};
double happy_birthday_durations[happy_birthday_length] = {0.5, 0.5, 1, 1, 1, 2,
                        0.5, 0.5, 1, 1, 1, 2, 0.5, 0.5, 1, 1, 1, 1, 1, 0.5, 0.5,
                        1, 1, 1, 3};


int *songs[num_songs] = {hot_to_go_notes, double_life_notes, god_save_the_queen_notes, bridget_song_notes,
                        happy_birthday_notes};
double *durations[num_songs] = {hot_to_go_durations, double_life_durations, god_save_the_queen_durations, bridget_song_durations,
                        happy_birthday_durations};
int lengths[num_songs] = {hot_to_go_length, double_life_length, god_save_the_queen_length, bridget_song_length, happy_birthday_length};
String titles[num_songs] = {"Hot To Go!", "Double Life", "God Save The Queen", "Man, I Feel Like A Woman",
                        "Happy Birthday"};

void setup() {
  // pin setup
  pinMode(buzzer, OUTPUT);
  pinMode(trigPin, OUTPUT);  
	pinMode(echoPin, INPUT); 
  pinMode(ledPin1, OUTPUT);
  pinMode(ledPin2, OUTPUT); 
  pinMode(buttonPin, OUTPUT);
	Serial.begin(9600);

  // initialize the LCD
  lcd.begin();

  // Turn on the blacklight
  lcd.backlight();
  lcd.print(titles[0]);

}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(trigPin, LOW);  
	delayMicroseconds(2);  
	digitalWrite(trigPin, HIGH);  
	delayMicroseconds(10);  
	digitalWrite(trigPin, LOW);  
  duration = pulseIn(echoPin, HIGH);
  distance = (duration*.0343)/2;

  // if button is pressed, move to next song
  buttonState = digitalRead(buttonPin);
  if (buttonState == HIGH){
    delay(500);
    idx = idx + 1;
    if (idx >= num_songs){
      idx = 0;
    }
    lcd.clear();
    if((titles[idx]).length() <= 16){
      lcd.print(titles[idx]);
      //Serial.println(titles[idx]);
    } else {
      String str1 = (titles[idx]).substring(0,16);
      String str2 = (titles[idx]).substring(16,(titles[idx]).length());
      lcd.print(str1);
      lcd.setCursor(0, 1);
      lcd.print(str2);
      //Serial.println(str1 + str2);
    }
  }
  // play song if something is within 80cm
  if (distance <= 120){
    for (int i = 0; i < lengths[idx]; i++){
      digitalWrite(ledPin1, ledState);
      digitalWrite(ledPin2, !ledState);
      ledState = !ledState;
      double waitTime = durations[idx][i] * 500;
      tone(buzzer, songs[idx][i], waitTime);
      //String debug = "note: " + String(songs[idx][i]) + " duration: " + String(durations[idx][i]) + " i: " + String(i) + " idx: " + String(idx);
      //Serial.println(debug);
      delay(waitTime); 
      // stop playing the song if the button is pressed
      buttonState = digitalRead(buttonPin);
      if (buttonState == HIGH){
        break;
      }
    }
    digitalWrite(ledPin1, LOW);
    digitalWrite(ledPin2, LOW);
  // otherwise get a new distance
  } else { 
	  delay(10);
  }
  
}
