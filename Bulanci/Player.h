//
// Created by bobak on 1/3/2022.
//
#include <stdbool.h>
#include <stdlib.h>
#include "Enums.h"
#include "Common.h"
#include "CMemLeak.h"

#ifndef BULANCI_PLAYER_H
#define BULANCI_PLAYER_H
#define MAX_LIVES 5

typedef struct player{
    int x;
    int y;
    int lives;
    bool isAlive;
    enum Direction direction;
    int hits;
    int id;
}PLAYER_STRUCT;

void MovePlayer(PLAYER_STRUCT* player, enum Direction direction, int maxX, int maxY, int offset);
#endif //BULANCI_PLAYER_H
