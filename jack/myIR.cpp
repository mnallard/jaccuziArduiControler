#include <Arduino.h>
#include "myIR.h"
#include <IRremote.h>

myIR::myIR(IRrecv * irRecv,myMenu * menu) {
  irReceiver=irRecv; 
  jacMenu=menu;
}


void myIR::IRtreat() {
  decode_results resultat;
  while (irReceiver->decode(&resultat)) {
    int codeIr=resultat.value;
    Serial.println(codeIr,HEX);
    
    if (codeIr==0xFFFFFF) {
      // nothing  to do repeat   
    }
    if (codeIr==0xFFFFE01F) {
      jacMenu->ozonerPressed();
    }
    if (codeIr==0xFFFFB04F) {
      jacMenu->leakPumpPressed();
    }
    if (codeIr==0xFFFFC23D) {
      jacMenu->nextMenu();
    }
    if (codeIr==0x000002FD) {
      jacMenu->previousMenu();
    }
    
    if (codeIr==0xFFFFA25D) {
      //stop start
    }
    if (codeIr==0xFFFF906F) {
      jacMenu->plusPressed();
    }
    if (codeIr==0xFFFFA857) {
      jacMenu->minusPressed();
      //-
    }
    if (codeIr ==0xFFFFE21D) {
      jacMenu->mutePressed();
      //mute
    }
    if (codeIr ==0xFFFF9867) {
      jacMenu->recircPressed();
    }

    if (codeIr==0x000022DD) {
      jacMenu->forceWarmPressed();
    }

    if(codeIr==0xFFFFA25D) {
      jacMenu->stopStartPressed();
    }

    delay(20);
    irReceiver->resume();
  }
}
