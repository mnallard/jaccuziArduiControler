#include <Arduino.h>
#include "circPump.h"

circPump::circPump(byte relayPin,byte monitoringLedPin) {
  pumpOn=false;
  pumpMuted=false;
  circPumpRelayPin=relayPin;
  circPumpMonitoringLedPin=monitoringLedPin;
  pinMode(circPumpRelayPin,OUTPUT);
  pinMode(circPumpMonitoringLedPin,OUTPUT);
  digitalWrite(circPumpRelayPin,HIGH);
  digitalWrite(circPumpMonitoringLedPin,LOW);
  blinkCounter=0;
}

bool circPump::isCircPumpMuted() {
  return pumpMuted;
}

bool circPump::isCircPumpRunning() {
  return pumpOn;
}
void circPump::circPumpMute() {
  pumpMuted=true;
  stopPump();
  blinkCounter=0;
}

void circPump::generalStopSet() {
  generalStop=true;  
}

void circPump::generalStopUnset() {
  generalStop=false;  
}

void circPump::runPump() {
  if(generalStop) {
    stopPump();
    return;
  }
  if (!pumpMuted) {
    pumpOn=true;
    digitalWrite(circPumpRelayPin,LOW);
  }
  
}

void circPump::runPumpSecurityCase() {
    pumpOn=true;
    digitalWrite(circPumpRelayPin,LOW);
    pumpMuted=false;
}

void circPump::stopPump() {
  pumpOn=false;
  digitalWrite(circPumpRelayPin,HIGH);
  digitalWrite(circPumpMonitoringLedPin,LOW);
}

byte circPump::getcircPumpRelayPin() {
  return circPumpRelayPin;
}

byte circPump::getcircPumpMonitoringLedPin() {
  return circPumpMonitoringLedPin;
}

void circPump::circPumpUnMute() {
  pumpMuted=false;
}

void circPump::circPumpRefresh() {
  if(!pumpOn) {
    return;
  }
  if(blinkCounter>16 && blinkCounter<20) {
    digitalWrite(circPumpMonitoringLedPin,HIGH);
  }
  if(!blinkCounter) {
    digitalWrite(circPumpMonitoringLedPin,LOW);  
  }
  blinkCounter++;
  blinkCounter=blinkCounter%20;
}
