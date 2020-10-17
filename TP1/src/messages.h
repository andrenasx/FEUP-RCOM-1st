#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <termios.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "macros.h"

enum states {START, FLAG_RCV, A_RCV, C_RCV, BCC_OK, STOP};

int sendSET(int fd);
int sendUA(int fd);
int sendDISC(int fd);
void processFrameSU(enum states *state,  unsigned char byte);