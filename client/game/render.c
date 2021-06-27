#include "render.h"





void renderTextures(SDL_Renderer *renderer)
{

    renderShip(renderer);
    renderBullet(renderer, bulletPlayer);
    renderBullet(renderer, bulletEnemy);
    renderBunker(renderer, bunkerList);
    renderEnemies(renderer);
    renderScore(renderer);
    renderLives(renderer);
    renderSpacecraft(renderer);



}


void renderBunker(SDL_Renderer* renderer, Bunker* list)
{


    



    for(int i=0; i < NUMBER_OF_BUNKERS; i++)
    {

        Bunker* current = bunkerList[i];


        if (current->isActive)
        {

            SDL_Rect dstrect = {current->posX, current->posY, RECT_WIDTH_BUNKER, RECT_HEIGHT_BUNKER};
            SDL_RenderCopy(renderer, current->currentTexture, NULL, &dstrect);

        }
        
        
       

    }



}



void renderShip(SDL_Renderer *renderer)
{
    
    SDL_Rect dstrect = {ship->posX, ship->posY, RECT_WIDTH_SHIP, RECT_HEIGHT_SHIP};
    SDL_RenderCopy(renderer, ship->texture, NULL, &dstrect);

}


void renderBullet(SDL_Renderer* renderer, Bullet* bullet)
{

    if (bullet != NULL)
    {

        SDL_Rect dstrect = {bullet->posX, bullet->posY, bullet->width, bullet->height};
        SDL_RenderCopy(renderer, bullet->currentTexture, NULL, &dstrect);


    }
  
 
}


void renderSpacecraft(SDL_Renderer* renderer)
{

    if (spacecraft != NULL)
    {

        if(spacecraft->active)
        {
            SDL_Rect dstrect = {spacecraft->posX, spacecraft->posY, RECT_WIDTH_ENEMY, RECT_HEIGHT_ENEMY};
            SDL_RenderCopy(renderer, spacecraft->texture, NULL, &dstrect);

        }



    }
  
 
}


void renderEnemies(SDL_Renderer* renderer)
{

    for(int row=0; row < ROW_ENEMY_MATRIX; row++)
    {

        for(int column=0; column < COLUMNS_ENEMY_MATRIX; column++)
        {

            Enemy* currentEnemy = enemyMatrix[row][column];

            if (currentEnemy->isActive)
            {

                SDL_Rect dstrect = {currentEnemy->posX, currentEnemy->posY, RECT_WIDTH_ENEMY, RECT_HEIGHT_ENEMY};
                SDL_RenderCopy(renderer, currentEnemy->texture, NULL, &dstrect);
            }




        } 

    }


    
}





void renderScore(SDL_Renderer* renderer){


    if(Sans == NULL){
        Sans = TTF_OpenFont("../resources/OpenSans-Regular.ttf", 12);
    }
    SDL_Color White = {255, 255, 255};
    char* scoreLabel =  "Score";
    SDL_Surface* surfaceMessage = TTF_RenderText_Solid(Sans, scoreLabel, White);
    SDL_Texture* Message = SDL_CreateTextureFromSurface(renderer, surfaceMessage);
    SDL_Rect Message_rect = {50,0,100, 70};
    SDL_RenderCopy(renderer, Message, NULL, &Message_rect);

    char score[20];
    sprintf(score, "%d", ship->score);
    SDL_Surface* surfaceScore = TTF_RenderText_Solid(Sans, score, White);
    SDL_Texture* scoreTexture = SDL_CreateTextureFromSurface(renderer, surfaceScore);
    SDL_Rect score_rect = {200,18,50, 50};
    SDL_RenderCopy(renderer, scoreTexture, NULL, &score_rect);
    SDL_FreeSurface(surfaceMessage);
    SDL_FreeSurface(surfaceScore);
}



void renderLives(SDL_Renderer* renderer){
    if(Sans == NULL){
        Sans = TTF_OpenFont("../resources/OpenSans-Regular.ttf", 12);
    }
    SDL_Color White = {255, 255, 255};

    SDL_Surface* surfaceMessage = TTF_RenderText_Solid(Sans, "Lives", White);
    SDL_Texture* Message = SDL_CreateTextureFromSurface(renderer, surfaceMessage);
    SDL_Rect Message_rect = {750,0,100, 70};

    char lives[20];
    sprintf(lives, "%d", ship->lives);
    SDL_Surface* surfaceLives = TTF_RenderText_Solid(Sans, lives, White);
    SDL_Texture* LivesTexture = SDL_CreateTextureFromSurface(renderer, surfaceLives);
    SDL_Rect lives_rect = {900,18,50, 50};
    SDL_RenderCopy(renderer, LivesTexture, NULL, &lives_rect);
    SDL_RenderCopy(renderer, Message, NULL, &Message_rect);
    SDL_FreeSurface(surfaceMessage);
    SDL_FreeSurface(surfaceLives);
}