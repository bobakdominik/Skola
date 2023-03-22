//
// Created by bobak on 12/21/2021.
//

#include "Server.h"

typedef struct bindingData BINDING_DATA;
typedef struct socketData SOCKET_DATA;
typedef struct gameData GAME_DATA;
typedef struct recipientData RECIPIENT_DATA;
int CreateBinding(SOCKET_DATA * socketData, int port);
void StartRequests(BINDING_DATA * bindingData);
int StartGame(SOCKET_DATA * socketData);
void MoveBullets(MAP* map);
void * Thread_ConnectPlayers(void * data);
void* Thread_ServerReceive(void* data);
void* Thread_ServerSend(void* data);

struct bindingData{
    SOCKET_DATA * socketData;
    bool waitingForConnection;
    bool gameStarted;

    pthread_mutex_t * bindingMutex;
    pthread_cond_t * playerConnected_c;
    pthread_cond_t * connectPlayers_c;
};

struct socketData{
    int sockfd, cli_sockfd[MAX_PLAYERS];
    socklen_t cli_len[MAX_PLAYERS];
    bool validSockets[MAX_PLAYERS];
    struct sockaddr_in serv_addr, cli_addr[MAX_PLAYERS];
    int connectedClients;
};

struct gameData{
    SOCKET_DATA * socketData;
    MAP* map;
    bool isRunning;

    pthread_mutex_t * gameMutex;
    pthread_cond_t * startGame_c;
};

struct recipientData{
    GAME_DATA * gameData;
    int id;
};

void init_Server(int port){
    pthread_t connectPlayers_t;
    pthread_mutex_t bindingMutex;
    pthread_cond_t playerConnected_c, connectPlayers_c;

    pthread_mutex_init(&bindingMutex,NULL);
    pthread_cond_init(&playerConnected_c, NULL);
    pthread_cond_init(&connectPlayers_c, NULL);
    SOCKET_DATA socketData;
    CreateBinding(&socketData, port);
    BINDING_DATA bindingData = {.socketData = &socketData,
                               .waitingForConnection = false,
                               .gameStarted = false,
                               .bindingMutex = &bindingMutex,
                               .connectPlayers_c = &connectPlayers_c,
                               .playerConnected_c = &playerConnected_c};


    while (1){
        bindingData.gameStarted = false;
        bindingData.waitingForConnection = false;
        socketData.connectedClients = 0;
        printf("init_Server: Server starting game...\n");
        sleep(1);
        pthread_create(&connectPlayers_t, NULL, &Thread_ConnectPlayers, &bindingData);
        StartRequests(&bindingData);
        pthread_cancel(connectPlayers_t);
        StartGame(&socketData);
        printf("init_Server: Game ended\n\n");
        sleep(1);
    }

    //TODO
    /*
    pthread_cond_destroy(&connectPlayers_c);
    pthread_cond_destroy(&playerConnected_c);
    pthread_mutex_destroy(&bindingMutex);
     */
}

int CreateBinding(SOCKET_DATA * socketData, int port){
    socketData->connectedClients = 0;
    socketData->sockfd = (int)socket(AF_INET, SOCK_STREAM, 0);
    if (socketData->sockfd < 0){
        perror("CreateBinding:Error creating socket\n");
    }

    bzero((char*)&socketData->serv_addr, sizeof(socketData->serv_addr));
    (socketData->serv_addr).sin_family = AF_INET;
    (socketData->serv_addr).sin_addr.s_addr = INADDR_ANY;
    (socketData->serv_addr).sin_port = htons(port);

    if (bind(socketData->sockfd, (struct sockaddr*)&socketData->serv_addr, sizeof(socketData->serv_addr)) < 0)
    {
        perror("CreateBinding: Error binding socket address\n");
        return 2;
    }

    return socketData->sockfd;
}

