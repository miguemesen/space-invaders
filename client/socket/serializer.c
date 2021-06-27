
#include "serializer.h"





void sendNewGameCommand(int id)
{
    cJSON *root;
    root = cJSON_CreateObject();
    cJSON_AddStringToObject(root, "command", "newGame");
    cJSON_AddNumberToObject(root, "gameId", id);
    char* command = cJSON_PrintUnformatted(root);
    sendServer(command);
    
}


void sendObserverCommand(int id)
{
    cJSON *root;
    root = cJSON_CreateObject();
    cJSON_AddStringToObject(root, "command", "observer");
    cJSON_AddNumberToObject(root, "gameId", id);
    char* command = cJSON_PrintUnformatted(root);
    sendServer(command);
    
}


void sendMovePlayerCommand(int posX, int posY)
{
    cJSON *root;
    root = cJSON_CreateObject();
    cJSON_AddStringToObject(root, "command", "movePlayer");
    cJSON_AddNumberToObject(root, "gameId", gameId);
    cJSON_AddNumberToObject(root, "posX", posX);
    cJSON_AddNumberToObject(root, "posY", posY);
    char* command = cJSON_PrintUnformatted(root);
    sendServer(command);

}


void sendUpdateGameStateCommand()
{

    cJSON* root = cJSON_CreateObject();
    cJSON* bulletEnemyStateJSON = bulletEnemyState();
    cJSON* bulletPlayerStateJSON =  bulletPlayerState();
    cJSON* enemiesStateJSON = enemiesState();
    cJSON* spacecraftJSON = spacecraftState();
    cJSON_AddStringToObject(root, "command", "updateGameState");
    cJSON_AddNumberToObject(root, "gameId", gameId);
    cJSON_AddItemToObject(root, "bulletEnemy", bulletEnemyStateJSON);
    cJSON_AddItemToObject(root, "bulletPlayer",bulletPlayerStateJSON);
    cJSON_AddItemToObject(root, "enemies",enemiesStateJSON);
    cJSON_AddItemToObject(root, "spacecraft",spacecraftJSON);
    char* command = cJSON_PrintUnformatted(root);
    sendServer(command);
  

}





void sendAttakedCommand()
{

    cJSON* root = cJSON_CreateObject();
    cJSON_AddStringToObject(root, "command", "attaked");
    cJSON_AddNumberToObject(root, "gameId", gameId);
    char* command = cJSON_PrintUnformatted(root);
    sendServer(command);
   



}

void sendKillEnemyCommand(int enemyId, char* type)
{
    cJSON* root = cJSON_CreateObject();
    cJSON_AddStringToObject(root, "command", "killEnemy");
    cJSON_AddNumberToObject(root, "gameId", gameId);
    cJSON_AddNumberToObject(root, "id", enemyId);
    cJSON_AddStringToObject(root, "type", type);
    char* command = cJSON_PrintUnformatted(root);
    sendServer(command);

}



void sendUpdateBunkerCommand(Bunker* bunkerList[NUMBER_OF_BUNKERS])
{

    cJSON* arr = cJSON_CreateArray();
  
    for(int i=0; i < NUMBER_OF_BUNKERS; i++)
    {

        Bunker* currentBunker = bunkerList[i];

        cJSON *root = cJSON_CreateObject();
        cJSON_AddNumberToObject(root, "health", currentBunker->health);
        cJSON_AddNumberToObject(root, "isActive", currentBunker->isActive);
        cJSON_AddItemToArray(arr, root);

    }

    cJSON * command = cJSON_CreateObject();
    cJSON_AddStringToObject(command, "command", "updateBunkers");
    cJSON_AddNumberToObject(command, "gameId", gameId);
    cJSON_AddItemToObject(command,"bunkers", arr);
    char* command_ = cJSON_PrintUnformatted(command);
    sendServer(command_);
    printf("%s \n", command_);


}



cJSON* spacecraftState()
{

    cJSON* root = cJSON_CreateObject();
    cJSON_AddNumberToObject(root, "posX", spacecraft->posX);
    cJSON_AddNumberToObject(root, "posY", spacecraft->posY);
    cJSON_AddNumberToObject(root, "isActive", spacecraft->isActive);
    return root;


}



cJSON* bulletEnemyState()
{

    cJSON* root = cJSON_CreateObject();
    cJSON_AddNumberToObject(root, "posX", bulletEnemy->posX);
    cJSON_AddNumberToObject(root, "posY", bulletEnemy->posY);
    cJSON_AddNumberToObject(root, "isActive", bulletEnemy->isActive);
    return root;




}

cJSON* bulletPlayerState()
{

    cJSON* root = cJSON_CreateObject();
    cJSON_AddNumberToObject(root, "posX", bulletPlayer->posX);
    cJSON_AddNumberToObject(root, "posY", bulletPlayer->posY);
    cJSON_AddNumberToObject(root, "isActive", bulletPlayer->isActive);
    return root;
    



}



cJSON* enemiesState()
{

    cJSON* arr = cJSON_CreateArray();
  
    for(int row=0; row < ROW_ENEMY_MATRIX; row++)
    {

        for(int column=0; column < COLUMNS_ENEMY_MATRIX; column++)
        {

            Enemy* currentEnemy = enemyMatrix[row][column];

            cJSON *root = cJSON_CreateObject();
            cJSON_AddNumberToObject(root, "posX", currentEnemy->posX);
            cJSON_AddNumberToObject(root, "posY", currentEnemy->posY);
            cJSON_AddNumberToObject(root, "isActive", currentEnemy->isActive);
            cJSON_AddItemToArray(arr, root);

        }

    }

    return arr;



}