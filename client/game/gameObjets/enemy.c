

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

    if (enemyMatrix[0][8]->posX == WINDOW_MAX_WIDTH)
    {
        checkBoundariesAux(LEFT);
    }

    if (enemyMatrix[2][0]->posY >= ship->posY)
    {

        sendEnemyImpactCommand();

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
            currentEnemy->isActive = cJSON_GetObjectItem(enemy, "isActive")->valueint;
            char* enemyType = cJSON_GetObjectItem(enemy, "type")->valuestring;

            if(currentEnemy->type == NULL && enemyType != NULL)
            {
                setEnemyTexture(enemyType, currentEnemy);
            }
        
        }

        temp += 10;
    }

    printf("----------------------------------- \n");

}


void putEnemy(cJSON* enemies)
{

    for(int i=0; i < cJSON_GetArraySize(enemies); i++)
    {

        cJSON * enemyJSON = cJSON_GetArrayItem(enemies, i);


        int enemyId = cJSON_GetObjectItem(enemyJSON, "enemyId")->valueint;
        char* enemyType = cJSON_GetObjectItem(enemyJSON, "enemyType")->valuestring;

        Enemy* enemy = getEnemyByID(enemyId);
        setEnemyTexture(enemyType, enemy);
        enemy->type = enemyType;
        enemy->isActive = 1;
    }

}



void setEnemyTexture(char* enemyType, Enemy* enemy)
{
    if (strcmp(enemyType, "crab") == 0)
        {
            enemy->texture = loadTexture(CRAB_SPRITE_PATH);
        }

        else if (strcmp(enemyType, "octo") == 0)
        {
            enemy->texture = loadTexture(OCTO_SPRITE_PATH);
        }
        else if (strcmp(enemyType, "squid") == 0)
        {
            enemy->texture = loadTexture(SQUID_SPRITE_PATH);
        }

}



void deleteEnemy(cJSON* enemies)
{


    for(int i=0; i < cJSON_GetArraySize(enemies); i++)
    {

        cJSON * enemy = cJSON_GetArrayItem(enemies, i);
        int id = cJSON_GetObjectItem(enemy, "enemyId")->valueint;

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

    return NULL;


}


void moveEnemies()
{


    for(int row=0; row < ROW_ENEMY_MATRIX; row++)
    {

        for(int column=0; column < COLUMNS_ENEMY_MATRIX; column++)
        {

            Enemy* enemy = enemyMatrix[row][column];

            enemy->posX += 5*enemy->dir;

        }
    
    }

    checkBoundaries();
 
}


void setDefaultEnemyValues()
{

    int posX = 0;
    int posY = 70;


    for(int row=0; row < ROW_ENEMY_MATRIX; row++)
    {
        posX = 0;
        posY += 40;
        
        for(int column=0; column < COLUMNS_ENEMY_MATRIX; column++)
        {
            posX += 60;

            Enemy* enemy = enemyMatrix[row][column];
            enemy->posX = posX;
            enemy->posY = posY;
            enemy->isActive = 1;
            enemy->dir = 1;
    
    
        } 
    }
}

 
int enemyLeft()

{

    for(int row=0; row < ROW_ENEMY_MATRIX; row++)
    {
       
         for(int column=0; column < COLUMNS_ENEMY_MATRIX; column++)
        {
        
            Enemy* enemy = enemyMatrix[row][column];
            

            if (enemy->isActive)
            {
                return 1;
            }

        } 
    }


    return 0;


}


cJSON* getActiveEnemies()
{


    cJSON* arr = cJSON_CreateArray();
  
    for(int row=0; row < ROW_ENEMY_MATRIX; row++)
    {

        for(int column=0; column < COLUMNS_ENEMY_MATRIX; column++)
        {

            Enemy* currentEnemy = enemyMatrix[row][column];

            if (currentEnemy->isActive)
            {

                printf("ENTRAAA \n");
                cJSON *root = cJSON_CreateObject();
                cJSON_AddNumberToObject(root, "posX", currentEnemy->posX);
                cJSON_AddNumberToObject(root, "posY", currentEnemy->posY);
                cJSON_AddItemToArray(arr, root);

            }
              
        }

    }

    return arr;




}









