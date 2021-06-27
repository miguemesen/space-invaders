

#include "game/game.h"
#include "socket/socketClient.h"
#include "time.h"
#include "socket/serializer.h"
void menu()
{
    connectionSuccessful = 1;
    printf("Bienvenido Space Invaders \n");
    int reply;
    printf("Ingrese: \n\n");
    printf("1. Jugar una partida \n");
    printf("2. Observar una partida \n");
    scanf("%d", &reply);


    int id;
    if(reply == 1) {

        printf("Ingrese la partida que desea jugar \n");
        printf("1. Partida 1 \n");
        printf("2. Partida 2 \n");
        scanf("%d", &id);
        sendNewGameCommand(id);
        sleep(2);
        if(connectionSuccessful){
            createWindow(id, 0);
        }else{
            printf("Lo siento la partida está ocupada, vuelva a intentarlo \n");
            menu();
        }



    }

    if(reply == 2){
        printf("Ingrese la partida que desea observar \n");
        printf("1. Partida 1 \n");
        printf("2. Partida 2 \n");
        scanf("%d", &id);
        sendObserverCommand(id);
        sleep(2);
        if(connectionSuccessful){
            createWindow(id, 1);
        }else{
            printf("Lo siento, la cantidad de observadores es máxima, vuelva a intentarlo \n");
            menu();
        }

    }
}



int main()

{

    srand(time(0));



    initClient();

    //createWindow(1,0);
    menu();
    


    




    
}