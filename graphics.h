#ifndef GRAPHICS_H
#define GRAPHICS_H

#include "Structs/World.h"
#include "Structs/Vec2.h"
#include "raylib.h"

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600

#define GAME_OVER_BUTTON ((Rectangle){.x = SCREEN_WIDTH/2 - 300/2, \
                                      .y = SCREEN_HEIGHT/2 + 70,   \
                                      .width = 300,                \
                                      .height = 50})

Camera2D cam;

void initGraphics();
void drawWorld(World);
void endGraphics();
int isGraphicsRunning();
Vector2 vec2ToVector2(Vec2);
void drawCircle(Ball, Color);
void drawPlaying(World, int);
void drawGameOver(World);
Rectangle centerText(Rectangle, char*, int);


#endif // GRAPHICS_H
