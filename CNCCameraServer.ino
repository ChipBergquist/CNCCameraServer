/*
          2020-08-10 - Test math for stepper motor microstep impact.
                       Control motors with limit switches.
*/

#include <Regexp.h>
#include <stdlib.h>

#include "API.h"
#include "CNCCameraHardware.h"

Command command;
CNCCameraHardware hardware;

void setup()
{
          char buff[20];

          Serial.begin(9600); 
          
          Serial.print("MM_PER_MICROSTEP: ");
          dtostrf( MM_PER_MICROSTEP, 8, 6, buff);
          Serial.println(buff);

          Serial.print("DEGREE_PER_MICROSTEP: ");
          dtostrf( DEGREE_PER_MICROSTEP, 8, 6, buff);
          Serial.println(buff);


}

void loop() {
          // Move the camrea up.
          if ( hardware.AMinLimitSwitch.Pressed() ) {
                    hardware.ZStepperMotor.move( 1000, StepperMotorControl::CounterClockwise );
          }
          
          // Move the camrea down.
          if ( hardware.AMaxLimitSwitch.Pressed() ) {
                    hardware.ZStepperMotor.move( 1000, StepperMotorControl::Clockwise );
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
