

#ifndef PLAYER_H
#define PLAYER_H


#include "SDL.h"
#include "../../constants.h"



typedef struct Ship
{
    int posX;
    int posY;
    int lives;
    int score; 
    SDL_Texture *texture;
} Ship;



Ship* ship; 


void moveShip(int dir);
void sendMovePlayerCommand(int posX, int posY);
void updateShipPosition(int posX, int posY);

#endif //SHIP_H