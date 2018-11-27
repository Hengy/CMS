#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int RLEncode(unsigned char* in, int iInLen, unsigned char* out, int iOutMax, unsigned char cEsc);
int RLDecode(unsigned char *in, int iInLen, unsigned char *out, int iOutMax, unsigned char cEsc);
unsigned char FindEscC(unsigned char * iBuf, int iBufLength);
