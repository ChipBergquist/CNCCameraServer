/*
          2020-08-10 - Refactor RAMPS hardware include file.
                       Send limit switches to stepper motor controllers.
                       Moved headers to dependent headers.
                       Began command implmentaitons. 
          2020-08-24 - Pass hardware by reference addressed the issues I was seeing.
*/

#include "CNCCameraHardware.h"

CNCCameraHardware::CNCCameraHardware() {
          // We will be using the X axis controls on the RAMPS board to control what we conside the A axis of the CNC Camera.
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
                              long steps = z - ZCurrentPosition;
                              if (steps < 0){
                                        ZStepperMotor.move( -steps, StepperMotorControl::Clockwise );
                              }
                              else {
                                        ZStepperMotor.move( steps, StepperMotorControl::CounterClockwise );
                              }
                              ZCurrentPosition += steps;
                    }               
          }
          else {
                    Serial.println("CNC Camrea Not Calibrated: Could not execute G0 command.");
          }
}

void CNCCameraHardware::M300( void ) {
          long zSteps;
          long aSteps;

          /*
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
          */
          
          // Go to A Min
          AStepperMotor.move( 1000000, StepperMotorControl::Clockwise );
          AStepperMotor.backoff();          

          // Go to Z Max
          aSteps = AStepperMotor.move( 1000000, StepperMotorControl::CounterClockwise );
          AStepperMotor.backoff();

          Serial.print("A axis Microsteps (Left)  : ");
          Serial.println(aSteps);

          // Go back to Z Min
          aSteps = AStepperMotor.move( 1000000, StepperMotorControl::Clockwise );
          AStepperMotor.backoff();
          
          Serial.print("A axis Microsteps (Right): ");
          Serial.println(aSteps);
          
          IsCalibrated = true;
          ZMinWorkingRange = 0;
          ZCurrentPosition = 0;
          ZMaxWorkingRange = zSteps;
          
          AMinWorkingRange = 0;
          ACurrentPosition = 0;
          AMaxWorkingRange = aSteps;
}

void CNCCameraHardware::M301( void ) {
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

          Serial.print("AMinWorkingRange: ");
          Serial.println(AMinWorkingRange);

          Serial.print("AMaxWorkingRange: ");
          Serial.println(AMaxWorkingRange);

          Serial.print("ACurrentPosition: ");
          Serial.println(ACurrentPosition);
}
