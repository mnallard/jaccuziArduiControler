#ifndef myIR_h
#define myIR_h
#include <arduino.h>
#include <IRremote.h>
#include "myMenu.h"


class myIR {
  public:
    myIR(IRrecv * irrcv,myMenu * menu);
    void IRtreat();
  private:
    IRrecv * irReceiver;
    myMenu * jacMenu;
};
#endif
