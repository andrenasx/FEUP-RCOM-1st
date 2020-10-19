#pragma once
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <termios.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "macros.h"
#include "ll.h"

enum states {START, FLAG_RCV, A_RCV, C_RCV, BCC_OK, STOP};

int sendSET(int fd);
int sendUA(int fd);
int sendDISC(int fd);
void processFrameSU(enum states *state,  unsigned char byte);
int readCommand(int fd);
int readResponse(int fd);

int writeStuffedFrame(int fd, unsigned char *buffer, int length);
int destuffFrame(unsigned char* frame, int length, unsigned char* destuffed_frame);