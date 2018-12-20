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
float hwpangle = 0;
float power = analogval/1023.0;

const int navg = 10;

const int minangle = 0, maxangle = 45, offset = 0;
const float gear_ratio = 1.0;
const float maxservoangle = maxangle*gear_ratio;

const int maxpower = 600; // mW at sample at 100% power setting ==> arbitrarily set on 181213, enter actual value.

boolean continuous = true; //vary without set pin
int roundto = 10;
int prevval = 0;


void setup() {
  pinMode(setpin,INPUT);

  hwpservo.attach(9);
  hwpservo.write(offset + hwpangle);
  delay(250);

  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print(String(power*100) + " %");
  lcd.setCursor(0,1);
  lcd.print(String(round(maxpower*power)) + " mW");
  
}


void loop() {

  setval = digitalRead(setpin);

  if (setval == HIGH) {
    analogval = analogSample(navg);
    setPosition(analogval);
  }

  if (continuous) {
    
    analogval = roundToNearest(analogSample(navg),roundto);
    if (analogval > 1023) {
      analogval = 1023;
    }
    
    if (analogval != prevval) {
      setPosition(analogval);
    }
    
    prevval = analogval;
  
  }

}


void setPosition(int val) {

  //hwpangle = map(val, 0, 1023, minangle, maxangle); // not linearized

  power = val/1023.0;

  hwpangle = (acos(1-(2*power))*(maxservoangle))/PI; // linearized
  
  hwpservo.write(offset + hwpangle);
  
  delay(250);

  lcd.clear();
  
  lcd.setCursor(0,0);
  lcd.print(String(power*100) + " %");
  lcd.setCursor(0,1);
  lcd.print(String(round(maxpower*power)) + " mW, 181213");

}


int analogSample(int numtoavg) {

  int val = 0;
  for (int i=0; i<numtoavg; i++) {
    val += analogRead(valpin);
    //delay(10);
  }
  val = val/numtoavg;

  return val;
  
}


int roundToNearest(int a, int nearest)
{
  return a >= 0 ? (a+2)/nearest*nearest : (a-2)/nearest*nearest ;
}

