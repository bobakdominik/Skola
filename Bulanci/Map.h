//
// Created by bobak on 1/5/2022.
//
#include "Player.h"
#include "Bullet.h"
#include "Common.h"
#include "CMemLeak.h"

#ifndef BULANCI_MAP_H
#define BULANCI_MAP_H

#define MAP_SIZE 10

typedef struct map{
    PLAYER_STRUCT players[MAX_PLAYERS];
    BULLET_STRUCT bullets[MAX_BULLETS];
    int numberOfPlayers;
    int numberOfBullets;
    const int mapY;
    const int mapX;
    enum KeyType lastKey;
}MAP;


#endif //BULANCI_MAP_H
