#include <Arduino.h>
#include "waterTemperature.h"
#include "waterConsigne.h"

int _calculeTempFromSonde(float tension) {
  float temperatureSonde;
  temperatureSonde=((tension-2.0)/0.050)+14;
  int Temp=ceil(temperatureSonde);
  //Serial.print("Valeur de temperature sonde : ");
  //Serial.println(Temp);
  return Temp;
}


waterTemperature::waterTemperature(byte pinSonde,byte defaultT,byte tl0,byte tl1,byte tl2,byte tl3,byte tl4,byte tl5) {
  temperatureAnalogPin=pinSonde;
  ledToDisp=0x00;
  temperature=defaultT;
  pinLed[0]=tl0;
  pinLed[1]=tl1;
  pinLed[2]=tl2;
  pinLed[3]=tl3;
  pinLed[4]=tl4;
  pinLed[5]=tl5;
  for(byte i=0;i<6;i++) {
    pinMode(pinLed[i],OUTPUT);
    digitalWrite(pinLed[i],HIGH);
  } 
  blinkCounter=0; 
}

void waterTemperature::initLedSequence() {
  for(byte i=0;i<6;i++) {
    digitalWrite(pinLed[i],LOW);
    delay(50); 
  }
  delay(500);
  for(byte j=0;j<10;j++) {
    for(byte i=0;i<6;i++) {
      if(j%2) {
        digitalWrite(pinLed[i],LOW);
      }
      else {
        digitalWrite(pinLed[i],HIGH);
      }
    }
    delay(100);
  }
  for(int i=5;i>=0;i--) {
    digitalWrite(pinLed[i],HIGH);
    delay(50); 
  }
  //Serial.println("Led sequence intialization completed");
}

void waterTemperature::updateLed(waterConsigne * consigne) {
  byte cons=consigne->getConsigne();
  int delta=temperature-cons;
  
  for (byte i=0;i<6;i++) {
    if(3-i+delta>=0) {
      digitalWrite(pinLed[i],LOW);
    }
    else {
      digitalWrite(pinLed[i],HIGH); 
    }
  }
  if (delta<=-4) {
    digitalWrite(pinLed[0],LOW);
  }
}

byte waterTemperature::getTemperatureFromSonde() {
  int valeurLue=analogRead(temperatureAnalogPin) ;
  float tensionLue=map(valeurLue,0,1023,0,500);
  float tension;
  tension=tensionLue/100.0;
  //Serial.print("Valeur de tension sonde temperature ");
  //Serial.println(tension);
  temperature=_calculeTempFromSonde(tension);
  if (tension>= 3.2) {
    //coupure chauffage si 40° mise en securite
    warmSecurity=true;
  }
  else {
    warmSecurity=false;
    blinkCounter=0;
  }  
  return temperature; 
}

byte waterTemperature::getTemperature() {
  getTemperatureFromSonde();
  if (temperature>=40) {
    //coupure chauffage si 40° mise en securite
    warmSecurity=true;
  }
  else {
    warmSecurity=false;
    blinkCounter=0;
  }
  return temperature;
}

bool waterTemperature::isWaterNeedWarming(waterConsigne * consigne) {
  byte cons=consigne->getConsigne();
  int delta=cons-temperature;
  if (delta>=1) {
    return true;
  }
  if(delta<=-1) {
   return false;
  }
}

bool waterTemperature::iswarmSecurity() {
  return warmSecurity;
}

void waterTemperature::setTemperature(byte temp) {
  temperature=temp; 
}

void waterTemperature::blinkLeds() {
  if (!blinkCounter) {
    for(byte i=0;i<6;i++) { 
      digitalWrite(pinLed[i],LOW); 
    }
    blinkCounter=1;
    return;
  } 
  for(byte i=0;i<6;i++) { 
    digitalWrite(pinLed[i],HIGH); 
  }
  blinkCounter=0;
}
  
