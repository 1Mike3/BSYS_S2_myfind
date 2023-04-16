//
// Created by osboxes on 24/03/23.
//

#ifndef FIND_SIMPLIFIED_EXPRESSIONFUNCTIONS_H
#define FIND_SIMPLIFIED_EXPRESSIONFUNCTIONS_H

#include "findFunctionality.h"
#include "linkedLists.h"
#include "stdlib.h"
#include <string.h>
#include <fnmatch.h>

void name(node * HEAD,char expressionParameter[MAXEXPRESSIONLENGTH]);
void type(node * HEAD,const char expressionParameter[MAXEXPRESSIONLENGTH]);
void user(node * HEAD, char expressionParameter[MAXEXPRESSIONLENGTH]);


#endif //FIND_SIMPLIFIED_EXPRESSIONFUNCTIONS_H