//TODO
void SetupPlayers(MAP * map){
    for (int i = 0; i < map->numberOfPlayers; ++i) {
        map->players[i].lives = MAX_LIVES;
        map->players[i].isAlive = true;
        map->players[i].direction = rand() % 4;
        map->players[i].x = rand() % (map->mapX - CELL_WIDTH - WALL_THICKNESS + 1) + CELL_WIDTH + WALL_THICKNESS;
        map->players[i].y = rand() % (map->mapX - CELL_WIDTH - WALL_THICKNESS + 1) + CELL_WIDTH + WALL_THICKNESS;
        map->players[i].hits = 0;
        map->players[i].id = i;
    }
}

int StartGame(SOCKET_DATA * socketData){
    int numberOfPlayers = socketData->connectedClients;
    pthread_t sender_t, receiver_t[numberOfPlayers];
    pthread_mutex_t gameMutex;
    pthread_cond_t starGame_c;

    pthread_mutex_init(&gameMutex, NULL);
    pthread_cond_init(&starGame_c, NULL);

    MAP map = {.numberOfBullets = 0, .numberOfPlayers = numberOfPlayers, .mapX = SCREEN_WIDTH, .mapY = SCREEN_HEIGHT};
    SetupPlayers(&map);
    GAME_DATA gameData = {.socketData = socketData, .map = &map, .isRunning = false, .gameMutex = &gameMutex, .startGame_c = &starGame_c};
    RECIPIENT_DATA recipientData[numberOfPlayers];

    pthread_create(&sender_t, NULL, &Thread_ServerSend, &gameData);
    for (int i = 0; i < numberOfPlayers; ++i) {
        recipientData[i].gameData = &gameData;
        recipientData[i].id = i;
        socketData->validSockets[i] = true;
        pthread_create(&receiver_t[i], NULL, &Thread_ServerReceive, &recipientData[i]);
    }

    pthread_join(sender_t, NULL);
    for (int i = 0; i < numberOfPlayers; ++i) {
        pthread_join(receiver_t[i], NULL);
    }
    pthread_cond_destroy(&starGame_c);
    pthread_mutex_destroy(&gameMutex);

    return 0;

}

void* Thread_ServerSend(void* data){
    GAME_DATA * gameData = data;
    MAP * map = gameData->map;
    SOCKET_DATA * socketData = gameData->socketData;
    int players = socketData->connectedClients;
    int gameTime = GAME_TIME;

    int turn = 0;
    long n;
    printf("Thread_ServerSend: Starts\n");
    pthread_mutex_lock(gameData->gameMutex);
    gameData->isRunning = true;
    pthread_mutex_unlock(gameData->gameMutex);
    pthread_cond_broadcast(gameData->startGame_c);
    while (gameTime > 0){
        pthread_mutex_lock(gameData->gameMutex);
        printf("Thread_ServerSend: Sending data to clients.\n");
        int numberOfInvalidSockets = 0;
        for (int i = 0; i < players; ++i) {
            if(!socketData->validSockets[i]){
                numberOfInvalidSockets++;
                continue;
            }
            printf("Thread_ServerSend: Client %d\n", i);
            enum ResponseType respond = PLAY;
            //n = write(socketData->cli_sockfd[i], &respond, sizeof(respond));//TODO
            n = send(socketData->cli_sockfd[i], (const char*)&respond, sizeof(respond), 0);
            if (n < 0){
                perror("Thread_ServerSend: Error sending PLAY response to client\n");
                continue;
            }
            //n = write(socketData->cli_sockfd[i], map, sizeof(*map)); // TODO
            n = send(socketData->cli_sockfd[i], (const char*)map, sizeof(*map),0);
            if (n < 0){
                perror("Thread_ServerSend: Error sending map to client\n");
                continue;
            }
            //n = write(socketData->cli_sockfd[i], map->players, sizeof(*map->players));//TODO
            n = send(socketData->cli_sockfd[i], (const char*)map->players, sizeof(*map->players), 0);
            if (n < 0){
                perror("Thread_ServerSend: Error sending players to client\n");
                continue;
            }
            //n = write(socketData->cli_sockfd[i], map->bullets, sizeof(*map->bullets));//TODO
            n = send(socketData->cli_sockfd[i], (const char*)map->bullets, sizeof(*map->bullets), 0);
            if (n < 0){
                perror("Thread_ServerSend: Error sending bullets to client\n");
                continue;
            }
        }
        if (numberOfInvalidSockets == players){
            printf("Thread_ServerSend: All clients disconnected\n");
            break;
        }
        MoveBullets(map);
        pthread_mutex_unlock(gameData->gameMutex);
        usleep(20000);
        turn = (turn + 1) % 50;
        if (!turn){
            gameTime--;
        }
        if (gameTime == 0){
            pthread_mutex_lock(gameData->gameMutex);
            printf("Thread_ServerSend: Game over, time runs out.\n");
            for (int i = 0; i < players; ++i) {
                if (socketData->validSockets[i]) {
                    enum ResponseType respond = STOP;
                    //n = write(socketData->cli_sockfd[i], &respond, sizeof(respond));//TODO
                    n = send(socketData->cli_sockfd[i], (const char*)&respond, sizeof(respond),0);
                    if (n < 0) {
                        perror("Thread_ServerSend: Error sending STOP response to client\n");
                    }
                }
            }
            gameData->isRunning = false;
            pthread_mutex_unlock(gameData->gameMutex);
        }
    }
    printf("Thread_ServerSend: Ends\n");
    return NULL;
}

