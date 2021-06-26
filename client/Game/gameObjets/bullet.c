

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

        if (bulletPlayer->posY <= WINDOW_MIN_HEIGHT) //Verifica sise encuentra en el limite de la pantalla  
        {

            free(bulletPlayer);
            bulletPlayer = NULL;
        

        }
    }


}


void moveBulletsEnemy() //Recorre la lista de los enemigos para moverlas
{

    if (bulletEnemy != NULL)
    {

    
        bulletEnemy->posY += BULLET_MOVE; //Actualiza la posicion 
       

            if (bulletEnemy->posY >= WINDOW_MAX_HEIGHT) //Verifica si la bala se encuentra en el limite de la pantalla
            {

                free(bulletEnemy);
                bulletEnemy = NULL;
            }
    }

}



void moveBullets()
{


    moveBulletsPlayer();
    moveBulletsEnemy();


}







