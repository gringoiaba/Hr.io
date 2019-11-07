#ifndef STRUCTS_VECTOR2_H
#define STRUCTS_VECTOR2_H

typedef struct {
    float x, y;
} Vector2;

Vector2 randomPosition(int, int, int, int);
void printVector2 (Vector2);
float distance(Vector2, Vector2);
float angleBetween (Vector2, Vector2);
Vector2 addVector2(Vector2, Vector2);
Vector2 scaleVector2(Vector2, float);

#endif // STRUCTS_VECTOR2_H
