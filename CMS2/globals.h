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
    unsigned char compEncrpyt[4] = {0x01,0x02,0x05,0x08};     // parameters of compression and encryption
    unsigned char checkSum;                     // checksum of message (including header)
} header;

typedef struct RecMsg {
    struct Msg* message;
    struct Header* head;
} RecMsg;

LList * sendMsgList;
Leaf * recMsgTree;

unsigned char thisID = 0x69;

int recSec;          // number of seconds to record
int bitrate;         // bitrate for recording
int sampleRate;      // sample rate for recording

int bufSize;         // buffer size in BYTES

int audioBusy = 0;   // program busy recording or playing

// COMM port
QSerialPort currPort;
int timeout = 8000;

#endif // GLOBALS_H
