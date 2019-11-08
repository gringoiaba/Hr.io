#ifndef INPUT_H
#define INPUT_H

#include "Structs/World.h"

void updateInput(World*, float);
void movePlayer(World*, float);
Vec2 vector2ToVec2(Vector2);

#endif // INPUT_H
