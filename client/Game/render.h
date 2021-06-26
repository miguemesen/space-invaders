

#ifndef RENDER_H
#define RENDER_H


#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL_ttf.h>
#include "gameObjets/ship.h"
#include "../constants.h"
#include "gameObjets/bullet.h"
#include "gameObjets/bunker.h"
#include "gameObjets/enemy.h"
#include "gameObjets/spacecraft.h"



TTF_Font* Sans;

void renderTextures(SDL_Renderer *renderer);

void renderShip(SDL_Renderer *renderer);

void renderBunker(SDL_Renderer *renderer, Bunker* list);

void renderBullet(SDL_Renderer* renderer, Bullet* list);

void renderEnemies(SDL_Renderer* renderer);

void renderScore(SDL_Renderer* renderer);

void renderLives(SDL_Renderer* renderer);

void renderSpacecraft(SDL_Renderer* renderer);

#endif
