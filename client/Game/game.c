

#include <slcurses.h>
#include "game.h"




void createWindow(int id, int observing){

    gameId = id;
    isObserver = observing;

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

    bunkerList = initBunkerList();


    createBunkers();
    createEnemies();
    createSpacecraft();
    gameLoop();

}



void gameLoop(){
    SDL_Event event;
    bool quit = 0;


    while(!quit){


        while(SDL_PollEvent( &event) !=0 && !isObserver){


            switch (event.type) {
                case SDL_QUIT:
                    quit = 1;
                    break;

                case SDL_KEYDOWN:

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


                default:

                    break;

            }
        }



            SDL_RenderClear(renderer);
            
            SDL_RenderCopy(renderer, background, NULL, NULL);


            moveBullets();
            moveEnemies();
            enemyFire();
            collisions();
            renderTextures(renderer);

    

    
            SDL_RenderPresent(renderer);
            SDL_Delay(DELAY);
    }
}




void initBackground()
{

    background = loadTexture(BACKGROUND_SPRITE_PATH);
    
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


    for(int i=0; i<4; i++)
    {

        Bunker* temp = (Bunker*) malloc(sizeof(Bunker));
        temp->posX = posX + i*280 ;
        temp->posY = posY;
        temp->health = 100;
        temp->texture = loadTexture(BUNKER_SPRITE_PATH);
        temp->texture80Health = loadTexture(BUNKER_80HEALTH_SPRITE_PATH);
        temp->texture60Health = loadTexture(BUNKER_60HEALTH_SPRITE_PATH);
        temp->texture40Health = loadTexture(BUNKER_40HEALTH_SPRITE_PATH);
        temp->texture20Health = loadTexture(BUNKER_20HEALTH_SPRITE_PATH);
        temp->currentTexture = temp->texture;
        temp->next = NULL;


        addBunker(&bunkerList, temp);

    }
}



void createEnemies()
{


    int id = 1;

    int posX = 0;
    int posY = 0;


    for(int row=0; row < ROW_ENEMY_MATRIX; row++)
    {
        posX = 0;
        posY += 75;
        
        for(int column=0; column < COLUMNS_ENEMY_MATRIX; column++)
        {
            posX += 60;

            Enemy* newEnemy = (Enemy*) malloc(sizeof(Enemy));
            newEnemy->posX = posX;
            newEnemy->posY = posY;
            newEnemy->isActive = 1; //Cambiar a False
            newEnemy->dir = 1;
            newEnemy->texture = loadTexture(CRAB_SPRITE_PATH);


            enemyMatrix[row][column] = newEnemy;

        } 

    }

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

        
    }



}



void createSpacecraft()
{

    spacecraft = (Spacecraft*) malloc(sizeof(Spacecraft));
    spacecraft->posX = 0;
    spacecraft->posY = 100;
    spacecraft->texture = loadTexture(SPACECRAFT_SPRITE_PATH);



}
