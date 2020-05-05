#include <Arduino.h>
#include "leakLevel.h"

leakLevel::leakLevel(byte leakLevelPin,byte powPin) {
  leakLevelAnalogPin=leakLevelPin;
  leakLowLevel=true;
  leakHighLevel=false;
  powerPin=powPin;
  pinMode(leakLevelAnalogPin,INPUT);
  pinMode(powerPin,OUTPUT);
  digitalWrite(powerPin,LOW);
  leakCurrentLevel=0;
}
void leakLevel::stopSensor() {
  digitalWrite(powerPin,LOW);
}
void leakLevel::startSensor() {
  digitalWrite(powerPin,HIGH);
}

byte leakLevel::getleakLevelAnalogPin() {
  return leakLevelAnalogPin;
}
bool leakLevel::isLeakHighLevel() {
  return leakHighLevel;
}

bool leakLevel::isLeakLowLevel() {
  return leakLowLevel;
}

int leakLevel::getLeakInstantValue() {
  return leakCurrentLevel;
}
int leakLevel::getleakLevel() {
  if(nbLoop) {
    nbLoop--;
    return 0;
  }
  digitalWrite(powerPin,HIGH);
  delay(100);
  leakCurrentLevel=analogRead(leakLevelAnalogPin);
  delay(100);
  Serial.println(leakCurrentLevel);
  digitalWrite(powerPin,LOW);
  if (leakCurrentLevel>320) {
    leakHighLevel=true;
    leakLowLevel=false;
  }  
  if (leakCurrentLevel<100) {
    leakHighLevel=false;
    leakLowLevel=true;
  }
  nbLoop=50;
  return leakCurrentLevel;
}
