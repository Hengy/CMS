#ifndef QUEUE_H
#define QUEUE_H

#pragma once

// message struct
typedef struct message {
    char * mBuf;
    short sid;
    short rid;
    unsigned char priority;
    short seq;
    unsigned char * unknown;
    struct message * next;
} Message;

// generic linked list
typedef struct node {
    void *data;
    struct node * next;
    struct node * prev;
} Link;

//  doubly linked list queue struct
typedef struct queue {
    struct node * head;
    struct node * tail;
} Queue;

// function defintions
int qIsEmpty(Queue * q);
void qPushToEnd(Queue * q, void *newData, size_t dataSize);
void qPushToStart(Queue * q, void *newData, size_t dataSize);
Link * qPopEnd(Queue * q);
Link * qPopStart(Queue * q);
void qPrintHelper(Link * n, void (*fp)(void *));
void qPrint(Link * n, void (*fp)(void *));

#endif // QUEUE_H
