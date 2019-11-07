#include "Circle.h"
#include "Enemy.h"
#include "World.h"
#include <math.h>
#include <stdlib.h>

#define ENEMY_SPEED 100
#define SWITCH_TIME 1

#define EXPLOSION_SCALE 1.5

#define RAD_TO_DEG (180.0 / M_PI);

char* enemyMoveTypeToString(EnemyMoveType t) {
    switch (t) {
    case STATIC:
        return "Static";
    case RANDOM:
        return "Random";
    case DIRECTED:
        return "Directed";
    case CHASER:
        return "Chaser";
    default:
        return "Undefined";
    }
}

char* enemyElementalTypeToString(EnemyElementalType t) {
    switch (t) {
    case NONE:
        return "None";
    case EXPLOSIVE:
        return "Explosive";
    case POISONOUS:
        return "Poisonous";
    default:
        return "Undefined";
    }
}

void updateEnemy (Enemy *self, World w, int index, float delta) {

    switch (self->moveType) {
    case STATIC:
        break;
    case RANDOM:
        moveRandom (self, w, index, delta);
        break;
    case DIRECTED:
        moveDirected (self, w, index, delta);
        break;
    case CHASER:
        moveChaser (self, w, index, delta);
        break;
    }
}

Vector2 getMovementByAngle(float angle) {
    Vector2 movement = {
        .x = cosf(angle) * ENEMY_SPEED,
        .y = sinf(angle) * ENEMY_SPEED
    };

    return movement;
}

void moveChaser (Enemy *self, World w, int index, float delta) {
    float angleToPlayer = angleBetween (self->ball.position, w.player.position);

    Vector2 movement = getMovementByAngle(angleToPlayer);
    movement = scaleVector2(movement, delta);

    moveCircle(&self->ball, movement);
}


void moveDirected (Enemy *self, World w, int index, float delta) {
    Vector2 movement = getMovementByAngle(self->movingDirection);
    movement = scaleVector2(movement, delta);

    moveCircle(&self->ball, movement);
}

void moveRandom (Enemy *self, World w, int index, float delta) {
    self->timeEllapsedSinceLastSwitch += delta;

    if (self->timeEllapsedSinceLastSwitch >= SWITCH_TIME) {
        self->movingDirection = randomRadian();
        self->timeEllapsedSinceLastSwitch = 0;
    }

    moveDirected (self, w, index, delta);
}

// Returns a random radian angle
float randomRadian() {
    return (rand()%360) * RAD_TO_DEG;
}

// Kills an enemy
void killEnemy(World* w, Enemy* killer, int killerIndex, Enemy* killed, int killedIndex) {

    // Do not kill the dead...
    if (!killed->ball.isAlive) {
        return;
    }

    killed->ball.isAlive = 0;

    switch (killed->elementalType) {
    case NONE:
        break;
    case EXPLOSIVE:
        explodeEnemy(w, killed, killedIndex);
        break;
    case POISONOUS:
        // poisonKiller(killer);
        break;
    }
}

void explodeEnemy(World* w, Enemy* e, int index) {
    int i;
    float explosionRadius = e->ball.radius * EXPLOSION_SCALE;

    for (i = 0; i < NUM_ENEMIES; i++) {
        // Do not explode us
        if (i == index) {
            continue;
        }

        // If is inside explosion radius...
        if (distance(e->ball.position, w->enemies[i].ball.position) <= explosionRadius) {
            killEnemy(w, e, index, &w->enemies[i], i);
        }
    }
}
