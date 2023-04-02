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

/// Possible Return Values of the Process Parameter Dunction
enum RETURNVALUESCHECKPARAMETER{
    INVALID_ARGUMENT,
    VALID_ARGUMENT_NOPAR,
    VALID_ARGUMENT_PAR
};

/// struct which holds all the req. information for the currently processed command line Argument
typedef struct ParameterData {
        char searchPathStart[128];
        char expression[128];
        bool expressionValid;
        bool expressionParReq;
        char expressionParameter[128];
        short totalArgumentCount;
        short totalProcessedParameters;
}parameterData ;


/**
 * @fn Process Parameter function
 * @brief looping though arguments and retrieving information
 *
 * behaves in the following way:
 * on the first call:
 * only determines path,
 * writes home dir if first arg is valid expression,
 * if first par is not valid expression assumes path and writes it as working dir.
 * on the following calls:
 * processes one parameter and optional expression at a time.
 * Increments the processed pars counter in the parameters Struct for
 * every valid, invalid expression and for every expression parameter
 *
 * @param argumentCount
 * @param argumentVector
 * @param parameters
 *
 * @return 0 if successful (even if invalid arg), -1 if an error occurred
 */

int ProcessParameterData(int argumentCount, char ** argumentVector, parameterData *parameters);

#endif //FIND_SIMPLIFIED_INPUTPROCESSING_H

