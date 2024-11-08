#ifndef BUTTONS_h
#define BUTTONS_h

#include <Arduino.h>


class Buttons{
  
  private:
    byte btnPin;
    bool btnState = 0;
    int debounceDelay = 100;
    bool toggled_logic = LOW;
    unsigned long int pressMillis = 0;
    
    

  public:
    Buttons(byte pin, byte _mode);
 
    void setDebounceDelay(int delayTime);
    void setToggledLogic(bool state);

    bool isToggled();
    bool isLongPressed(byte pressTime);
    bool checkState();
    bool isPressed();
    bool isReleased();
    
    
};

#endif
