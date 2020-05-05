#include <Arduino.h>
#include "waterWarmer.h"
#include "circPump.h"

waterWarmer::waterWarmer(byte relayPin,byte monitoringLedPin,circPump * cP) {
  warmerOn=false;
  warmerMuted=false;
  warmerShouldRun=false;
  warmerRelayPin=relayPin;
  warmerMonitoringLedPin=monitoringLedPin;
  pinMode(warmerRelayPin,OUTPUT);
  pinMode(warmerMonitoringLedPin,OUTPUT);
  digitalWrite(warmerRelayPin,HIGH);
  digitalWrite(warmerMonitoringLedPin,LOW);
  blinkCounter=0;
  circP=cP;
}

void waterWarmer::generalStopSet() {
  generalStop=true;  
}

void waterWarmer::generalStopUnset() {
  generalStop=false;  
}

bool waterWarmer::isWarmerMuted() {
  return warmerMuted;
}

bool waterWarmer::isWarmerShouldRun() {
  return warmerShouldRun;
}

void waterWarmer::warmerMute() {
  warmerMuted=true;
  stopWarmer();
}

void waterWarmer::warmerUnMute() {
  warmerMuted=false;
}

void waterWarmer::forceWarmUnset() {
  forceWarm=false;
}

void waterWarmer::forceWarmSet() {
  forceWarm=true;
}

void waterWarmer::runWarmer(byte hoursNow) {
  if (generalStop) {
    stopWarmer();
    return; 
  }
  if (!warmerMuted) {
    if (circP->isCircPumpRunning()) {
      if((hoursNow>12 && hoursNow>=autorizedWarmHourStart) || (hoursNow<12 && hoursNow<autorizedWarmHourStop) || forceWarm) {
        warmerOn=true;
        digitalWrite(warmerRelayPin,LOW);
      }
      else {
        //Serial.println(hoursNow);
        //Serial.println("Forbidden to warm. Not in the eco timeslot");
        warmerOn=false;
        stopWarmer();
      }
    }
    else {
      stopWarmer(); 
    }
  }
  else {
    warmerShouldRun=true;
  }
}

void waterWarmer::stopWarmer() {
  warmerOn=false;
  warmerShouldRun=false;
  digitalWrite(warmerRelayPin,HIGH);
  digitalWrite(warmerMonitoringLedPin,LOW);
  blinkCounter=0;
}

byte waterWarmer::getWarmerRelayPin() {
  return warmerRelayPin;
}

byte waterWarmer::getWarmerMonitoringLedPin() {
  return warmerMonitoringLedPin;
}

bool waterWarmer::isWarmerRunning() {
  return warmerOn;
}

void waterWarmer::warmerRefresh() {
  if(!warmerOn) {
    return;
  }
  if(blinkCounter>4 && blinkCounter<8) {
    digitalWrite(warmerMonitoringLedPin,HIGH);
  }
  if(blinkCounter==9) {
    digitalWrite(warmerMonitoringLedPin,LOW);  
  }
  blinkCounter++;
  blinkCounter=blinkCounter%20;
}
