/*
          2020-08-10 - Include the limit switches.
                       There are enough steps that it must be a long.
                       Added backoff logic for after the switches are tripped.
                       There are enough steps that it must be a long.
                       Added backoff logic for after the switches are tripped.
*/

#include "StepperMotorControl.h"

StepperMotorControl::StepperMotorControl() {
}

StepperMotorControl::StepperMotorControl(int dir_pin, int step_pin, int enable_pin, LimitSwitch & minSwitch, LimitSwitch & maxSwitch ) {
          _dir_pin = dir_pin;
          _step_pin = step_pin; 
          _enable_pin = enable_pin;
          _min = minSwitch;
          _max = maxSwitch;
          
          pinMode(_dir_pin, OUTPUT);
          pinMode(_step_pin, OUTPUT);
          pinMode(_enable_pin, OUTPUT);
          digitalWrite(_enable_pin, LOW);
}

float StepperMotorControl::calculate_step_delay (long steps_total, long steps_remaining, float delay ) {
          float new_delay = delay;

          if ( _steps_ramp_up == 0 ) {
                    new_delay = delay - 5;

                    if ( new_delay <= MIN_DELAY ) {
                              new_delay = MIN_DELAY;
                              _steps_ramp_up = steps_remaining;
                    }

                    if ( steps_remaining < steps_total / 2 ) {
                              _steps_ramp_up = steps_remaining;
                    }
          }

          else if (steps_remaining <= (steps_total - _steps_ramp_up)) {
                    new_delay = delay + 5;

                    if ( new_delay >= MAX_DELAY ) {
                              new_delay = MAX_DELAY;
                    }
          }

          return new_delay;
}

long StepperMotorControl::move(long steps, DirectionType direction ) {
          long totalSteps = steps;
          float delay = MAX_DELAY;
          _steps_ramp_up = 0;
          
          if (direction == Clockwise) {
                    digitalWrite(_dir_pin, HIGH);
          }  
          else {
                    digitalWrite(_dir_pin, LOW);
          }

          while ((steps > 0) && (!_min.Pressed()) && (!_max.Pressed())) {
                    digitalWrite(_step_pin, HIGH);
                    digitalWrite(_step_pin, LOW);
                    delay = calculate_step_delay(totalSteps, steps, delay);
                    delayMicroseconds(delay);
                    --steps;
          }
          return totalSteps - steps;
}

void StepperMotorControl::backoff( void ) {
          if (_max.Pressed()) {
                    // direction == Clockwise
                    digitalWrite(_dir_pin, HIGH);
          }  
          else {
                    digitalWrite(_dir_pin, LOW);
          }

          while ((_min.Pressed()) || (_max.Pressed())) {
                    digitalWrite(_step_pin, HIGH);
                    digitalWrite(_step_pin, LOW);
                    delayMicroseconds(MAX_DELAY);
          }
}
