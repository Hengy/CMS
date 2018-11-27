

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "rle.h"

int RLEncode(unsigned char* in, int iInLen,	unsigned char* out, int iOutMax, unsigned char cEsc) {
    int count;

    unsigned char charac;	// repeated character
    unsigned char output[10];	// temp buffer with room for RLE sequence
    out[0] = '\0';		// Set so can use strcat()
    int i = 0;
    int j;
    count = 1;
    while (i < iInLen) {
        //printf("\ni = %d\n\n", i);
        charac = (unsigned char)in[i];		// repeated character
        //printf("charc: %c\n\n", charac);
        while ((in[i] == in[i+1])) {
            //printf("in[%d]: %c\n", i, in[i]);
            count++;
            //printf("count = %d\n", count);
            i++;
        }

        if (count > 3) {
            sprintf((char*)output, "%c%02x%c", cEsc, count, charac);
            strcat((char*)out, (char*)output);
            //printf("out: %s", out);
            count = 1;
        }
        else
        {					//if count is equal or less than 3 compress
            for (j = 0; j < count; j++)
            {
                output[j] = charac;
            }
            output[j] = '\0';
            strcat((char*)out, (char*)output);
            count = 1;
        }
        i++;


    }

    return(strlen((const char*)out)); // Returns length of output
}





int RLDecode(unsigned char *in, int iInLen, unsigned char *out, int iOutMax, unsigned char cEsc)
{
    int i = 0, j = 0, repeats = 0;
    unsigned char HEX[3];	// String rep of HEX number of repeats
    char charac[2];		// repeated character
    out[0] = '\0';		// To use strcat()
    // Build the out buffer using in buffer
    for (i = 0; i < iInLen; i++) {
        //printf("i = %d", i);
        if (in[i] != cEsc) {  // No RLE sequence (no repeats)
            charac[0] = in[i]; charac[1] = '\0';
            strcat((char*)out, charac);
        }
        else {		// RLE sequence (repeats encountered)
            HEX[0] = in[++i];
            HEX[1] = in[++i];
            HEX[2] = '\0'; // repeats string
            charac[0] = in[++i];
            charac[1] = '\0';	// repeated char
            repeats = (int)strtol((char*)HEX, NULL, 16); // repeats as num
            for(j=0;j<repeats;j++) strcat((char*)out, charac);
        }
        if (strlen((char*)out) > iOutMax) { printf("OVERFLOW"); return 0; }
    }
    return(strlen((char*)out));  // Return length of output buffer
}

unsigned char FindEscC(unsigned char * iBuf, int iBufLength)
{
    unsigned char Esc= '~';
    for (int i = 0; i < iBufLength; i++)
    {
        if ((Esc == iBuf[i]) && (Esc !=32))    // If the escape character is in the array and escape chartater is  not space.
        {
            Esc--;								// try next escape charater
            i = 0;								// reset count to start at begining of array.

        }


    }

    if (Esc == 32) return('~');					// after trying every escape charter fails. use ~ by defult
    return (Esc);								// Else return the escape character not found in array.


}
