#ifndef STRUCTS_ENEMY_H
#define STRUCTS_ENEMY_H

#include "Circle.h"

typedef enum {
    STATIC,
    RANDOM,
    CHASER,
    DIRECTED
} EnemyMoveType;

typedef enum {
    NONE,
    EXPLOSIVE,
    POISONOUS
} EnemyElementalType;

typedef struct {
    Ball ball;

    EnemyMoveType moveType;
    EnemyElementalType elementalType;

    float timeEllapsedSinceLastSwitch; // Time in seconds elapsed since the last direction switch
    float movingDirection; // Angle in radians which the AI uses to move
} Enemy;

#include "World.h"

char* enemyMoveTypeToString (EnemyMoveType);
char* enemyElementalTypeToString (EnemyElementalType);
void updateEnemy (Enemy*, World, int, float);
void moveChaser (Enemy*, World, int, float);
void moveDirected (Enemy*, World, int, float);
void moveRandom (Enemy*, World, int, float);
float randomRadian();
void killEnemy(World*, Enemy*, int, Enemy*, int);
void explodeEnemy(World*, Enemy*, int);

#endif
