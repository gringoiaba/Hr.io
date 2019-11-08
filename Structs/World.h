#include "Enemy.h"
#include "Circle.h"

#ifndef STRUCTS_WORLD_H
#define STRUCTS_WORLD_H

#define NUM_ENEMIES 100
#define NUM_FOOD 200

#define FOOD_RADIUS 4
#define BASE_RADIUS 10

#define WORLD_Y_LENGHT 1000
#define WORLD_X_LENGHT 1000

#define WORLD_LEFT_BOUNDARY (-WORLD_X_LENGHT+WORLD_X_LENGHT/2)
#define WORLD_RIGHT_BOUNDARY (WORLD_X_LENGHT-WORLD_X_LENGHT/2)
#define WORLD_TOP_BOUNDARY (-WORLD_Y_LENGHT+WORLD_Y_LENGHT/2)
#define WORLD_BOTTOM_BOUNDARY (WORLD_Y_LENGHT-WORLD_Y_LENGHT/2)

typedef struct {
    Ball player;
    Enemy enemies[NUM_ENEMIES];
    Ball foods[NUM_FOOD];
} World;

void updateWorld(World*, float);
void checkFoods (World *);
void checkCollisions (World *);
void respawnFoods (World*);
void printWorld(World);
void respawnEnemies(World*);
void updateEnemies(World*, float);
void killPlayer(World*, Enemy*, int);

#endif // STRUCTS_WORLD_H
