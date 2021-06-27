

#include <slcurses.h>
#include "game.h"




void createWindow(int id, int observing){

    gameId = id;
    isObserver = observing;
    hasStarted = 0;

    if(SDL_Init(SDL_INIT_EVERYTHING) < 0){
        printf("Could not initialise SDL");
        exit(-1);
    };

    IMG_Init(IMG_INIT_PNG);
    if(TTF_Init() == -1){
       printf("TTF_INIT: %s\n", TTF_GetError());
    
    }
  

    window = SDL_CreateWindow(
            "Space Invaders",                  // window title
            SDL_WINDOWPOS_UNDEFINED,           // initial x position
            SDL_WINDOWPOS_UNDEFINED,           // initial y position
            1000,                               // width, in pixels
            700,                               // height, in pixels
            SDL_WINDOW_ALLOW_HIGHDPI                  // flags - see below
    );
    renderer = SDL_CreateRenderer(window, -1, 0);

    SDL_RenderClear(renderer);

    SDL_RenderPresent(renderer);

    SDL_Delay(500);


    
    initBackground(); 
    createShip(); 
    
    bulletPlayer = NULL; //Inicializa la lista de balas del jugador 

    bulletEnemy = NULL; //Inicializa la lista de balas del enemigo


    createBunkers();
    createEnemies();
    createSpacecraft();
    gameLoop();

}



void gameLoop(){
    SDL_Event event;
    bool quit = 0;


    while(!quit){

        
            while(SDL_PollEvent( &event) !=0){

                switch (event.type) {
                    case SDL_QUIT:
                        quit = 1;
                        break;


                    case SDL_KEYDOWN:

                        if (!isObserver && hasStarted)
                        {

                            switch (event.key.keysym.sym) {


                                case SDLK_a:

                                    moveShip(LEFT);
                                    break;

                                case SDLK_d:

                                    moveShip(RIGHT);
                                    break;


                                case SDLK_SPACE:
                            
                                    shoot();
                                    break;

                    
                                default:

                                    break;

                            }
                        }


                    default:

                        break;

                }
            
            }

        if (!isObserver && hasStarted)
        {
            moveBullets();
            moveEnemies();
            moveSpacecraft();
            enemyFire();
        }

        collisions();

        SDL_RenderClear(renderer);
            
        SDL_RenderCopy(renderer, background, NULL, NULL);

        renderTextures(renderer);

        SDL_RenderPresent(renderer);
        SDL_Delay(DELAY);

    }
}





void initBackground()
{

    background = loadTexture(BACKGROUND_SPRITE_PATH);
    
}


void startGame()
{

    hasStarted = 1;

}





SDL_Texture * loadTexture(const char* path){

    SDL_Texture *texture = NULL;
    SDL_Surface *surface = IMG_Load(path);


    if(!surface){

        printf("Could not load image %s\n", IMG_GetError());

    }


    texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);

    return texture;
}



void createShip()
{
    
    ship = (Ship*) malloc(sizeof(Ship));
    ship->posX = INITIAL_POS_X;
    ship->posY  = INITIAL_POS_Y;
    ship->score = 0;
    ship->lives = 3;
    ship->texture = loadTexture(SHIP_SPRITE_PATH);

    
}


void createBunkers()
{

    int posX = 20;
    int posY = 520;


    for(int i=0; i< NUMBER_OF_BUNKERS; i++)
    {

        Bunker* temp = (Bunker*) malloc(sizeof(Bunker));
        temp->posX = posX + i*280 ;
        temp->posY = posY;
        temp->health = 100;
        temp->texture = loadTexture(BUNKER_SPRITE_PATH);
        temp->isActive = 1;
        temp->texture80Health = loadTexture(BUNKER_80HEALTH_SPRITE_PATH);
        temp->texture60Health = loadTexture(BUNKER_60HEALTH_SPRITE_PATH);
        temp->texture40Health = loadTexture(BUNKER_40HEALTH_SPRITE_PATH);
        temp->texture20Health = loadTexture(BUNKER_20HEALTH_SPRITE_PATH);
        temp->currentTexture = temp->texture;
  
        bunkerList[i] = temp;

    }
}



void createEnemies()
{


    int id = 1;
    int posX = 0;
    int posY = 70;


    for(int row=0; row < ROW_ENEMY_MATRIX; row++)
    {
        posX = 0;
        posY += 40;
        
        for(int column=0; column < COLUMNS_ENEMY_MATRIX; column++)
        {
            posX += 60;

            Enemy* newEnemy = (Enemy*) malloc(sizeof(Enemy));
            newEnemy->posX = posX;
            newEnemy->posY = posY;
            newEnemy->isActive = 0;
            newEnemy->type = NULL;
            newEnemy->id = id;
            newEnemy->dir = 1;
            newEnemy->texture = NULL;

            enemyMatrix[row][column] = newEnemy;

            id++;
        } 
    }

}



void putEnemy(char* type, int enemyId)
{


    Enemy* enemy = getEnemyByID(enemyId);

    if (strcmp(type, "crab"))
    {
        enemy->texture = loadTexture(CRAB_SPRITE_PATH);
        enemy->type = "crab";
    }

    else if (strcmp(type, "octo"))
    {
        enemy->texture = loadTexture(OCTO_SPRITE_PATH);
        enemy->type = "octo";
    }
    else if (strcmp(type, "squid"))
    {
        enemy->texture = loadTexture(SQUID_SPRITE_PATH);
        enemy->type = "squid";
    }
    enemy->isActive = 1;



}



