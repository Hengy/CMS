// commSend.cpp : Defines the entry point for the console application.
//

#include <Windows.h>    // Includes the functions for serial communication via RS232
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "RS232Comm.h"

#define BUFSIZE 140

extern HANDLE hCom;

int main()
{
	initPort();										// Initialize the port
	char msgIn[BUFSIZE];
	//memset(msgIn, '\0', BUFSIZE);
	//for (int i = 0; i < 10; i++) {
	//	inputFromPort(msgIn, BUFSIZE);
	//	printf("\nMessage Received: %s\n\n", msgIn);	// Display message from port
	//	memset(msgIn, '\0', BUFSIZE);
	//	Sleep(900);
	//}

	int count = 100;

	int recvBytes = inputFromPort(msgIn, BUFSIZE);
	while (--count > 0) {
		if (recvBytes > 0) {
			printf("\nMessage Received: %s\n\n", msgIn);	// Display message from port
			memset(msgIn, '\0', BUFSIZE);
		}
		purgePort();
		Sleep(100);
		recvBytes = inputFromPort(msgIn, BUFSIZE);
	}

	printf("Done receiving\n");
	purgePort();									// Purge the port
	CloseHandle(hCom);								// Closes the handle pointing to the COM port
	system("pause");

	return 0;
}

