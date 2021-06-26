


#include "bunker.h"


Bunker* initBunkerList()
{
    return NULL;
}

void updateBunkerHealth(Bunker** bunker)
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
        deleteBunker(&bunkerList, *bunker);
    }
  

}



void addBunker(Bunker** list, Bunker* bunker)
{





    if (*list == NULL)
    {   

        bunker->next = NULL;
        *list = bunker;
        return;
    
     
    
    } else 

    {

        Bunker* current = *list; 

        while (current->next != NULL)
        {
          
            current = current->next;

        }

        current->next = bunker;

    }
}
  


void deleteBunker(Bunker** list, Bunker* bunker)
{
    Bunker* current = *list;
    Bunker* prev = *list; 

    if (current == bunker){

        *list = current->next;
        free(current);
    }


    current = current->next;

    while(current != NULL)
    {

        if (current == bunker)
        {
            prev->next = current->next;
            free(current);
            break;

        }

        prev = current;
        current = current->next;
        
    }


}
