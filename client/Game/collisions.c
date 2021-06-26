

#include "collisions.h"




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
    }

}



int shipCollision(int posX, int posY)
{

    if(bulletEnemy != NULL)
    {

        if(posX >= ship->posX && posX <= ship->posX + 40 && posY >= ship->posY && posY <= ship->posY + 40)
        {

            return 1;

        } 

        return 0;

    }

    return 0;

}

int bunkerCollision(int posX, int posY)
{

    
    Bunker* current = bunkerList;

    while(current != NULL)
    {


        if(posX >= current->posX && posX <= current->posX + 90 && posY >= current->posY && posY <= current->posY + 70)
        {

            updateBunkerHealth(&current);
            return 1;

        }

        current = current->next;
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
                    return 1;
                }
            }


        }
    }

    return 0;
}