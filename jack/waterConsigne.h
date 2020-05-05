#ifndef waterConsigne_h
#define waterConsigne_h
#include <arduino.h>
#include "myClock.h"



class waterConsigne {
  public:
    waterConsigne(byte consigne,myClock * mClock);
    void setConsigne(byte newConsigne);
    byte getConsigne();
    byte incConsigne();
    byte decConsigne();

  private:
    byte consigne;
    byte maxConsigne;
    byte minConsigne;
    myClock * theClock;
    
};
#endif
