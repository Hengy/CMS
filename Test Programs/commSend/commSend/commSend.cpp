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
	//getPortNames();

	initPort();										// Initialize the port
	char msgOut[BUFSIZE];
	for (int i = 0; i < 10; i++) {
		memset(msgOut, '\0', BUFSIZE);
		sprintf_s(msgOut, BUFSIZE, "Message %d\0\0", i);
		outputToPort(msgOut, strlen(msgOut) + 1);		// Send string to port - include space for '\0' termination
		purgePort();
		Sleep(1000);									// Allow time for signal propagation on cable 
	}
	printf("Done sending\n");
	purgePort();									// Purge the port
	CloseHandle(hCom);								// Closes the handle pointing to the COM port
	system("pause");

    return 0;
}

