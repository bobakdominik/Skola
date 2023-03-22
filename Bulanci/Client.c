//
// Created by bobak on 12/21/2021.
//

#include "Client.h"
typedef struct socketData SOCKET_DATA;
typedef struct gameData GAME_DATA;
int ConnectToServer(SOCKET_DATA* socketData);
CLIENT_MESSAGE GetClientMessage(MAP * map);
void ShowMap(Game* game);
void* Thread_ClientSend(void* data);
void* Thread_ClientReceive(void* data);

struct socketData{
    int sockfd;
    struct sockaddr_in serv_addr;
    struct hostent* server;
};

struct gameData{
    SOCKET_DATA * socketData;
    MAP * map;
    bool gameStarted;
    bool isRunning;
    const int id;

    pthread_mutex_t * gameMutex;
    pthread_cond_t * startGame_c;
    pthread_cond_t * keyPressed_c;
};

void ShowMap(Game * game){
    draw_map(game);
}

void init_Client() {
    int id;
    pthread_t sender_t, receiver_t;
    pthread_mutex_t gameMutex;
    pthread_cond_t startGame_c, keyPressed_c;
    SOCKET_DATA socketData;

    pthread_mutex_init(&gameMutex, NULL);
    pthread_cond_init(&startGame_c, NULL);
    pthread_cond_init(&keyPressed_c, NULL);
    printf("init_Client: Client starts\n");
    id = ConnectToServer(&socketData);
    printf("init_Client: id: %d\n", id);
    if (id >= 0) {
        MAP map = {.mapX = SCREEN_WIDTH, .mapY = SCREEN_HEIGHT, .numberOfBullets = 0, .numberOfPlayers = 0};

        GAME_DATA gameData = {.socketData = &socketData,
                              .isRunning = false,
                              .gameStarted = false ,
                              .map = &map,
                              .id = id,
                              .gameMutex = &gameMutex,
                              .startGame_c = &startGame_c,
                              .keyPressed_c = &keyPressed_c};
        printf("init_Client: Client starting game\n");

        pthread_create(&receiver_t, NULL, &Thread_ClientReceive, &gameData);
        pthread_create(&sender_t, NULL, &Thread_ClientSend, &gameData);

        pthread_join(sender_t, NULL);
        pthread_join(receiver_t, NULL);
    }
    pthread_mutex_destroy(&gameMutex);
    pthread_cond_destroy(&startGame_c);
    pthread_cond_destroy(&keyPressed_c);
    close(socketData.sockfd);
    printf("init_Client: Client ends\n");

}

CLIENT_MESSAGE GetClientMessage(MAP * map){
    enum KeyType type = map->lastKey;
    CLIENT_MESSAGE message;
    switch (type) {
        case LEFT_ARROW:
            message.type = PLAYER;
            message.direction = LEFT;
            break;
        case RIGHT_ARROW:
            message.type = PLAYER;
            message.direction = RIGHT;
            break;
        case UP_ARROW:
            message.type = PLAYER;
            message.direction = UP;
            break;
        case DOWN_ARROW:
            message.type = PLAYER;
            message.direction = DOWN;
            break;
        case SPACEBAR:
            message.type = BULLET;
            break;
        case BACKSPACE:
        case ESCAPE:
            message.type = CANCEL;
            break;
        case UNDEF:
        default:
            message.type = UNKNOWN;
    }
    return message;
}

void* Thread_ClientSend(void* data){
    sleep(1);
    long n;
    GAME_DATA * gameData = data;
    SOCKET_DATA * socketData = gameData->socketData;
    MAP* map = gameData->map;
    int id = gameData->id;
    printf("Thread_ClientSend: Starts, ID = %d\n", id);
    pthread_mutex_lock(gameData->gameMutex);
    if (!gameData->gameStarted){
        printf("Thread_ClientSend: Waiting for game start\n");
        pthread_cond_wait(gameData->startGame_c, gameData->gameMutex);
    }
    pthread_mutex_unlock(gameData->gameMutex);

    while(gameData->isRunning){
        pthread_mutex_lock(gameData->gameMutex);
        CLIENT_MESSAGE message = GetClientMessage(map);
        while (message.type == UNKNOWN){
            printf("\nThread_ClientSend: Message with type: %s and direction: %s\n",
                   MessageType_toString(message.type), Direction_toString(message.direction));
            pthread_cond_wait(gameData->keyPressed_c, gameData->gameMutex);
            message = GetClientMessage(map);

        }
        map->lastKey = UNDEF;
        if(message.type == BULLET)
            message.direction = map->players[id].direction;
        pthread_mutex_unlock(gameData->gameMutex);
        printf("Thread_ClientSend: Sending message with type: %s and direction: %s\n",
               MessageType_toString(message.type), Direction_toString(message.direction));
        //n = write(socketData->sockfd, &message, sizeof(message));// TODO
        n = send(socketData->sockfd, (char*)&message, sizeof(message), 0);
        if (n < 0){
            perror("Thread_ClientSend: Error writing to socket for server\n");
        }
    }

    printf("Thread_ClientSend: Stops.\n");
    return NULL;
}

