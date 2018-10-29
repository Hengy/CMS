#ifndef GLOBALS_H
#define GLOBALS_H

extern short iBigBuf[];

int recSec;          // number of seconds to record
int bitrate;         // bitrate for recording
int sampleRate;      // sample rate for recording

int bufSize;         // buffer size

int audioBusy = 0;   // program busy recording or playing

unsigned int baudrate = 9600;

#endif // GLOBALS_H
