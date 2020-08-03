#include <Regexp.h>

#include "API.h"
#include "CNCCameraHardware.h"

Command command;
CNCCameraHardware hardware;

void setup() {   
          Serial.begin(9600); 
}

void loop() {
          //Serial.println("(Waiting for Command.)");

          // Wait for then parse the data passed for the command to execute.
          // command.Parse();
          
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
          
          
          // Execute the commands sent.
          // command.Execute(hardware);

          //Serial.println("(Command Complete.)");
}
























