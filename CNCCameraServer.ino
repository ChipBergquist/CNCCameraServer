#include <Regexp.h>

#include "API.h"
#include "CNCCameraHardware.h"

Command command;
CNCCameraHardware hardware;

void setup()
{
          Serial.begin(9600); 
}

void loop() {
          // Move the camrea up with no control.
          if ( hardware.AMinLimitSwitch.IsPressed() ) {
                    hardware.ZStepperMotor.move( 1000, StepperMotorControl::CounterClockwise );
          }
          
          // Move the camrea down, as long as there is no endstop triggered.
          if ( hardware.AMaxLimitSwitch.IsPressed() ) {
                    if ( !hardware.ZMinLimitSwitch.IsPressed() ) {
                              hardware.ZStepperMotor.move( 1000, StepperMotorControl::Clockwise );
                    }
          }
          
          // This "works", but will move the entrie 1000 revolutions before stopping. Need the check deep in the bowels of the move logic, not utside like this.
}

/*
  Simple controller.
          if ( !hardware.AMinLimitSwitch.IsReleased() )
          {
            Serial.println("hardware.AMinLimitSwitch.IsPressed()");
            hardware.AStepperMotor.move( 100, StepperMotorControl::Clockwise );
          }
          if ( !hardware.AMaxLimitSwitch.IsReleased() )
          {
            Serial.println("hardware.AMaxLimitSwitch.IsPressed()");
            hardware.AStepperMotor.move( 100, StepperMotorControl::CounterClockwise );
          }
          if ( !hardware.ZMinLimitSwitch.IsReleased() )
          {
            Serial.println("hardware.ZMinLimitSwitch.IsPressed()");
            hardware.ZStepperMotor.move( 1000, StepperMotorControl::Clockwise );
          }
          if ( !hardware.ZMaxLimitSwitch.IsReleased() )
          {
            Serial.println("hardware.ZMaxLimitSwitch.IsPressed()");
            hardware.ZStepperMotor.move( 1000, StepperMotorControl::CounterClockwise );
          }
*/
