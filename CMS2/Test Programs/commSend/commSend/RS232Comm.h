#pragma once

// Prototype the functions to be used

void initPort(); 
void purgePort();
void getPortNames();
void outputToPort(LPCVOID buf, DWORD szBuf);
int inputFromPort(LPVOID buf, DWORD szBuf);

// Sub functions
void createPortFile();
static int SetComParms();