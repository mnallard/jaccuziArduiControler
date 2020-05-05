#ifndef myDisplay_h
#define myDisplay_h
#include <arduino.h>
#include <LiquidCrystal.h>

class myDisplay {
  public:
    void lcdWriteLine1(String str);
    void lcdWriteLine2(String str);
    void lcdResfresh();
    myDisplay(byte d4pin,byte d5pin,byte d6pin,byte d7pin,byte rsPin,byte EnablePin);
    myDisplay(LiquidCrystal * mLcd);
  private:
    byte dataPin[4];
    byte rsPin;
    byte enablePin;
    LiquidCrystal * mLcd;
};
#endif
