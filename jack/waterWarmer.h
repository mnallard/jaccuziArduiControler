#ifndef waterWarmer_h
#define waterWarmer_h
#include "circPump.h"

class waterWarmer {
  public:
    void runWarmer(byte hour);
    void stopWarmer();
    byte getWarmerRelayPin();
    byte getWarmerMonitoringLedPin();
    bool isWarmerRunning();
    bool isWarmerShouldRun();
    bool isWarmerMuted();
    void warmerMute();
    void warmerUnMute();
    void warmerRefresh();
    void forceWarmSet();
    void forceWarmUnset();
    void generalStopSet();
    void generalStopUnset();
    waterWarmer(byte warmerRelayPin,byte warmerMonitoringLedPin,circPump * cPump);
  private:
    byte autorizedWarmHourStart=22;
    byte autorizedWarmHourStop=06;
    byte warmerRelayPin;
    byte warmerMonitoringLedPin;
    bool warmerMuted;
    bool warmerShouldRun;
    bool warmerOn;
    byte blinkCounter;
    byte forceWarm=false;
    circPump * circP;
    bool generalStop=false;
};
#endif
