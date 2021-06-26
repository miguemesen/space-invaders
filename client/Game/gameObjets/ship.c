


#include "ship.h"

void moveShip(int dir)
{

    if (dir == LEFT) {

        if (ship->posX != WINDOW_MIN_WIDTH)
        {

            ship->posX -= SHIP_MOVE;

        }

        
    }

    if (dir == RIGHT) {

        if (ship->posX != WINDOW_MAX_WIDTH) 
        {

            ship->posX += SHIP_MOVE;


        }

        
    }

}