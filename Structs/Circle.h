#ifndef STRUCTS_CIRCLE_H
#define STRUCTS_CIRCLE_H

#include "Vector2.h"

typedef struct {
    Vector2 position;
    int isAlive;
    float radius;
} Ball;

float newRadius (Ball, Ball);
float areaToRadius (float);
float radiusToArea (float);
void printBall(Ball);
int isInside(Vector2, Ball);
void moveCircle(Ball*, Vector2);

#endif
