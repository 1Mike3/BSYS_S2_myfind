//
// Created by Mike on 24/03/23.
//

#include "inputProcessing.h"
#include <stdio.h>
#include <string.h>


#define DEBUG_I 0


// my_find [starting point] [expression]

// function Definitions
int checkArgument(char *const *argumentVector, short expressionCount,
                   const char possibleExpressions[MAXEXPRESSIONAMMOUNT][MAXEXPRESSIONLENGTH], parameterData *parameters);








int ProcessParameterData(int argumentCount, char ** argumentVector, parameterData *parameters){

    if(argumentCount == 1){ //for starters if no args detected no point in going on
        fprintf(stderr,"No Arguments detected!\n");
        return -1;
    }
    static int callCounter = 0; // helper to determine path during first call, and for debugging

    //the possible expressions and their count, so they can be checked in a loop
    //! if changes to this the check parameter function needs to be adjusted because of the parameters required attribute
    const short possibleExpressionCount = 5; //just write the number of valid expressions below into this variable
    const char possibleExpressions[MAXEXPRESSIONAMMOUNT][MAXEXPRESSIONLENGTH] = {
            "-print",
            "-ls",
            "-name", //tests for the last three Parameters Required
            "-type",
            "-user",
            "",
            "",
            "",
            "",
            ""
    };






//!! ## first call ##       only for determining path, called once
    if(callCounter == 0){
        int expressionValidDetermination = checkArgument(argumentVector, possibleExpressionCount, possibleExpressions, parameters);
        if(expressionValidDetermination == VALID_ARGUMENT_NOPAR || expressionValidDetermination == VALID_ARGUMENT_PAR){
            //if first argument determined to be expression write current dir as path
            parameters->searchPathStart[0] = '.';
            parameters->searchPathStart[1] = '/';
            parameters->searchPathStart[2] = '\0';
            //decrement processed Parameters, because path has been written manually
            parameters->totalProcessedParameters = 1;

        } else{  //first (second) arg is assumed to be Path
            //copy the contents of the first argument into parameters-Path
            strcpy(parameters->searchPathStart, argumentVector[1]);
            parameters->totalProcessedParameters = 2;
        }






   //!! ## Normal Operation Mode ##              activated every time after path has been determined
    } else {

        //check if valid arg
        int expressionValidDetermination = checkArgument(argumentVector, possibleExpressionCount, possibleExpressions,
                                                         parameters);

        //reaction if valid arg
        if (expressionValidDetermination == VALID_ARGUMENT_NOPAR || expressionValidDetermination == VALID_ARGUMENT_PAR) {
            strcpy(parameters->expression, argumentVector[parameters->totalProcessedParameters + STRCPYOFFSET]);
            parameters->expressionValid = true;
            parameters->totalProcessedParameters += 1;

            //reaction if argument also requires parameter
            if (expressionValidDetermination == VALID_ARGUMENT_PAR) { //arg required value meaning
                parameters->expressionParReq = true;
                strcpy(parameters->expressionParameter,
                       argumentVector[parameters->totalProcessedParameters + EXPRESSIONPAROFFSET]);
                parameters->totalProcessedParameters += 1; // increment after argument has been processed


                //if it does not require value set to zero so clear that invalid value
            } else {
                parameters->expressionParReq = false;
                parameters->expressionParameter[0] = '\0';
            }


            //reaction if not valid arg
        } else {
            printf("!!Invalid Argument Detected and Skipped!!\n");
            parameters->expressionParameter[0] = '\0';
            parameters->expression[0] = '\0';
            parameters->expressionValid = false;
            parameters->expressionParReq = false;
            parameters->totalProcessedParameters += 1; //skip parameter by incrementing processed pars counter
        }
    }






    //Debug Argument on every call helper
#if DEBUG_I

    printf( "\n\n===== DEBUG_ProcessParameter function: ====\n");
    printf("Function Call Counter: %i\n", callCounter);
    printf("PARAMETERS:: Path: %s\n\n", parameters->searchPathStart);
    printf("PARAMETERS:: Total ArgumentCount: %i\n", parameters->totalArgumentCount);
    printf("PARAMETERS:: total processed parameters: %i\n\n", parameters->totalProcessedParameters);

    printf("PARAMETERS:: Expression Valid?: %i\n", parameters->expressionValid);
    printf("PARAMETERS:: ExpressionValue: %s\n\n", parameters->expression);

    printf("PARAMETERS:: Expression Parameter Required?: %i \n", parameters->expressionParReq);
    printf("PARAMETERS:: Expression Parameter: %s\n\n", parameters->expressionParameter);

#endif

    callCounter++;
    return 0;
}




/**
 * @brief if expression valid returns true
 * rewritten so writes nothing in parameters, only says if is valid expression and if it needs a par
 * @param argumentVector
 * @param expressionCount
 * @param possibleExpressions
 * @param parameters
 * @return
 * 0 if not valid argument
 * 1 if valid Argument
 * 2 if valid Argument and requires Parameter
 */
int checkArgument(char *const *argumentVector,short expressionCount,
                  const char possibleExpressions[MAXEXPRESSIONAMMOUNT][MAXEXPRESSIONLENGTH], parameterData *parameters){


#if DEBUG_I
    printf("\n##EVALUETED String: %s ##\n", *(argumentVector + parameters->totalProcessedParameters + CHECKARGOFFSET));
#endif
    for (short i = 0; i <= expressionCount; i++) {

        if (0 == strcmp(*(argumentVector + parameters->totalProcessedParameters + CHECKARGOFFSET), possibleExpressions[i])) {
            if(i > 1){ //determine if Parameter for the expression is required
#if DEBUG_I
                printf("##EVALUETED String RETURN: 2, valid arg and Par required ##\n\n");
#endif
                return VALID_ARGUMENT_PAR;
            }
#if DEBUG_I
            printf("##EVALUETED String RETURN: 1, valid arg##\n\n");
#endif
            return VALID_ARGUMENT_NOPAR;
        }

    }
#if DEBUG_I
    printf("##EVALUETED String RETURN: 0, invalid arg##\n\n");
#endif
    return INVALID_ARGUMENT;
}



