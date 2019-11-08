#ifndef GRAPHICS_H
#define GRAPHICS_H

#include "Structs/World.h"
#include "Structs/Vec2.h"
#include "raylib.h"

Camera2D cam;

void initGraphics();
void drawWorld(World);
void endGraphics();
int isGraphicsRunning();
Vector2 vec2ToVector2(Vec2);

#endif // GRAPHICS_H
