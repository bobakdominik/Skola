//
// Created by gajdo on 9. 1. 2022.
//

#include "GUI.h"


void draw_map(Game* game){
    SDL_SetRenderDrawColor(game->renderer, 255, 255, 255, 255);
    SDL_RenderClear(game->renderer);
    draw_walls(game);
    for (int i = 0; i < game->map->numberOfPlayers; ++i) {
        draw_player(game, &game->map->players[i]);
    }
    for (int i = 0; i < game->map->numberOfBullets; ++i) {
        draw_bullet(game, &game->map->bullets[i]);
    }
    SDL_RenderPresent(game->renderer);
    //SDL_Delay(30);
}

int getIntFromInputBox() {

    bool quit = false;
    SDL_Event event;

    char port[10] = "";
    char c[30] = "Zadaj port: "; //"Zadajte port: "

    SDL_Init(SDL_INIT_VIDEO);
    TTF_Init();
    SDL_Window * window = SDL_CreateWindow("Client",
                                           SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 250,
                                           60, 0);
    SDL_Renderer * renderer = SDL_CreateRenderer(window, -1, 0);


    SDL_StartTextInput();
    while (!quit)
    {


        if(event.type == SDL_TEXTINPUT && strlen(port)<5)
        {

            //printf(" %d. pozicia: ",strlen(port));

            strcat(c,event.text.text);
            printf(event.text.text);
            strcat(port,event.text.text);

        }

        if(event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_BACKSPACE && strlen(port)>0)
        {
            c[strlen(c) - 1] = '\0';
            port[strlen(port) - 1] = '\0';
        }

        SDL_RenderClear(renderer);

        TTF_Font* font = TTF_OpenFont("arial.ttf", 25);
        SDL_Color color = { 255, 255, 255 };
        SDL_Surface * surface = TTF_RenderText_Solid(font,c, color);
        SDL_Texture * texture = SDL_CreateTextureFromSurface(renderer, surface);
        int texW = 0;
        int texH = 0;
        SDL_QueryTexture(texture, NULL, NULL, &texW, &texH);
        SDL_Rect dstrect = { 10, 10, texW, texH };


        if(event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_RETURN)
        {
            quit = true;
        }

        //if (strlen(port)==5){
        //    quit = true;
        //}

        SDL_WaitEvent(&event);

        switch (event.type)
        {
            case SDL_QUIT:
                quit = true;
                break;
        }



        SDL_RenderCopy(renderer, texture, NULL, &dstrect);
        SDL_RenderPresent(renderer);
        SDL_DestroyTexture(texture);
        SDL_FreeSurface(surface);
        TTF_CloseFont(font);
    }

    printf("\nPripojili ste sa na port: \n");
    for (int i=0;i < (strlen(port));i++) {
        printf("%c",port[i]);
    }
    SDL_StopTextInput();
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    TTF_Quit();
    SDL_Quit();



    return getIntFromCharPtr(port);
}




void initialize(Game* game) {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("error: failed to initialize SDL: %s\n", SDL_GetError());
        terminate(game, EXIT_FAILURE);
    }

    // create the game window
    game->window = SDL_CreateWindow("Starting",
                                   SDL_WINDOWPOS_UNDEFINED,
                                   SDL_WINDOWPOS_UNDEFINED,
                                   SCREEN_WIDTH,
                                   SCREEN_HEIGHT,
                                   SDL_WINDOW_SHOWN
    );

    if (!game->window) {
        printf("error: failed to open %d x %d window: %s\n", SCREEN_WIDTH, SCREEN_HEIGHT, SDL_GetError());
        terminate(game, EXIT_FAILURE);
    }

    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");
    game->renderer = SDL_CreateRenderer(game->window, -1, SDL_RENDERER_ACCELERATED);

    if (!game->renderer) {
        printf("error: failed to create renderer: %s\n", SDL_GetError());
        terminate(game, EXIT_FAILURE);
    }
}


void terminate(Game* game, int exit_code) {
    if (game->renderer) {
        SDL_DestroyRenderer(game->renderer);
    }
    if (game->window) {
        SDL_DestroyWindow(game->window);
    }
    SDL_Quit();
    exit(exit_code);
}


void update_title(Game* game, char * message) {
    SDL_SetWindowTitle(game->window, message);
}