void* Thread_ServerReceive(void* data){
    RECIPIENT_DATA* recipientData = data;
    GAME_DATA * gameData = recipientData->gameData;
    MAP * map = gameData->map;
    SOCKET_DATA* socketData = gameData->socketData;
    int id = recipientData->id;
    PLAYER_STRUCT * player = &map->players[id];

    int maxBullets = MAX_BULLETS;
    long n;

    printf("Thread_ServerReceive %d: Starts\n", id);
    pthread_mutex_lock(gameData->gameMutex);
    while (!gameData->isRunning){
        printf("Thread_ServerReceive %d: Player is waiting for game\n", id);
        pthread_cond_wait(gameData->startGame_c, gameData->gameMutex);
    }
    pthread_mutex_unlock(gameData->gameMutex);
    while (gameData->isRunning){
        printf("Thread_ServerReceive %d: Waiting for message from player\n", id);
        while (!player->isAlive) {
            pthread_mutex_lock(gameData->gameMutex);
            player->lives++;
            if (player->lives == MAX_LIVES)
                player->isAlive = true;
            pthread_mutex_unlock(gameData->gameMutex);
            sleep(1);
        }
        CLIENT_MESSAGE message;
        //n = read(socketData->cli_sockfd[id], &message, sizeof(message));//TODO
        n = recv(socketData->cli_sockfd[id], (char*)&message, sizeof(message), 0);
        if (n < 0){
            perror("Thread_ServerReceive: Error reading from socket from client\n");
            break;
        }
        else if (n == 0){
            perror("Thread_ServerReceive: Client disconnected.\n");
            break;
        }
        pthread_mutex_lock(gameData->gameMutex);
        if (player->isAlive){
            printf("Thread_ServerReceive %d: Received %s with direction %s\n", id, MessageType_toString(message.type),
                   Direction_toString(message.direction));
            if (message.type == PLAYER)
                MovePlayer(player, message.direction, map->mapX, map->mapY, WALL_THICKNESS);
            else if(message.type == BULLET && map->numberOfBullets < maxBullets)
            {
                BULLET_STRUCT newBullet = {.y = player->y, .x = player->x, .direction = message.direction, .shooterId = id};
                int shift = 1;
                switch (message.direction) {
                    case UP:
                        newBullet.y -= (BULLET_SIZE + shift);
                        newBullet.x += CELL_WIDTH - (BULLET_SIZE + shift);
                        break;
                    case DOWN:
                        newBullet.y += CELL_WIDTH + shift;
                        newBullet.x += shift;
                        break;
                    case LEFT:
                        newBullet.x -= (BULLET_SIZE + shift);
                        newBullet.y += shift;
                        break;
                    case RIGHT:
                        newBullet.x += CELL_WIDTH + shift;
                        newBullet.y += CELL_WIDTH - (BULLET_SIZE + shift);
                        break;
                }
                map->bullets[map->numberOfBullets++] = newBullet;
            }
        }
        pthread_mutex_unlock(gameData->gameMutex);
    }
    printf("Thread_ServerReceive [%d]: Ends\n", id);
    pthread_mutex_lock(gameData->gameMutex);
    close(socketData->cli_sockfd[id]);
    socketData->validSockets[id] = false;
    player->isAlive = false;
    pthread_mutex_unlock(gameData->gameMutex);
    return NULL;
}

