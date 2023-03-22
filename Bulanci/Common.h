//
// Created by bobak on 1/5/2022.
//

#include <ctype.h>
#include <string.h>
#include "Enums.h"
#include "CMemLeak.h"

#ifndef BULANCI_COMMON_H
#define BULANCI_COMMON_H

#define bzero(b,len) (memset((b), '\0', (len)), (void) 0)
#define bcopy(b1,b2,len) (memmove((b2), (b1), (len)), (void) 0)

#define MAX_PLAYERS 4
#define MIN_PLAYERS 2
#define MAX_BULLETS 50
#define DEFAULT_PORT 10025
#define GAME_TIME 600
#define SCREEN_WIDTH   500
#define SCREEN_HEIGHT  500
#define WALL_THICKNESS  10
#define CELL_WIDTH      20
#define BULLET_SIZE      5

int GetPort();
char* GetHostname();
int getIntFromCharPtr(char * arg);

typedef struct clientMessage{
    enum Direction direction;
    enum MessageType type;
}CLIENT_MESSAGE;

#endif //BULANCI_COMMON_H
