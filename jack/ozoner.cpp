#include <Arduino.h>
#include "ozoner.h"

ozoner::ozoner(byte relayPin,byte monitoringLedPin,circPump * cP) {
  ozonerOn=false;
  ozonerMuted=false;
  ozonerRelayPin=relayPin;
  ozonerMonitoringLedPin=monitoringLedPin;
  pinMode(ozonerRelayPin,OUTPUT);
  pinMode(ozonerMonitoringLedPin,OUTPUT);
  digitalWrite(ozonerRelayPin,HIGH);
  digitalWrite(ozonerMonitoringLedPin,LOW);
  blinkCounter=0;
  cPump=cP;
}

void ozoner::generalStopSet() {
  generalStop=true;  
}

void ozoner::generalStopUnset() {
  generalStop=false;  
}

bool ozoner::isOzonerMuted() {
  return ozonerMuted;
}

bool ozoner::isOzonerRunning() {
  return ozonerOn;
}
void ozoner::ozonerMute() {
  ozonerMuted=true;
  stopOzoner();
}

void ozoner::ozonerUnMute() {
  ozonerMuted=false;
}

byte ozoner::getNexRunCycle(byte hoursNow) {
  byte i=1;
  while((hoursNow+i)%4) {
    i++;
  }
  return hoursNow+i;
}
void ozoner::runOzoner(byte hoursNow) {
  if (generalStop) {
    stopOzoner();
    return;  
  }
  if (!ozonerMuted) {
    if (cPump->isCircPumpRunning()) {
      if(hoursNow%4==0 || forceOzoner) {
        ozonerOn=true;
        digitalWrite(ozonerRelayPin,LOW);
      }
      else {
        stopOzoner();
      }
    }
    else {
      stopOzoner();  
    }
  }
  else {
    stopOzoner();  
  }
}

void ozoner::stopOzoner() {
  ozonerOn=false;
  digitalWrite(ozonerRelayPin,HIGH);
  digitalWrite(ozonerMonitoringLedPin,LOW);
  blinkCounter=0;
}

byte ozoner::getOzonerRelayPin() {
  return ozonerRelayPin;
}

byte ozoner::getOzonerMonitoringLedPin() {
  return ozonerMonitoringLedPin;
}

void ozoner::ozonerRefresh() {
  if(!ozonerOn) {
    return;
  }
  if(blinkCounter>10 && blinkCounter<14) {
    digitalWrite(ozonerMonitoringLedPin,HIGH);
  }
  if(blinkCounter==15) {
    digitalWrite(ozonerMonitoringLedPin,LOW);  
  }
  blinkCounter++;
  blinkCounter=blinkCounter%20;
}
