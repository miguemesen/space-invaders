

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
#include "collisions.h"
#include "gameObjets/enemy.h"
#include "gameObjets/spacecraft.h"
#include "util.h"


TTF_Font* Sans;
SDL_Window *window;
SDL_Renderer *renderer;
SDL_Texture *background;

int gameId; 
int isObserver;



void createWindow(int gameId, int observing);

void gameLoop();
void initBackground();
void createShip();
void createBunkers();
void createEnemies();
void createSpacecraft();


void shoot();
void enemyFire();

void moveShip(int dir);
SDL_Texture* loadTexture(const char* path);





#endif //CLIENT_GAME_CUH


