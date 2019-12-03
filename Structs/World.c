#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#include "World.h"
#include "PlayerScore.h"
#include "../input.h"

void updateWorld(World *w, float deltaTime) {
    // Update the input
    updateInput(w, deltaTime);

    switch (w->state) {
    case MAIN_MENU:
        // In the main menu, the world should update
        // but the player should not be there (hence the lack of a break)
        w->player.isAlive = 0;
    case PLAYING:
        updatePlaying(w, deltaTime);
        break;
    default:
        // World doesn't change when not playing.
        break;
    }
}

// Updates the PLAYING state
void updatePlaying(World* w, float deltaTime) {
    // Increase score
    w->elapsedTime += deltaTime;

    // Respawn dead things
    respawnEnemies(w);
    respawnFoods(w);

    // Update the enemies
    updateEnemies(w, deltaTime);

    // Update the poison
    updatePoison(w, deltaTime);

    // Check for collisions
    checkCollisions(w);
    checkFoods(w);

    // Moves everything that is too far away from the player
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
        // For all foods, if the player is eating it,
        // kill the food and increase the player's radius
        for (i = 0; i < NUM_FOOD; i++) {
            if (w->foods[i].isAlive && isInside(w->foods[i].position, w->player)) {
                w->foods[i].isAlive = 0;
                w->player.radius = newRadius(w->player, w->foods[i]);
            }
        }
    }

    // Do the same for all the enemies
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

// Respawns foods
void respawnFoods(World *w) {
    int i;
    // For all dead foods, revive them
    // and assing it a new random position
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
void respawnEnemies(World *w) {
    int i;
    // For all dead enemies,
    // revive them ang generate random traits
    for (i = 0; i < NUM_ENEMIES; i++) {
        if (!w->enemies[i].ball.isAlive) {
            w->enemies[i].ball.isAlive = 1;
            // Random position not so far from the player
            w->enemies[i].ball.position = randomPosition(WORLD_LEFT_BOUNDARY + w->player.position.x,
                                                         WORLD_RIGHT_BOUNDARY + w->player.position.x,
                                                         WORLD_TOP_BOUNDARY + w->player.position.y,
                                                         WORLD_BOTTOM_BOUNDARY + w->player.position.y);
            w->enemies[i].moveType = rand()%4;
            w->enemies[i].movingDirection = randomRadian();
            w->enemies[i].timeEllapsedSinceLastSwitch = 0;
            w->enemies[i].elementalType = rand()%3;
            w->enemies[i].ball.radius = rand()%40 + BASE_RADIUS;
            w->enemies[i].ball.poisonTimeRemaining = 0;
            strcpy(w->enemies[i].ball.name, randomName());
        }
    }
}

// Update all enemies
void updateEnemies(World *w, float delta) {
    int i;
    for (i = 0; i < NUM_ENEMIES; i++) {
        updateEnemy(&w->enemies[i], *w, i, delta);
    }
}

// Kill the player
void killPlayer(World* w, Enemy* killer, int index) {
    w->player.isAlive = 0;
    // Increase the killer radius
    killer->ball.radius = newRadius(killer->ball, w->player);

    // Create the player score
    PlayerScore score;
    strcpy(score.name, w->player.name);
    score.score = w->elapsedTime;

    // Try inserting it into the
    // highscore board
    insertScore(score, 0);

    // Go to the game over state
    w->state = GAME_OVER;
}

// Updates the poison effect
void updatePoison(World *w, float delta) {
    int i;

    // For all enemies, if it is poisoned,
    // reduce it's area and decrease the remaining
    // poison time
    for (i = 0; i < NUM_ENEMIES; i++) {
        // If is poisoned...
        if (w->enemies[i].ball.poisonTimeRemaining > 0) {
            Ball* b = &w->enemies[i].ball;

            // Decrease the area in 10% per second
            float area = radiusToArea(b->radius);
            area -= area * 0.1f * delta;

            b->radius = areaToRadius(area);

            // Decrease the remaining poison time
            b->poisonTimeRemaining -= delta;
        }
    }

    // Do the same for the player
    if (w->player.poisonTimeRemaining > 0) {
        Ball* b = &w->player;

        float area = radiusToArea(b->radius);
        // Reduce the area by 1% per second
        area -= area * 0.1f * delta;

        b->radius = areaToRadius(area);

        b->poisonTimeRemaining -= delta;
    }
}

// Kills circles that are simply too far from the player to make a difference
// This creates the impression of a "infinite" world
void moveUnused(World* w) {
    int i;

    // For all enemies, if it's distance is too big,
    // kill it
    for (i = 0; i < NUM_ENEMIES; i++) {
        if (distance(w->enemies[i].ball.position, w->player.position) > MAX_PLAYER_DISTANCE) {
            w->enemies[i].ball.isAlive = 0;
        }
    }

    // For all foods, if it's distance is too big,
    // kill it
    for (i = 0; i < NUM_FOOD; i++) {
        if (distance(w->foods[i].position, w->player.position) > MAX_PLAYER_DISTANCE) {
            w->foods[i].isAlive = 0;
        }
    }
}

// Initializes a world to it's basic state
// If the parameter "old" is not null, some data
// is carried to the new world
World newWorld(World *old) {
    Ball b = {
        .position = { 0, 0 },
        .isAlive = 1,
        .radius = BASE_RADIUS * 1.5,
        .poisonTimeRemaining = 0,
        .name = {0}
    };

    World w = {
        .player = b,
        .state = MAIN_MENU,
    };

    if (old) {
        // Carry over the player's name from the old world
        strcpy(w.player.name, old->player.name);
    }

    return w;
}

// Saves a world
void saveWorld(World w) {
    FILE *f;
    f = fopen("save","wb");
    fwrite(&w, sizeof(World), 1, f);
}

// Tries to load a world.
// Returns 1 when successful,
// 0 otherwise
int loadWorld(World *w) {
    FILE *f;
    f = fopen("save", "rb");
    if (f != NULL) {
        // Read a world in the file onto w
        fread(w, sizeof(World), 1, f);
        return 1;
    }
    return 0;
}
