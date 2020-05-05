#include <Wire.h>
#include <IRremote.h>
#include <arduino.h>
#include "myClock.h"
#include "circPump.h"
#include "leakPump.h"
#include "leakLevel.h"
#include "waterWarmer.h"
#include "myDisplay.h"
#include "waterTemperature.h" 
#include "myIR.h"
#include "myMenu.h"
#include "ozoner.h"

#define leakLevelAnalogPin A0
#define waterTempAnalogPin A1

#define waterTempLed0 40
#define waterTempLed1 41
#define waterTempLed2 42
#define waterTempLed3 43
#define waterTempLed4 44
#define waterTempLed5 45

#define lcdD4 22
#define lcdD5 23
#define lcdD6 24
#define lcdD7 25
#define lcdRS 27
#define lcdEnable 28


#define pinIRSignal 8
#define pinRVBLedBlue 32
#define pinRVBLebRed  34
#define pinRVBLedGreen 33

#define ozonerRelayPin 36
#define leakSensorVccPin 9
#define leakPumpRelayPin 29
#define waterWarmerRelayPin 53
#define waterWarmerLedPin 34

#define circPumpRelayPin 37
#define circPumpLedPin 32

#define defaultConsigne 35
#define defautTemp 35

DateTime_t nowTime;
int loop4GettingTime;
String nowStr="";
myClock clockTime=myClock();   //instantiation of new clock
leakLevel myLeakLevel(leakLevelAnalogPin,leakSensorVccPin);
leakPump myLeakPump(leakPumpRelayPin);
LiquidCrystal myLcd(lcdRS,lcdEnable,lcdD4,lcdD5,lcdD6,lcdD7);
myDisplay mDisplay(&myLcd);

waterConsigne myWaterConsigne(defaultConsigne,&clockTime);
circPump myCircPump(circPumpRelayPin,circPumpLedPin);
waterWarmer mywaterWarmer(waterWarmerRelayPin,waterWarmerLedPin,&myCircPump);
ozoner myOzoner(ozonerRelayPin,pinRVBLedGreen,&myCircPump);
waterTemperature myWaterTemperature(waterTempAnalogPin,defautTemp,waterTempLed0,waterTempLed1,waterTempLed2,waterTempLed3,waterTempLed4,waterTempLed5);
myMenu jacMenu=myMenu(&mDisplay,&myWaterConsigne,&myWaterTemperature,&mywaterWarmer,&myCircPump,&myLeakPump,&myLeakLevel,&myOzoner);
IRrecv irrecv(pinIRSignal);
myIR myIRSensor(&irrecv,&jacMenu);

byte currentTemperature=0;
int leakLvl;

void setClockToNow() {
  DateTime_t now;
  now.seconds = 0;
  now.minutes = 39;
  now.hours = 1; // 12h 0min 0sec
  now.is_pm = 0; 
  now.day_of_week = 6;
  now.days = 03; 
  now.months = 5;
  now.year = 20; // 1 dec 2016
  clockTime.setClockTime(now);

}
void setup() {
  Serial.begin(9600);
  //setClockToNow();
  myWaterTemperature.initLedSequence();
  irrecv.enableIRIn(); 
  Serial.println("Initialised");
  String nowStr="";
  DateTime_t now;
  clockTime.getClockTime(&now,&nowStr);
  Serial.println(nowStr);
  mDisplay.lcdWriteLine1("Jack controler");
  mDisplay.lcdWriteLine2("Nitram Drallan");
  mywaterWarmer.stopWarmer();
  myOzoner.stopOzoner();
  myCircPump.stopPump();
  myLeakPump.stopPump();
  myLeakLevel.stopSensor();
  loop4GettingTime=0;
}

boolean is_a_number(int n) {
  return n >= 48 && n <= 57;
}

int ascii2int(int n, int byte_read) {
  return n*10 + (byte_read - 48);
}

void loop(){
  //getting date 
  
  if(loop4GettingTime>0) {
    loop4GettingTime--;
  }
  else {
    clockTime.getClockTime(&nowTime,&nowStr);
    loop4GettingTime=3;
  }
  // for debug
  String inString = "";
  while (Serial.available() > 0) {
    int inChar = Serial.read();
    delay(100);
    if (isDigit(inChar)) {
      // convert the incoming byte to a char and add it to the string:
      inString += (char)inChar;
    }
    // if you get a newline, print the string, then the string's value:
    if (inChar == '\n') {
      Serial.print("Value:");
      Serial.println(inString.toInt());
      Serial.print("String: ");
      Serial.println(inString);
      // clear the string for new input:
      myWaterTemperature.setTemperature(inString.toInt());
      Serial.print("Setting temp to :");
      Serial.println(inString.toInt(),DEC);
    }
  }
  // manage IR inputs
  myIRSensor.IRtreat();
  // manage the lcd display
  jacMenu.displayMainScreen(nowStr,nowTime.hours);
  // manage the leak
  leakLvl=myLeakLevel.getleakLevel();
  if (myLeakLevel.isLeakHighLevel()) {
    myLeakPump.runPump();  
  }
  if(myLeakPump.isLeakPumpForced()) {
    myLeakPump.runPump();  
  }
  if (myLeakLevel.isLeakLowLevel()) {
    myLeakPump.stopPump();  
  }
  //
  // manage water circulation
  myCircPump.runPump();
  myCircPump.circPumpRefresh();
  // manage ozoner
  myOzoner.runOzoner(nowTime.hours);
  myOzoner.ozonerRefresh();
  // manage the heater
  currentTemperature=myWaterTemperature.getTemperature();
  if (myWaterTemperature.isWaterNeedWarming(&myWaterConsigne)) {
    mywaterWarmer.runWarmer(nowTime.hours); 
  }
  else {
    mywaterWarmer.stopWarmer();   
  }
  mywaterWarmer.warmerRefresh();
  if (myWaterTemperature.iswarmSecurity()) {
    myCircPump.runPumpSecurityCase(); 
    mywaterWarmer.stopWarmer();
    myWaterTemperature.blinkLeds();
  }
  else {
    myWaterTemperature.updateLed(&myWaterConsigne);
  } 
  delay(100);
}
