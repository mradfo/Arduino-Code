#include <Wire.h>
#include <LiquidCrystal.h>
#include <LiquidCrystal_I2C.h>

// initialize the library with the numbers of the interface pins
LiquidCrystal_I2C lcd(0x27,16,2);

signed short minutes = 00, seconds = 05;
char timeline[16];
int done = 0;
const int buttonPin = 2; 
int buttonState = 0;
void end();


void setup()
{
  lcd.begin(16, 2); // set up the LCD's number of columns and rows:
  lcd.init(); //initialize the lcd
  lcd.backlight(); //open the backlight
  lcd.print("Timer: ");
  pinMode(2, INPUT);

}

void loop()
{
  buttonState = digitalRead(buttonPin); 
  if(buttonState == HIGH){
    while (done == 0) {
      lcd.setCursor(0, 1);
      sprintf(timeline,"%0.2d mins %0.2d secs", minutes, seconds);
      lcd.print(timeline);
      
      delay(1000);
      seconds--;

      if (seconds == 00) {
        if (minutes == 0) {
          done = 1;
          lcd.clear();
          lcd.print("It has been 30 minutes.");
          delay(1000);
          lcd.clear();
          lcd.print("Go outside");
          delay(1000);
          lcd.clear();
          return;
        } else {
          seconds = 59;     
          minutes --;
        }
      }
    }
  }
}
