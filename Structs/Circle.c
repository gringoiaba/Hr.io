#include <stdio.h>
#include <math.h>
#include "Vector2.h"
#include "Circle.h"

// Calculates the area of a circle based on its radius
float radiusToArea (float r) {
    return M_PI*r*r;
}

// Calculates the radius of a circle based on its area
float areaToRadius (float area) {
    return sqrtf(area/M_PI);
}

// Returns the radius of the sum of two circles areas
float newRadius (Ball a, Ball b) {
    return areaToRadius(
        radiusToArea(a.radius) +
        radiusToArea(b.radius)
    );
}

void printBall(Ball b) {
    printVector2(b.position);
    printf(", isAlive: %d, radius: %g", b.isAlive, b.radius);
}

// Tells if a Vector2 is inside a circle
int isInside(Vector2 point, Ball circle) {
    float dist = distance(point, circle.position);

    return dist <= circle.radius;
}

void moveCircle(Ball* b, Vector2 movement) {
    b->position = addVector2(b->position, movement);
}