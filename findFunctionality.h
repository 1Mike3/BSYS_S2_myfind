//
// Created by osboxes on 24/03/23.
//

#ifndef FIND_SIMPLIFIED_FINDFUNCTIONALITY_H
#define FIND_SIMPLIFIED_FINDFUNCTIONALITY_H

#include "inputProcessing.h"

#define FILECOUNTLIMIT 50
#define FILENAMESIZELIMIT 128

int makeListOfAllObjects(char readOutFileNames[FILECOUNTLIMIT][FILENAMESIZELIMIT], const int maxFilenameCount, const int maxFileNameSize, parameterData parameters);

#endif //FIND_SIMPLIFIED_FINDFUNCTIONALITY_H
