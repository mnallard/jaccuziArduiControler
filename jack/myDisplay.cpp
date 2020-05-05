#include <Arduino.h>
#include "myDisplay.h"


myDisplay::myDisplay(LiquidCrystal * mlcd) {
  mLcd=mlcd;
  mLcd->begin(16,2);
  mLcd->print("Lcd start");    
}

void myDisplay::lcdWriteLine1(String str) {
  mLcd->setCursor(0,0);
  mLcd->print("                ");
  mLcd->setCursor(0,0);
  mLcd->print(str);
}

void myDisplay::lcdWriteLine2(String str) {
  mLcd->setCursor(0,1);
  mLcd->print("                ");
  mLcd->setCursor(0,1);
  mLcd->print(str);
}

void myDisplay::lcdResfresh() {
  mLcd->begin(16,2);
  mLcd->clear();
}
