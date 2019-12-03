#include "Circle.h"
#include "Enemy.h"
#include "World.h"
#include "Vec2.h"
#include <math.h>
#include <stdlib.h>

#define ENEMY_SPEED 100
#define SWITCH_TIME 1

#define EXPLOSION_SCALE 1.5

#define RAD_TO_DEG (180.0 / M_PI);

#define POISON_TIME 5

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

void moveChaser (Enemy *self, World w, int index, float delta) {

    if (!w.player.isAlive) {
        moveRandom(self, w, index, delta);
        return;
    }

    float angleToPlayer = angleBetween (self->ball.position, w.player.position);

    Vec2 movement = getMovementByAngle(angleToPlayer, ENEMY_SPEED);
    movement = scaleVec2(movement, delta);

    moveCircle(&self->ball, movement);
}


void moveDirected (Enemy *self, World w, int index, float delta) {
    Vec2 movement = getMovementByAngle(self->movingDirection, ENEMY_SPEED);
    movement = scaleVec2(movement, delta);

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
void killEnemy(World* w, Ball* killer, int killerIndex, Enemy* killed, int killedIndex) {

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
        poisonKiller(killer);
        break;
    }

    killer->radius = newRadius(*killer, killed->ball);
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
            killEnemy(w, &e->ball, index, &w->enemies[i], i);
        }
    }

    if (w->player.isAlive) {
        if (distance(e->ball.position, w->player.position) <= explosionRadius) {
            killPlayer(w, e, index);
        }
    }
}

void poisonKiller(Ball* killer) {
    killer->poisonTimeRemaining += POISON_TIME;
}

char* randomName() {
    char* names[] = {
        "Ferrari",
        "Raider",
        "JoseStar",
        "Laggy",
        "Garp",
        "RAPTOR",
        "hdabjh",
        "Equipo Novato",
        "Lukas Dark",
        "Equipo Meteoro",
        "angel",
        "Frostblink",
        "Smash YT",
        "Amigo Proo",
        "An unnamed cell",
        "Abril",
        "Percival",
        "Sarinela",
        "tonello",
        "cuky",
        "LOL",
        "APOLO",
        "MARINAA",
        "Ariel",
        "VIP Neymar",
        "YT: Kevinkf2",
        "Vou Sair",
        "doge",
        "cavera",
        "kiriko",
        "santos",
        "kolibre"
    };

    return names[rand() % 32];
}
