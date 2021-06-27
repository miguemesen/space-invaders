


#include "bunker.h"


Bunker* initBunkerList()
{
    return NULL;
}

void updateBunkerHealth(Bunker** bunker)
{
    if((*bunker)->isActive)
    {




        int health = (*bunker)->health;


        if (health == 100){

            return;
        }

        if (health == 80)
        {

            (*bunker)->currentTexture = (*bunker)->texture80Health;
            return;

        }

        else if (health == 60)
        {
         
            (*bunker)->currentTexture = (*bunker)->texture60Health;
            return;

        }

        else if (health == 40)
        {

            (*bunker)->currentTexture = (*bunker)->texture40Health;
            return;

        }

        else if (health == 20)
        {

            (*bunker)->currentTexture = (*bunker)->texture20Health;
            return;

        }else 
        {
            (*bunker)->isActive = 0;
        }

    }
  
}


void updateBunkers(cJSON* bunkers)
{

 

    for(int i=0; i < NUMBER_OF_BUNKERS; i++)
    {

        Bunker* currentBunker = bunkerList[i];

        cJSON * bunker = cJSON_GetArrayItem(bunkers, i);
        currentBunker->health = cJSON_GetObjectItem(bunker, "health")->valueint;
        currentBunker->isActive = cJSON_GetObjectItem(bunker, "isActive")->valueint;
        updateBunkerHealth(&currentBunker);



    }

    printf("----------------------------\n");




}


