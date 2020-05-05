#ifndef waterTemperature_h
#define waterTemperature_h
#include "waterConsigne.h"

class waterTemperature {
  public:
    byte getTemperature();
    byte getTemperatureFromSonde();
    bool isWaterNeedWarming(waterConsigne * consigne);
    void blinkLeds();
    void setTemperature(byte temp);
    void initLedSequence(); 
    waterTemperature(byte pinSonde,byte defaultTemp,byte tl0,byte tl1,byte tl2,byte tl3,byte tl4,byte tl5);
    void updateLed(waterConsigne * consigne);
    bool iswarmSecurity();
  private:
    byte temperature;
    byte temperatureAnalogPin;
    byte ledToDisp;
    byte pinLed[6];
    bool warmSecurity=false;
    int  blinkCounter;
};
#endif
