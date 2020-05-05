#ifndef myShifter_h
#define myShifter_h
#include <arduino.h>

class myShifter {
  public:
    myShifter(byte serialInputPin,byte clockPin,byte latchPin,byte enablePin);
    void sendData(byte dataToSend);
    void enableShifter();
    void disableShifter();
    
  private:
    byte clockPin;
    byte latchPin;
    byte serialInputPin;
    byte MRPin;
    
    
};
#endif
