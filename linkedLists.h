//
// Created by osboxes on 02/04/23.
//

#ifndef FIND_SIMPLIFIED_LINKEDLISTS_H
#define FIND_SIMPLIFIED_LINKEDLISTS_H

#include "findFunctionality.h"
/**
 *
 * @fn link node
 * @brief create and initialize a node in the LL
 *
 * Attributes:
 * Always inserts new nodes after the HeadPointer
 * initializes The object in the node with the VALUES of the object par
 * last Node next pointer is always NULL
 *
 * @param HEAD Headpointer of the linked list, type node
 * @param objectToBeLinked pass the pointer to the Object which will be written into the node (Values)
 * @return returns 0 if everything is alright, oth. for future use
 */
int llLink(node *HEAD, fileSystemObject * objectToBeLinked);



/**
 * @fn unlink whole LL
 *
 * @brief Destroys a Linked list and frees all the allocated Memory
 * Note: also frees HeadPointer
 * @param HEAD  only the headpointer of type node has to be passed
 * @return returns 0 if everything is alright, oth. for future use
 */
int llDestroyLinkedList(node *HEAD);


/**
 * @fn Print the objects of the linked list for debug purposes
 *
 * @brief Print the name of every object of the linked list
 *        Expanded to accept flags to decide how to
 *        print depending on the ls and print parameters
 * @param HEAD  only the headpointer of type node has to be passed
 * @param flagLs flag which will be set to create ls output
 * @param flagPrint flag whcih will be set to creat print output
 * */
void printLinkedList(node * head,bool flagLs, bool flagPrint);

#endif //FIND_SIMPLIFIED_LINKEDLISTS_H
