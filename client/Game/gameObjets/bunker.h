


#ifndef BUNKER_H
#define BUNKER_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "../../constants.h"




typedef struct Bunker
{

    int posX;
    int posY;
    int health; 
    struct Bunker* next;
    SDL_Texture *currentTexture;
    SDL_Texture *texture;
    SDL_Texture *texture80Health; 
    SDL_Texture *texture60Health;
    SDL_Texture *texture40Health;
    SDL_Texture *texture20Health;
    SDL_Texture *texture0Health;


} Bunker;




Bunker* bunkerList;


void updateBunkerHealth(Bunker **bunker);

void addBunker(Bunker** list, Bunker* bunker);

void deleteBunker(Bunker** list, Bunker* bunker);

Bunker* initBunkerList();


#endif