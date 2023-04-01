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


// OBJECT TYPE

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
    char fullObjectPath; //let's see if i'll need this two, but will add them anyway
    char pathFromStartDir;
}fileSystemObject;

enum OBJECT_TYPES{
    T_REGULAR_FILE,
    T_DIRECTORY,
    T_CHARACTER_DEVICE,
    T_BLOCK_DEVICE,
    T_NAMED_PIPE,
    T_SYMBOLIC_LINK,
    T_SOCKET
};



//Time

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




// LINKED LIST for managing the Object Data

typedef struct node{
    fileSystemObject object;
    fileSystemObject *next;
}node;

extern fileSystemObject * head;
extern fileSystemObject * tail;




// FUNCTIONS

int makeDirectoryObjectsList(char readOutFileNames[FILECOUNTLIMIT][FILENAMESIZELIMIT],int maxFilenameCount,int maxFileNameSize, parameterData parameters);

int createFileSystemObjectInstance(char objectName[FILENAMESIZELIMIT], fileSystemObject *objectStruct);

void printObject(fileSystemObject *object);

#endif //FIND_SIMPLIFIED_FINDFUNCTIONALITY_H