//
// Created by bobak on 12/21/2021.
//
#include <sys/types.h>
//#include <sys/socket.h> //Uncomment this if Linux
//#include <netinet/in.h> //Uncomment this if Linux
#include <winsock2.h> //Uncomment this if Windows
#include <Ws2tcpip.h> //Uncomment this if Windows
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdbool.h>
#include <pthread.h>
#include "Common.h"
#include "Enums.h"
#include "Map.h"
#include "CMemLeak.h"

#ifndef BULANCI_SERVER_H
#define BULANCI_SERVER_H
void init_Server(int port);

#endif //BULANCI_SERVER_H
