


#include "bunker.h"


Bunker* initBunkerList()
{
    return NULL;
}

void updateBunkerHealth(Bunker** bunker)
{
    if((*bunker)->isActive)
    {

        (*bunker)->health -= 20;

        int health = (*bunker)->health;

        if (health == 80)
        {

            (*bunker)->currentTexture = (*bunker)->texture80Health;

        }

        else if (health == 60)
        {

            (*bunker)->currentTexture = (*bunker)->texture60Health;

        }

        else if (health == 40)
        {

            (*bunker)->currentTexture = (*bunker)->texture40Health;

        }

        else if (health == 20)
        {

            (*bunker)->currentTexture = (*bunker)->texture20Health;

        }else 
        {
            (*bunker)->isActive = 0;
        }

        sendUpdateBunkerCommand(bunkerList);
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
        updateBunkerHealth(&bunker);



    }




}

