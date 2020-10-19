#pragma once
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <termios.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "messages.h"
#include "alarm.h"

#define BAUDRATE B38400
#define MODEMDEVICE "/dev/ttyS1"
#define _POSIX_SOURCE 1 /* POSIX compliant source */
#define TRANSMITTER 0
#define RECEIVER 1
#define MAX_TRANSMISSIONS 3

typedef struct 
{
    int fileDescriptor;
    int status; //TRANSMITTER/RECEIVER
} applicationLayer;

typedef struct 
{
    char port[20]; // /dev/ttySx
    int baudRate;  //transmission speed
    int flag; //TRANSMITTER/RECEIVER
    unsigned int sequenceNumber; //trama sequence
    unsigned int timeout;
    unsigned int numTransmissions; //atempt number in case of failure
    unsigned int alarm;
    char frame[256]; //trama
} linkLayer;

extern linkLayer linklayer;

void setDataLinkLayer(int port, int flag);

//ll functions
int llopen(int port, int flag);
int llclose(int fd);


int openSerial();