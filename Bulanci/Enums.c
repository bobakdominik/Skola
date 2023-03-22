//
// Created by bobak on 1/3/2022.
//

#include "Enums.h"

char* WeaponType_toString(enum WeaponType type){
    switch (type) {
        case PISTOL:
            return "PISTOL";
        default:
            return "UNKNOWN WEAPON TYPE";
    }
}
char* Direction_toString(enum Direction type){
    switch (type) {
        case UP:
            return "UP";
        case DOWN:
            return "DOWN";
        case LEFT:
            return "LEFT";
        case RIGHT:
            return "RIGHT";
        default:
            return "UNKNOWN DIRECTION TYPE";
    }
}
char* MessageType_toString(enum MessageType type){
    switch (type) {
        case BULLET:
            return "BULLET";
        case PLAYER:
            return "PLAYER";
        default:
            return "UNKNOWN MESSAGE TYPE";
    }
}

char* ResponseType_toString(enum ResponseType type){
    switch (type) {
        case ACK:
            return "ACK";
        case WAIT:
            return "WAIT";
        case PLAY:
            return "PLAY";
        case UPDATE:
            return "UPDATE";
        case STOP:
            return "STOP";
        case ERR:
            return "ERR";
        default:
            return "UNKNOWN RESPONSE TYPE";
    }
}