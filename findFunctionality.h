//
// Created by Mike on 24/03/23.
//



#ifndef FIND_SIMPLIFIED_FINDFUNCTIONALITY_H
#define FIND_SIMPLIFIED_FINDFUNCTIONALITY_H

#include "inputProcessing.h"
#define FILECOUNTLIMIT 50
#define FILENAMESIZELIMIT 128



#define PERMISSION_STRING_LENGTH 12
#define MAX_OWNER_AND_GROUP_NAME_LENGTH 20
#define MAX_DATE_TIME_LENGTH 30
#define MAX_OWNER_ID_LENGTH 10
#define MAX_PATH_LIMIT 257

#include <sys/stat.h>

/// Struct holding all the required Information of an Object in the Filesystem eg. Dir, File, Link
typedef struct FilesystemObject {
    unsigned long inodeNumber;
    long usedBlocks;
    char permissionString[PERMISSION_STRING_LENGTH];
    int numberOfLinks;
    char owner[MAX_OWNER_AND_GROUP_NAME_LENGTH];
    char group[MAX_OWNER_AND_GROUP_NAME_LENGTH];
    unsigned long fileSize_Bytes;
    char modificationDate[MAX_DATE_TIME_LENGTH];
    char objectName[FILENAMESIZELIMIT];
    int objectType;  //corresponding enum for easier use
    char fullObjectPath[MAX_PATH_LIMIT]; //Path from start dir
    __UID_T_TYPE ownerID;
   // char pathFromStartDir[MAX_PATH_LIMIT]
}fileSystemObject;


/// ennum decoding the different object types in FilesystemObject.objectType
enum OBJECT_TYPES{
    T_REGULAR_FILE,
    T_DIRECTORY,
    T_CHARACTER_DEVICE,
    T_BLOCK_DEVICE,
    T_NAMED_PIPE,
    T_SYMBOLIC_LINK,
    T_SOCKET
};



///Months enum for the correct -ls format
enum MONTHS{
    JANUARY,
    FEBRUARY,
    MARCH,
    APRIL,
    MAY,
    JUNE,
    JULY,
    AUGUST,
    SEPTEMBER,
    OCTOBER,
    NOVEMBER,
    DECEMBER
};




/// node struct for LL
typedef struct node node;
struct node {
    fileSystemObject object;
    node *next;
};


// FUNCTIONS
/**
 *
 * @param readOutFileNames
 * @param maxFilenameCount
 * @param maxFileNameSize
 * @param parameters
 * @return
 */
int makeDirectoryObjectsList(parameterData parameters,char RecursiveSearchPath[MAX_PATH_LIMIT], node * HEAD);
/**
 * @fn Create Object Instance
 * @brief creates an Object of the passed-through path and links it together in a LL
 *
 * One of the largest Functions, hard to Debug
 * Also formats the Object Data in the -ls format
 *
 * @param objectName Name of the Path that points to the Object
 * @param HEAD headpointer passed to created to
 * @return 0 if successful, -1 on Error
 */


int createFileSystemObjectInstance(char objectName[FILENAMESIZELIMIT],char currentDirPath[MAX_PATH_LIMIT], node *HEAD);



/**
 *@fn
 * @brief Pints all* the Information of an Object in the -ls Format
 * @param object
 */

void printObject(fileSystemObject *object);



#endif //FIND_SIMPLIFIED_FINDFUNCTIONALITY_H