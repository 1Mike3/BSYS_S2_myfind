
//   ##############   myfind utility  ###################################
// Author: Michal Kuc

//Standard Headers
#include <stdio.h>
//My Headers
#include "findFunctionality.h"
#include "inputProcessing.h"

int main(int argc, char ** argv) {
    //printf("Hello, World!\n");

    //central location where the User Parameters are held
    parameterData parameters = {};

    if( 0 > getStartingPointAndExpression(argc, argv, &parameters) ){
        printf("Program shutting down\n");
        return -1;
    }

    return 0;
}