void sdl_ellipse(SDL_Renderer* r, int x0, int y0, int radiusX, int radiusY)
{
    float pi  = 3.14159265358979323846264338327950288419716939937510f;
    float pih = pi / 2.0f; //half of pi

    //drew  28 lines with   4x4  circle with precision of 150 0ms
    //drew 132 lines with  25x14 circle with precision of 150 0ms
    //drew 152 lines with 100x50 circle with precision of 150 3ms
    const int prec = 27; // precision value; value of 1 will draw a diamond, 27 makes pretty smooth circles.
    float theta = 0;     // angle that will be increased each loop

    //starting point
    int x  = (int)(radiusX * cos((double )theta));//start point
    int y  = (int)(radiusY * sin((double )theta));//start point
    int x1 = x;
    int y1 = y;

    //repeat until theta >= 90;
    float step = pih/(float)prec; // amount to add to theta each time (degrees)
    for(theta=step;  theta <= pih;  theta+=step)//step through only a 90 arc (1 quadrant)
    {
        //get new point location
        x1 = (int)(radiusX * cosf(theta) + 0.5); //new point (+.5 is a quick rounding method)
        y1 = (int)(radiusY * sinf(theta) + 0.5); //new point (+.5 is a quick rounding method)

        //draw line from previous point to new point, ONLY if point incremented
        if( (x != x1) || (y != y1) )//only draw if coordinate changed
        {
            SDL_RenderDrawLine(r, x0 + x, y0 - y,    x0 + x1, y0 - y1 );//quadrant TR
            SDL_RenderDrawLine(r, x0 - x, y0 - y,    x0 - x1, y0 - y1 );//quadrant TL
            SDL_RenderDrawLine(r, x0 - x, y0 + y,    x0 - x1, y0 + y1 );//quadrant BL
            SDL_RenderDrawLine(r, x0 + x, y0 + y,    x0 + x1, y0 + y1 );//quadrant BR
        }
        //save previous points
        x = x1;//save new previous point
        y = y1;//save new previous point
    }
    //arc did not finish because of rounding, so finish the arc
    if(x!=0)
    {
        x=0;
        SDL_RenderDrawLine(r, x0 + x, y0 - y,    x0 + x1, y0 - y1 );//quadrant TR
        SDL_RenderDrawLine(r, x0 - x, y0 - y,    x0 - x1, y0 - y1 );//quadrant TL
        SDL_RenderDrawLine(r, x0 - x, y0 + y,    x0 - x1, y0 + y1 );//quadrant BL
        SDL_RenderDrawLine(r, x0 + x, y0 + y,    x0 + x1, y0 + y1 );//quadrant BR
    }
}



void draw_walls(Game* game) {
    // make the walls gray
    SDL_SetRenderDrawColor(game->renderer, 210, 209, 205, 255);

    SDL_Rect block = {
            .x = 0,
            .y = 0,
            .w = WALL_THICKNESS,
            .h = SCREEN_HEIGHT
    };

    // left wall
    SDL_RenderFillRect(game->renderer, &block);

    // right wall
    block.x = SCREEN_WIDTH - WALL_THICKNESS;
    SDL_RenderFillRect(game->renderer, &block);

    // top wall
    block.x = 0;
    block.w = SCREEN_WIDTH;
    block.h = WALL_THICKNESS;
    SDL_RenderFillRect(game->renderer, &block);

    // bottom wall
    block.y = SCREEN_HEIGHT - WALL_THICKNESS;
    SDL_RenderFillRect(game->renderer, &block);
}

