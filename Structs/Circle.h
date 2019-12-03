#ifndef STRUCTS_CIRCLE_H
#define STRUCTS_CIRCLE_H

#include "Vec2.h"
#include "PlayerScore.h"

typedef struct {
    Vec2 position; // Position of the ball within the world
    int isAlive; // Boolean to indicate if a circle is alive
    float radius; // Float of the circle radius
    char name[NAME_SIZE]; // Name of the circle

    float poisonTimeRemaining; // Time remaining to a circle stop being poisoned
} Ball;

float newRadius (Ball, Ball);
float areaToRadius (float);
float radiusToArea (float);
void printBall(Ball);
int isInside(Vec2, Ball);
void moveCircle(Ball*, Vec2);
float getCircleSpeed(Ball);


#endif
