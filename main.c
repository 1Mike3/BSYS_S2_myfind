
//   ##############   myfind utility  ###################################
// Author: Michal Kuc

#include <stdio.h>
#include "findFunctionality.h"
#include "inputProcessing.h"
#include <stdlib.h>
#include "linkedLists.h"
#include "expressionFunctions.h"


#define DEBUGM 0

//TODO make static to limit the number the function can be recursively called

// EXPIRED FUNCTION
//helper for printing all objects, need to be modified for ll
//void helperPrintMultidimensionalStringArray(char charArray[FILECOUNTLIMIT][FILENAMESIZELIMIT], int lineCount, int rowCount );


int main(int argc, char ** argv) {



    ///create HEAD POINTER for ll
    node *HEAD = calloc(1, sizeof(node));

    //for the initial call of the makedirlist function because this par is only used on recursive calls
    char nullPathForStarters[MAX_PATH_LIMIT] = {}; //it is set to null so the initial function call can be recognized in the function

    //flags for The Print function to change the Output
    bool flagLs = false;
    bool flagPrint = false;


    ///###########################  READ PAR AREA   ########################################

    //central location where the (currently processed) User Parameters are held
    parameterData parameters = {};
    parameters.totalArgumentCount = (short)argc;
    parameters.totalProcessedParameters = 1; //start Value so Prog name Counted

    //marker which is used so the directory list is only created once
    bool markerCreateDirectoryList = false;

    // loop to read out all the Parameters
    do { //!START



        //Reading out of the first Parameter Data and checking if it returned an error
        if (0 > ProcessParameterData(argc, argv, &parameters)) {
            printf("Program shutting down\n");
            return -1;
        }

        ///making of the directory list
       //if statement so it is definitively only called once
        if(markerCreateDirectoryList == false){
           if(-1 == makeDirectoryObjectsList(parameters,nullPathForStarters, HEAD)) {
               fprintf(stderr, "ERROR makeDirectoryObjectsList function failed!\n EID = 2345896\n");
               return -1;
           }
            markerCreateDirectoryList = true;
        }



///Applying of the Filters
if(parameters.expressionValid == true){
    ///case -ls
    if(0 == strcmp(parameters.expression,"-ls")){
        flagLs = true;
    }
    ///case -print
    else if(0 == strcmp(parameters.expression,"-print")){
        flagPrint = true;
    }
    ///case -name
    else if(0 == strcmp(parameters.expression,"-name")){
        name(HEAD, parameters.expressionParameter);
    }
    ///case -type
    else if(0 == strcmp(parameters.expression,"-type")){
        type(HEAD,parameters.expressionParameter);
    }
    ///case -user
    else if(0 == strcmp(parameters.expression,"-user")){
        user(HEAD,parameters.expressionParameter);
    }

}



#if DEBUGM
        static int b = 1;
        printf("OUTSIDE OF LOOP, LOOPCOUNTER: %i\n", b);
        printf("Starting Point: %s \n", parameters.searchPathStart);
        printf("Expression: %s \n", parameters.expression);
        printf("Expression Parameter: %s \n", parameters.expressionParameter);
        b++;
#endif
    }while(parameters.totalProcessedParameters != parameters.totalArgumentCount); //!END



    ///Print the Output to the command line
    printLinkedList(HEAD);

///Destroy the Linked List
    llDestroyLinkedList(HEAD);






    return 0;

}




// EXPIRED FUNCTION

 /*
//helper for printing all objects, need to be modified for ll
void helperPrintMultidimensionalStringArray(char charArray[FILECOUNTLIMIT][FILENAMESIZELIMIT], int lineCount, int rowCount ){
    for (int i = 0; i < lineCount; ++i){

        if(charArray[i][0] == 0){
            break;
        }

        printf("Printed Object: %s\n", *(charArray + i));
    }
}
*/