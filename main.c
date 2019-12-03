#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <string.h>

#include "Structs/Enemy.h"
#include "Structs/Circle.h"
#include "Structs/Vec2.h"
#include "Structs/World.h"
#include "Structs/PlayerScore.h"

#include "graphics.h"

int main(void) {
    srand(time(NULL));

    World w = newWorld(NULL); // Creates a new world from scratch

    loadScore(); // Loads the high scores from previous games
    initGraphics(); // Initiate the graphics

    while (isGraphicsRunning()) { // While the game is running

        updateWorld(&w, 1/(float)60); // Updates the world
        drawWorld(w); // Draws the world
    }
    saveScore(); // Saves the player score
    endGraphics(); // Ends the graphics

    return 0;
}


