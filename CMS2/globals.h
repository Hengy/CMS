#ifndef GLOBALS_H
#define GLOBALS_H

#include "L2L.h"
#include "bst.h"
#include <QList>
#include <QString>
#include <QSerialPort>

#define STD_BAUDRATE    4800

extern short playRecBuf[];

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

// sent message header structure
typedef struct Header {
    unsigned char priority; // priority of message
    unsigned char type;     // type of message: (0) audio (1) text
    unsigned char lSignature[4] = {0xDE,0xAD,0xBE,0xEF};      // must be 0xDEADBEEF
    unsigned char recAddr;                      // receiver address; address of the receiving computer
    unsigned char sendAddr;                     // sender address; address of the sending computer
    unsigned long dataLen;                      // length of data in BYTES
    unsigned char sampleRate = 8;
    unsigned char compEncrpyt[6] = {0x01,0x01,0x01,0x01,0x01,0x01};     // parameters of compression and encryption
    unsigned int timestamp = 0;
    unsigned char checkSum;                     // checksum of message (including header)
} header;

typedef struct RecMsg {
    struct Header* head;
    struct Msg* message;
} RecMsg;

LList * sendMsgList;
Leaf * recMsgTreePri;
Leaf * recMsgTreeTime;

unsigned char thisID = 0x69;

int recSec;          // number of seconds to record
int bitrate;         // bitrate for recording
int sampleRate;      // sample rate for recording

int bufSize;         // buffer size in BYTES

// COMM port
QSerialPort currPort;
int timeout = 8000;

int treeCount = 0;

QTimer *timer;

unsigned char BERarray[20] = {0x5A, 0xA5, 0x55, 0xAA, 0x11,
                             0x5A, 0xA5, 0x55, 0xAA, 0x11,
                             0x5A, 0xA5, 0x55, 0xAA, 0x11,
                             0x5A, 0xA5, 0x55, 0xAA, 0x11};

int sortOrder = 1;  // (0) time recieved (1) priority

unsigned long startTime = 0;

#endif // GLOBALS_H
