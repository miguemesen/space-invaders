


#include "ship.h"

void moveShip(int dir)
{

    if (dir == LEFT) {

        if (ship->posX >= WINDOW_MIN_WIDTH)
        {

            ship->posX -= SHIP_MOVE;
            sendMovePlayerCommand(ship->posX, ship->posY);
        
        }

        
    }

    else if (dir == RIGHT) {

        if (ship->posX <= WINDOW_MAX_WIDTH) 
        {

            ship->posX += SHIP_MOVE;
            sendMovePlayerCommand(ship->posX, ship->posY);



        }

        
    }
    

}


void updateScore(int newScore)
{

    ship->score = newScore;


}



void updateLives(int newLives)
{
    ship->lives = newLives;
}


void updateShipPosition(int posX, int posY)
{

    if (ship != NULL)
    {

        ship->posX = posX;
        ship->posY = posY;
    }
}