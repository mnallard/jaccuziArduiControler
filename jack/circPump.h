#ifndef circPump_h
#define circPump_h

class circPump {
  public:
    void runPump();
    void runPumpSecurityCase();
    void stopPump();
    byte getcircPumpRelayPin();
    byte getcircPumpMonitoringLedPin();
    bool isCircPumpRunning();
    void circPumpUnMute();
    bool isCircPumpMuted();
    void circPumpMute();
    void circPumpRefresh();
    void generalStopUnset();
    void generalStopSet();
    circPump(byte relayPin,byte monitoringLedPin);

  private:
    byte blinkCounter;
    bool pumpOn;
    bool pumpMuted;
    byte circPumpRelayPin;
    byte circPumpMonitoringLedPin;
    bool generalStop=false;
    
};
#endif
