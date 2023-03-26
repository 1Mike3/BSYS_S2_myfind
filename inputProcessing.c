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
bool checkIfArgumentIsValidExpression(char *const *argumentVector,const short expressionCount,
                                      const char possibleExpressions[MAXEXPRESSIONAMMOUNT][MAXEXPRESSIONLENGTH],
                                      short currentArgumentIndex);


int ProcessParameterData(int argumentCount, char ** argumentVector, parameterData *parameters){

    //the possible expressions and their count, so they can be checked in a loop
    const short expressionCount = 4; //just write the number of valid expressions below into this variable
    const char possibleExpressions[MAXEXPRESSIONAMMOUNT][MAXEXPRESSIONLENGTH] = {
        "-print",
        "-ls",
        "-name",
        "-type",
        "",
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
    CurrentArgumentIndex++;
    // static PATH has been Processed
    static bool pathHasBeenProcessed = false; //TODO will probably cause an error


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

    //loop to check if first input is Path
    //if one of the possible matches the first input was not a path so the bool marker will be set
    pathNotDetected = checkIfArgumentIsValidExpression(argumentVector, expressionCount, possibleExpressions, CurrentArgumentIndex);

    //############################### REACT TO PATH DETECTION
    if (pathNotDetected == true) {

        // no path was entered so write home directory as starting directory
        parameters->searchPathStart[0] = '.';
        parameters->searchPathStart[1] = '/';
        parameters->searchPathStart[2] = '\0';
        pathHasBeenProcessed = true; //set so Program knows not to evaluate path on second call

        // because first argument is not path so must be argument, write argument first parameter
        if (argumentCount >= PARAMETERSAFEGUARD1)
            strcpy(parameters->expression, *(argumentVector + PARAMETERINDEX1));

        // same logic for the following argument
        if (argumentCount >= PARAMETERSAFEGUARD2)
            strcpy(parameters->expressionParameter, *(argumentVector + PARAMETERINDEX2));


#if DEBUGI
        printf("No Path detected, Path is: %s\n", parameters->searchPathStart);
#endif

    } else {    //Path was detected as the first Parameter

        //the first Parameter is the assumed Path, not checked for correctness
        if (argumentCount >= PARAMETERSAFEGUARD1) {
            strcpy(parameters->searchPathStart, *(argumentVector + PARAMETERINDEX1));
            pathHasBeenProcessed = true; //set so Program knows not to evaluate path on second call
        }


        //same logic for the expression and its Parameter:
        if (argumentCount >= PARAMETERSAFEGUARD2)
            strcpy(parameters->expression, *(argumentVector + PARAMETERINDEX2));

        if (argumentCount >= PARAMETERSAFEGUARD3)
            strcpy(parameters->expressionParameter, *(argumentVector + PARAMETERINDEX3));
#if DEBUGI
        printf("Path detected path is: %s\n", parameters->searchPathStart);
#endif
    }


#if DEBUGI
    printf("This Should be the Starting Point: %s \n", parameters->searchPathStart);
    printf("This Should be the Expression: %s \n", parameters->expression);
    printf("This Should be the Expression Parameter: %s \n", parameters->expressionParameter);
#endif

} //!! END IF PATH HAS BEEN PROCESSED



    return 0;
}

bool checkIfArgumentIsValidExpression(char *const *argumentVector, const short expressionCount,
                                      const char possibleExpressions[MAXEXPRESSIONAMMOUNT][MAXEXPRESSIONLENGTH],
                                      short currentArgumentIndex){

    for (short i = 0; i <= expressionCount; i++) {
        if (0 == strcmp(*(argumentVector + currentArgumentIndex), possibleExpressions[i])) {
            return true;
        }
    }
    return false;
}





















//old getopt
/*
             //getting stuff from getOpt
 while (true)
 {

              //some Stuff to detect wrong Inputs


     int result = getopt(argumentCount, argumentVector, "print:ls:name:type");
     if (result == -1) break;
     switch (result)
     {
         case '?':
             break;
         case ':':
             fprintf(stderr, "missing argument.\n");
             break;
         case 'print':
             printf("'a' was specified.\n");
             break;
         case 'b':
             printf("'b' was specified.\n");
             break;
         case 'c':
             printf("'c' was specified. Arg: <%s>\n", optarg);
             break;
         case 'd':
             printf("'d' was specified.\n");
             break;
         default:
             break;
     }
 }

*/

