



#ifndef BULLET_H
#define BULLET_H


#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "../../constants.h"
#include "../util.h"

typedef struct Bullet
{

    int posX;
    int posY;
    int isActive;
    SDL_Texture *texture; 
    SDL_Texture *textureImpact;
    SDL_Texture *currentTexture;

} Bullet;



void shoot();

void moveBullets();
void checkBulletBoundaries();
void sendMoveBulletPlayerCommand(int posX, int posY);
void sendMoveBulletEnemyCommand(int posX, int posY);

void updateBulletPlayer(int posX, int posY, int isActive);
void updateBulletEnemy(int posX, int posY, int isActive);

Bullet* bulletPlayer;
Bullet* bulletEnemy;










#endif 