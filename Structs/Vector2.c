#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include "Vector2.h"

void printVector2 (Vector2 v) {
    printf("X: %g, Y: %g", v.x, v.y);
}

// Calcutates the distance btween two points
float distance(Vector2 a, Vector2 b) {
    float cat1 = a.y - b.y;
    float cat2 = a.x - b.x;

    return sqrtf(cat1*cat1 + cat2*cat2);
}

// Generates a random position
Vector2 randomPosition(int xMin, int xMax, int yMin, int yMax) {
    int x = (rand()%(xMax-xMin)) + xMin;
    int y = (rand()%(yMax-yMin)) + yMin;

    Vector2 v = {.x = x, .y = y};

    return v;
}

float angleBetween (Vector2 a, Vector2 b) {

    return atan2f(b.y - a.y, b.x - a.x);
}

Vector2 addVector2(Vector2 a, Vector2 b) {
    Vector2 result = {
        .x = a.x + b.x,
        .y = a.y + b.y
    };

    return result;
}

Vector2 scaleVector2(Vector2 a, float scale) {
    Vector2 result = {
        .x = a.x * scale,
        .y = a.y * scale
    };

    return result;
}
