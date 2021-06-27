#include "spacecraft.h"



int shouldMove()
{

    if (!spacecraft->isActive)
    {

        currentTime = (double) clock();
        time_ += (currentTime - prevTime) / CLOCKS_PER_SEC;
    
        if (time_ >= 0.7)
        {

            spacecraft->isActive = 1;
            return 1;

        }

        return 0;

    }
    return 1;
        
}



void moveSpacecraft()
{

    if (shouldMove())
    {


        spacecraft->posX -= 5;
    
        if (spacecraft->posX <= WINDOW_MIN_WIDTH)
        {

            killSpacecraft();

        }

        //sendMoveSpacecraftCommand(spacecraft->posX, spacecraft->posY);
        prevTime = (double) clock();

    }



    prevTime = (double) clock();

 
}



void updateSpaceCraft(int posX, int posY, int isActive)
{

    spacecraft->posX = posX;
    spacecraft->posY = posY;
    spacecraft->isActive = isActive;

    if (spacecraft->posX <= WINDOW_MIN_WIDTH)
    {

        killSpacecraft();

    }



}



void killSpacecraft()
{
    spacecraft->isActive = 0;
    time_ = 0;
    spacecraft->posX = WINDOW_MAX_WIDTH;

}