#include <Arduino.h>
#include "waterConsigne.h"
#include "myClock.h"

waterConsigne::waterConsigne(byte cons,myClock * mClock) {
  consigne=cons;
  maxConsigne=40;
  minConsigne=20;
  theClock=mClock;
  byte co=0;
  //if(theClock->getFromModuleMem(0,&co)) {
  //  consigne=co;   
  //} 
}

void waterConsigne::setConsigne(byte newConsigne) {
  consigne=newConsigne;
  theClock->sendInModuleMem(0,consigne);
}

byte waterConsigne::getConsigne() {
  return consigne;
}

byte waterConsigne::incConsigne() {
  if (consigne<maxConsigne) {
    consigne++; 
    return 1; 
  }
  return 0;
}

byte waterConsigne::decConsigne() {
  if (consigne>minConsigne) {
    consigne--; 
    return 1; 
  }
  return 0;
}
