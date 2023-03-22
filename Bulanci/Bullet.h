//
// Created by bobak on 1/3/2022.
//
#include "Enums.h"
#include "CMemLeak.h"

#ifndef BULANCI_BULLET_H
#define BULANCI_BULLET_H
typedef struct Bullet{
    int x;
    int y;
    enum Direction direction;
    int shooterId;
}BULLET_STRUCT;

void MoveBullet(BULLET_STRUCT* bullet, enum Direction direction);
#endif //BULANCI_BULLET_H
