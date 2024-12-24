const int RED_PIN = 11;
const int GREEN_PIN = 10;
const int BLUE_PIN = 9;


void setup() {
  // put your setup code here, to run once:
  pinMode(RED_PIN, OUTPUT);
  pinMode(GREEN_PIN, OUTPUT);
  pinMode(BLUE_PIN, OUTPUT);
  //Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  color_loop();
        
}

void color_loop(){
  int r = 255;
  int g,b = 0;
  for(int i = 0; i < 1530; i++){
    analogWrite(RED_PIN, r);
    analogWrite(BLUE_PIN, b);
    analogWrite(GREEN_PIN, g);
    delay(10);
    /*Serial.print("R:");
    Serial.print(r);
    Serial.print(" G:");
    Serial.print(g);
    Serial.print(" B:");
    Serial.println(b);*/
    if(i >= 0 && i < 255){
      b++;
    }else if(i >= 255 && i < 510){
      r--;
    }else if(i >= 510 && i < 765){
      g++;
    }else if(i >= 765 && i < 1020){
      b--;
    }else if(i >= 1020 && i < 1275){
      r++;
    }else if(i >= 1275 && i < 1530){
      g--;
    }
  }
}
