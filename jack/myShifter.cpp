#include "myShifter.h"
#include <arduino.h>
myShifter::myShifter(byte serialInputP,byte clockP,byte latchP,byte enablePin) {
  serialInputPin=serialInputP;
  clockPin=clockP;
  latchPin=latchP; 
  MRPin=enablePin;
  pinMode(clockPin,OUTPUT);
  pinMode(latchPin,OUTPUT);
  pinMode(serialInputPin,OUTPUT);
  pinMode(MRPin,OUTPUT);
}

void myShifter::enableShifter() {
  digitalWrite(MRPin,HIGH);
}

void myShifter::disableShifter() {
  digitalWrite(MRPin,LOW);
}

void myShifter::sendData(byte data2send) {
  digitalWrite(latchPin,LOW);
  byte mask=0x01;
  for(byte i=0; i<8; i++) {
    digitalWrite(clockPin,LOW);
    Serial.print("Mask :");
    Serial.println(mask,BIN);
    Serial.print("Data :");
    Serial.println(data2send,BIN);
    byte sendD=mask&data2send;
    digitalWrite(serialInputPin,sendD);
    Serial.print("Sending ");
    Serial.println(sendD,BIN);
    digitalWrite(clockPin,HIGH);
    mask=mask<<1;
  }
  digitalWrite(latchPin,HIGH);
}
