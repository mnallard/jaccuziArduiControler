#include <Arduino.h>
#include "myMenu.h"
#include "myDisplay.h"

myMenu::myMenu(myDisplay * lcdScreen,waterConsigne * cons,waterTemperature * wTemp,waterWarmer * warmer,circPump * cP,leakPump * leakP,leakLevel * lLvl,ozoner * oz) {
  stepMenu=0; 
  lcd=lcdScreen;
  consigne=cons;
  wTemperature=wTemp;
  wWarmer=warmer;
  wleakPump=leakP;
  wLeakLevel=lLvl;
  wOzoner=oz;
  circP=cP;
  muteState=false;
  loopCount=0;
  recircMuted=false; 
  ozonerMuted=false; 
  leakPumpMuted=false;  
}

void myMenu::nextMenu() {
  stepMenu++;
  stepMenu=stepMenu%nbMenu; 
  loopCount=100;
  displayMenu();
}

void myMenu::previousMenu() {
  if (!stepMenu) {
    stepMenu=nbMenu-1;
  }
  else {
    stepMenu--;  
  }
  loopCount=100;
  displayMenu();
}

void myMenu::plusPressed() {
  if (stepMenu==1) {
    if(consigne->incConsigne()) {
      loopCount=100;
      displayMenu();
    }
    else {
      lcd->lcdWriteLine2("MAX");
      delay(1000);
      loopCount=100;
      displayMenu();
    } 
  }
  if (stepMenu==5) {
    if(wleakPump->isLeakPumpForced()) {
      wleakPump->leakPumpForce();   
    }
    else {
      wleakPump->leakPumpUnforce();
    }
  }
}
  
void myMenu::minusPressed() {
  if (stepMenu==1) {
    if (consigne->decConsigne()) {
      loopCount=100;
      displayMenu();  
    }
    else {
      lcd->lcdWriteLine2("MIN");
      delay(1000);
      loopCount=100;
      displayMenu();
    }
  }  
}

void myMenu::mutePressed() {
  if(muteState) {
    lcd->lcdWriteLine1("Setting WARMER");
    lcd->lcdWriteLine2("ON");
    muteState=false;
    wWarmer->warmerUnMute();
    delay(2000);
    loopCount=100;
    displayMenu();
  }
  else {
    lcd->lcdWriteLine1("Setting WARMER");
    lcd->lcdWriteLine2("OFF");
    muteState=true;
    wWarmer->warmerMute();
    delay(2000);
    loopCount=100;
    displayMenu(); 
  }
}
void myMenu::stopStartPressed() {
  if(!stopStartP) {
    lcd->lcdWriteLine1("STOP/START");
    lcd->lcdWriteLine2("All periph STOP");
    wWarmer->generalStopSet();
    wOzoner->generalStopSet();
    circP->generalStopSet();
    wleakPump->generalStopSet();
    stopStartP=true;
  }
  else {
    stopStartP=false;
    lcd->lcdWriteLine1("STOP/START");
    lcd->lcdWriteLine2("All periph ON");
    circP->generalStopUnset();
    wOzoner->generalStopUnset();
    wWarmer->generalStopUnset(); 
    wleakPump->generalStopUnset(); 
  }
  delay(2000);
  loopCount=100;
  displayMenu(); 
}
void myMenu::forceWarmPressed() {
  if(forceWarm) {
    lcd->lcdWriteLine1("WARMER forced");
    lcd->lcdWriteLine2("OFF");
    forceWarm=false;
    wWarmer->forceWarmUnset();
    delay(2000);
    loopCount=100;
    displayMenu();  
    return;
  }
  lcd->lcdWriteLine1("WARMER forced");
  lcd->lcdWriteLine2("ON");
  forceWarm=true;
  wWarmer->forceWarmSet();
  delay(2000);
  loopCount=100;
  displayMenu(); 
}

