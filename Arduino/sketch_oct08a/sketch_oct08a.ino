
void setup() {
  Serial.begin(9600);
  pinMode(8,OUTPUT);
  pinMode(10, INPUT);

}
void loop() {
int  buttonState = digitalRead(10);
 if (buttonState == HIGH) {
    // turn LED on:
    digitalWrite(8, HIGH);
  } else {
    // turn LED off:
    digitalWrite(8, LOW);
  }

}
