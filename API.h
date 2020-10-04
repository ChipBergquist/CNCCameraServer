/*
          2020-08-10 - Add this comment history approach.
                       Moved Regexp into project due to complier issues.
          2020-08-24 - Added Dx commands for debugging.
                       Pass hardware by reference. Duh.
*/

#ifndef API_H
#define API_H

#include <Arduino.h>

#include "CNCCameraHardware.h"
#include "Regexp.h"


const char D1[] = "D1";
const char D2[] = "D2";
const char D3[] = "D3";

const char G0[] = "G0";
const char M300[] = "M300";
const char M301[] = "M301";
const char M302[] = "M302";
const char COMMENT[] = "COM";
const char INVALID[] = "INV";

class Command
{
public:  
          //enum CommandType { G0, M300, M301, M302, COMMENT };

          Command();
          void Parse(void);
          void Execute(CNCCameraHardware &hardware);
private:
          char name[5];
          bool hasA;
          float a;
          bool hasZ;
          float z;
          char comment[100];
};


#endif // API_H


