#pragma once
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <netdb.h>
#include <strings.h>

int open_socket(const char* ip_address, const int port);
int write_to_socket(const int sockfd, const char* buf, const size_t buf_size);
void read_from_socket(const int sockfd, char* buf, size_t buf_size);