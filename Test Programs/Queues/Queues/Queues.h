#/*     Queues.h - Interface of Queue Functionality 
By: Mark WHipple 2018

*/
#pragma once

typedef struct message {								//decares vairiables for struct
	char * mBuf;
	short sid;
	short rid;
	unsigned char priority;
	short seq;
	unsigned char * unknown;
	struct message * next;
} Message;

// linked list node type
typedef struct node {
	long data;
	struct node * next;
} Link;

// function defintions
int qIsEmpty(Link * h);
void qAddToEnd(Link * h, long i);
void qAddToStart(Link * h, long i);
Link * qPopEnd(Link * h);
Link * qPopStart(Link * h);
void qPrint(Link * h);

// message queue function defintions
int mqIsEmpty(Message * m);
void mqAddToEnd(Message * messageQueue, Message * m);
Message * mqPopStart(Message * m);
void mqPrint(Message * m);