#ifndef INPUT_H
#define INPUT_H

#include "Structs/World.h"
#include "Structs/Vec2.h"
#include "Structs/PlayerScore.h"
#include "raylib.h"

void updateInput(World*, float, PlayerScore*);
void movePlayer(World*, float);
Vec2 vector2ToVec2(Vector2);
void updateInputPlaying(World*, float);
int pointInRect(Rectangle, Vector2);
void updateInputGameOver(World*, float);
void updateInputPauseMenu(World*, float);
void updateInputMainMenu(World*, float, PlayerScore*);





#endif // INPUT_H
