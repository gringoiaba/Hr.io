#ifndef STRUCTS_VEC2_H
#define STRUCTS_VEC2_H

typedef struct {
    float x, y;
} Vec2;

Vec2 randomPosition(int, int, int, int);
void printVec2 (Vec2);
float distance(Vec2, Vec2);
float angleBetween (Vec2, Vec2);
Vec2 addVec2(Vec2, Vec2);
Vec2 scaleVec2(Vec2, float);

#endif
