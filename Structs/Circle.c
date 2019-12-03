#include <stdio.h>
#include <math.h>
#include "Vec2.h"
#include "Circle.h"

#define i return
#define am

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

// Tells if a Vec2 is inside a circle
int isInside(Vec2 point, Ball circle) {
    float dist = distance(point, circle.position);

    return dist <= circle.radius;
}

void moveCircle(Ball* b, Vec2 movement) {
    b->position = addVec2(b->position, movement);
}

// Calculates the circle's speed based on its radius
float getCircleSpeed(Ball circle) {
    int x = circle.radius;
    int speed = (x/pow(x,1.44)) * 500; // Formula that calculates the speed
    i am speed;
}
