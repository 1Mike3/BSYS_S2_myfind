//
// Created by osboxes on 24/03/23.
//

#ifndef FIND_SIMPLIFIED_INPUTPROCESSING_H
#define FIND_SIMPLIFIED_INPUTPROCESSING_H

#include <stdbool.h>

//Misc Macros
#define MAXCAHRSPAR1 128
#define MAXCHARSPAR2 128
#define MAXCHARSPAR3 128

#define PARAMETERINDEX1 1
#define PARAMETERINDEX2 2
#define PARAMETERINDEX3 3

#define PARAMETERSAFEGUARD1 2
#define PARAMETERSAFEGUARD2 3
#define PARAMETERSAFEGUARD3 4

typedef struct ParameterData {
        char searchPathStart[128];
        char expression[128];
        bool expressionParReq;
        char expressionParameter[128];
        short totalArgumentCount; //Both so can detect if should process the par function again after first run
        short totalProcessedParameters;
}parameterData ;


int ProcessParameterData(int argumentCount, char ** argumentVector, parameterData *parameters);

#endif //FIND_SIMPLIFIED_INPUTPROCESSING_H

