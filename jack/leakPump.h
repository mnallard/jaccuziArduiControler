#ifndef leakPump_h
#define leakPump_h

class leakPump {
  public:
    void runPump();
    void stopPump();
    byte getleakPumpRelayPin();
    bool isLeakPumpRunning();
    void leakPumpMute();
    void leakPumpUnMute();
    bool isLeakPumpMuted();
    leakPump(byte relayPin);
    void generalStopSet();
    void generalStopUnset();
    bool isLeakPumpForced();
    void leakPumpForce();
    void leakPumpUnforce();
  private:
    bool pumpOn;
    byte leakPumpRelayPin;
    bool pumpMute=false;
    bool generalStop=false;
    bool leakPumpForced=false;
};
#endif
