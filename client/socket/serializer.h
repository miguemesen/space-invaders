

#ifndef SERIALIZER_H
#define SERIALIZER_H


#include "cJson.h"
#include "socketClient.h"
#include "../game/game.h"
#include "../constants.h"


void sendNewGameCommand(int id);

void sendObserverCommand(int id);

void sendMovePlayerCommand(int posX, int posY);

void sendAttackedCommand();

void sendKillEnemyCommand(int enemyId, char* type);

void sendKillSpacecraftCommand();

void sendWinCommand();

void sendEnemyImpactCommand();

void sendGameOverCommand();

cJSON* bunkerState();

cJSON* spacecraftState();

cJSON* bulletPlayerState();

cJSON* bulletEnemyState();

cJSON* enemiesState();

void sendUpdateGameStateCommand();



#endif //PROJECT_SERIALIZER_H