void draw_player(Game* game, PLAYER_STRUCT * player){

    int eyeSize = 3;
    int r,g,b;
    enum Color color = player->id;
    switch (color) {
        case ORANGE:
            r = 250;
            g = 104;
            b = 0;
            break;
        case BROWN:
            r = 210;
            g = 105;
            b = 30;
            break;
        case GREEN:
            r = 0;
            g = 255;
            b = 0;
            break;
        case YELLOW:
            r = 255;
            g = 215;
            b = 0;
            break;
        default:
            r = 0;
            g = 0;
            b = 0;
    }
    SDL_SetRenderDrawColor(game->renderer, r, g, b, 255);
    for (int i = 0; i < CELL_WIDTH / 2; ++i) {
        sdl_ellipse(game->renderer, player->x + 10, player->y + 10, i, i);
    }

    if (!player->isAlive){
        SDL_SetRenderDrawColor(game->renderer, 0, 0, 0, 255);
        SDL_RenderDrawLine(game->renderer, player->x + 5, player->y + 4, player->x + 8, player->y + 7);
        SDL_RenderDrawLine(game->renderer, player->x + 6, player->y + 5, player->x + 9, player->y + 8);
        SDL_RenderDrawLine(game->renderer, player->x + 11, player->y + 4, player->x + 14, player->y + 7);
        SDL_RenderDrawLine(game->renderer, player->x + 12, player->y + 5, player->x + 15, player->y + 8);

        SDL_RenderDrawLine(game->renderer, player->x + 6, player->y + 7, player->x + 9, player->y + 4);
        SDL_RenderDrawLine(game->renderer, player->x + 5, player->y + 8, player->x + 8, player->y + 5);
        SDL_RenderDrawLine(game->renderer, player->x + 12, player->y + 7, player->x + 15, player->y + 4);
        SDL_RenderDrawLine(game->renderer, player->x + 11, player->y + 8, player->x + 14, player->y + 5);
        return;
    }

    //Draw eyes
    int x1;
    int x2;
    int y1;
    int y2;
    switch (player->direction) {
        case UP:
            x1 = player->x + 6;
            x2 = player->x + 13;
            y1 = player->y + 7;
            y2 = player->y + 7;
            break;
        case DOWN:
            x1 = player->x + 7;
            x2 = player->x + 14;
            y1 = player->y + 14;
            y2 = player->y + 14;
            break;
        case LEFT:
            x1 = player->x + 7;
            x2 = player->x + 7;
            y1 = player->y + 7;
            y2 = player->y + 14;
            break;
        case RIGHT:
            x1 = player->x + 13;
            x2 = player->x + 13;
            y1 = player->y + 6;
            y2 = player->y + 13;
            break;
    }
    SDL_SetRenderDrawColor(game->renderer, 0, 96, 255, 255);
    for (int i = 0; i < eyeSize; ++i) {
        sdl_ellipse(game->renderer, x1, y1, i, i);
        sdl_ellipse(game->renderer, x2, y2, i, i);
    }

    //Draw gun
    SDL_SetRenderDrawColor(game->renderer, 0, 0, 0, 255);
    switch (player->direction) {
        case UP:
            SDL_RenderDrawLine(game->renderer, player->x + 18, player->y + 0, player->x + 18, player->y + 10);
            SDL_RenderDrawLine(game->renderer, player->x + 17, player->y + 0, player->x + 17, player->y + 10);
            break;
        case DOWN:
            SDL_RenderDrawLine(game->renderer, player->x + 2, player->y + 10, player->x + 2, player->y + 20);
            SDL_RenderDrawLine(game->renderer, player->x + 3, player->y + 10, player->x + 3, player->y + 20);
            break;
        case LEFT:
            SDL_RenderDrawLine(game->renderer, player->x, player->y + 2, player->x + 10, player->y + 2);
            SDL_RenderDrawLine(game->renderer, player->x, player->y + 3, player->x + 10, player->y + 3);
            break;
        case RIGHT:
            SDL_RenderDrawLine(game->renderer, player->x + 10, player->y + 18, player->x + 20, player->y + 18);
            SDL_RenderDrawLine(game->renderer, player->x +10, player->y + 17, player->x + 20, player->y + 17);
            break;
    }
    SDL_SetRenderDrawColor(game->renderer, 0, 0, 0, 255);
}

void draw_bullet(Game* game, BULLET_STRUCT * bullet){
    SDL_Rect rect = {.x = bullet->x, .y = bullet->y, .w = BULLET_SIZE, .h = BULLET_SIZE};
    SDL_RenderFillRect(game->renderer, &rect);
}

enum KeyType handle_input(Game* game) {
    while (SDL_PollEvent(&game->event)) {
        if (game->event.type == SDL_QUIT || (game->event.type == SDL_KEYDOWN && game->event.key.keysym.sym == SDLK_ESCAPE)) {
            return ESCAPE;
        }
        if (game->event.type == SDL_KEYDOWN && game->event.key.keysym.sym == SDLK_UP) {
            return UP_ARROW;
        }
        else if (game->event.type == SDL_KEYDOWN && game->event.key.keysym.sym == SDLK_DOWN){
            return DOWN_ARROW;
        }
        else if (game->event.type == SDL_KEYDOWN && game->event.key.keysym.sym == SDLK_LEFT){
            return LEFT_ARROW;
        }
        else if (game->event.type == SDL_KEYDOWN && game->event.key.keysym.sym == SDLK_RIGHT){
            return RIGHT_ARROW;
        }else if (game->event.type == SDL_KEYDOWN && game->event.key.keysym.sym == SDLK_SPACE){
            return SPACEBAR;
        }
        return UNDEF;
    }
    return UNDEF;
}

