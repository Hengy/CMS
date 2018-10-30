// messageQueue.cpp : Defines the entry point for the console application.
//

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <time.h>

// linked list node type
typedef struct node {
	long index;
	struct node * next;
} Link;

// globals
Link * head;	// points to first in linked list

// checks if queue is empty
int qIsEmpty(Link * h) {
	if (h->next  == NULL) {
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
	tail->next = new Link;		// new link
	tail->index = i;			// link data
	tail->next->next = NULL;	// new link points to NULL
}

// adds to START
void qAddToStart(Link * h, long i) {

	Link * newNode = new Link;
	newNode->index = i;			// link data
	newNode->next = h->next;	// new link points to old first
	h->next = newNode;			// head points to new node
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

	Link * temp = h->next;		// get first
	h->next = h->next->next;	// head points to second

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
		printf(" %ld\n", p->index);
		p = p->next;
	}
}

int main()
{
	Link * head = NULL;
	head = new Link;
	if (head == NULL) {
		return 1;
	}

	head->next = NULL;

	if (qIsEmpty(head)) {
		printf("\nQueue initialized.\n");
	}

	srand((unsigned)time(NULL));

	int iterations = rand() % 100;

	for (int i = 0; i < iterations; i++) {
		int r = rand() % 10000;
		printf("Pushing %d\n", r);
		qAddToEnd(head, r);
	}

	qPrint(head);

	system("pause");

    return 0;
}

