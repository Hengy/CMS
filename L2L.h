// DOUBLE LINKED LIST (L2L)

#pragma once

#ifndef L2L_H
#define L2L_H

typedef void(*funcPointer)(void *);

// generic linked list
typedef struct node {
    void *data;
    struct node * next;
    struct node * prev;
} Link;

//  doubly linked list struct
typedef struct lList {
    struct node * head;
    struct node * tail;
    funcPointer printFunc;
} LList;

// function defintions
void lInit(LList * l);
int lIsEmpty(LList * l);
void lPushToEnd(LList * l, void *newData, size_t dataSize);
void lPushToStart(LList * l, void *newData, size_t dataSize);
Link * lPopEnd(LList * l);
Link * lPopStart(LList * l);
Link * lTraverseHelper(Link * n, int i, int j);
Link * lTraverse(LList * l, int j);

#endif // L2L_H
