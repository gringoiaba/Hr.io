#ifndef STRUCTS_ENEMY_H
#define STRUCTS_ENEMY_H

#include "Circle.h"

// Enumeration for possible moving types
typedef enum {
    STATIC,
    RANDOM,
    CHASER,
    DIRECTED
} EnemyMoveType;

// Enumeration for possible enemy types
typedef enum {
    NONE,
    EXPLOSIVE,
    POISONOUS
} EnemyElementalType;

// Struct of an enemy
typedef struct {
    Ball ball; // An enemy is a ball structure

    EnemyMoveType moveType; // An enemy is composed by a type of movement
    EnemyElementalType elementalType; // And composed by a elemental type

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
void killEnemy(World*, Ball*, int, Enemy*, int);
void explodeEnemy(World*, Enemy*, int);
void poisonKiller(Ball*);
char* randomName();

#endif