void* Thread_ClientReceive(void* data){
    long n;
    GAME_DATA * gameData = data;
    SOCKET_DATA * socketData = gameData->socketData;
    MAP * map = gameData->map;
    int id = gameData->id;
    printf("Thread_ClientReceive: Starts, ID = %d\n", id);
    enum ResponseType respond;
    Game game = {
            .running = 1,
            .state = NOT_PLAYING,
            .map = map,
    };
    initialize(&game); //Gui
    while (1) {
        //n = read(socketData->sockfd, &respond, sizeof(respond));// TODO
        n = recv(socketData->sockfd, (char*)&respond, sizeof(respond),0);
        if (n < 0){
            perror("Thread_ClientReceive: Error reading from socket\n");
            break;
        } else if (n == 0){
            perror("Thread_ClientReceive: Server stops.\n");
            break;
        }
        if (respond == WAIT){
            printf("Thread_ClientReceive: Waiting for server to start the game\n");
            update_title(&game, "Waiting for server to start the game");
        }else if (respond == PLAY){
            printf("Thread_ClientReceive: Receiving game updates\n");
            pthread_mutex_lock(gameData->gameMutex);
            if (!gameData->isRunning || !gameData->gameStarted){
                gameData->isRunning = true;
                gameData->gameStarted = true;
            }
            //n = read(socketData->sockfd, map, sizeof(*map));//TODO
            n = recv(socketData->sockfd, (char*)map, sizeof(*map),0);
            if (n <= 0){
                perror("Thread_ClientReceive: Error reading map from server\n");
                break;
            }
            //n = read(socketData->sockfd, map->players, sizeof(*map->players));//TODO
            n = recv(socketData->sockfd, (char*)map->players, sizeof(*map->players),0);
            if (n <= 0){
                perror("Thread_ClientReceive: Error reading players from server\n");
                break;
            }
            //n = read(socketData->sockfd, map->bullets, sizeof(*map->bullets))//TODO
            n = recv(socketData->sockfd, (char*)map->bullets, sizeof(*map->bullets),0);
            if (n <= 0){
                perror("Thread_ClientReceive: Error reading bullets from server\n");
                break;
            }
            char buffer[255];
            snprintf(buffer, sizeof(buffer), "Lives: %d, Hits: %d", map->players[id].lives, map->players[id].hits);
            update_title(&game, buffer);
            ShowMap(&game);
            map->lastKey = handle_input(&game);
            printf("Thread_ClientReceive: Key = %d\n", map->lastKey);
            pthread_mutex_unlock(gameData->gameMutex);
            if (map->lastKey != UNDEF) {
                pthread_cond_signal(gameData->keyPressed_c);
            }
            pthread_cond_signal(gameData->startGame_c);
        }else if(respond == STOP){
            update_title(&game, "Game ended");
            printf("Thread_ClientReceive: Game ended\n");
            break;
        } else{
            perror("Thread_ClientReceive: Unknown response type\n");
            break;
        }
    }
    pthread_mutex_lock(gameData->gameMutex);
    gameData->gameStarted = true;
    gameData->isRunning = false;
    char buffer[255];
    snprintf(buffer, sizeof(buffer), "Game ended, press ESC to exit! Lives: %d, Hits: %d", map->players[id].lives, map->players[id].hits);
    update_title(&game, buffer);
    ShowMap(&game);
    do {
        map->lastKey = handle_input(&game);
    } while (map->lastKey != ESCAPE);
    pthread_mutex_unlock(gameData->gameMutex);
    terminate(&game, 0);
    printf("Thread_ClientReceive %d: Stops\n", id);
    return NULL;
}

int ConnectToServer(SOCKET_DATA* socketData){
    int id;
    long n;
    int port = GetPort();
    char* hostname = GetHostname();
    socketData->server = gethostbyname(hostname);
    if (socketData->server == NULL)
    {
        perror("ConnectToServer: Error, no such host\n");
        return -1;
    }
    bzero((char*)&socketData->serv_addr, sizeof(socketData->serv_addr));
    socketData->serv_addr.sin_family = AF_INET;
    bcopy(
            (char*)socketData->server->h_addr,
            (char*)&socketData->serv_addr.sin_addr.s_addr,
            socketData->server->h_length
    );
    socketData->serv_addr.sin_port = htons(port);
    socketData->sockfd = (int)socket(AF_INET, SOCK_STREAM, 0);
    if (socketData->sockfd < 0)
    {
        perror("ConnectToServer: Error creating socket");
        return -1;
    }
    if(connect(socketData->sockfd, (struct sockaddr*)&socketData->serv_addr, sizeof(socketData->serv_addr)) < 0)
    {
        perror("ConnectToServer: Error connecting to socket");
        return -1;
    }
    enum ResponseType respond;
    //n = read(socketData->sockfd, &respond, sizeof(respond));//TODO
    n = recv(socketData->sockfd, (char*)&respond, sizeof(respond),0);
    if (n < 0)
    {
        perror("ConnectToServer: Error reading from socket");
        return -1;
    }
    if (respond == ACK){
        printf("ConnectToServer: Connected to server\n");
        //n = read(socketData->sockfd, &id, sizeof(id));// TODO
        n = recv(socketData->sockfd, (char*)&id, sizeof(id), 0);
        if (n < 0)
        {
            perror("ConnectToServer: Error reading id from socket");
            return -1;
        }
        return id;
    }else  {
        printf("ConnectToServer: Can not connect to server\n");
        printf("ConnectToServer: Maximum number of players has been reached or game already started\n");
    }
    return -1;
}