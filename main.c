
//   ##############   myfind utility  ###################################
// Author: Michal Kuc

//Standard Headers
#include <stdio.h>
//My Headers
#include "findFunctionality.h"
#include "inputProcessing.h"
#include "expressionFunctions.h"
#define DEBUGM 0

void helperPrintMultidimensionalStringArray(char charArray[FILECOUNTLIMIT][FILENAMESIZELIMIT], int lineCount, int rowCount ){
    for (int i = 0; i < lineCount; ++i){

        if(charArray[i][0] == 0){
            break;
        }

        printf("Printed Object: %s\n", *(charArray + i));
    }
}




int main(int argc, char ** argv) {

    //central location where the (currently processed) User Parameters are held
    parameterData parameters = {};
    parameters.totalArgumentCount = (short)argc;
    parameters.totalProcessedParameters = 1; //start Value so Prog name Counted


    // loop to read out all the Parameters
    do { //!START



        //Reading out of the first Parameter Data and checking if it returned an error
        if (0 > ProcessParameterData(argc, argv, &parameters)) {
            printf("Program shutting down\n");
            return -1;
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






    //read through all the for the current directory in Pars and read them out into a multiDimensionalCharArray
    char readOutNames[FILECOUNTLIMIT][FILENAMESIZELIMIT] = {};
    makeDirectoryObjectsList(readOutNames, FILECOUNTLIMIT, FILENAMESIZELIMIT, parameters);

    //helper function to Print the names Array to the console for easier overview for me
    helperPrintMultidimensionalStringArray(readOutNames, FILECOUNTLIMIT, FILENAMESIZELIMIT);


    return 0;
}


