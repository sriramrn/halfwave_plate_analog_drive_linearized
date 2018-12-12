#include <LiquidCrystal.h>

#include <Servo.h>
Servo hwpservo;

#define PI 3.141592

const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

const int setpin = 8;
const int valpin = A0;

boolean setval = LOW;
int analogval = 0;
int hwpangle = 0;
int power = 100*analogval/1023;

const int navg = 10;

const int minangle = 0, maxangle = 45, offset = 0, gear_ratio;
const int maxservoangle = maxangle*gear_ratio;


void setup() {
  pinMode(setpin,INPUT);

  hwpservo.attach(9);
  hwpservo.write(offset + hwpangle);
  delay(250);

  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  // Print a message to the LCD.
  lcd.print(power);
  
}


void loop() {

  setval = digitalRead(setpin);

  if (setval == HIGH) {
    setPosition();
  }

}


void setPosition() {

  analogval = 0;
  for (int i=0; i<navg; i++) {
    analogval += analogRead(valpin);
    delay(10);
  }
  analogval = analogval/navg;

  //hwpangle = map(analogval, 0, 1023, minangle, maxangle); // not linearized

  power = 100*analogval/1023;

  hwpangle = acos(1-2*power)*maxservoangle/PI; // linearized
  
  hwpservo.write(offset + hwpangle);
  
  delay(250);

  lcd.clear();
  lcd.print(power);
  
}

