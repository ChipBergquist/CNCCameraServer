/*
          2020-08-10 - Simplify to just Pressed().
*/

#ifndef LIMITSWITCH_H
#define LIMITSWITCH_H

#include <Arduino.h>

class LimitSwitch
{
public:  
          enum SwitchType { NormallyOpen, NormallyClosed };
          
          LimitSwitch();
          LimitSwitch(int pin, SwitchType type);

          boolean Pressed(void);
private:
          int _pin;
          LimitSwitch::SwitchType _type;
};

#endif // LIMITSWITCH_H





