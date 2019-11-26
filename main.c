#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#include "Structs/Enemy.h"
#include "Structs/Circle.h"
#include "Structs/Vec2.h"
#include "Structs/World.h"
#include "Structs/PlayerScore.h"

#include "graphics.h"

int main(void) {
    srand(time(NULL));

    World w = newWorld();

    PlayerScore scores[HIGHSCORE_SIZE] = {0};

    w.state = MAIN_MENU;

    initGraphics();

    while (isGraphicsRunning()) {

        updateWorld(&w, 1/(float)60, scores);
        drawWorld(w);
    }

    endGraphics();

    return 0;
}


