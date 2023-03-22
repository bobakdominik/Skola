//
// Created by bobak on 1/5/2022.
//

#include "Common.h"
#include "GUI.h"

//TODO
int GetPort(){
    return getIntFromInputBox();
}

//TODO
char* GetHostname(){
    return "localhost";
}

int getIntFromCharPtr(char * arg){
    int port = 0;
    for (int i = 0; i < strlen(arg); ++i) {
        if (!isdigit(arg[i])){
            return -1;
        }
        int num = arg[i] - '0';
        port = port * 10 + num;
    }
    return port;
}