/*
          2020-08-10 - Refactor RAMPS hardware include file.
                       Send limit switches to stepper motor controllers.
*/

#include "CNCCameraHardware.h"
#include "LimitSwitch.h"
#include "StepperMotorControl.h"

CNCCameraHardware::CNCCameraHardware() {
          // We will be using the X axis controls on the RAMPS board to control what we conside the A axis of the cnc camera.
          AMinLimitSwitch = LimitSwitch(X_MIN_PIN, LimitSwitch::NormallyClosed);
          AMaxLimitSwitch = LimitSwitch(X_MAX_PIN, LimitSwitch::NormallyClosed);
          AStepperMotor = StepperMotorControl(X_DIR_PIN, X_STEP_PIN, X_ENABLE_PIN, AMinLimitSwitch, AMaxLimitSwitch);

          ZMinLimitSwitch = LimitSwitch(Z_MIN_PIN, LimitSwitch::NormallyClosed);
          ZMaxLimitSwitch = LimitSwitch(Z_MAX_PIN, LimitSwitch::NormallyClosed);
          ZStepperMotor = StepperMotorControl(Z_DIR_PIN, Z_STEP_PIN, Z_ENABLE_PIN, ZMinLimitSwitch, ZMaxLimitSwitch);
}
