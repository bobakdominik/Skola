//
// Created by bobak on 1/3/2022.
//
#include "Enums.h"
#ifndef BULANCI_WEAPON_H
#define BULANCI_WEAPON_H

typedef struct Weapon{
    int bullets;

}WEAPON;

WEAPON createWeapon(enum WeaponType type);

#endif //BULANCI_WEAPON_H
