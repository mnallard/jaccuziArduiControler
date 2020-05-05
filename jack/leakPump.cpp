#include <Arduino.h>
#include "leakPump.h"

leakPump::leakPump(byte relayPin) {
  pumpOn=false;
  pumpMute=false;
  leakPumpRelayPin=relayPin;
  pinMode(leakPumpRelayPin,OUTPUT);
  digitalWrite(leakPumpRelayPin,HIGH);
}

void leakPump::generalStopSet() {
  generalStop=true;  
}

void leakPump::generalStopUnset() {
  generalStop=false;  
}

bool leakPump::isLeakPumpForced() {
  return leakPumpForced; 
}

void leakPump::leakPumpForce() {
  leakPumpForced=true;  
}
    
void leakPump::leakPumpUnforce() {
  leakPumpForced=false;
  pumpOn=false;
  digitalWrite(leakPumpRelayPin,HIGH);
}
    
void leakPump::runPump() {
  if(generalStop) {
    pumpOn=false;
    digitalWrite(leakPumpRelayPin,HIGH);
    return;   
  }
  if(leakPumpForced) {
    pumpOn=true;
    digitalWrite(leakPumpRelayPin,LOW);
    return;
  }
  if(!pumpMute) {
    pumpOn=true;
    digitalWrite(leakPumpRelayPin,LOW);
  }
  else {
    pumpOn=false;
    digitalWrite(leakPumpRelayPin,HIGH);
  }
}

void leakPump::leakPumpUnMute() {
  pumpMute=false;
}

void leakPump::leakPumpMute() {
  pumpMute=true;
}

bool leakPump::isLeakPumpRunning() {
  return pumpOn;
}

bool leakPump::isLeakPumpMuted() {
  return pumpMute;
}
void leakPump::stopPump() {
  pumpOn=false;
  digitalWrite(leakPumpRelayPin,HIGH);
}

byte leakPump::getleakPumpRelayPin() {
  return leakPumpRelayPin;
}
