#include "L2L.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <QDebug>

// ---------------------------------------------------------------------------------
// DOUBLY LINKED LIST
// ---------------------------------------------------------------------------------

// initialize list head & tail
void lInit(LList * l) {

    // create head and tail
    struct node* newHead = new Link;
    struct node* newTail = new Link;

    // put into linked list
    l->head = newHead;
    l->tail = newTail;

    // set empty
    l->head->next = NULL;
    l->tail->next = NULL;   // always NULL
    l->head->prev = NULL;   // always NULL
    l->tail->prev = NULL;
}

// checks if list is empty; returns 1 if empty
int lIsEmpty(LList * l) {
    if (l->head->next == NULL) {
        return 1;
    }
    return 0;
}

// adds link to END
void lPushToEnd(LList * l, void *newData, size_t dataSize) {
    // allocate memory for node
    struct node* newNode = new Link;

    // new node at end points to NULL
    newNode->next = NULL;

    if (l->head->next == NULL) {	// nothing in queue
        l->head->next = newNode;	// head points to new node
    }
    else {
        newNode->prev = l->tail->next;	// new node prev points to old last node
        l->tail->next->next = newNode;	// old last node next points to new node
    }

    // add to end
    l->tail->next = newNode;	// tail points to new node

    // copy data
    newNode->data = newData;
    //memcpy(newNode->data, newData, sizeof(newData));
}

// adds to START
void lPushToStart(LList * l, void *newData, size_t dataSize) {
    // allocate memory for node
    struct node* newNode = new Link;

    if (l->head->next == NULL) {	// nothing in lueue
        // new node is first and only node
        newNode->next = NULL;
        l->tail->next = newNode;
    }
    else {
        // new node at start points to old first node
        newNode->next = l->head->next;
        newNode->next->prev = newNode;	// new second node now points to new node (first node)
    }

    l->head->next = newNode;	// head points to new node

    // add to head
    newNode->prev = NULL;			// first node has no prev

    // copy data
    newNode->data = newData;
    //memcpy(newNode->data, newData, sizeof(newData));
}

// pops from END
Link * lPopEnd(LList * l) {
    struct node * last = l->tail->next;			// get last node
    l->tail->next = l->tail->next->prev;		// last node is now the second last
    l->tail->next->next = NULL;					// new last node points to NULL
    return last;
}

// pops from START
Link * lPopStart(LList * l) {
    struct node * start = l->head->next;		// get node
    l->head->next = l->head->next->next;		// second node is now the first node
    l->head->next->prev = NULL;					// new first node previous points to NULL
    return start;
}

// traverse helper
Link * lTraverseHelper(Link * n, int i, int j) {
    if ((i != j) && (n->next != NULL)) {
        return lTraverseHelper(n->next, i++, j);
    }
    return n;
}

// traverse list and return node
Link * lTraverse(LList * l, int j) {
    struct node * temp = new Link;
    temp = lTraverseHelper(l->head, 1, j);
    return temp;
}