void shoot()
{
    if (bulletPlayer == NULL)
    {
        bulletPlayer = (Bullet*) malloc(sizeof(Bullet));
        bulletPlayer->posX = ship->posX + 20;
        bulletPlayer->posY = ship->posY; 
        bulletPlayer->width = RECT_WIDTH_BULLET;
        bulletPlayer->height = RECT_HEIGHT_BULLET;
        bulletPlayer->texture = loadTexture(BULLET_SPRITE_PATH);
        bulletPlayer->textureImpact = loadTexture(IMPACT_SPRITE_PATH);
        bulletPlayer->currentTexture = bulletPlayer->texture;
        bulletPlayer->next = NULL;

        sendPutBulletPlayerCommand(bulletPlayer->posX, bulletPlayer->posY);
    }

}



void enemyFire()
{

    if (bulletEnemy == NULL)
    {   

        int i = generateRandomNum(ROW_ENEMY_MATRIX - 1);
        int j = generateRandomNum(COLUMNS_ENEMY_MATRIX - 1);
        Enemy* tempEnemy = enemyMatrix[i][j];
        bulletEnemy = (Bullet*) malloc(sizeof(Bullet));
        bulletEnemy->posX = tempEnemy->posX;
        bulletEnemy->posY = tempEnemy->posY;
        bulletEnemy->width = RECT_WIDTH_BULLET;
        bulletEnemy->height = RECT_HEIGHT_BULLET;
        bulletEnemy->texture = loadTexture(BULLET_SPRITE_PATH);
        bulletEnemy->textureImpact = loadTexture(IMPACT_SPRITE_PATH);
        bulletEnemy->currentTexture = bulletEnemy->texture;
        bulletEnemy->next = NULL;


        sendPutBulletEnemyCommand(bulletEnemy->posX, bulletEnemy->posY);

        
    }



}


void createSpacecraft()
{

    spacecraft = (Spacecraft*) malloc(sizeof(Spacecraft));
    spacecraft->posX = WINDOW_MAX_WIDTH;
    spacecraft->posY = 100;
    spacecraft->active = 0;
    spacecraft->texture = loadTexture(SPACECRAFT_SPRITE_PATH);



}




void collisions()
{

    bulletPlayerCollisions();
    bulletEnemyCollisions();

}

void bulletPlayerCollisions()
{

    if (bulletPlayer != NULL)
    {

        if (bunkerCollision(bulletPlayer->posX, bulletPlayer->posY))
        {

            free(bulletPlayer);
            bulletPlayer = NULL;


        }
        
        else if(enemiesCollision(bulletPlayer->posX, bulletPlayer->posY))
        {

            free(bulletPlayer);
            bulletPlayer = NULL;
        }

        else if(spacecraftCollision(bulletPlayer->posX, bulletPlayer->posY))
        {

            free(bulletPlayer);
            bulletPlayer = NULL;

        }

        else if(bulletPlayer->posY <= WINDOW_MIN_HEIGHT)
        {

            free(bulletPlayer);
            bulletPlayer = NULL;

        }

    }

}




void bulletEnemyCollisions()
{

    if (bulletEnemy != NULL)
    {

        if (bunkerCollision(bulletEnemy->posX, bulletEnemy->posY))
        {

            free(bulletEnemy);
            bulletEnemy = NULL;
                    
        }

        else if(shipCollision(bulletEnemy->posX, bulletEnemy->posY))
        {

            free(bulletEnemy);
            bulletEnemy = NULL;

        }

        else if(bulletEnemy->posY >= WINDOW_MAX_HEIGHT)
        {

            free(bulletEnemy);
            bulletEnemy = NULL;

        }
    }

}



int shipCollision(int posX, int posY)
{

    if(bulletEnemy != NULL)
    {

        if(posX >= ship->posX && posX <= ship->posX + 40 && posY >= ship->posY && posY <= ship->posY + 40)
        {

            if (!isObserver)
            {

                sendAttakedCommand();

            }

            return 1;

        } 

        return 0;

    }

    return 0;

}

int bunkerCollision(int posX, int posY)
{

    for(int i=0; i < NUMBER_OF_BUNKERS; i++)
    {

        Enemy* current = bunkerList[i];
    

        if(current->isActive)
        {
            if(posX >= current->posX && posX <= current->posX + 90 && posY >= current->posY && posY <= current->posY + 70)
            {

                updateBunkerHealth(&current);
                return 1;

            }
        }
    }

    return 0;
}


int enemiesCollision(int posX, int posY)
{


    for(int row=0; row < ROW_ENEMY_MATRIX; row++)
    {

        for(int column=0; column < COLUMNS_ENEMY_MATRIX; column++)
        {

            Enemy* currentEnemy = enemyMatrix[row][column];

            if(currentEnemy->isActive)
            {


                if(posX >= currentEnemy->posX && posX <= currentEnemy->posX + 50 && posY >= currentEnemy->posY && posY <= currentEnemy->posY + 50)
                {

                    currentEnemy->isActive = 0;  

                    if (!isObserver)
                    {

                        sendKillEnemyCommand(currentEnemy->id, currentEnemy->type);

                    }
                             
                    return 1;
                }
            }


        }
    }

    return 0;
}


int spacecraftCollision(int posX, int posY)
{

    if (spacecraft->active)
    {


        if(posX >= spacecraft->posX && posX <= spacecraft->posX + 90 && posY >= spacecraft->posY && posY <= spacecraft->posY + 70)
        {

            killSpacecraft();
            return 1;

        }

        return 0;





        


    }
}