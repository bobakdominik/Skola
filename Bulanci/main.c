//
// Created by bobak on 12/21/2021.
//
#include <stdlib.h>
#include "Client.h"
#include "Server.h"

void * thread1(void* data){
    int port = DEFAULT_PORT;
    init_Server(port);
}

void * thread2(void* data) {
    sleep(2);
    init_Client();
}

int main(int argc, char *argv[]){
    srand(time(NULL));

    //Comment this if Linux
    static WSADATA wsaData;
    int wsaerr = WSAStartup(MAKEWORD(2, 0), &wsaData);
    if (wsaerr)
        exit(1);

    //TODO odkomentovat
    /*
    int port;
    if(argc > 1){
        printf("main: Starting server\n");
        port = getIntFromCharPtr(argv[1]);
        if(port > 0){
            init_Server(port);
        }else{
            printf("main: Port is in bad format\n");
        }
    }else{
        printf("main: Starting client\n");
        init_Client();
    }
    */

    //TODO vyhodit

    pthread_t t1, t2;
    pthread_create(&t1, NULL, &thread1, NULL);
    pthread_create(&t2, NULL, &thread2, NULL);

    pthread_join(t1, NULL);
    pthread_join(t2, NULL);


    WSACleanup(); //Comment this if Linux

    return 0;
}

