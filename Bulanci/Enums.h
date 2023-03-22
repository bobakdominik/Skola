//
// Created by bobak on 1/3/2022.
//
#include "CMemLeak.h"

#ifndef BULANCI_ENUMS_H
#define BULANCI_ENUMS_H
enum WeaponType{
    PISTOL
};

enum KeyType{
    UNDEF,
    LEFT_ARROW,
    RIGHT_ARROW,
    UP_ARROW,
    DOWN_ARROW,
    SPACEBAR,
    BACKSPACE,
    ESCAPE
};

enum Color{
    YELLOW,
    BROWN,
    GREEN,
    ORANGE
};

enum Direction{
    UP,
    DOWN,
    LEFT,
    RIGHT
};

enum MessageType{
    PLAYER,
    BULLET,
    CANCEL,
    UNKNOWN
};

enum ResponseType{
    ACK,
    WAIT,
    PLAY,
    UPDATE,
    STOP,
    ERR
};

char* WeaponType_toString(enum WeaponType type);
char* Direction_toString(enum Direction type);
char* MessageType_toString(enum MessageType type);
char* ResponseType_toString(enum ResponseType type);
#endif //BULANCI_ENUMS_H
