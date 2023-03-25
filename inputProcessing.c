//
// Created by osboxes on 24/03/23.
//

#include "inputProcessing.h"
#include <stdio.h>
#include <string.h>

#define DEBUGI 1

//TODO add functionality for further expressions and tests

// myfind [starting point] [expression]

//return Values
//successful return 0
//unsuccessful return -1

//TODO well should have read the assignmment correctly i will need to adapt this ...
int ProcessParameterData(int argumentCount, char ** argumentVector, parameterData *parameters){

    //the possible expressions and their count, so they can be checked in a loop
    const short expressionCount = 4;
    const char possibleExpressions[10][10] = {
        "-print",
        "-ls",
        "-name",
        "-type",
        "0",
        "0",
        "0",
        "0",
        "0",
        "0"
    };


    //if the first expression is no standard expression path is assumed
    bool pathNotDetected = false;

    //argument counter to count the processed Information
    int processedArguments = 1; //one because of firs one prog name


                                    //check IF ENOUGH PARAMETERS

                                    if(argumentCount == 1){
                                        fprintf(stderr, "ERROR: no Parameters submitted!\n");
                                        return -1;
                                    }


                                  //check IF NOT too MANY CHARS entered
    int lengthArgOne = 0;
    int lengthArgTwo = 0;
    int lengthArgThree = 0;

    //check if every entery not too long, if so don't try to reed in unassigned location
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




                                //Checking IF first input PATH and REACTING

            //loop to check if first input is Path
   //if one of the possible matches the first input was not a path so the bool marker will be set
    for(short i = 0; i <= expressionCount; i++){
       if(0 == strcmp(*(argumentVector+1), possibleExpressions[i])  ){
           pathNotDetected = true; //setMarker so know if path was specified
           break;
       }
    }

            //react to path detection
    if(pathNotDetected == true){

        // no path was entered so write home directory as starting directory
        parameters->searchPathStart[0] = '.';
        parameters->searchPathStart[1] = '/';
        parameters->searchPathStart[1] = '\0';

        // because first argument is not path so must be argument, write argument first parameter

         if(argumentCount >= PARAMETERSAFEGUARD1)
        strcpy(parameters->expression, *(argumentVector+PARAMETERINDEX1));

        // same logic for the following argument

         if(argumentCount >= PARAMETERSAFEGUARD2)
       strcpy(parameters->expressionParameter, *(argumentVector+PARAMETERINDEX2));
#if DEBUGI
        printf("No Path detected, Path is: %s\n", parameters->searchPathStart);
#endif
        //Path was detected as the first Parameter
    } else{
        //the first Parameter is the assumed Path, not checked for correctness

            if(argumentCount >= PARAMETERSAFEGUARD1)
        strcpy(parameters->searchPathStart, *(argumentVector+PARAMETERINDEX1));

        //same logic for the expression and its Parameter:

             if(argumentCount >= PARAMETERSAFEGUARD2)
        strcpy(parameters->expression, *(argumentVector+PARAMETERINDEX2));

            if(argumentCount >= PARAMETERSAFEGUARD3)
        strcpy(parameters->expressionParameter, *(argumentVector+PARAMETERINDEX3));
#if DEBUGI
            printf("Path detected path is: %s\n", parameters->searchPathStart);
#endif
    }



#if DEBUGI
    printf("This Should be the Starting Point: %s \n", parameters->searchPathStart);
    printf("This Should be the Expression: %s \n", parameters->expression);
    printf("This Should be the Expression Parameter: %s \n", parameters->expressionParameter);
#endif


    return 0;
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

