#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include "Vec2.h"

// Calcutates the distance btween two points
float distance(Vec2 a, Vec2 b) {
    float cat1 = a.y - b.y;
    float cat2 = a.x - b.x;

    // Pythagoras' theorem
    return sqrtf(cat1*cat1 + cat2*cat2);
}

// Generates a random position
Vec2 randomPosition(int xMin, int xMax, int yMin, int yMax) {
    int x = (rand()%(xMax-xMin)) + xMin;
    int y = (rand()%(yMax-yMin)) + yMin;

    Vec2 v = {.x = x, .y = y};

    return v;
}

// Calculates the angle in radians between two points
float angleBetween (Vec2 a, Vec2 b) {

    return atan2f(b.y - a.y, b.x - a.x);
}

// Transforms a angle and a speed into a movement
// described by a X axis movement and a Y axis movement
Vec2 getMovementByAngle(float angle, float speed) {
    Vec2 movement = {
        .x = cosf(angle) * speed,
        .y = sinf(angle) * speed
    };

    return movement;
}

// Adds two vectors together
Vec2 addVec2(Vec2 a, Vec2 b) {
    Vec2 result = {
        .x = a.x + b.x,
        .y = a.y + b.y
    };

    return result;
}

// Scales the x and y of a vector by a scale
Vec2 scaleVec2(Vec2 a, float scale) {
    Vec2 result = {
        .x = a.x * scale,
        .y = a.y * scale
    };

    return result;
}
