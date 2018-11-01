#pragma warning(suppress : 4996)
#pragma warning(disable : 4996)
#define _CRT_SECURE_NO_WARNINGS
#define MESSAGE_SIZE 250
#define MESSAGE_SIZE_MAX 140


#include "Queues.h"
#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <time.h>
#include <string.h>


int GetMessageFromFile(char buf[])
{
	Link * qIndex = new Link;				// Allocate memory for Queue Head
	qIndex->next = NULL;						// When queue empty pointer point to NULL 

	int count = 0;							// sets count to 0
	

	FILE * fp;								// Create file pointer

	fp = fopen("FortuneCookies.txt", "r+" );			//Opens file to read
		
	char c;			
								
	while ((c = fgetc(fp)) != EOF)						// loop to set each quote an Index Number
	{ 
		if (c == '%')								// Here startst to find each double percent and uses them to mark each
		{
			if ((c = fgetc(fp)) == '%')
			{
				qAddToEnd(qIndex, ftell(fp));

				count++;
			}
		}
	}
		
	int r = rand() % count;
	printf("The random number of the count is %d\n", r);			// prints the random number that's generated

	for (int i = 0; i < (count-r); i++)
	{
		qPopEnd(qIndex);											// takes all the quotes off till you get the random quote chosen
	}
	int rIndex = qPopEnd(qIndex)->data;								// gets the index for the quote
	printf("%d\n", rIndex);											// prints the Index Number

	fseek(fp, rIndex, SEEK_SET);									//file pointer points to character at Index

	count = 0;


	char tbuffer[MESSAGE_SIZE];
	memset(tbuffer, 32, MESSAGE_SIZE);								//fills space in quote

	for (int i = 0; i < MESSAGE_SIZE; i++)							// for loop to get 140 characters of quote.
	{
		c = fgetc(fp);												// gets individual character from quote
		if (c == '%') break;										// looks for end of quote
		
		tbuffer[count] = c;												//puts character (in order) into buffer

		count++;													//count buffer posistion increment
		
	}
	memcpy(buf, tbuffer, MESSAGE_SIZE_MAX);

	fclose(fp);														//closes file to free up space
	
	return count;													//returns length of quote
}

int main() {

	int n = 0;
	while ((n < 1) || (n > 10))

	{
		printf("Please input the amount of quotes to display(1-10)  ");				//asks for users input for amount of questions

		scanf("%d", &n);															// gets users input and sets it as vairiable n
	}
	
	

	srand((unsigned)time(NULL));									// uses srand to generate random number with time

	
	int iLen;														//iLen declares quote length
		
	Message * messageQueue = new message;							// Allocate memory for Queue Head
	messageQueue->next = NULL;										// sets next link to NULL



	



	for (int i = 0; i < n; i++) {									// for loop
	
		Message * m = new Message;											// Putting into buff

		m->mBuf = (char *)malloc(sizeof(char) * 140);				//allocates memory for Message Size(up to 140)
		memset(m->mBuf, 32, 140);
		m->priority = rand() % 255;											// set random namber 255
		m->sid = rand() % 9999;												//set random number between 0-9999 for sid
		m->rid = rand() % 9999;												//set random number between 0-9999 for rid
		m->seq = i;															//  uses counting variebale to sequence order of quotes
		m->unknown = NULL;													// unknown variable is set to NULL

		char* pointer = m->mBuf;											//Sends selected quote into buffer
	

		iLen = GetMessageFromFile(m->mBuf);									//gets the set amount of characters from the quote
		printf("Quote length: %d\n", iLen);									// prints the quote length selected

		mqAddToEnd(messageQueue, m);
	}

	mqPrint(messageQueue);													//runs function to print

	system("pause");
}
