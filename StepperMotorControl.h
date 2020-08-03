#ifndef STEPPERMOTORCONTROL_H
#define STEPPERMOTORCONTROL_H

#include "Arduino.h"

// CMB - Find a way to justify these numbers.
#define MAX_DELAY 600 // Slowest speed we will support.
#define MIN_DELAY 600 // Fastest possible speed, after already accelerating.


/*
// Constants for supporting commands using Degrees for movement
// - Math
#define DEGREES_PER_REVOLUTION 360

// - RAMPS Microsteping Configuration 
#define MICROSTEPS_PER_STEP 16

// - Nema 17 Bipolar Stepper Motor
#define STEPS_PER_REVOLUTION 200

// - Microsteps/Degree of Rotation
#define MICROSTEPS_PER_DEGREE = MICROSTEPS_PER_STEP * STEPS_PER_REVOLUTION / DEGREES_PER_REVOLUTION;

// - Gear Ratios
#define TEETH_1 1
#define TEETH_2 1
#define TEETH_N 1
#define GEAR_RATIO TEETH_1 / TEETH_2 / TEETH_N

// - Geared Microsteps/Degree of Rotation
#define GEARED_MICROSTEPS_PER_DEGREE MICROSTEPS_PER_DEGREE * GEAR_RATIO
*/


class StepperMotorControl
{
public:
          enum DirectionType { Clockwise, CounterClockwise };
          
          StepperMotorControl();
          StepperMotorControl(int dir_pin, int step_pin, int enable_pin);
          
          void move(int steps, DirectionType direction );

private:
          int _dir_pin;
          int _step_pin;
          int _enable_pin;
          int _steps_ramp_up = 0;
          
          float calculate_step_delay (int steps_total, int steps_remaining, float delay );
};

#endif // STEPPERMOTORCONTROL_H


