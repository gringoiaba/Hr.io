#include "World.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void updateWorld(World *w, float deltaTime) {
    respawnEnemies(w);
    respawnFoods(w);
    updateEnemies(w, deltaTime);
    checkCollisions(w);
    checkFoods(w);
}

// Checks if circles are being eaten,
// kills them and increases radius
void checkCollisions(World *w) {
    int i, j;

    // Checks for player eating the enemies
    if (w->player.isAlive) {
        for (i = 0; i < NUM_ENEMIES; i++) {
            if (w->enemies[i].ball.isAlive && isInside(w->enemies[i].ball.position, w->player)) {
                printf("O player comeu o inimigo %d!\n", i);
                killEnemy(w, &w->player, -1, &w->enemies[i], i);
            }
        }
    }

    // Check for enemies eating themselves and/or the player
    for (i = 0; i < NUM_ENEMIES; i++) {
        if (!w->enemies[i].ball.isAlive) {
            continue;
        }

        for (j = 0; j < NUM_ENEMIES; j++) {
            if (i == j) {
                continue;
            }

            // If enemy i eats enemy j...
            if (w->enemies[j].ball.isAlive && isInside(w->enemies[j].ball.position, w->enemies[i].ball)) {
                printf("O inimigo %d comeu o inimigo %d!\n", i, j);
                killEnemy(w,
                          &w->enemies[i].ball,
                          i,
                          &w->enemies[j],
                          j);
            }

        }
        if (w->player.isAlive && isInside(w->player.position, w->enemies[i].ball)) {
            printf("O inimigo %d comeu o player!\n", i);
            killPlayer(w, &w->enemies[i], i);
        }


    }

}

// Checks for foods being eaten
void checkFoods (World *w) {
    int i, j;

    if (w->player.isAlive) {
        for (i = 0; i < NUM_FOOD; i++) {
            if (w->foods[i].isAlive && isInside(w->foods[i].position, w->player)) {
                printf("O player comeu a frutinha %d!\n", i);
                w->foods[i].isAlive = 0;
                w->player.radius = newRadius(w->player, w->foods[i]);
            }
        }
    }

    for (i = 0; i < NUM_ENEMIES; i++) {
        if (!w->enemies[i].ball.isAlive) {
            continue;
        }

        for (j = 0; j < NUM_FOOD; j++) {

            if (w->foods[j].isAlive && isInside(w->foods[j].position, w->enemies[i].ball)) {
                w->foods[j].isAlive = 0;
                printf("O inimigo %d comeu a frutinha %d!\n", i, j);
                w->enemies[i].ball.radius = newRadius(w->enemies[i].ball, w->foods[j]);
            }
        }
    }


}

void printWorld(World w) {
    int i;

    printf("player: ");
    printBall(w.player);

    printf("\n");
    for (i = 0; i < NUM_ENEMIES; i++) {
        if (w.enemies[i].ball.isAlive) {
            printf("Enemy %d: ", i);
            printBall(w.enemies[i].ball);
            printf("\n  MoveType: %s ", enemyMoveTypeToString(w.enemies[i].moveType));
            printf("\n  ElementalType: %s", enemyElementalTypeToString(w.enemies[i].elementalType));
            printf("\n");
        }
    }
    for (i = 0; i < NUM_FOOD; i++) {
        if (w.foods[i].isAlive) {
            printf("Food %d: ", i);
            printBall(w.foods[i]);
            printf("\n");
        }
    }
}

void respawnFoods(World *w) {
    int i;
    for (i = 0; i < NUM_FOOD; i++) {
        if (!w->foods[i].isAlive) {
            w->foods[i].isAlive = 1;
            w->foods[i].position = randomPosition(WORLD_LEFT_BOUNDARY,
                                                  WORLD_RIGHT_BOUNDARY,
                                                  WORLD_TOP_BOUNDARY,
                                                  WORLD_BOTTOM_BOUNDARY);
            w->foods[i].radius = FOOD_RADIUS;
        }
    }
}

// Respawns enemies
// TODO: implement random traits
void respawnEnemies(World *w) {
    int i;
    for (i = 0; i < NUM_ENEMIES; i++) {
        if (!w->enemies[i].ball.isAlive) {
            w->enemies[i].ball.isAlive = 1;
            w->enemies[i].ball.position = randomPosition(WORLD_LEFT_BOUNDARY,
                                                         WORLD_RIGHT_BOUNDARY,
                                                         WORLD_TOP_BOUNDARY,
                                                         WORLD_BOTTOM_BOUNDARY);
            w->enemies[i].moveType = rand()%4;
            w->enemies[i].movingDirection = randomRadian();
            w->enemies[i].timeEllapsedSinceLastSwitch = 0;
            w->enemies[i].elementalType = rand()%3;
            w->enemies[i].ball.radius = BASE_RADIUS;
        }
    }
}

void updateEnemies(World *w, float delta) {
    int i;
    for (i = 0; i < NUM_ENEMIES; i++) {
        updateEnemy(&w->enemies[i], *w, i, delta);
    }
}

void killPlayer(World* w, Enemy* killer, int index) {
    w->player.isAlive = 0;
    killer->ball.radius = newRadius(killer->ball, w->player);
}
