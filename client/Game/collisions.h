



#ifndef COLLISIONS_H
#define COLLISIONS_H

#include "gameObjets/bullet.h"
#include "gameObjets/bunker.h"
#include "render.h"
#include "gameObjets/ship.h"


void collisions();

void bulletPlayerCollisions();
void bulletEnemyCollisions();

int bunkerCollision(int posX, int posY);
int enemiesCollision(int posX, int posY);
int shipCollision(int posX, int posY);


#endif