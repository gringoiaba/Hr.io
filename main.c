#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#include "Structs/Enemy.h"
#include "Structs/Circle.h"
#include "Structs/Vector2.h"
#include "Structs/World.h"

int main(void) {
    int i = 0;
    srand(time(NULL));

    Ball b = {
        position: { 0, 0 },
        isAlive: 1,
        radius: BASE_RADIUS
    };

    World w = {
        .player = b,
    };

    for (i = 0; i < 20; i++) {
        updateWorld(&w, 1/(float)10);
        printWorld(w);

        getchar();
        system("cls");
    }

    return 0;
}
