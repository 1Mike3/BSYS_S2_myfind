//
// Created by osboxes on 02/04/23.
//

#include "linkedLists.h"
#include <stdlib.h>
#include <stdio.h>
#include "findFunctionality.h"

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

    //condition to abort if the list is already empty
    if(HEAD->next == NULL){
        free(HEAD);
        return 1;
    }

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

void printLinkedList(node * head){
    node * tempNode = head->next;
    int index = 0;
    printf("###PRINT LINKED LISTS FUNCTION: \n");

    while(tempNode != NULL){
        //printf("Index: [%i], Object: \t %s\n", index, tempNode->object.objectName);
        printObject(&tempNode->object);
        tempNode = tempNode->next;
        index++;
    }
}

//because it is a singely linked list removing a node just with the address would be hard
//so removing node will be made custom in the other functions