void myMenu::leakPumpPressed() {
  if(leakPumpMuted) {
    lcd->lcdWriteLine1("Setting LeakPump");
    lcd->lcdWriteLine2("AUTO");
    leakPumpMuted=false;
    wleakPump->leakPumpUnMute();
    delay(2000);
    loopCount=100;
    displayMenu();  
  }
  else {
    lcd->lcdWriteLine1("Setting LeakPump");
    lcd->lcdWriteLine2("OFF");
    leakPumpMuted=true;
    wleakPump->leakPumpMute();
    delay(2000);
    loopCount=100;
    displayMenu(); 
  }
}
void myMenu::ozonerPressed() {
  if(ozonerMuted) {
    lcd->lcdWriteLine1("Setting OZONER");
    lcd->lcdWriteLine2("AUTO");
    ozonerMuted=false;
    wOzoner->ozonerUnMute();
    delay(2000);
    loopCount=100;
    displayMenu();  
  }
  else {
    lcd->lcdWriteLine1("Setting OZONER");
    lcd->lcdWriteLine2("OFF");
    ozonerMuted=true;
    wOzoner->ozonerMute();
    delay(2000);
    loopCount=100;
    displayMenu(); 
  }
}

void myMenu::recircPressed() {
  if(recircMuted) {
    lcd->lcdWriteLine1("Setting RECIRC");
    lcd->lcdWriteLine2("ON");
    recircMuted=false;
    circP->circPumpUnMute();
    delay(2000);
    loopCount=100;
    displayMenu();
  }
  else {
    lcd->lcdWriteLine1("Setting RECIRC");
    lcd->lcdWriteLine2("OFF");
    recircMuted=true;
    circP->circPumpMute();
    delay(2000);
    loopCount=100;
    displayMenu(); 
  }
}

byte myMenu::getStepMenu() {
  return stepMenu;
}


void myMenu::displayMainScreen(String dateNow,byte hNow) {
  if(loopCount) {
    mainLoopCount=0;
    loopCount--;
    return;
  }
  if(mainLoopCount) {
    mainLoopCount--;
    return;
  }
  hoursNow=hNow;
  stepMenu=0;
  lcd->lcdResfresh();
  lcd->lcdWriteLine1(dateNow);
  lcd->lcdWriteLine2("Temp:"+String(wTemperature->getTemperature())+"  Cons:"+String(consigne->getConsigne()));
  mainLoopCount=300;
}
void myMenu::displayMenu() {
  lcd->lcdResfresh();
  if (!stepMenu) {
    lcd->lcdWriteLine1("TEMPERATURE     ");
    lcd->lcdWriteLine2(String(wTemperature->getTemperature()));
  }
  if (stepMenu==1) {
    lcd->lcdWriteLine1("CONSIGNE        ");
    lcd->lcdWriteLine2(String(consigne->getConsigne()));
  }
  if (stepMenu==2) {
    lcd->lcdWriteLine1("CIRC PUMP     ");
    if(circP->isCircPumpRunning()) {
      lcd->lcdWriteLine2("Run: Y");
    }
    else {
      lcd->lcdWriteLine2("Run: N");  
    }
  }
  if (stepMenu==3) {
    lcd->lcdWriteLine1("OZONER     ");
    if(wOzoner->isOzonerRunning()) {
      lcd->lcdWriteLine2("Run: Y");
    }
    else {
      String lineToDisp="Run: N. Next:";
      byte nextRun=wOzoner->getNexRunCycle(hoursNow);
      lineToDisp+=nextRun+"h";
      lcd->lcdWriteLine2(lineToDisp);
    }
  }
  if (stepMenu==4) { 
    if(wWarmer->isWarmerMuted()) {
      lcd->lcdWriteLine1("WARMER (MUTE)");
    }
    else {
      lcd->lcdWriteLine1("WARMER");     
    }
    String warmerDisp="Run: ";
    if (wWarmer->isWarmerRunning()) {
      warmerDisp+="Y";
    }
    else {
      warmerDisp+="N";  
    }
    warmerDisp+=" Should: ";
    if (wWarmer->isWarmerShouldRun()) {
      warmerDisp+="Y";
    }
    else {
      warmerDisp+="N";   
    }
    lcd->lcdWriteLine2(warmerDisp); 
  }
  if (stepMenu==5) {
    lcd->lcdWriteLine1("LEAK LVL/PUMP");
    if(wleakPump->isLeakPumpRunning()) {
      String toDisp="Pump:Y Lvl:"+wLeakLevel->getLeakInstantValue();
      lcd->lcdWriteLine2(toDisp);
    }
    else {
      String toDisp="Pump:N Lvl:"+wLeakLevel->getLeakInstantValue();
      lcd->lcdWriteLine2(toDisp);
    }
  }
}
