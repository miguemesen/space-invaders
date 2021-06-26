

#ifndef SPACECRAFT_H
#define SPACECRAFT_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>


typedef struct  Spacecraft
{
    int posX;
    int posY;
    SDL_Texture *texture;
    

} Spacecraft;


Spacecraft *spacecraft;

#endif 