#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int compressRLE(unsigned char * data, unsigned char * dataOut, int max, int len);

int RLEncode(unsigned char* in, int iInLen, unsigned char* out, int max, unsigned char cEsc);
int RLDecode(unsigned char *in, int iInLen, unsigned char *out, unsigned char cEsc);
unsigned char FindEscC(unsigned char * iBuf, int iBufLength);
