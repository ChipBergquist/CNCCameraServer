/*
          2020-08-10 - Simplify to just Pressed().
*/

#include "LimitSwitch.h"

LimitSwitch::LimitSwitch() {
}

LimitSwitch::LimitSwitch(int pin, SwitchType type) {
          pinMode(pin, INPUT);
          _pin = pin;
          _type = type;
}

boolean LimitSwitch::Pressed(void) {
          boolean Pressed = false;
          
          int pin = digitalRead(_pin);

          if (((pin == LOW) && (_type == NormallyClosed)) || ((pin == HIGH) && (_type == NormallyOpen))) {
                    Pressed = true;
          }
          
          return (Pressed);
}













