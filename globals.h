#ifndef GLOBALS_H
#define GLOBALS_H

#include "L2L.h"

extern short iBigBuf[];

// audio message

// audio message struct
typedef struct audioMsg {
    char name[20];      // name of msg
    short * buf;        // audio buffer
    long bufSize = 0;   // size of buffer
    int bitrate;        // bitrate of message
    int samplerate;     // samplerate of message
    int len;            // length of message (in seconds)
} AudioMsg;

LList * sendMsgList;

int recSec;          // number of seconds to record
int bitrate;         // bitrate for recording
int sampleRate;      // sample rate for recording

int bufSize;         // buffer size

int audioBusy = 0;   // program busy recording or playing

// COMM port
unsigned int baudrate = 4800;
unsigned int timeout = 1000;


#endif // GLOBALS_H
