#ifndef STRUCTS_CIRCLE_H
#define STRUCTS_CIRCLE_H

#include "Vec2.h"
#include "PlayerScore.h"

typedef struct {
    Vec2 position;
    int isAlive;
    float radius;
    char name[NAME_SIZE];

    float poisonTimeRemaining;
} Ball;

float newRadius (Ball, Ball);
float areaToRadius (float);
float radiusToArea (float);
void printBall(Ball);
int isInside(Vec2, Ball);
void moveCircle(Ball*, Vec2);

#endif
