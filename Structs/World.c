#include "World.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "World.h"
#include "../input.h"

void updateWorld(World *w, float deltaTime) {
    w->elapsedTime += deltaTime;

    respawnEnemies(w);
    respawnFoods(w);

    updateInput(w, deltaTime);

    updateEnemies(w, deltaTime);

    updatePoison(w, deltaTime);

    checkCollisions(w);
    checkFoods(w);

    // Moves everything that is simply too far away from the player
    moveUnused(w);
}

// Checks if circles are being eaten,
// kills them and increases radius
void checkCollisions(World *w) {
    int i, j;

    // Checks for player eating the enemies
    if (w->player.isAlive) {
        for (i = 0; i < NUM_ENEMIES; i++) {
            if (w->enemies[i].ball.isAlive && isInside(w->enemies[i].ball.position, w->player)) {
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
                killEnemy(w,
                          &w->enemies[i].ball,
                          i,
                          &w->enemies[j],
                          j);
            }

        }
        if (w->player.isAlive && isInside(w->player.position, w->enemies[i].ball)) {
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
            printBall(w.enemies[i].ball);
            printf("\n  MoveType: %s ", enemyMoveTypeToString(w.enemies[i].moveType));
            printf("\n  ElementalType: %s", enemyElementalTypeToString(w.enemies[i].elementalType));
            printf("\n");
        }
    }
    for (i = 0; i < NUM_FOOD; i++) {
        if (w.foods[i].isAlive) {
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
            w->foods[i].position = randomPosition(WORLD_LEFT_BOUNDARY + w->player.position.x,
                                                  WORLD_RIGHT_BOUNDARY + w->player.position.x,
                                                  WORLD_TOP_BOUNDARY + w->player.position.y,
                                                  WORLD_BOTTOM_BOUNDARY + w->player.position.y);
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
            w->enemies[i].ball.position = randomPosition(WORLD_LEFT_BOUNDARY + w->player.position.x,
                                                         WORLD_RIGHT_BOUNDARY + w->player.position.x,
                                                         WORLD_TOP_BOUNDARY + w->player.position.y,
                                                         WORLD_BOTTOM_BOUNDARY + w->player.position.y);
            w->enemies[i].moveType = rand()%4;
            w->enemies[i].movingDirection = randomRadian();
            w->enemies[i].timeEllapsedSinceLastSwitch = 0;
            w->enemies[i].elementalType = rand()%3;
            w->enemies[i].ball.radius = BASE_RADIUS;
            w->enemies[i].ball.poisonTimeRemaining = 0;
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

void updatePoison(World *w, float delta) {
    int i;

    for (i = 0; i < NUM_ENEMIES; i++) {
        // If is poisoned...
        if (w->enemies[i].ball.poisonTimeRemaining > 0) {
            Ball* b = &w->enemies[i].ball;

            float area = radiusToArea(b->radius);
            area -= area * 0.1f * delta;

            b->radius = areaToRadius(area);

            b->poisonTimeRemaining -= delta;
        }
    }

    if (w->player.poisonTimeRemaining > 0) {
        Ball* b = &w->player;

        float area = radiusToArea(b->radius);
        // Reduce the area by 1% per second
        area -= area * 0.1f * delta;

        b->radius = areaToRadius(area);

        b->poisonTimeRemaining -= delta;
    }
}

void moveUnused(World* w) {
    int i;

    for (i = 0; i < NUM_ENEMIES; i++) {
        if (distance(w->enemies[i].ball.position, w->player.position) > MAX_PLAYER_DISTANCE) {
            w->enemies[i].ball.isAlive = 0;
        }
    }

    for (i = 0; i < NUM_FOOD; i++) {
        if (distance(w->foods[i].position, w->player.position) > MAX_PLAYER_DISTANCE) {
            w->foods[i].isAlive = 0;
        }
    }
}
