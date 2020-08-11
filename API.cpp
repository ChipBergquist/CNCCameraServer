/*
          2020-08-10 - Add this comment history approach.
                       Moved Regexp into project due to complier issues.
                       Added hooks to command implmentaitons. 
*/

#include "API.h"

Command::Command(){
}

void Command::Parse(void) {
          strcpy(name, INVALID);
          hasA = false;
          hasZ = false;

          char serialdata[80];
          int nchars;

          while (strcmp(name,INVALID) == 0)
          {
                    while(Serial.available() > 0)
                    {
                              nchars=Serial.readBytes(serialdata, 80);
                              serialdata[nchars]='\0';

                              MatchState ms;
                              ms.Target (serialdata);

                              if ( ms.Match ("^M300$", 0) == REGEXP_MATCHED ){
                                        strcpy(name, M300);
                                        strcpy(comment, "");
                              }
                              else if ( ms.Match ("^M300 %((.*)%)$", 0) == REGEXP_MATCHED ){
                                        strcpy(name, M300);
                                        strcpy(comment, ms.GetCapture (serialdata, 0));
                              }
                              else if ( ms.Match ("^M301$", 0) == REGEXP_MATCHED ){
                                        strcpy(name, M301);
                                        strcpy(comment, "");
                              }
                              else if ( ms.Match ("^M301 %((.*)%)$", 0) == REGEXP_MATCHED ){
                                        strcpy(name, M301);
                                        strcpy(comment, ms.GetCapture (serialdata, 0));
                              }
                              else if ( ms.Match ("^M302$", 0) == REGEXP_MATCHED ){
                                        strcpy(name, M302);
                                        strcpy(comment, "");
                              }
                              else if ( ms.Match ("^M302 %((.*)%)$", 0) == REGEXP_MATCHED ){
                                        strcpy(name, M302);
                                        strcpy(comment, ms.GetCapture (serialdata, 0));
                              }
                              else if ( ms.Match ("^%((.*)%)$", 0) == REGEXP_MATCHED ){
                                        strcpy(name, COMMENT);
                                        strcpy(comment, ms.GetCapture (serialdata, 0));
                              }
                              else if (ms.Match ("^G0 A(%d+%.%d+)$", 0) == REGEXP_MATCHED){
                                        strcpy(name, G0);
                                        hasA = true;
                                        a = atof(ms.GetCapture (serialdata, 0));
                                        strcpy(comment, "");
                              }
                              else if (ms.Match ("^G0 A(%d+%.%d+) %((.*)%)$", 0) == REGEXP_MATCHED){
                                        strcpy(name, G0);
                                        hasA = true;
                                        a = atof(ms.GetCapture (serialdata, 0));
                                        strcpy(comment, ms.GetCapture (serialdata, 1));
                              }
                              else if (ms.Match ("^G0 Z(%d+%.%d+)$", 0) == REGEXP_MATCHED){
                                        strcpy(name, G0);
                                        hasZ = true;
                                        z = atof(ms.GetCapture (serialdata, 0));
                                        strcpy(comment, "");
                              }
                              else if (ms.Match ("^G0 Z(%d+%.%d+) %((.*)%)$", 0) == REGEXP_MATCHED){
                                        strcpy(name, G0);
                                        hasZ = true;
                                        z = atof(ms.GetCapture (serialdata, 0));
                                        strcpy(comment, ms.GetCapture (serialdata, 1));
                              }
                              else if (ms.Match ("^G0 A(%d+%.%d+) Z(%d+%.%d+)", 0) == REGEXP_MATCHED){
                                        strcpy(name, G0);
                                        hasA = true;
                                        a = atof(ms.GetCapture (serialdata, 0));
                                        hasZ = true;
                                        z = atof(ms.GetCapture (serialdata, 1));
                                        strcpy(comment, "");
                              }
                              else if (ms.Match ("^G0 A(%d+%.%d+) Z(%d+%.%d+) %((.*)%)$", 0) == REGEXP_MATCHED){
                                        strcpy(name, G0);
                                        hasA = true;
                                        a = atof(ms.GetCapture (serialdata, 0));
                                        hasZ = true;
                                        z = atof(ms.GetCapture (serialdata, 1));
                                        strcpy(comment, ms.GetCapture (serialdata, 2));
                              }
                    }
          }
}

void Command::Execute(CNCCameraHardware hardware) {

          String message;
          char buff[100];
          message = String("Executing: ") + name;

          if (hasA) {
                    dtostrf(a, 1, 4, buff);
                    message = message + String(" A") + String( buff );
          }

          if (hasZ) {
                    dtostrf(z, 1, 4, buff);
                    message = message + String(" Z") + buff;
          }

          if (strcmp(comment, "") != 0) {
                    message = message + String(" (") + comment + String(")");
          }

          Serial.println(message);

          if (strcmp(name, G0) == 0) {
                    hardware.G0(hasA, a, hasZ, z);
          }
          else if (strcmp(name, M300) == 0) {
                    
                    hardware.M300();
          }
          else if (strcmp(name, M301) == 0) { 
                    hardware.M301();
          }
          else if (strcmp(name, M302) == 0) {
          }
          else if (strcmp(name, COMMENT) == 0) {
          }
          else if (strcmp(name, INVALID)== 0) {
                    Serial.println("(Invalid Command!)");
          }
          else {
                    Serial.println("(Unknown Command!)");
          }
}

