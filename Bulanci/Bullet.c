//
// Created by bobak on 1/3/2022.
//

#include "Bullet.h"
void MoveBullet(BULLET_STRUCT* bullet, enum Direction direction){
    switch (direction) {
        case UP:
            bullet->y = bullet -> y - 6;
            break;
        case DOWN:
            bullet->y = bullet -> y + 6;
            break;
        case LEFT:
            bullet->x = bullet -> x - 6;
            break;
        case RIGHT:
            bullet->x = bullet -> x + 6;
            break;
    }
}