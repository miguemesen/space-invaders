

#ifndef SPACECRAFT_H
#define SPACECRAFT_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <time.h>
#include "../../constants.h"

typedef struct  Spacecraft
{
    int posX;
    int posY;
    int active;
    SDL_Texture *texture;
    

} Spacecraft;


Spacecraft *spacecraft;


double prevTime;
double currentTime;
double time_;

void moveSpacecraft();
int shouldMove();
void killSpacecraft();

void updateSpaceCraftPosition(int posX, int posY);


void sendMoveSpacecraftCommand(int posX, int posY);

#endif 