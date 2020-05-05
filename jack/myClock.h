#ifndef myClock_h
#define myClock_h
#include "DS1307.h"
class myClock {
  public:
    void setClockTime(DateTime_t datetime);
    bool getClockTime(DateTime_t * datetime,String * outP); 
    bool getClockState();
    bool validClock();
    bool sendInModuleMem(byte octNum,byte value);
    bool getFromModuleMem(byte octNum,byte * value);
    myClock();
    myClock(DateTime_t datetime);

  private:
    bool stateClock;
};
#endif
