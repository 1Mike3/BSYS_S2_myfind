//
// Created by Mike on 24/03/23.
//

#include "findFunctionality.h"



#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <fcntl.h>

#define DEBUG_F 1
#define DEBUG_PRINT_OBJECT 1

int makeDirectoryObjectsList(char readOutFileNames[FILECOUNTLIMIT][FILENAMESIZELIMIT], const int maxFilenameCount, const int maxFileNameSize, parameterData parameters){

    //TODO write into LINKED LIST isntead INTO ARRAY
    
#if DEBUG_F
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
#if DEBUG_F
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







int createFileSystemObjectInstance(char objectName[FILENAMESIZELIMIT], fileSystemObject *objectStruct){

    //experiment filesStat
    struct stat statBuffer;
    char pathname[FILENAMESIZELIMIT];

    strcpy(pathname, objectName);

    stat(pathname, &statBuffer);

   // printf("statStuff1 (mode_t): %i \n", statBuffer.st_mode);




                    //Write object Name         ,checked
    strcpy(objectStruct->objectName, pathname);

                    //Determine object type and write into Object
    if       (S_ISREG(statBuffer.st_mode)){
        objectStruct->objectType = T_REGULAR_FILE;
    } else if(S_ISDIR(statBuffer.st_mode)){
        objectStruct->objectType = T_DIRECTORY;
    } else if(S_ISCHR(statBuffer.st_mode)){
        objectStruct->objectType = T_CHARACTER_DEVICE;
    } else if(S_ISBLK(statBuffer.st_mode)){
        objectStruct->objectType = T_BLOCK_DEVICE;
    } else if(S_ISFIFO(statBuffer.st_mode)){
        objectStruct->objectType = T_NAMED_PIPE;
    }else if(S_ISLNK(statBuffer.st_mode)){
        objectStruct->objectType = T_SYMBOLIC_LINK;
    }else if(S_ISSOCK(statBuffer.st_mode)){
        objectStruct->objectType = T_SOCKET;
    }

            //Determine Inode Number            ,checked
    objectStruct->inodeNumber = statBuffer.st_ino;

            //Determine number of Used Blocks               ,wrong
    objectStruct->usedBlocks = statBuffer.st_blocks;

            //Determine Permission String

            //Determine Number of links

            //Determine Owner Name

            //Determine Group

            //Determine number of size in Bytes             ,checked
            objectStruct->fileSize_Bytes = statBuffer.st_size;

            //Determine Timestamp


    return 0;
}






void printObject(fileSystemObject *object){
#if DEBUG_PRINT_OBJECT
    printf("#### print object function ####\n");
    printf("Filename: %s\n", object->objectName);
    printf("ObjectType: %i \n\n", object->objectType);
#endif
    printf("%li\t", object->inodeNumber);
    printf("%li\t", object->usedBlocks);
    printf("%s\t", object->permissionString);
    printf("%i\t", object->numberOfLinks);
    printf("%s\t", object->owner);
    printf("%s\t", object->group);
    printf("%li\t", object->fileSize_Bytes);
    printf("%s\n", object->modificationDate);
#if DEBUG_PRINT_OBJECT
    printf("## END print object function ##\n\n");
#endif
}