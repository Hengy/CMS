/*     Queues.cpp - Implementation of Queue Functionality 
By: Mark WHipple 2018

*/
#include "Queues.h"
#include <stdio.h>
#include <stdlib.h>


//--------------------------------------------------------------
//	Queue
//--------------------------------------------------------------

// checks if queue is empty
int qIsEmpty(Link * h) {
	if (h->next == NULL) {
		return 1;
	}
	return 0;
}
// adds link to END
void qAddToEnd(Link * h, long i) {
	// find tail
	Link * tail = h;
	if (h->next != NULL) {
		while (tail->next != NULL) {
			tail = tail->next;
		}
	}
	// add to end
	tail->next = new Link; // new link
	tail->data = i; // link data
	tail->next->next = NULL; // new link points to NULL
}
// adds to START
void qAddToStart(Link * h, long i) {
	Link * newNode = new Link;
	newNode->data = i; // link data
	newNode->next = h->next; // new link points to old first
	h->next = newNode; // head points to new node
}
// pops from END
Link * qPopEnd(Link * h) {
	// find tail-1
	Link * p = h;
	while (p->next->next != NULL) {
		p = p->next;
	}
	Link * temp = p->next;
	p->next = NULL;
	return temp;
}
// pops from START
Link * qPopStart(Link * h) {
	Link * temp = h->next; // get first
	h->next = h->next->next; // head points to second
	return temp;
}
// print list
void qPrint(Link * h) {
	int count = 0;
	printf("------List START------\n");
	Link * p = h;
	while (p->next != NULL) {
		for (int i = 0; i < count; i++) {
			printf(" ");
		}
		printf(" %ld\n", p->data);
		p = p->next;
	}
}


//--------------------------------------------------------------
//	Message Queue
//--------------------------------------------------------------

// checks if queue is empty
int mqIsEmpty(Message * m) {
	if (m->next == NULL) {
		return 1;
	}
	return 0;
}

// adds link to END
void mqAddToEnd(Message * messageQueue, Message * m) {
	// find tail
	Message * tail = messageQueue;
	while (tail->next != NULL) {
		tail = tail->next;
	}
	// add to end
	tail->next = m; // new link
	m->next = NULL; // new link points to NULL
}

// pops from START
Message * mqPopStart(Message * m) {
	Message * temp = m->next; // get first
	m->next = m->next->next; // head points to second
	return temp;
}

// print list
void mqPrint(Message * m) {						//get first message
	int count = 0;								//set count to 0
	printf("------List START------\n");			// print start
	Message * p = m->next ;							// copy to temp location
	while (p->next != NULL) {					// loop untill find a NULL link (end)
		char* pointer = p->mBuf;

		for (int i = 0; i < 139; i++) {	

			printf("%c", *pointer);
			pointer++;
			
		}

		//prints data needed
		printf("\nPriority %d\n", p->priority);		
		printf("Sender ID %d\n", p->sid);
		printf("Receiver ID %d\n", p->rid);
		printf("Sequence # %d\n\n", p->seq);

		p = p->next;
	}

	char* pointer = p->mBuf;

	for (int i = 0; i < 139; i++) {

		printf("%c", *pointer);
		pointer++;

	}

	//prints last data result 
	printf("\nPriority %d\n", p->priority);
	printf("Sender ID %d\n", p->sid);
	printf("Receiver ID %d\n", p->rid);
	printf("Sequence # %d\n\n", p->seq);
}