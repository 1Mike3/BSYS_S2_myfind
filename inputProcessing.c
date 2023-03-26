//
// Created by osboxes on 24/03/23.
//

#include "inputProcessing.h"
#include <stdio.h>
#include <string.h>

#define DEBUGI 1


// myfind [starting point] [expression]

//return Values
//successful return 0
//unsuccessful return -1

//LOOPS THROUGH ARGUMENT AND CHECKS IF IT MATCHES POSSIBLE EXPRESSIONS
//Return: if found expression returns true
// if not found expression returns FALSE
//added parameters for good mesaure so i can check extaStuff in this Function:
//If Parameter is Required
bool checkParameter(char *const *argumentVector, const short expressionCount,
                    const char possibleExpressions[MAXEXPRESSIONAMMOUNT][MAXEXPRESSIONLENGTH],
                    short *currentArgumentIndex, parameterData *parameters);


int ProcessParameterData(int argumentCount, char ** argumentVector, parameterData *parameters){

    //TODO reset Parameter Data and its flags exept path so no wron information on second run

    //the possible expressions and their count, so they can be checked in a loop
    const short expressionCount = 5; //just write the number of valid expressions below into this variable
    const char possibleExpressions[MAXEXPRESSIONAMMOUNT][MAXEXPRESSIONLENGTH] = {
        "-print",
        "-ls",
        "-name", //tests so for the last three Parameters Required
        "-type",
        "-user",
        "",
        "",
        "",
        "",
        ""
    };


    //if the first expression is no standard expression path is assumed
    bool pathNotDetected = false;
    // index which indicates which parameter is being Processed
    short CurrentArgumentIndex = (parameters->totalProcessedParameters); //Argument which should be considerd during the next operation

    // static PATH has been Processed
    static bool pathHasBeenProcessed = false; //TODO will probably cause an error
    // Parameter is for expression is Required
    bool expressionParameterRequired = false;

    //CHECK IF ENOUGH PARAMETERS
    if(argumentCount == 1){
        fprintf(stderr, "ERROR: no Parameters submitted!\n");
        return -1;
    }


  //check IF NOT too MANY CHARS entered
    int lengthArgOne = 0;
    int lengthArgTwo = 0;
    int lengthArgThree = 0;


    //check if every entry not too long, if so don't try to reed in unassigned location
        if(argumentCount >= 2)
    lengthArgOne = (int)strlen(*(argumentVector+1));

        if(argumentCount >= 3)
    lengthArgTwo = (int)strlen(*(argumentVector+2));

        if(argumentCount >= 4)
    lengthArgThree = (int)strlen(*(argumentVector+3));

     if(lengthArgOne >= MAXCAHRSPAR1 || lengthArgTwo >= MAXCHARSPAR2 || lengthArgThree >= MAXCHARSPAR3){
        fprintf(stderr, "ERROR: too long Parameters!\n");
        return -1;
    }




                                //CHECKING IF FIRST INPUT PATH AND REACTING
if(!pathHasBeenProcessed) { // if not the first run through ignore the path stuff


    CurrentArgumentIndex++; // fo first argument gets skipped on first run
    parameters->totalProcessedParameters ++;


    //LOOP TO CHECK IF FIRST INPUT IS PATH
    //if one of the possible matches the first input was not a path so the bool marker will be set
    pathNotDetected = checkParameter(argumentVector, expressionCount, possibleExpressions,
                                     &CurrentArgumentIndex, parameters);



    //!! path not detected first par
    if (pathNotDetected == true) {

        // no path was entered so write home directory as starting directory
        parameters->searchPathStart[0] = '.';
        parameters->searchPathStart[1] = '/';
        parameters->searchPathStart[2] = '\0';
        pathHasBeenProcessed = true; //set so Program knows not to evaluate path on second call

        // because first argument is not path so must be argument, write argument first parameter
        if (argumentCount >= PARAMETERSAFEGUARD1){

           checkParameter(argumentVector, expressionCount, possibleExpressions
                          ,&CurrentArgumentIndex, parameters);

            strcpy(parameters->expression, *(argumentVector + PARAMETERINDEX1));

        }


        // same logic for the following argument // if it requires an expression
        if (argumentCount >= PARAMETERSAFEGUARD2 && parameters->expressionParReq == true) {
            strcpy(parameters->expressionParameter, *(argumentVector + PARAMETERINDEX2));
            CurrentArgumentIndex++; //incremet the Processed Parameters
            parameters->totalProcessedParameters ++;
        }

#if DEBUGI
        printf("No Path detected, Path is: %s\n", parameters->searchPathStart);
#endif

    //!! path detected first par
    } else {    //Path was detected as the first Parameter

        //the first Parameter is the assumed Path, not checked for correctness
        if (argumentCount >= PARAMETERSAFEGUARD1) {
            strcpy(parameters->searchPathStart, *(argumentVector + PARAMETERINDEX1));
            pathHasBeenProcessed = true; //set so Program knows not to evaluate path on second call
        }


        //same logic for the expression and its Parameter:
        if (argumentCount >= PARAMETERSAFEGUARD2){

             checkParameter(argumentVector, expressionCount, possibleExpressions,
                            &CurrentArgumentIndex, parameters);

            strcpy(parameters->expression, *(argumentVector + PARAMETERINDEX2));
        }


        if (argumentCount >= PARAMETERSAFEGUARD3 && parameters->expressionParReq == true) {
            strcpy(parameters->expressionParameter, *(argumentVector + PARAMETERINDEX3));
            CurrentArgumentIndex++; //incremet the Processed Parameters
            parameters->totalProcessedParameters++;
        }

#if DEBUGI
        printf("Path detected path is: %s\n", parameters->searchPathStart);
#endif
    }


#if DEBUGI
    printf("This Should be the Starting Point: %s \n", parameters->searchPathStart);
    printf("This Should be the Expression: %s \n", parameters->expression);
    printf("This Should be the Expression Parameter: %s \n", parameters->expressionParameter);
#endif

//!! END IF PATH HAS BEEN PROCESSED
} else{ //!! Process if this has been the second call

}



    return 0;
}



bool checkParameter(char *const *argumentVector, const short expressionCount,
                    const char possibleExpressions[MAXEXPRESSIONAMMOUNT][MAXEXPRESSIONLENGTH],
                    short *currentArgumentIndex, parameterData *parameters){

    for (short i = 0; i <= expressionCount; i++) {
        if (0 == strcmp(*(argumentVector + *(currentArgumentIndex)), possibleExpressions[i])) {
            if(i > 1){ //determine if Parameter for the expression is required
                //if so set the Flag in parameters
                parameters->expressionParReq = true;
            }
            parameters->expressionValid = true;
            parameters->totalProcessedParameters++;
            *(currentArgumentIndex) = *(currentArgumentIndex) +1;
            return true;
        }
    }
    parameters->expressionValid = false;
    parameters->expressionParReq = false;
    parameters->totalProcessedParameters++;
    *(currentArgumentIndex) = *(currentArgumentIndex) +1;
    return false;
}








