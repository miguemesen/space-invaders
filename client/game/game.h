

#ifndef CLIENT_GAME_CUH
#define CLIENT_GAME_CUH

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <SDL_ttf.h>
#include "gameObjets/ship.h"
#include "../constants.h"
#include "render.h"
#include "gameObjets/bullet.h"
#include "gameObjets/bunker.h"
#include "gameObjets/enemy.h"
#include "gameObjets/spacecraft.h"
#include "util.h"


TTF_Font* Sans;
SDL_Window *window;
SDL_Renderer *renderer;
SDL_Texture *background;

int gameId; 
int isObserver;
int hasStarted;



void createWindow(int id, int observing);

void gameLoop();
void initBackground();
void createShip();
void createBunkers();
void createEnemies();
void createSpacecraft();
void startGame();
void shoot();
void enemyFire();
void moveShip(int dir);
void collisions();
void bulletPlayerCollisions();
void bulletEnemyCollisions();
int bunkerCollision(int posX, int posY);
int enemiesCollision(int posX, int posY);
int shipCollision(int posX, int posY);
int spacecraftCollision(int posX, int posY);
void hasWin();
void gameOver(int score, int lives);


void sendPutBulletPlayerCommand(int posX, int posY);
void sendPutBulletEnemyCommand(int posX, int posY);
void sendKillPlayerCommand();
void sendKillEnemyCommand(int enemyId, char* type);
void sendAttackedCommand();
void sendUpdateGameStateCommand();
void sendWinCommand();
void sendGameOverCommand();
void sendKillSpacecraftCommand();

#endif //CLIENT_GAME_CUH


