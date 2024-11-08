#include "Buttons.h"

Buttons::Buttons(byte pin, byte _mode) {
  btnPin  = pin;
  pinMode(btnPin, _mode);  
}


bool Buttons::isToggled(){

  bool btnVal = digitalRead(btnPin);
  
  if(btnState == 0){
    if(btnVal == 0){
      btnState = 1;
      delay(100);
    }
  }
  else if(btnState == 1){
    if(btnVal == 1){
      btnState = 0;
      delay(100);
      return true;
    }
  }
  return false;
}

void Buttons::setDebounceDelay(int delayTime){
  debounceDelay = delayTime;
}

void Buttons::setToggledLogic(bool state){
  toggled_logic = state;
}

bool Buttons::checkState(){
  return digitalRead(btnPin);
}

bool Buttons::isPressed(){ 
  return (digitalRead(btnPin) == toggled_logic) ? true : false;
}

bool Buttons::isReleased(){ 
  return (digitalRead(btnPin) == toggled_logic) ? false : true;
}

bool Buttons::isLongPressed(byte pressTime){
  
  bool btnVal = digitalRead(btnPin);
  
  if(btnState == 0){
    if(btnVal == toggled_logic){
      btnState = 1;
      delay(debounceDelay);
      pressMillis = millis();
    }
  }
  if(btnState == 1){
    if(btnVal == !toggled_logic){
      btnState = 0;
      delay(debounceDelay);
      if(millis() - pressMillis > (pressTime * 1000)){
        return true;
      }
    }
  }
  return false;
}
  
  
