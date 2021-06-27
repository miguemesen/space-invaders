

#include "bullet.h"






Bullet* initBulletList() //Inicializa la lista 
{

    return NULL;
}




void moveBulletsPlayer() //Recorre la lista de balas del jugador para moverlas
{

    if (bulletPlayer != NULL)
    {
  
        bulletPlayer->posY -= BULLET_MOVE; //Actualiza la posicion 
        //sendMoveBulletPlayerCommand(bulletPlayer->posX, bulletPlayer->posY);

    }


}


void moveBulletsEnemy() //Recorre la lista de los enemigos para moverlas
{

    if (bulletEnemy != NULL)
    {

    
        bulletEnemy->posY += BULLET_MOVE; //Actualiza la posicion 
        //sendMoveBulletEnemyCommand(bulletEnemy->posX, bulletEnemy->posY);
       

    }

}



void moveBullets()
{


    moveBulletsPlayer();
    moveBulletsEnemy();


}

void updateBulletPlayer(int posX, int posY, int isActive)
{

  
    bulletPlayer->isActive = isActive; 
    bulletPlayer->posX = posX; 
    bulletPlayer->posY = posY;





}


void updateBulletEnemy(int posX, int posY, int isActive)
{

   

        
    bulletEnemy->isActive = isActive;
    bulletEnemy->posX = posX; 
    bulletEnemy->posY = posY;


}



void createBulletPlayer()
{

        bulletPlayer = (Bullet*) malloc(sizeof(Bullet));
        bulletPlayer->posX = 0;
        bulletPlayer->posY = 0;
        bulletPlayer->isActive = 0;
        bulletPlayer->texture = loadTexture(BULLET_SPRITE_PATH);
        bulletPlayer->currentTexture = bulletPlayer->texture;
    
}



void createBulletEnemy()
{

        bulletEnemy = (Bullet*) malloc(sizeof(Bullet));
        bulletEnemy->posX = 0;
        bulletEnemy->posY = 0;
        bulletEnemy->isActive = 0;
        bulletEnemy->texture = loadTexture(BULLET_SPRITE_PATH);
        bulletEnemy->currentTexture = bulletEnemy->texture;


}




