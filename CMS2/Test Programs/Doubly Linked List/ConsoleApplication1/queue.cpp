#include "queue.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// ---------------------------------------------------------------------------------
// DOUBLY LINKED LIST
// ---------------------------------------------------------------------------------

// initialize queue head & tail
void qInit(Queue * q, funcPointer fp) {

	// create head and tail
	struct node* newHead = new Link;
	struct node* newTail = new Link;

	// put into linked list
	q->head = newHead;
	q->tail = newTail;

	// set empty
	q->head->next = NULL;
	q->tail->next = NULL;   // always NULL
	q->head->prev = NULL;   // always NULL
	q->tail->prev = NULL;

	// set print function
	q->printFunc = *fp;
}

// checks if queue is empty; returns 1 if empty
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

	// new node at end points to NULL
	newNode->next = NULL;

	if (q->head->next == NULL) {	// nothing in queue
		q->head->next = newNode;	// head points to new node
	}
	else {
		newNode->prev = q->tail->next;	// new node prev points to old last node
		q->tail->next->next = newNode;	// old last node next points to new node
	}

	// add to end
	q->tail->next = newNode;	// tail points to new node

	// copy data
	newNode->data = newData;
 	//memcpy(newNode->data, newData, sizeof(newData));
}

// adds to START
void qPushToStart(Queue * q, void *newData, size_t dataSize) {
	// allocate memory for node
	struct node* newNode = new Link;

	if (q->head->next == NULL) {	// nothing in queue
		// new node is first and only node
		newNode->next = NULL;
		q->tail->next = newNode;
	}
	else {
		// new node at start points to old first node
		newNode->next = q->head->next;
		newNode->next->prev = newNode;	// new second node now points to new node (first node)
	}

	q->head->next = newNode;	// head points to new node

	// add to head
	newNode->prev = NULL;			// first node has no prev

	// copy data
	newNode->data = newData;
	//memcpy(newNode->data, newData, sizeof(newData));
}

// pops from END
Link * qPopEnd(Queue * q) {
	struct node * last = q->tail->next;			// get last node
	q->tail->next = q->tail->next->prev;		// last node is now the second last
	q->tail->next->next = NULL;					// new last node points to NULL
	return last;
}

// pops from START
Link * qPopStart(Queue * q) {
	struct node * start = q->head->next;		// get node
	q->head->next = q->head->next->next;		// second node is now the first node
	q->head->next->prev = NULL;					// new first node previous points to NULL
	return start;
}

// traverse helper
Link * qTraverseHelper(Link * n, int i, int j) {
	if ((i != j) || (n->next != NULL)) {
		return qTraverseHelper(n->next, i++, j);
	}
	return n;
}

// traverse list and return node
Link * qTraverse(Queue * q, int j) {
	struct node * temp = new Link;
	temp = qTraverseHelper(q->head, 1, j);
	return temp;
}

// print node data
void qPrintNode(Link * n, funcPointer fp) {
	(*fp)(n->data);
}

// print queue helper
void qPrintHelper(Link * n, funcPointer fp) {
	qPrintNode(n, (*fp));
	if (n->next != NULL) {
		qPrintHelper(n->next, (*fp));
	}
}

// print queue
void qPrintList(Queue * q) {
	qPrintHelper(q->head->next, q->printFunc);
}
