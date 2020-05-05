#ifndef ozoner_h
#define ozoner_h
#include "circPump.h"
class ozoner {
  public:
    void runOzoner(byte hours);
    void stopOzoner();
    byte getOzonerRelayPin();
    byte getOzonerMonitoringLedPin();
    bool isOzonerRunning();
    bool isOzonerMuted();
    void ozonerMute();
    void ozonerUnMute();
    void ozonerRefresh();
    byte getNexRunCycle(byte hoursNow);
    ozoner(byte relayPin,byte monitoringLedPin,circPump * cP);
    void generalStopSet();
    void generalStopUnset();

  private:
    bool ozonerOn;
    byte blinkCounter;
    bool forceOzoner=false;
    bool ozonerMuted;
    byte ozonerRelayPin;
    byte ozonerMonitoringLedPin;
    circPump * cPump;
    bool generalStop=false; 
    
};
#endif
