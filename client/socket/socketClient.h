
#ifndef PROJECT_SOCKET_H
#define PROJECT_SOCKET_H


#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include "../constants.h"
#include <stdlib.h>
#include <pthread.h>
#include "cJson.h"
#include "../game/game.h"



int client;
struct sockaddr_in server;
void *listen_socket();
_Noreturn void *listen_socket();
char server_reply[2000];
pthread_t pthread_read;
pthread_t pthread_send;

int connectionSuccessful;



int createClient();
void initClient();
void sendServer(char* info);
void connectionRefused();


void startGame();
void connectionRefused();





#endif
