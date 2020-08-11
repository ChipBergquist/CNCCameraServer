/*
          2020-08-10 - Refactor RAMPS hardware include file.
                       Send limit switches to stepper motor controllers.
                       Moved headers to dependent headers.
                       Began command implmentaitons. 
*/

#include "CNCCameraHardware.h"

CNCCameraHardware::CNCCameraHardware() {
          // We will be using the X axis controls on the RAMPS board to control what we conside the A axis of the cnc camera.
          AMinLimitSwitch = LimitSwitch(X_MIN_PIN, LimitSwitch::NormallyClosed);
          AMaxLimitSwitch = LimitSwitch(X_MAX_PIN, LimitSwitch::NormallyClosed);
          AStepperMotor = StepperMotorControl(X_DIR_PIN, X_STEP_PIN, X_ENABLE_PIN, AMinLimitSwitch, AMaxLimitSwitch);

          ZMinLimitSwitch = LimitSwitch(Z_MIN_PIN, LimitSwitch::NormallyClosed);
          ZMaxLimitSwitch = LimitSwitch(Z_MAX_PIN, LimitSwitch::NormallyClosed);
          ZStepperMotor = StepperMotorControl(Z_DIR_PIN, Z_STEP_PIN, Z_ENABLE_PIN, ZMinLimitSwitch, ZMaxLimitSwitch);
}

void CNCCameraHardware::G0(bool hasA, float a, bool hasZ, float z) {
          if ( IsCalibrated == true) {
                    if ( hasZ ) {
                              // This mathis not worekingworking as epxected. The motor only ever moves up, never down.
                              long steps = z - ZCurrentPosition;
                              if (steps < 0){
                                        ZStepperMotor.move( -steps, StepperMotorControl::Clockwise );
                              }
                              else {
                                        ZStepperMotor.move( steps, StepperMotorControl::CounterClockwise );
                              }
                              // But this value is what is expected. 
                              ZCurrentPosition += steps;
                    }                    

                    CurrentSettings();
          }
          else {
                    Serial.println("CNC Camrea Not Calibrated: Could not execute G0 command.");
          }
}

void CNCCameraHardware::M300( void ) {
          long zSteps;

          // Go to Z Min
          ZStepperMotor.move( 1000000, StepperMotorControl::Clockwise );
          ZStepperMotor.backoff();

          // Go to Z Max
          zSteps = ZStepperMotor.move( 1000000, StepperMotorControl::CounterClockwise );
          ZStepperMotor.backoff();

          Serial.print("Z axis Microsteps (Up)  : ");
          Serial.println(zSteps);

          // Go back to Z Min
          zSteps = ZStepperMotor.move( 1000000, StepperMotorControl::Clockwise );
          ZStepperMotor.backoff();

          Serial.print("Z axis Microsteps (Down): ");
          Serial.println(zSteps);
          
          IsCalibrated = true;
          ZMinWorkingRange = 0;
          ZCurrentPosition = 0;
          ZMaxWorkingRange = zSteps;
 
          CurrentSettings();
}

void CNCCameraHardware::M301( void ) {
          ZStepperMotor.move( 5000, StepperMotorControl::CounterClockwise );
}

void CNCCameraHardware::CurrentSettings( void ) {
          Serial.print("IsCalibrated: ");
          Serial.println(IsCalibrated);

          Serial.print("ZMinWorkingRange: ");
          Serial.println(ZMinWorkingRange);

          Serial.print("ZMaxWorkingRange: ");
          Serial.println(ZMaxWorkingRange);

          Serial.print("ZCurrentPosition: ");
          Serial.println(ZCurrentPosition);
}
