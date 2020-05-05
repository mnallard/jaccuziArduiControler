#ifndef leakLevel_h
#define leakLevel_h

class leakLevel {
  public:
    int getleakLevel();
    byte getleakLevelAnalogPin();
    bool isLeakHighLevel(); 
    bool isLeakLowLevel();
    void stopSensor();
    void startSensor();
    int getLeakInstantValue();
    leakLevel(byte leakLevelAnalogPin,byte powerPin);

  private:
    bool leakLowLevel;
    bool leakHighLevel;
    int leakCurrentLevel;
    int nbLoop=50;
    byte leakLevelAnalogPin;
    byte powerPin;
};
#endif
