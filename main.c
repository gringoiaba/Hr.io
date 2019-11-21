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

    World w = newWorld();

    initGraphics();

    while (isGraphicsRunning())
    {
        updateWorld(&w, 1/(float)60);
        drawWorld(w);
    }

    endGraphics();

    return 0;
}


