#include "DS1307.h"
#include <Wire.h>
#include <Arduino.h>
#include "myClock.h"

byte bcd2Decimal(byte bcd) {
  return (bcd/16*10)+(bcd%16); 
}

byte decimal2Bcd(byte decimal) {
  return (decimal/10*16)+(decimal%10);
}

void myClock::setClockTime(DateTime_t datetime) {
  /* Début de la transaction I2C */
  Wire.beginTransmission(DS1307_ADDRESS);
  Wire.write((byte)0); 
  Wire.write(decimal2Bcd(datetime.seconds)&127); // CH = 0
  Wire.write(decimal2Bcd(datetime.minutes));
  Wire.write(decimal2Bcd(datetime.hours)&63); // Mode 24h
  Wire.write(decimal2Bcd(datetime.day_of_week));
  Wire.write(decimal2Bcd(datetime.days));
  Wire.write(decimal2Bcd(datetime.months));
  Wire.write(decimal2Bcd(datetime.year));
  Wire.endTransmission(); // Fin de transaction I2C
}

bool myClock::getClockState() {
  /* Début de la transaction I2C */
  Wire.beginTransmission(DS1307_ADDRESS);
  Wire.write((byte)0); 
  Wire.endTransmission();
  Wire.requestFrom(DS1307_ADDRESS,(byte)1);
  byte raw_seconds=Wire.read();
  if (raw_seconds & 128) {
    stateClock=false;  
    return false;
  }
  stateClock=true;  
  return true;
  
}

bool myClock::getClockTime(DateTime_t * datetime,String * outPutStr) {
  *outPutStr="";
  Wire.beginTransmission(DS1307_ADDRESS);
  Wire.write((byte)0); 
  Wire.endTransmission();
  Wire.requestFrom(DS1307_ADDRESS,(byte)7);
  byte raw_seconds=Wire.read();
  datetime->seconds=bcd2Decimal(raw_seconds);
  datetime->minutes=bcd2Decimal(Wire.read());
  byte raw_hours=Wire.read();
  if (raw_hours&64) { // 12h format
    datetime->hours=bcd2Decimal(raw_hours&31);
    datetime->is_pm=raw_hours&32;
  } 
  else { // 24h format
    datetime->hours= bcd2Decimal(raw_hours&63);
    datetime->is_pm=0;
  }
  datetime->day_of_week=bcd2Decimal(Wire.read());
  datetime->days=bcd2Decimal(Wire.read());
  datetime->months=bcd2Decimal(Wire.read());
  datetime->year=bcd2Decimal(Wire.read());
  if(datetime->days<10) {
    *outPutStr="0";
  }
  *outPutStr+=String(datetime->days)+"/";
  if(datetime->months<10) {
    *outPutStr+="0";
  }
  *outPutStr+=String(datetime->months)+" ";
  if(datetime->hours<10) {
    *outPutStr+="0";
  }
  *outPutStr+=String(datetime->hours)+":";
  if(datetime->minutes<10) {
    *outPutStr+="0";
  }
  *outPutStr+=String(datetime->minutes)+":";
  
  if(datetime->seconds<10) {
    *outPutStr+="0";
  }
  *outPutStr+=String(datetime->seconds);
  
  /* Si le bit 7 des secondes == 1 : le module RTC est arrêté */
  if(raw_seconds&128) {
    stateClock=false;
    return false;
  }
  else {
    stateClock=true;
    return true;
  }
}


myClock::myClock() {
  Wire.begin();  
  stateClock=false;
}

myClock::myClock(DateTime_t datetime) {
  Wire.begin();
  stateClock=false;
  setClockTime(datetime);
}

bool myClock::getFromModuleMem(byte octNum,byte * value) {
  if (octNum > DS1307_NVRAM_SIZE)
    return false;
  Wire.beginTransmission(DS1307_ADDRESS);
  if (!Wire.write(DS1307_NVRAM_BASE + octNum)) {
    return false;
  }
  if(Wire.endTransmission()) {
    return false;
  }
  
  if(!Wire.requestFrom(DS1307_ADDRESS, (byte) 1)) {
    return false;
  }
  *value=Wire.read();
  return true;
}

bool myClock::sendInModuleMem(byte octNum,byte value) {
  if (octNum > DS1307_NVRAM_SIZE)
    return false;
  Wire.beginTransmission(DS1307_ADDRESS);
  if(!Wire.write(DS1307_NVRAM_BASE + octNum)) {
    return false;
  }
  if (!Wire.write(value)) {
    return false;
  }
  Wire.endTransmission(); 
  return true;
}
