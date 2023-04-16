//
// Created by osboxes on 24/03/23.
//

#include "expressionFunctions.h"

//fuctions which filter the output of the print ll function according to the parameters

//no function for LS is necessary as it will only function as a Flag when printing the list
//no function for print is necessary as it will only function as a Flag when printing the list
//TODO expand print ll function to behave differently on ls and print flag

void name(node * HEAD,char expressionParameter[MAXEXPRESSIONLENGTH]){

if(HEAD == NULL){
    return;
}
    node *prevNode = HEAD;
    node *workingNode = HEAD->next;
    while (workingNode != NULL) {

        if(0 != fnmatch(expressionParameter, workingNode->object.objectName, FNM_NOESCAPE)){
        prevNode->next = workingNode->next;
            free(workingNode);

            workingNode = prevNode->next;
        }else{
            prevNode = workingNode;
            workingNode = workingNode->next;
        }
    }//end while

}


void type(node * HEAD,const char expressionParameter[MAXEXPRESSIONLENGTH]){
    if(HEAD == NULL){
        return;
    }

    //determining type for comparision with expression Parameter
    int comparisonValue;
    switch (expressionParameter[0]) {
        case 'b':
            comparisonValue = T_BLOCK_DEVICE;
            break;
        case 'c':
            comparisonValue = T_CHARACTER_DEVICE;
            break;
        case 'd':
            comparisonValue = T_DIRECTORY;
            break;
        case 'p':
            comparisonValue = T_NAMED_PIPE;
            break;
        case 'f':
            comparisonValue = T_REGULAR_FILE;
            break;
        case 'l':
            comparisonValue = T_SYMBOLIC_LINK;
            break;
        case 's':
            comparisonValue = T_SOCKET;
            break;

    }

    node *prevNode = HEAD;
    node *workingNode = HEAD->next;
    while (workingNode != NULL) {

        if(workingNode->object.objectType != comparisonValue){
            prevNode->next = workingNode->next;
            free(workingNode);

            workingNode = prevNode->next;
        }else{
            prevNode = workingNode;
            workingNode = workingNode->next;
        }
    }//end while

}



void user(node * HEAD, char expressionParameter[MAXEXPRESSIONLENGTH]){

    if(HEAD == NULL || HEAD->next == NULL){

        return;
    }

    node *prevNode = HEAD;
    node *workingNode = HEAD->next;
    __UID_T_TYPE comparisonValueUID;
    char *endPtr;
    while (workingNode != NULL) {
        comparisonValueUID = strtoul(&expressionParameter[0],&endPtr,10);
        if(0 != strcmp(workingNode->object.owner, expressionParameter) && comparisonValueUID != workingNode->object.ownerID){
            prevNode->next = workingNode->next;
            free(workingNode);

            workingNode = prevNode->next;
        }else{
            prevNode = workingNode;
            workingNode = workingNode->next;
        }
    }//end while

}