void MoveBullets(MAP* map){
    printf("MoveBullets: Number of bullets is %d\n", map->numberOfBullets);

    int lastBulletIndex = map->numberOfBullets - 1;
    for (int i = lastBulletIndex; i >= 0; --i) {
        BULLET_STRUCT * bullet = &map->bullets[i];
        MoveBullet(bullet, bullet->direction);
        if (bullet->x < WALL_THICKNESS || bullet->x > map->mapX - WALL_THICKNESS - BULLET_SIZE ||
        bullet->y < WALL_THICKNESS || bullet->y > map->mapY - WALL_THICKNESS - BULLET_SIZE){
            *bullet = map->bullets[--map->numberOfBullets];
            continue;
        }
        for (int j = 0; j < map->numberOfPlayers; ++j) {
            PLAYER_STRUCT *player = &map->players[j];
            if (player->isAlive &&
            bullet->x >= player->x && bullet->x <= player->x + CELL_WIDTH &&
            bullet->y >= player->y && bullet->y <= player->y + CELL_WIDTH) {
                player->lives--;
                map->players[bullet->shooterId].hits++;
                if (player->lives == 0) {
                    player->isAlive = false;
                }
                *bullet = map->bullets[--map->numberOfBullets];
                break;
            }
        }
    }
}

void StartRequests(BINDING_DATA * bindingData){
    SOCKET_DATA * socketData = bindingData->socketData;
    int lastConnectedClients = socketData->connectedClients;
    int minimumPlayers = MIN_PLAYERS;
    int maxPlayers = MAX_PLAYERS;
    int sleepTime = 10;
    printf("StartRequest: Started.\n");
    pthread_mutex_lock(bindingData->bindingMutex);
    bindingData->waitingForConnection = true;
    printf("StartRequest: Waiting for clients.\n");
    while (socketData->connectedClients < minimumPlayers){
        pthread_cond_signal(bindingData->connectPlayers_c);
        pthread_cond_wait(bindingData->playerConnected_c, bindingData->bindingMutex);
        printf("StartRequest: Number of connected clients is %d.\n", socketData->connectedClients);
        lastConnectedClients = socketData->connectedClients;
    }
    printf("StartRequest: Minimum number of connected clients has been reached.\n");
    while (sleepTime > 0) {
        printf("StartRequest:Waiting %d seconds for other clients\n", sleepTime);
        pthread_mutex_unlock(bindingData->bindingMutex);
        pthread_cond_signal(bindingData->connectPlayers_c);
        sleep(1);
        pthread_mutex_lock(bindingData->bindingMutex);
        if (lastConnectedClients < socketData->connectedClients){
            printf("StartRequest: Number of connected clients is %d.\n", socketData->connectedClients);
            lastConnectedClients = socketData->connectedClients;
            if (lastConnectedClients == maxPlayers){
                printf("StartRequest: Maximum number of clients has been reached.\n");
            }
        }
        sleepTime--;
    }
    printf("StartRequest: Cancel receiving requests\n");
    bindingData->gameStarted = true;
    pthread_mutex_unlock(bindingData->bindingMutex);
    pthread_cond_signal(bindingData->connectPlayers_c);
}

