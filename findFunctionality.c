//
// Created by osboxes on 24/03/23.
//

#include "findFunctionality.h"


#include <sys/types.h>
#include <dirent.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#define DEBUGF 1

int makeDirectoryObjectsList(char readOutFileNames[FILECOUNTLIMIT][FILENAMESIZELIMIT], const int maxFilenameCount, const int maxFileNameSize, parameterData parameters){

#if DEBUGF
    //just wrote random garbage into array to test something
    /*
    readOurFileNames[0][0] = 'a';
    readOurFileNames[0][1] = '\0';

    readOurFileNames[1][0] = 'b';
    readOurFileNames[1][1] = 'c';
    readOurFileNames[1][2] = 'd';
    readOurFileNames[1][3] = '\0';
*/

#endif

DIR * dir;
struct dirent *dd = NULL; // Directory Data


//open the directory from the parameters, if not valid throw error and exit

    dir = opendir(parameters.searchPathStart);
#if DEBUGF
    printf("Parameter Opening: %s  \n", parameters.searchPathStart);
    printf("Dir Value: %p\n", dir);
    perror("Error Value: ");
#endif
    if (dir <= 0){
       fprintf(stderr,"ERROR opening \"Path\" Directory!\n");
       exit(-1);
   } else{

        //loop to read out the data from the directory into the array
        int tempLength = 0; // helper for checking if directory length = 0;
        int i = 0; //counter for the index of the FilenamesArray
        while (((dd = readdir( dir)) != NULL)) //check if an element could be read

            if(dd->d_name[0] != 0){ //check if the entry is empty before copying it
                tempLength = (int)strlen(dd->d_name); // seecond snaity check if really empty
                if(tempLength != 0){
                    strcpy(readOutFileNames[i], dd->d_name); //copy to array and increase array index
                    i++;
                } else {
                    break;// conditon to break the loop if templength = 0
                }

            } else{
                break; //condition to break the loop if first byte of ddname empty
            }


   }
//if closedir does not return >0 print error and exit
    if(0 != closedir(dir)){
        fprintf(stderr,"ERROR closing \"Path\" Directory!\n");
        exit(-1);
    }

    return  0;
}