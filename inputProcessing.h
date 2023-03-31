//
// Created by Mike on 24/03/23.
//

#ifndef FIND_SIMPLIFIED_INPUTPROCESSING_H
#define FIND_SIMPLIFIED_INPUTPROCESSING_H

#include <stdbool.h>

// defines limit for max POSSIBLE expressions to CHOSE from and their length (unlimited possible expr entered still possible)
#define MAXEXPRESSIONAMMOUNT 10
#define MAXEXPRESSIONLENGTH 10

//Misc offsets that are apparently not needed and don't do shit
#define STRCPYOFFSET 0
#define CHECKARGOFFSET 0
#define EXPRESSIONPAROFFSET 0

enum RETURNVALUESCHECKPARAMETER{
    INVALID_ARGUMENT,
    VALID_ARGUMENT_NOPAR,
    VALID_ARGUMENT_PAR
};


typedef struct ParameterData {
        char searchPathStart[128];
        char expression[128];
        bool expressionValid;
        bool expressionParReq;
        char expressionParameter[128];
        short totalArgumentCount;
        short totalProcessedParameters;
}parameterData ;


int ProcessParameterData(int argumentCount, char ** argumentVector, parameterData *parameters);

#endif //FIND_SIMPLIFIED_INPUTPROCESSING_H

