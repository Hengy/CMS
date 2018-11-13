#pragma once

#ifndef QUEUE_H
#define QUEUE_H

typedef void(*funcPointer)(void *);

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
	funcPointer printFunc;
} Queue;

// function defintions
void qInit(Queue * q, funcPointer fp);
int qIsEmpty(Queue * q);
void qPushToEnd(Queue * q, void *newData, size_t dataSize);
void qPushToStart(Queue * q, void *newData, size_t dataSize);
Link * qPopEnd(Queue * q);
Link * qPopStart(Queue * q);
Link * qTraverseHelper(Link * n, int i, int j);
Link * qTraverse(Queue * q, int j);
void qPrintNode(Link * n, funcPointer fp);
void qPrintHelper(Link * n, funcPointer fp);
void qPrintList(Queue * n);

#endif // QUEUE_H
