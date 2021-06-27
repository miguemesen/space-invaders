

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
            printf("xdd %s",server_reply);
            cJSON *serverReplyCommand = cJSON_Parse(server_reply);
            char* command = cJSON_GetObjectItem(serverReplyCommand, "command")->valuestring;


            if(strcmp(command, "startGame") == 0)
            {

                startGame();

            }


            else if (strcmp(command, "connectionRejected") == 0)
            {

                connectionRefused();
                
            }


            else if (strcmp(command, "moveEnemies") == 0)
            {

                cJSON *enemies = cJSON_GetObjectItem(serverReplyCommand, "enemies");

                updateEnemiesPosition(enemies);

            }


            else if (strcmp(command, "updateBunkers") == 0)
            {

                cJSON *bunkers = cJSON_GetObjectItem(serverReplyCommand, "bunkers");

                void updateBunkers(cJSON* bunkers);

            }

            else if (strcmp(command, "moveBulletPlayer") == 0)
            {

                int posX = cJSON_GetObjectItem(serverReplyCommand, "posX")->valueint;
                int posY = cJSON_GetObjectItem(serverReplyCommand, "posY")->valueint;
                updateBulletPlayer(posX, posY);

            }

            else if (strcmp(command, "moveBulletEnemy") == 0)
            {

                int posX = cJSON_GetObjectItem(serverReplyCommand, "posX")->valueint;
                int posY = cJSON_GetObjectItem(serverReplyCommand, "posY")->valueint;
                updateBulletEnemy(posX, posY);


            }

            else if (strcmp(command, "putEnemy"))
            {


                char* type = cJSON_GetObjectItem(serverReplyCommand, "type")->valuestring;
                int enemyId = cJSON_GetObjectItem(serverReplyCommand, "enemyId")->valueint;
                void putEnemy(char* type, int enemyId);
            }


            else if (strcmp(command, "moveSpacecraft"))
            {

                int posX = cJSON_GetObjectItem(serverReplyCommand, "posX")->valueint;
                int posY = cJSON_GetObjectItem(serverReplyCommand, "posY")->valueint;
            

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
