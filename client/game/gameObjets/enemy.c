

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



void deleteEnemy(cJSON* enemies)
{


    for(int i=0; i < cJSON_GetArraySize(enemies); i++)
    {

        cJSON * enemy = cJSON_GetArrayItem(enemies, i);
        int id = cJSON_GetObjectItem(enemy, "id")->valueint;

        Enemy* currentEnemy = getEnemyByID(id);

        currentEnemy->isActive = 0;
     


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
    //sendMoveEnemiesCommand(enemyMatrix);


}



