



#ifndef BULLET_H
#define BULLET_H


#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "../../constants.h"


typedef struct Bullet
{

    int posX;
    int posY;
    int width;
    int height;
    SDL_Texture *texture; 
    SDL_Texture *textureImpact;
    SDL_Texture *currentTexture;


    struct Bullet *next;



} Bullet;



void shoot();

void moveBullets();
void checkBulletBoundaries();
void sendMoveBulletPlayerCommand(int posX, int posY);
void sendMoveBulletEnemyCommand(int posX, int posY);

void updateBulletPlayer(int posX, int posY);
void updateBulletEnemy(int posX, int posY);


Bullet* bulletPlayer;
Bullet* bulletEnemy;










#endif 