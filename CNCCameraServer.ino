/*
          2020-08-10 - Test math for stepper motor microstep impact.
                       Control motors with limit switches.
                       Moved Regexp into project due to complier issues.
                       Use the command parser and executer.
                       Remove superfolous comments and commands.
*/

#include <stdlib.h>

#include "API.h"
#include "CNCCameraHardware.h"

Command command;
CNCCameraHardware hardware;

void setup()
{
          Serial.begin(9600); 
}

void loop() {
          // Wait for then parse the data passed for the command to execute.
          command.Parse();
          
          // Execute the commands sent.
          command.Execute(hardware);
}
