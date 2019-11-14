#include "Enemy.h"
#include "Circle.h"

#ifndef STRUCTS_WORLD_H
#define STRUCTS_WORLD_H

#define NUM_ENEMIES 40
#define NUM_FOOD 200

#define FOOD_RADIUS 4
#define BASE_RADIUS 10

#define WORLD_Y_LENGHT 3000
#define WORLD_X_LENGHT 3000

#define WORLD_LEFT_BOUNDARY (-WORLD_X_LENGHT+WORLD_X_LENGHT/2)
#define WORLD_RIGHT_BOUNDARY (WORLD_X_LENGHT-WORLD_X_LENGHT/2)
#define WORLD_TOP_BOUNDARY (-WORLD_Y_LENGHT+WORLD_Y_LENGHT/2)
#define WORLD_BOTTOM_BOUNDARY (WORLD_Y_LENGHT-WORLD_Y_LENGHT/2)

#define MAX_PLAYER_DISTANCE 1500

typedef enum {
    PLAYING,
    GAME_OVER,
    MAIN_MENU
} WorldState;

typedef struct {
    WorldState state;

    Ball player;
    Enemy enemies[NUM_ENEMIES];
    Ball foods[NUM_FOOD];
    float elapsedTime; // Time the world has been running
} World;

void updateWorld(World*, float);
void checkFoods (World *);
void checkCollisions (World *);
void respawnFoods (World*);
void printWorld(World);
void respawnEnemies(World*);
void updateEnemies(World*, float);
void killPlayer(World*, Enemy*, int);
void updatePoison(World*, float);
void moveUnused(World*);
void updatePlaying(World*, float);

#endif // STRUCTS_WORLD_H
