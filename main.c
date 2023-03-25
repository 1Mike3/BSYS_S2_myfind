
//   ##############   myfind utility  ###################################
// Author: Michal Kuc

//Standard Headers
#include <stdio.h>
//My Headers
#include "findFunctionality.h"
#include "inputProcessing.h"
#include "expressionFunctions.h"
#define DEBUGM 1

void helperPrintMultidimensionalStringArray(char charArray[FILECOUNTLIMIT][FILENAMESIZELIMIT], int lineCount, int rowCount ){
    for (int i = 0; i < lineCount; ++i){

        if(charArray[i][0] == 0){
            break;
        }

        printf("Printed Object: %s\n", *(charArray + i));
    }
}




int main(int argc, char ** argv) {
    //printf("Hello, World!\n");

    //central location where the User Parameters are held
    parameterData parameters = {};

    if( 0 > getStartingPointAndExpression(argc, argv, &parameters) ){
        printf("Program shutting down\n");
        return -1;
    }

    //read through all the files and read them out into a multiDimensionalCharArray


    char readOutNames[FILECOUNTLIMIT][FILENAMESIZELIMIT] = {};

    makeListOfAllObjects(readOutNames, FILECOUNTLIMIT, FILENAMESIZELIMIT,parameters);

    helperPrintMultidimensionalStringArray(readOutNames, FILECOUNTLIMIT, FILENAMESIZELIMIT);


    return 0;
}


