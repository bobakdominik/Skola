//
// Created by bobak on 12/21/2021.
//

#include <sys/types.h>
//#include <sys/socket.h>//Uncomment if Linux
#include <winsock2.h> //Uncomment if Windows
#include <Ws2tcpip.h> //Uncomment if Windows
//#include <netinet/in.h> //Uncomment if Linux
//#include <netdb.h>//Uncomment if Linux
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdbool.h>
#include <pthread.h>
#include "Common.h"
#include "Map.h"
#include "GUI.h"
#include "CMemLeak.h"

#ifndef BULANCI_CLIENT_H
#define BULANCI_CLIENT_H

void init_Client();

#endif //BULANCI_CLIENT_H
