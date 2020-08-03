#ifndef CNCCAMERAHARDWARE_H
#define CNCCAMERAHARDWARE_H

#include "LimitSwitch.h"
#include "StepperMotorControl.h"

class CNCCameraHardware
{
public:  
          CNCCameraHardware(void);
          
          void G0(void);
          void M300(void);
          void M301(void);

//private:
          boolean IsCalibrated = false;
          
          LimitSwitch AMinLimitSwitch;
          LimitSwitch AMaxLimitSwitch;
          StepperMotorControl AStepperMotor;
          static const int AMinWorkingRange = 0;
          int ACurrentPosition = 0;
          static const int AMaxWorkingRange = 64000;

          LimitSwitch ZMinLimitSwitch;
          LimitSwitch ZMaxLimitSwitch;
          StepperMotorControl ZStepperMotor;
          static const int ZMinWorkingRange = 0;
          int ZCurrentPosition = 0;
          static const int ZMaxWorkingRange = 32000;
};

#endif // CNCCAMERAHARDWARE_H