void * Thread_ConnectPlayers(void * data){
    BINDING_DATA * bindingData = data;
    SOCKET_DATA * socketData = bindingData->socketData;
    int maxPlayers = MAX_PLAYERS;
    long n;
    printf("Thread_ConnectPlayers: Started.\n");
    listen(socketData->sockfd, maxPlayers);
    for (int i = 0; i < maxPlayers; ++i) {
        pthread_mutex_lock(bindingData->bindingMutex);
        while (!bindingData->waitingForConnection){
            printf("Thread_ConnectPlayers: Waiting for permission to accepting requests.\n");
            pthread_cond_wait(bindingData->connectPlayers_c, bindingData->bindingMutex);
        }
        if (bindingData->gameStarted){
            printf("Thread_ConnectPlayers: Connection requests are canceled\n");
            pthread_mutex_unlock(bindingData->bindingMutex);
            break;
        }
        printf("Thread_ConnectPlayers: Starting connection.\n");
        memset(&socketData->cli_addr[bindingData->socketData->connectedClients],
               0,
               sizeof(socketData->cli_addr[socketData->connectedClients]));
        socketData->cli_len[socketData->connectedClients] = sizeof(socketData->cli_addr[socketData->connectedClients]);
        printf("Thread_ConnectPlayers: Waiting for client connection.\n");
        pthread_mutex_unlock(bindingData->bindingMutex);
        int new_sockfd = (int)accept(socketData->sockfd,
                                (struct sockaddr *) &socketData->cli_addr[socketData->connectedClients],
                                &socketData->cli_len[socketData->connectedClients]);
        if (new_sockfd < 0){
            perror("Thread_ConnectPlayers: Error accepting connection from client.\n");
        }
        pthread_mutex_lock(bindingData->bindingMutex);
        socketData->cli_sockfd[socketData->connectedClients] = new_sockfd;
        enum ResponseType response;
        if (!bindingData->waitingForConnection || socketData->connectedClients == maxPlayers){
            printf("Thread_ConnectPlayers: Cannot accept new clients.\n");
            response = STOP;
            //n = write(socketData->cli_sockfd[socketData->connectedClients], &response, sizeof(response));//todo
            n = send(socketData->cli_sockfd[socketData->connectedClients], (const char*)&response, sizeof(response), 0);
            if (n < 0){
                perror("Thread_ConnectPlayers: Error writing server response to socket\n");
            }
            close(socketData->cli_sockfd[socketData->connectedClients]);
            pthread_mutex_unlock(bindingData->bindingMutex);
            break;
        }else {
            printf("Thread_ConnectPlayers: Accepting client connection.\n");
            response = ACK;
            //n = write(socketData->cli_sockfd[socketData->connectedClients], &response, sizeof(response));//todo
            n = send(socketData->cli_sockfd[socketData->connectedClients], (const char*)&response, sizeof(response), 0);
            if (n < 0){
                perror("Thread_ConnectPlayers: Error writing server response to socket\n");
            }
            //n = write(socketData->cli_sockfd[socketData->connectedClients], &socketData->connectedClients, sizeof(socketData->connectedClients));//todo
            n = send(socketData->cli_sockfd[socketData->connectedClients], (const char*)&socketData->connectedClients, sizeof(socketData->connectedClients),0);
            if (n < 0){
                perror("Thread_ConnectPlayers: Error writing server id to socket\n");
            }
            response = WAIT;
            //n = write(socketData->cli_sockfd[socketData->connectedClients], &response, sizeof(response));//TODO
            n = send(socketData->cli_sockfd[socketData->connectedClients], (const char*)&response, sizeof(response),0);
            if (n < 0){
                perror("Thread_ConnectPlayers: Error writing server response to socket\n");
            }
            bindingData->socketData->connectedClients++;
        }
        pthread_mutex_unlock(bindingData->bindingMutex);
        pthread_cond_signal(bindingData->playerConnected_c);
    }
    printf("Thread_ConnectPlayers: Ended.\n");
    return NULL;
}
