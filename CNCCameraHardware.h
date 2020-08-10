/*
          2020-08-10 - Refactor RAMPS hardware include file.
                       Send limit switches to stepper motor controllers.
*/

#ifndef CNCCAMERAHARDWARE_H
#define CNCCAMERAHARDWARE_H

#include "LimitSwitch.h"
#include "StepperMotorControl.h"

// RAMPS 1.4 Hardware Pins
#define X_STEP_PIN         54
#define X_DIR_PIN          55
#define X_ENABLE_PIN       38
#define X_MIN_PIN          3
#define X_MAX_PIN          2

#define Y_STEP_PIN         60
#define Y_DIR_PIN          61
#define Y_ENABLE_PIN       56
#define Y_MIN_PIN          14
#define Y_MAX_PIN          15

#define Z_STEP_PIN         46
#define Z_DIR_PIN          48
#define Z_ENABLE_PIN       62
#define Z_MIN_PIN          18
#define Z_MAX_PIN          19

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




