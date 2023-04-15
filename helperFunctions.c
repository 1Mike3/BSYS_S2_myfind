//
// Created by michi on 4/15/23.
//

#include "helperFunctions.h"
#include <string.h>
/**
 * @brief helper to remove the last entry added to path
 *      it removes everything until and including the / character
 * @param str string which will be modified
 */
void removeLastEntryToPath(char *str) {
    const char ch = '/';
    char *last_occurrence = strrchr(str, ch);
    if (last_occurrence) {
        *last_occurrence = '\0';
    }
}