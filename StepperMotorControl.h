/*
          2020-08-10 - Include the limit switches.
                       Include calcuations for microstep effects.
*/

#ifndef STEPPERMOTORCONTROL_H
#define STEPPERMOTORCONTROL_H

#include "Arduino.h"
#include "LimitSwitch.h"

// CMB - Find a way to justify these numbers.
#define MAX_DELAY 600 // Slowest speed we will support.
#define MIN_DELAY 600 // Fastest possible speed, after already accelerating.


#define DEGREES_PER_REVOLUTION 360.0

// RAMPS Microsteping Configuration 
#define MICROSTEPS_PER_STEP 16.0

// Nema 17 Bipolar Stepper Motor
#define STEPS_PER_REVOLUTION 200.0


// - Gear Sizes
#define MOTOR_GEAR_TEETH 20.0
#define PIVOT_GEAR_TEETH 90.0

// - Degree of Rotation/Microstep
#define DEGREE_PER_MICROSTEP      DEGREES_PER_REVOLUTION * ( MOTOR_GEAR_TEETH / PIVOT_GEAR_TEETH ) / ( MICROSTEPS_PER_STEP * STEPS_PER_REVOLUTION )

// - Z Axis lead screw lead distance
#define MM_PER_REVOLUTION 8

// - mm/Microstep
#define MM_PER_MICROSTEP MM_PER_REVOLUTION / ( MICROSTEPS_PER_STEP * STEPS_PER_REVOLUTION )

class StepperMotorControl
{
public:
          enum DirectionType { Clockwise, CounterClockwise };
          
          StepperMotorControl();
          StepperMotorControl(int dir_pin, int step_pin, int enable_pin, LimitSwitch & minSwitch, LimitSwitch & maxSwitch );
          
          void move(int steps, DirectionType direction );

private:
          int _dir_pin;
          int _step_pin;
          int _enable_pin;
          int _steps_ramp_up = 0;
          
          LimitSwitch _min;
          LimitSwitch _max;
          
          float calculate_step_delay (int steps_total, int steps_remaining, float delay );
};

#endif // STEPPERMOTORCONTROL_H


