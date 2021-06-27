

#include "enemy.h"


void checkBoundariesAux(int dir)
{

    for(int row=0; row < ROW_ENEMY_MATRIX; row++)
        {

            for(int column=0; column < COLUMNS_ENEMY_MATRIX; column++)
            {

                Enemy* enemy = enemyMatrix[row][column];

                enemy->dir = dir;

                enemy->posY += 25;
            }
    
        }

}


void checkBoundaries()
{

    if (enemyMatrix[0][0]->posX == WINDOW_MIN_WIDTH)
    {

        checkBoundariesAux(RIGHT);
    }

    if (enemyMatrix[2][9]->posX == WINDOW_MAX_WIDTH)
    {
        checkBoundariesAux(LEFT);
    }


    
}


void updateEnemiesPosition(cJSON* enemies)
{

    int temp = 0;

    for(int row=0; row < ROW_ENEMY_MATRIX; row++)
    {

        for(int column=0; column < COLUMNS_ENEMY_MATRIX; column++)
        {

            Enemy* currentEnemy = enemyMatrix[row][column];

            cJSON * enemy = cJSON_GetArrayItem(enemies, column + temp);
            currentEnemy->posX = cJSON_GetObjectItem(enemy, "posX")->valueint;
            currentEnemy->posY = cJSON_GetObjectItem(enemy, "posY")->valueint;
          

        }

        temp += 10;
    
    }







}



Enemy* getEnemyByID(int id)
{

    for(int row=0; row < ROW_ENEMY_MATRIX; row++)
    {

        for(int column=0; column < COLUMNS_ENEMY_MATRIX; column++)
        {

            Enemy* enemy = enemyMatrix[row][column];

            if (enemy->id == id)
            {
                return enemy;
            }

        }
    
    }


}


void moveEnemies()
{


    for(int row=0; row < ROW_ENEMY_MATRIX; row++)
    {

        for(int column=0; column < COLUMNS_ENEMY_MATRIX; column++)
        {

            Enemy* enemy = enemyMatrix[row][column];

            enemy->posX += 1*enemy->dir;

        }
    
    }

    checkBoundaries();
    sendMoveEnemiesCommand(enemyMatrix);


}



