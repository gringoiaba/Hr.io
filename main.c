#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#include "Structs/Enemy.h"
#include "Structs/Circle.h"
#include "Structs/Vec2.h"
#include "Structs/World.h"

#include "graphics.h"

int main(void) {
    srand(time(NULL));

    Ball b = {
        .position = { 0, 0 },
        .isAlive = 1,
        .radius = BASE_RADIUS,
        .poisonTimeRemaining = 0
    };

    World w = {
        .player = b,
        .state = PLAYING,
    };

    initGraphics();

    while (isGraphicsRunning())
    {
        updateWorld(&w, 1/(float)60);
        drawWorld(w);
    }

    endGraphics();

    return 0;
}


