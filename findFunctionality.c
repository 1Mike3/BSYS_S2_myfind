//
// Created by osboxes on 24/03/23.
//

#include "findFunctionality.h"


#include <sys/types.h>
#include <dirent.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int makeListOfAllObjects(char readOurFileNames[FILECOUNTLIMIT][FILENAMESIZELIMIT], const int maxFilenameCount, const int maxFileNameSize,parameterData parameters){
/*
    readOurFileNames[0][0] = 'a';
    readOurFileNames[0][1] = '\0';

    readOurFileNames[1][0] = 'b';
    readOurFileNames[1][1] = 'c';
    readOurFileNames[1][2] = 'd';
    readOurFileNames[1][3] = '\0';
*/

DIR * dir;
struct dirent *dd = NULL; // Directory Data


//open the directory from the parameters, if not valid throw error and exit
    dir = opendir(parameters.searchPathStart);


    if (dir <= 0){
       fprintf(stderr,"ERROR opening \"Path\" Directory!\n");
       exit(-1);
   } else{

        //loop to read out the data from the directory into the array
        int i = 0;
        while ((dd ))
      dd = readdir( dir);




        i++;
   }
//if closedir does not return >0 print error and exit
    if(!closedir(dir)){
        fprintf(stderr,"ERROR closing \"Path\" Directory!\n");
        exit(-1);
    }

    return  0;
}