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
#include <time.h>
#include <pwd.h>
#include <grp.h>
#include "linkedLists.h"
#include "helperFunctions.h"

#define DEBUG_F 0
#define DEBUG_PRINT_OBJECT 0



//TODO adapt to ll
int makeDirectoryObjectsList( parameterData parameters,char RecursiveSearchPath[MAX_PATH_LIMIT], node * HEAD){


    
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
        //const for excluding standard directorys
        const char homeDir[] = ".";
        const char prevDir[] = "..";

        /// OPENING THE DIRECTORY
            //open the directory from the parameters, if not valid throw error and exit
            //if statement added to differentiate between the initial call and the following recursive calls
            if(RecursiveSearchPath[0] == '\0') {
                dir = opendir(parameters.searchPathStart);
            } else{
                dir = opendir(RecursiveSearchPath);
            }

#if DEBUG_F
    printf("Parameter Opening: %s  \n", parameters.searchPathStart);
    printf("Dir Value: %p\n", dir);
    perror("Error Value: ");
#endif

            ///Area for adding full Path so it can be transfered to the object
    //contains the "working directory Path so it can be correctly added to the object and used to switch dirs"
            static char currentDirPath[MAX_PATH_LIMIT] = {};
            static const char pathSeparator[] = "/";
            if(*currentDirPath == '\0'){
                strcpy(currentDirPath, parameters.searchPathStart);
            }

    if (dir <= 0){
       fprintf(stderr,"ERROR opening \"Path\" Directory!\n EID = 346745\n");
       exit(-1);
   } else{

        //loop to read out the data from the directory into the array
        int tempLength = 0; // helper for checking if directory length = 0;
        int i = 0; //counter for the index of the FilenamesArray
        while (((dd = readdir( dir)) != NULL)) //check if an element could be read

            if(dd->d_name[0] != 0){ //check if the entry is empty before copying it
                tempLength = (int)strlen(dd->d_name); // second sanity check if really not empty



                if(tempLength != 0 ) {

                    /// CREATE LINKED LIST AREA
                    //switch to linked list and create object, so will comment out
                    /*
                    strcpy(readOutFileNames[i], dd->d_name); //copy to array and increase array index
                    i++;
                     */

                    //condition for skipping the . and .. dirs
                    if(0 != strcmp(dd->d_name, prevDir) && 0 != strcmp(dd->d_name, homeDir)){

                        int returnCrObjInst; //return value of the function below

                            ///CREATING OBJECT

                            if(RecursiveSearchPath[0] == '\0') {
                                returnCrObjInst = createFileSystemObjectInstance(dd->d_name, currentDirPath, HEAD);
                            }else{
                                char fullObjectName[MAX_PATH_LIMIT];
                                strcat(fullObjectName, currentDirPath);
                                strcat(fullObjectName, pathSeparator);
                                strcat(fullObjectName, dd->d_name);
                                returnCrObjInst = createFileSystemObjectInstance(fullObjectName, currentDirPath, HEAD);
                            }
                           if(returnCrObjInst == -1){
                               fprintf(stderr,"!ERROR, createFileSystemObjectInstance Failed!\n EID = 925899\n");
                               return -1;
                            }

                    i++;

                    ///conditions if Object is DIRECTORY
                    if (dd->d_type == DT_DIR) {
                        size_t currentDirPathLen = strlen(currentDirPath);
                        size_t availableSpace = MAX_PATH_LIMIT - currentDirPathLen - 1;
//adding the directory th the path
                        if (availableSpace > 0) {
                            strncat(currentDirPath, pathSeparator, availableSpace);
                            strncat(currentDirPath, dd->d_name, availableSpace);
                        } else {
                            fprintf(stderr, "ERROR, could not append Dir Path, Path too long\n EID: 452345 \n");
                        }
                    }
#if DEBUG_F
                        printf("FUSED String: %s \n", currentDirPath);
#endif
                    //!!! call the function again with the updated path
                        strcpy(RecursiveSearchPath, currentDirPath); //add search path to parameter so can be used on anoter function call
                        int returnMkdirOl = makeDirectoryObjectsList(parameters, RecursiveSearchPath, HEAD);
                        if(returnMkdirOl == -1)
                            return -1;
                        removeLastEntryToPath(currentDirPath);
                        removeLastEntryToPath(RecursiveSearchPath);
                    } // end if is dir statement
                    ///END CREATE LINKED LIST AREA

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








//#############################################################################################

int createFileSystemObjectInstance(char objectName[FILENAMESIZELIMIT],char currentDirPath[MAX_PATH_LIMIT], node *HEAD){


    ///initialize object struct
    fileSystemObject *objectStruct = calloc(1, sizeof(fileSystemObject));



/// initailize stat struct with object instance with selected boject
    struct stat statBuffer;
    char pathname[FILENAMESIZELIMIT];
    strcpy(pathname, objectName);
    stat(pathname, &statBuffer);






//######################################################## Start determine -ls Objects Area


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
//writing symbols char by char with the permission macros
    objectStruct->permissionString[0] = (char)(S_ISDIR(statBuffer.st_mode) ? 'd' : '-');
    objectStruct->permissionString[1] = (char )((statBuffer.st_mode & S_IRUSR) ? 'r' : '-');
    objectStruct->permissionString[2] = (char )((statBuffer.st_mode & S_IWUSR) ? 'w' : '-');
    objectStruct->permissionString[3] = (char )((statBuffer.st_mode & S_IXUSR) ? 'x' : '-');
    objectStruct->permissionString[4] = (char )((statBuffer.st_mode & S_IRGRP) ? 'r' : '-');
    objectStruct->permissionString[5] = (char )((statBuffer.st_mode & S_IWGRP) ? 'w' : '-');
    objectStruct->permissionString[6] = (char )((statBuffer.st_mode & S_IXGRP) ? 'x' : '-');
    objectStruct->permissionString[7] = (char )((statBuffer.st_mode & S_IROTH) ? 'r' : '-');
    objectStruct->permissionString[8] = (char )((statBuffer.st_mode & S_IWOTH) ? 'w' : '-');
    objectStruct->permissionString[9] = (char )((statBuffer.st_mode & S_IXOTH) ? 'x' : '-');



            //Determine Number of links
    objectStruct->numberOfLinks = (int)statBuffer.st_nlink;



            //Determine Owner Name
    //guess i'll do it with the password function
    struct passwd *pw = getpwuid(statBuffer.st_uid);
    if(pw == NULL){
        fprintf(stderr,"!ERROR, Determining pw Struct returned NULL!\n EID = 024968\n");
        return -1;
    }
    strcpy(objectStruct->owner, pw->pw_name);



            //Determine Group
    struct group *grp = getgrgid(statBuffer.st_gid);
    if(grp == NULL){
        fprintf(stderr, "!ERROR determining Group, groupPointer = Null!\n EID = 24356\n");
        return -1;
    }

    strcpy(objectStruct->group, grp->gr_name);



        //Determine number of size in Bytes             ,checked
        objectStruct->fileSize_Bytes = statBuffer.st_size;




                        //Determine Timestamp

            //objectStruct->modificationDate
            char lastModTimeString[MAX_DATE_TIME_LENGTH];
            struct timespec timeMod = statBuffer.st_mtim;

                struct tm tm; //create struct broken down in time valuesl
                tm  = *gmtime(&timeMod.tv_sec); //get time split into struct

                int year = tm.tm_year;
                int day = tm.tm_mday;
                int min = tm.tm_min;
                int hour = tm.tm_hour;
            /*
                printf("TIMEPRINTTEST:::::::::\n\n");
                printf("mon = %d\n",mon);
                printf("day = %d\n", day);
               // printf("year = %i\n", year);
                printf("hour = %d\n", hour);
                printf("min = %d\n\n", min);
            */
                //determine Month
                char monthString[4] = {};
                //stitchcase To write correct monthstring.
                switch (tm.tm_mon) {
                    case JANUARY:strcpy(monthString, "JAN");break;
                    case FEBRUARY:strcpy(monthString, "FEB");break;
                    case MARCH:strcpy(monthString, "MAR");break;
                    case APRIL:strcpy(monthString, "APR");break;
                    case MAY:strcpy(monthString, "MAY");break;
                    case JUNE:strcpy(monthString, "JUN");break;
                    case JULY:strcpy(monthString, "JUL");break;
                    case AUGUST:strcpy(monthString, "AUG");break;
                    case SEPTEMBER:strcpy(monthString, "SEP");break;
                    case OCTOBER:strcpy(monthString, "OCT");break;
                    case NOVEMBER:strcpy(monthString, "NOV");break;
                    case DECEMBER:strcpy(monthString, "DEC");break;
                    default:
                        fprintf(stderr, "ERROR Time Determination unexpected Behavior\n");
                        break;
                }

                //days
                char dayString[5];
                sprintf(dayString, "%d", day);

                //shift hour offset
                hour++; //because counts from 0 offset
                char hourString[5];
                sprintf(hourString, "%d", hour);

                //minutes a
                char minuteString[5];
                sprintf(minuteString, "%d", min);

                // colon separator
                char separator = ':';

                // Fuse everything together into Correct time String
                lastModTimeString[0] = '\0'; // set to zero in the beginning
                strcpy(lastModTimeString, monthString);
                strcat(lastModTimeString, " ");
                strcat(lastModTimeString, dayString);
                strcat(lastModTimeString, " ");
                strcat(lastModTimeString, hourString);
                strcat(lastModTimeString, ":");
                strcat(lastModTimeString, minuteString);



                // OLD WORKS BUT WRONG FORMAT strcpy(lastModTimeString,(ctime(&timeMod.tv_sec)));
                strcpy(objectStruct->modificationDate, lastModTimeString);

//determine full path of the object and write it into the struct
static const char pathSeparator[] = "/";
    strcat(objectStruct->fullObjectPath,currentDirPath);
    strcat(objectStruct->fullObjectPath,pathSeparator);
    strcat(objectStruct->fullObjectPath,objectStruct->objectName);


#if DEBUG_F
    printf("FULL OBJECT PATH IN CREATE OBJECT: %s \n", objectStruct->fullObjectPath);
#endif
//############################## End Determine Objects Area




    //zone in which th Linked List functions are being processed
    ///############### LL ZONE #########################################
    llLink(HEAD, objectStruct);
    free(objectStruct);

    ///################## END LL ZONE #########################################


    return 0;
};







//#############################################################################################

void printObject(fileSystemObject *object){
#if DEBUG_PRINT_OBJECT
    printf("#### print object function ####\n");
   // printf("Filename: %s\n", object->objectName);
    printf("ObjectType: %i \n", object->objectType);
#endif
    printf("%li\t", object->inodeNumber);
    printf("%li\t", object->usedBlocks);
    printf("%s\t", object->permissionString);
    printf("%i\t", object->numberOfLinks);
    printf("%s\t", object->owner);
    printf("%s\t", object->group);
    printf("%li\t", object->fileSize_Bytes);
    printf("%s\t", object->modificationDate);
    printf("%s\n", object->objectName); //TODO maybe change later to full object path
#if DEBUG_PRINT_OBJECT
    printf("## END print object function ##\n\n");
#endif
}