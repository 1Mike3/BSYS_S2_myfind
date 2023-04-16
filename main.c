
//   ##############   myfind utility  ###################################
// Author: Michal Kuc

#include <stdio.h>
#include "findFunctionality.h"
#include "inputProcessing.h"
#include <stdlib.h>
#include "linkedLists.h"
#include "expressionFunctions.h"


#define DEBUGM 0


// EXPIRED FUNCTION
//helper for printing all objects, need to be modified for ll
//void helperPrintMultidimensionalStringArray(char charArray[FILECOUNTLIMIT][FILENAMESIZELIMIT], int lineCount, int rowCount );


int main(int argc, char ** argv) {



    ///###########################  READ PAR AREA   ########################################

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





///###########################  Object Information and Linked Lists  ########################################

    ///create HEAD POINTER
    node *HEAD = calloc(1, sizeof(node));

// commenting out to focus on making of the directory list
/*
  char filename[FILENAMESIZELIMIT] = "file1.txt";


                              //TEST
                                char filename2[FILENAMESIZELIMIT] = "TestDir2";
                                char filename3[FILENAMESIZELIMIT] = "Animals";

    /// create and Link Object Instance
    createFileSystemObjectInstance(filename, HEAD);
    printObject(&(HEAD->next->object));

                            //TEST
                            createFileSystemObjectInstance(filename2, HEAD);
                            printObject(&(HEAD->next->object));

                            createFileSystemObjectInstance(filename3, HEAD);
                            printObject(&(HEAD->next->object));
*/



    ///###########################  Parsing Through Dir Structure   ########################################

char nullPathForStarters[MAX_PATH_LIMIT] = {}; //it is set to null so the initial function call can be recognized in the function
    makeDirectoryObjectsList(parameters,nullPathForStarters, HEAD);


    //Print the linked list:
    printLinkedList(HEAD);

    name(HEAD, "file1.txt");



///###########################  Helper Functions  ########################################

    //NO Longer Required, for old Array system
    //helper function to Print the names Array to the console for easier overview for me
    //helperPrintMultidimensionalStringArray(readOutNames, FILECOUNTLIMIT, FILENAMESIZELIMIT);


    //Print the linked list:
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