//
// Created by gajdo on 9. 1. 2022.
//
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include "SDL.h"
#include "SDL_ttf.h"
#include <ctype.h>
#include <string.h>
#include <pthread.h>

#include "Player.h"
#include "Bullet.h"
#include "Common.h"
#include "Map.h"
#include "CMemLeak.h"

#ifndef BULANCI_GUI_H
#define BULANCI_GUI_H

typedef enum Game_State {
    NOT_PLAYING = 0,
    PLAYING = 1,
    PAUSED = 2,
    GAME_OVER = 3
} Game_State;

typedef struct {
    SDL_Renderer *renderer;
    SDL_Window *window;
    int running;
    Game_State state;
    MAP* map;
    SDL_Event event;
} Game;



void draw_map(Game* game);
void update_title(Game* game,char * message);
int getIntFromInputBox();
void initialize(Game* game);
void terminate(Game* game, int exit_code);
void sdl_ellipse(SDL_Renderer* r, int x0, int y0, int radiusX, int radiusY);
enum KeyType handle_input(Game* game);
void draw_player(Game* game, PLAYER_STRUCT * player);
void draw_bullet(Game* game, BULLET_STRUCT * bullet);
void draw_walls(Game* game);

#endif //BULANCI_GUI_H
