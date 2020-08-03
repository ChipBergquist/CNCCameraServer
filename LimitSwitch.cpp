#include "LimitSwitch.h"

LimitSwitch::LimitSwitch() {
}

LimitSwitch::LimitSwitch(int pin, SwitchType type) {
          pinMode(pin, INPUT);
          _pin = pin;
          _type = type;
}

boolean LimitSwitch::IsReleased(void) {
          boolean IsReleased = false;
          int pin = digitalRead(_pin);

          if (((pin == HIGH) && (_type == NormallyClosed)) || ((pin == LOW) && (_type == NormallyOpen))) {
                    IsReleased = true;
          }

          return (IsReleased);
}

boolean LimitSwitch::IsPressed(void) {
          boolean IsPressed = false;
          int pin = digitalRead(_pin);

          if (((pin == LOW) && (_type == NormallyClosed)) || ((pin == HIGH) && (_type == NormallyOpen))) {
                    IsPressed = true;
          }
          
          return (IsPressed);
}













