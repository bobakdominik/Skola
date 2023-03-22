//
// Created by bobak on 1/3/2022.
//

#include "Player.h"

void MovePlayer(PLAYER_STRUCT* player, enum Direction direction, int maxX, int maxY, int offset){
    if(player->direction == direction) {
        switch (direction) {
            case UP:
                player->y = abs(((player->y - 4) % maxY));
                if (player->y < offset)
                    player->y = maxY - (CELL_WIDTH + offset);
                break;
            case DOWN:
                player->y = abs(((player->y + 4) % maxY));
                if (player->y > maxY - (CELL_WIDTH + offset))
                    player->y = offset;
                break;
            case LEFT:
                player->x = abs(((player->x - 4) % maxX));
                if (player->x < offset)
                    player->x = maxX - (CELL_WIDTH + offset);
                break;
            case RIGHT:
                player->x = abs(((player->x + 4) % maxX));
                if (player->x > maxX - (CELL_WIDTH + offset))
                    player->x = offset;
                break;
        }
    } else{
        player->direction = direction;
    }
}