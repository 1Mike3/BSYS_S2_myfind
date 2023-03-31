//
// Created by osboxes on 24/03/23.
//

#include "inputProcessing.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

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
                    const char possibleExpressions[MAXEXPRESSIONAMMOUNT][MAXEXPRESSIONLENGTH], parameterData *parameters);

/*
int ProcessParameterData(int argumentCount, char ** argumentVector, parameterData *parameters){

    //TODO TEST
    parameters->expressionParameter[0] = '\0';
    parameters->expression[0] = '\0';
    //TODO reset Parameter Data/ !NOTALL and its flags exept path so no wrong information on second run

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


    //if the first expression is no standard expression path is assumed
    bool pathNotDetected = false;
    // index which indicates which parameter is being Processed
    short CurrentArgumentIndex = (parameters->totalProcessedParameters); //Argument which should be considerd during the next operation

    // static PATH has been Processed
    static bool pathHasBeenProcessed = false;



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
    pathNotDetected = checkParameter(argumentVector, possibleExpressionCount, possibleExpressions,
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

           checkParameter(argumentVector, possibleExpressionCount, possibleExpressions
                          , &CurrentArgumentIndex, parameters);

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
        if (argumentCount >= PARAMETERSAFEGUARD2) {

            checkParameter(argumentVector, possibleExpressionCount, possibleExpressions,
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
} else{//!! Process if this has been the second call

#if DEBUGI
    //printf("secondloopstuff #####:\n");
#endif
//TODO check if number of processed Arrguments is correct on entering
    checkParameter(argumentVector, possibleExpressionCount, possibleExpressions,
                   &CurrentArgumentIndex, parameters);
    CurrentArgumentIndex--; // so doesn't write outside argv bounds
    if(parameters->expressionValid == true){
        strcpy(parameters->expression, *(argumentVector+ CurrentArgumentIndex));
        if(parameters->expressionParReq == true){
            //TODO Manging error if Argument missing
            parameters->totalProcessedParameters++;
            CurrentArgumentIndex++;
            strcpy(parameters->expressionParameter, *(argumentVector+ CurrentArgumentIndex));

        } else{
            parameters->expressionParameter[0] = '\0';
        }
    } else{
        return 0;
    }
}
return 0;
}
*/


// if expression valid returns true
bool checkParameter(char *const *argumentVector, const short expressionCount,
                    const char possibleExpressions[MAXEXPRESSIONAMMOUNT][MAXEXPRESSIONLENGTH],parameterData *parameters){
//total processed parameters inserted below, check if it works TODO
    for (short i = 0; i <= expressionCount; i++) {
        if (0 == strcmp(*(argumentVector + parameters->totalProcessedParameters), possibleExpressions[i])) {
            if(i > 1){ //determine if Parameter for the expression is required
                //if so set the Flag in parameters
                parameters->expressionParReq = true;
            }
            parameters->expressionValid = true;
            parameters->totalProcessedParameters++;

            return true;
        }

    }
    parameters->expressionValid = false;
    parameters->expressionParReq = false;
    parameters->totalProcessedParameters++;
    return false;
}


int ProcessParameterData(int argumentCount, char ** argumentVector, parameterData *parameters){



    static int callCounter = 0; // helper to determine path during first call



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






    if(callCounter == 0){ //detrmine Path statement

        //check if the first arg is one of the valid expressions
        bool expressionValid = checkParameter(argumentVector, possibleExpressionCount, possibleExpressions, parameters);

        if(expressionValid){
            //if first argument determined to be expression write current dir as path
            parameters->searchPathStart[0] = '.';
            parameters->searchPathStart[1] = '/';
            parameters->searchPathStart[2] = '\0';
            //decrement processed Parameters, because path has been written manually
            parameters->totalProcessedParameters = 0;

        } else{  //first (second) arg is assumed to be Path
            //copy the contents of the first argument into patameters-Path
            strcpy(parameters->searchPathStart, argumentVector[1]);
        }


   //normal  operation mode, not first runthrough path determined
    } else{
// TODO No checks implemented, maybe would be good idea
        bool expressionValid = checkParameter(argumentVector, possibleExpressionCount, possibleExpressions, parameters);
        strcpy(parameters->expression, argumentVector[parameters->totalProcessedParameters]);

        if(parameters->expressionParReq == true){
            //TODO add expression valid check to notice if something is fucked up
            checkParameter(argumentVector, possibleExpressionCount, possibleExpressions, parameters);
            strcpy(parameters->expressionParameter, argumentVector[parameters->totalProcessedParameters]);
        }
    }



    //Debug Argument on every call helper
#if DEBUGI

    printf( "\n\n===== DEBUG_ProcessParameter function: ====\n");
    printf("Function Call Counter: %i\n", callCounter);
    printf("ArgumentCount: %i\n", argumentCount);
    printf("PARAMETERS:: total processed parameters: %i\n", parameters->totalProcessedParameters);
    printf("PARAMETERS:: Expression Valid?: %i\n", parameters->expressionValid);
    printf("PARAMETERS:: ExpressionValue: %s\n", parameters->expression);
    printf("PARAMETERS:: Expression Parameter: %s\n", parameters->expressionParameter);
    printf("PARAMETERS:: Expression Parameter Required?: %i \n", parameters->expressionParReq);
    printf("PARAMETERS:: Path: %s\n\n", parameters->searchPathStart);

#endif



    callCounter++;
    return 0;
}





