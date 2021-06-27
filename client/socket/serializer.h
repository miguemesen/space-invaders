

#ifndef SERIALIZER_H
#define SERIALIZER_H


#include "cJson.h"
#include "socketClient.h"
#include "../game/game.h"
#include "../constants.h"


void sendNewGameCommand(int id);

void sendObserverCommand(int id);

void sendMovePlayerCommand(int posX, int posY);

void sendMoveBulletPlayerCommand(int posX, int posY);

void sendMoveBulletEnemyCommand(int posX, int posY);

void sendPutBulletPlayerCommand(int posX, int posY);

void sendPutBulletEnemyCommand(int posX, int posY);

void sendAttakedCommand();

void sendKillEnemyCommand(int enemyId, char* type);

void sendUpdateBunkerCommand(Bunker* bunkerList[NUMBER_OF_BUNKERS]);

void sendMoveEnemiesCommand(Enemy* enemyMatrix[ROW_ENEMY_MATRIX][COLUMNS_ENEMY_MATRIX]);

void sendMoveSpacecraftCommand(int posX, int posY);



#endif //PROJECT_SERIALIZER_H
