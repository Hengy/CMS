#include "queue.h"
#include <stdio.h>
#include <stdlib.h>

// ---------------------------------------------------------------------------------
// DOUBLY LINKED LIST
// ---------------------------------------------------------------------------------

// initialize queue head & tail
void qInit(Queue * q) {
    q->head->next = NULL;
    q->tail->next = NULL;   // always NULL
    q->head->prev = NULL;   // always NULL
    q->tail->prev = NULL;
}

// checks if queue is empty
int qIsEmpty(Queue * q) {
    if (q->head->next == NULL) {
        return 1;
    }
    return 0;
}

// adds link to END
void qPushToEnd(Queue * q, void *newData, size_t dataSize) {
    // allocate memory for node
    struct node* newNode = new Link;

    // add to end
    newNode->next = NULL;
    q->tail->next = newNode;

    // copy data
    for (int i = 0; i < dataSize; i++) {
        *((char *)newNode->data + i) = *((char *)newData + i);
    }
}

// adds to START
void qPushToStart(Queue * q, void *newData, size_t dataSize) {
    // allocate memory for node
    struct node* newNode = new Link;

    // copy data
    for (int i = 0; i < dataSize; i++) {
        *((char *)newNode->data + i) = *((char *)newData + i);
    }

    // add to head
    newNode->next = q->head->next;
    q->head->next = newNode;
}

// pops from END
Link * qPopEnd(Queue * q) {
    struct node * temp = q->tail->next; // get last node
    q->tail->next = q->tail->prev;      // last node is now the second last
    q->tail->prev->next = NULL;
    return temp;
}

// pops from START
Link * qPopStart(Queue * q) {
    struct node * temp = q->head->next; // get node
    q->head->next = q->head->next->next;      // node is now the first node
    q->head->next->prev = NULL;
    return temp;
}

// traverse helper
Link * qTraverseHelper(Link * n, int i, int j) {
    if ((i != j) || (n->next != NULL)) {
        return qTraverseHelper(n->next, i++, j);
    }
    return n->next;
}

// traverse list and return node
Link * qTraverse(Queue * q, int j) {
    struct node * temp = new Link;
    int i = 0;
    temp = qTraverseHelper(q->head, i, j);
}

// print node data
void qPrintNode(Link * n, void (*fp)(void *)) {
    (*fp)(n->data);
}

// print queue helper
void qPrintHelper(Link * n, void (*fp)(void *)) {
    if (n->next != NULL) {
        qPrintHelper(n->next, (*fp));
    }
}

// print queue
void qPrintList(Queue * q, void (*fp)(void *)) {
    qPrintHelper(q->head->next, (*fp));
}
