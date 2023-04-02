//
// Created by osboxes on 02/04/23.
//

#include "linkedLists.h"
#include "stdlib.h"

int llLink(node *HEAD, fileSystemObject * objectToBeLinked){

    /// create node Instance
    node *insertedNode = calloc(1, sizeof(node));
    insertedNode->object = *objectToBeLinked;

    /// case not the first element
    if(HEAD->next != NULL){
        insertedNode->next = HEAD->next;
        HEAD->next = insertedNode;
    }

    /// case first Element to be linked
    if(HEAD->next == NULL){
        HEAD->next = insertedNode;
        insertedNode->next = NULL;
    }


    return 0;
}


int llDestroyLinkedList(node *HEAD) {
    node *tempNode;
    while (HEAD->next->next != NULL) {
        tempNode = HEAD->next->next;
        free(HEAD->next);
        HEAD->next = tempNode;
    }
    free(HEAD->next);
    free(HEAD);
    return 0;
}

