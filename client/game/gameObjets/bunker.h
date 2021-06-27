


#ifndef BUNKER_H
#define BUNKER_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "../../constants.h"
#include "../../socket/cJson.h"




typedef struct Bunker
{

    int posX;
    int posY;
    int health; 
    int isActive;
    SDL_Texture *currentTexture;
    SDL_Texture *texture;
    SDL_Texture *texture80Health; 
    SDL_Texture *texture60Health;
    SDL_Texture *texture40Health;
    SDL_Texture *texture20Health;
    SDL_Texture *texture0Health;


} Bunker;




Bunker* bunkerList[NUMBER_OF_BUNKERS];


void updateBunkerHealth(Bunker **bunker);

void sendUpdateBunkerCommand(Bunker* bunkerList[NUMBER_OF_BUNKERS]);

void updateBunkers(cJSON* bunkers);

Bunker* initBunkerList();


#endif