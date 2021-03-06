

#include "socketClient.h"


void initClient()
{
    client = createClient();
    pthread_create(&pthread_send, NULL, &listen_socket, NULL);
}


int createClient()
{
    int sock = socket(AF_INET , SOCK_STREAM , 0);
    if (sock == -1){
        printf("Could not create socket");
    }


    server.sin_addr.s_addr = inet_addr(IP);
    server.sin_family = AF_INET;
    server.sin_port = htons(PORT);

    // connect to remote printf("Se crea una nueva partida");server
    if (connect(sock , (struct sockaddr *)&server , sizeof(server)) != 0){
        perror("connect failed. Error");
        exit(1);
    }

    return sock;

}


_Noreturn void *listen_socket(){

    while(1){

        if (read(client, server_reply, 2000) > 0) {
            cJSON *serverReplyCommand = cJSON_Parse(server_reply);
            char* command = cJSON_GetObjectItem(serverReplyCommand, "command")->valuestring;
            //printf("command : %s \n", command);


            if(strcmp(command, "startGame") == 0)
            {

                startGame();

            }


            else if (strcmp(command, "connectionRejected") == 0)
            {

                connectionRefused();
                
            }

            else if (strcmp(command, "movePlayer") == 0)
            {


                int posX = cJSON_GetObjectItem(serverReplyCommand, "posX")->valueint;
                int posY = cJSON_GetObjectItem(serverReplyCommand, "posY")->valueint;
                updateShipPosition(posX, posY);


            }

            else if (strcmp(command, "updateGameState") == 0)
            {

        
                cJSON* bulletEnemyJSON = cJSON_GetObjectItem(serverReplyCommand, "bulletEnemy");
                int bulletEnemyPosX = cJSON_GetObjectItem(bulletEnemyJSON, "posX")->valueint;
                int bulletEnemyPosY = cJSON_GetObjectItem(bulletEnemyJSON, "posY")->valueint;
                int bulletEnemyIsActive = cJSON_GetObjectItem(bulletEnemyJSON, "isActive")->valueint;
                updateBulletEnemy(bulletEnemyPosX, bulletEnemyPosY, bulletEnemyIsActive);
                


                cJSON* bulletPlayerJSON = cJSON_GetObjectItem(serverReplyCommand, "bulletPlayer");
                int bulletPlayerPosX = cJSON_GetObjectItem(bulletPlayerJSON, "posX")->valueint;
                int bulletPlayerPosY = cJSON_GetObjectItem(bulletPlayerJSON, "posY")->valueint;
                int bulletPlayerIsActive = cJSON_GetObjectItem(bulletPlayerJSON, "isActive")->valueint;
                updateBulletPlayer(bulletPlayerPosX, bulletPlayerPosY, bulletPlayerIsActive);



                cJSON* bulletEnemiesJSON = cJSON_GetObjectItem(serverReplyCommand, "enemies");
                updateEnemiesPosition(bulletEnemiesJSON);

                cJSON* spacecraftJSON = cJSON_GetObjectItem(serverReplyCommand, "spacecraft");
                int spacecraftPosX = cJSON_GetObjectItem(spacecraftJSON , "posX")->valueint;
                int spacecraftPosY = cJSON_GetObjectItem(spacecraftJSON , "posY")->valueint;
                int spacecraftIsActive = cJSON_GetObjectItem(spacecraftJSON , "isActive")->valueint;
                updateSpaceCraft(spacecraftPosX, spacecraftPosY,spacecraftIsActive);


                cJSON* bunkersJSON = cJSON_GetObjectItem(serverReplyCommand, "bunkers");
                updateBunkers(bunkersJSON);

            }


    

            else if (strcmp(command, "putEnemies")== 0)
            {
            
                cJSON *enemies = cJSON_GetObjectItem(serverReplyCommand, "enemies");
                putEnemy(enemies);
            }




            else if (strcmp(command, "removeEnemies")==0)
            {


    
                cJSON* enemies = cJSON_GetObjectItem(serverReplyCommand, "enemies");
                deleteEnemy(enemies);
                

    
            }

            else if (strcmp(command, "updateScore") == 0)
            {


                int newScore = cJSON_GetObjectItem(serverReplyCommand, "score")->valueint;
                updateScore(newScore);


            }

            else if(strcmp(command, "updateLives") == 0)
            {

                int newLives = cJSON_GetObjectItem(serverReplyCommand, "lives")->valueint;
                updateLives(newLives);

            }


            else if(strcmp(command, "gameOver") == 0)
            {


    
                int score = cJSON_GetObjectItem(serverReplyCommand, "score")->valueint;
                int lives = cJSON_GetObjectItem(serverReplyCommand, "lives")->valueint;
                gameOver(score, lives);



            }







        }
        
    }
 }


void sendServer(char* info){

    char sendBuff[2500];
    bzero(sendBuff, sizeof(sendBuff));
    strcpy(sendBuff, info);
    write(client, info, strlen(info));
    char *line_delimeter = "\n";
    write(client, line_delimeter, strlen(line_delimeter));
}



void connectionRefused()
{
    connectionSuccessful = 0;
}
