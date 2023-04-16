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

///unfinished condition
void type(node * HEAD, char expressionParameter[MAXEXPRESSIONLENGTH]){
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

///unfinished condition
void user(node * HEAD, char expressionParameter[MAXEXPRESSIONLENGTH]){
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