#ifndef myMenu_h
#define myMenu_h
#include <arduino.h>
#include "myDisplay.h"
#include "waterConsigne.h"
#include "waterTemperature.h"
#include "waterWarmer.h"
#include "circPump.h"
#include "leakLevel.h"
#include "leakPump.h"
#include "ozoner.h"


class myMenu {
  public:
    myMenu(myDisplay * lcdScreen,waterConsigne * cons,waterTemperature * temp,waterWarmer * warmer,circPump * circ,leakPump * leakP,leakLevel * lLvl,ozoner * oz);
    void nextMenu();
    void previousMenu();
    void displayMenu();
    byte getStepMenu();
    void plusPressed();
    void minusPressed();
    void mutePressed();
    void recircPressed();
    void forceWarmPressed();
    void stopStartPressed();
    void leakPumpPressed();
    void displayMainScreen(String dateNow,byte hNow);
    void ozonerPressed();
    
  private:
    byte stepMenu;
    byte nbMenu=6;
    int  loopCount;
    int mainLoopCount=0;
    myDisplay * lcd;
    waterConsigne * consigne;
    waterTemperature * wTemperature;
    waterWarmer * wWarmer;
    leakPump * wleakPump;
    circPump * circP;
    ozoner * wOzoner;
    leakLevel * wLeakLevel;
    bool muteState;
    byte hoursNow;
    bool recircMuted=false;
    bool ozonerMuted=false;
    bool forceWarm=false;
    bool leakPumpMuted=false;
    bool stopStartP=false;
    
};
#endif
