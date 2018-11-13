#ifndef GLOBALS_H
#define GLOBALS_H

#include "L2L.h"
#include <QList>
#include <QString>
#include <QSerialPort>

#define STD_BAUDRATE    4800

extern short playRecBuf[];

// audio message

// audio message struct
typedef struct Msg {
    unsigned char type; // type of message: (0) audio (1) text
    char name[20];      // name of msg
    void * buf;         // msg buffer
    long bufSize = 0;   // size of buffer
    int bitrate;        // bitrate of message
    int samplerate;     // samplerate of message
    int len;            // length of message (in seconds)
} Msg;

LList * sendMsgList;

int recSec;          // number of seconds to record
int bitrate;         // bitrate for recording
int sampleRate;      // sample rate for recording

int bufSize;         // buffer size

int audioBusy = 0;   // program busy recording or playing

// COMM port
QSerialPort currPort;
int timeout = 2000;

#endif // GLOBALS_H
