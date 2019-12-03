#include "Circle.h"
#include "Enemy.h"
#include "World.h"
#include "Vec2.h"
#include <math.h>
#include <stdlib.h>

#define SWITCH_TIME 1

#define EXPLOSION_SCALE 1.5

#define RAD_TO_DEG (180.0 / M_PI);

#define POISON_TIME 5

// Function that determines the behavior of a enemy based on its type
void updateEnemy (Enemy *self, World w, int index, float delta) {

    switch (self->moveType) {
    case STATIC:
        break;
    case RANDOM:
        moveRandom (self, w, index, delta); // Moves the enemy stochastically
        break;
    case DIRECTED:
        moveDirected (self, w, index, delta); // Moves the enemy in a single direction
        break;
    case CHASER:
        moveChaser (self, w, index, delta); // Enemy that always chases the player
        break;
    }
}

// Sets the movement of a chaser enemy
void moveChaser (Enemy *self, World w, int index, float delta) {

    // If the player is not alive, moves the chaser in a random way
    if (!w.player.isAlive) {
        moveRandom(self, w, index, delta);
        return;
    }

    // Calculates the angle of the enemy to the player
    float angleToPlayer = angleBetween (self->ball.position, w.player.position);

    // Calculates the direction of the enemy to the player
    Vec2 movement = getMovementByAngle(angleToPlayer, getCircleSpeed(self->ball));
    movement = scaleVec2(movement, delta);

    // Moves the circle
    moveCircle(&self->ball, movement);
}

// Moves the enemy to a single direction
void moveDirected (Enemy *self, World w, int index, float delta) {
    Vec2 movement = getMovementByAngle(self->movingDirection, getCircleSpeed(self->ball));
    movement = scaleVec2(movement, delta);

    moveCircle(&self->ball, movement);
}

// Changes the direction of the enemy constantly
void moveRandom (Enemy *self, World w, int index, float delta) {
    self->timeEllapsedSinceLastSwitch += delta;

    // Changes the direction at every "SWITCH_TIME" defined seconds
    if (self->timeEllapsedSinceLastSwitch >= SWITCH_TIME) {
        self->movingDirection = randomRadian(); // Selects a random radian to move to
        self->timeEllapsedSinceLastSwitch = 0; // Sets the time since last switch to zero
    }

    // Moves to a single direction at a time
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

    // Set the kill status as DEAD
    killed->ball.isAlive = 0;

    // Sees which enemy was killed to determine the reaction
    switch (killed->elementalType) {
    case NONE:
        break;
    case EXPLOSIVE:
        explodeEnemy(w, killed, killedIndex); // If the Explosive type was killed creates an explosion
        break;
    case POISONOUS:
        poisonKiller(killer); // If the poisonous type was killed poisons the killer
        break;
    }

    killer->radius = newRadius(*killer, killed->ball); // Updates the killer radius based on the killed radius
}

// Function to explode the Explosion type enemies
void explodeEnemy(World* w, Enemy* e, int index) {
    int i;
    float explosionRadius = e->ball.radius * EXPLOSION_SCALE; // Sets the explosion radius based on the enemy radius

    // Checks for circles inside the enemy explosion radius
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

    // If the player is inside the explosion, kills the player
    if (w->player.isAlive) {
        if (distance(e->ball.position, w->player.position) <= explosionRadius) {
            killPlayer(w, e, index);
        }
    }
}

// If the poisonous enemy is killed, the killer is poisoned
void poisonKiller(Ball* killer) {
    killer->poisonTimeRemaining += POISON_TIME; // Adds poisoned time to the killer
}

// Function that returns random names to be given to the enemies
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
