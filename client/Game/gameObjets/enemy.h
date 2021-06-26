


#ifndef ENEMY_H
#define ENEMY_H


#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "../../constants.h"
#include "bullet.h"
#include "../util.h"

typedef struct Enemy
{

    int posX;
    int posY;
    int id;
    int isActive; 
    int dir;
    SDL_Texture *texture;
    
} Enemy;



Enemy* enemyMatrix[ROW_ENEMY_MATRIX][COLUMNS_ENEMY_MATRIX];


void moveEnemies();





#endif