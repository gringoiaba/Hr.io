#include "Enemy.h"
#include "Circle.h"
#include "PlayerScore.h"

#ifndef STRUCTS_WORLD_H
#define STRUCTS_WORLD_H

// Number of enemies
#define NUM_ENEMIES 40
// Number of foods
#define NUM_FOOD 600

// Base radius for all balls
#define BASE_RADIUS 10

// Food size
#define FOOD_RADIUS 4

// Size of the world (how far away things can be put)
#define WORLD_Y_LENGHT 3000
#define WORLD_X_LENGHT 3000

// Defines a "Rectangle" to make it easier to generate positions
// inside the world
#define WORLD_LEFT_BOUNDARY (-WORLD_X_LENGHT+WORLD_X_LENGHT/2)
#define WORLD_RIGHT_BOUNDARY (WORLD_X_LENGHT-WORLD_X_LENGHT/2)
#define WORLD_TOP_BOUNDARY (-WORLD_Y_LENGHT+WORLD_Y_LENGHT/2)
#define WORLD_BOTTOM_BOUNDARY (WORLD_Y_LENGHT-WORLD_Y_LENGHT/2)

// Maximum distance something can go off of the player before being deleted
#define MAX_PLAYER_DISTANCE (WORLD_Y_LENGHT/2+WORLD_X_LENGHT/2)

// Enumeration of possible world
// states.
typedef enum {
    PLAYING,
    GAME_OVER,
    MAIN_MENU,
    PAUSE_MENU,
    ASK_NAME,
    HIGH_SCORE_SCREEN
} WorldState;

// The game "world"
typedef struct {
    WorldState state; // Indicator of the current state

    Ball player; // The player of the game
    Enemy enemies[NUM_ENEMIES]; // Array of enemies
    Ball foods[NUM_FOOD]; // Array of foods
    float elapsedTime; // Time the world has been running (player score)
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
World newWorld(World*);
int loadWorld(World*);
void saveWorld(World);

#endif // STRUCTS_WORLD_H
