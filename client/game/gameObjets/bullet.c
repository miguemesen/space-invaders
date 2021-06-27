

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
        sendMoveBulletPlayerCommand(bulletPlayer->posX, bulletPlayer->posY);

    }


}


void moveBulletsEnemy() //Recorre la lista de los enemigos para moverlas
{

    if (bulletEnemy != NULL)
    {

    
        bulletEnemy->posY += BULLET_MOVE; //Actualiza la posicion 
        sendMoveBulletEnemyCommand(bulletEnemy->posX, bulletEnemy->posY);
       

    }

}



void moveBullets()
{


    moveBulletsPlayer();
    moveBulletsEnemy();


}

void updateBulletPlayer(int posX, int posY)
{

    if (bulletPlayer != NULL)
    {

        bulletPlayer->posX; 
        bulletPlayer->posY;

    }



}


void updateBulletEnemy(int posX, int posY)
{

      if (bulletEnemy != NULL)
    {

        bulletEnemy->posX; 
        bulletEnemy->posY;

    }



}







