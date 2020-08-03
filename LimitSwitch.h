#ifndef LIMITSWITCH_H
#define LIMITSWITCH_H

#include <Arduino.h>

class LimitSwitch
{
public:  
          enum SwitchType { NormallyOpen, NormallyClosed };
          
          LimitSwitch();
          LimitSwitch(int pin, SwitchType type);
          boolean IsReleased(void);
          boolean IsPressed(void);
private:
          int _pin;
          LimitSwitch::SwitchType _type;
};

#endif // LIMITSWITCH_H





