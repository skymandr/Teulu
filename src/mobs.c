 /*
 *  Teulu - A game about bumbarrels gathering food and building a family
 *  Copyright (C) 2021  Andreas Skyman (Bumbarrel Computing)
 * 
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 * 
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 * 
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */ 
/*
 *  File: mobs.c
 *  Logic for moveable objects
 */

#include <math.h>

#include "SDL/SDL.h"

#include "mobs.h"
#include "screen.h"
#include "util.h"


/* Function prototypes */

static void mobs_boundary_conditions(mobs_mob* mob);
static void mobs_move(mobs_mob* mob, double timestep);
static void mobs_stop(mobs_mob* mob);
static void mobs_drag(mobs_mob* mob, double timestep);
static void mobs_gravity(mobs_mob* mob, double timestep);


/* External function definitions */

// Move a mob:
void mobs_kinematics(mobs_mob* mob) {
    double timestep = (double) (SDL_GetTicks() - mob->last_move) / 1000.0;

    if (timestep <= 0) {
        return;
    }

    mobs_gravity(mob, timestep);
    mobs_drag(mob, timestep);
    mobs_stop(mob);
    mobs_move(mob, timestep);
    mobs_boundary_conditions(mob);

    mob->last_move = SDL_GetTicks();
}


mobs_mob mobs_new(void) {
    mobs_mob mob = {
        .pos = {.x = 0, .y = 0},
        .vel = {.x = 0, .y = 0},
        .drag = {.x = mobs_DRAG, .y = 2 * mobs_DRAG},
        .dir = 0,
        .gravity = mobs_GRAVITY,
        .periodic = FALSE,
    };
    return mob;
}


/* Static function definitions */

// Apply velocity:
static void mobs_move(mobs_mob* mob, double timestep) {
    mob->pos.x += mob->vel.x * timestep;
    mob->pos.y += mob->vel.y * timestep;
};


// Apply boundary conditions:
static void mobs_boundary_conditions(mobs_mob* mob) {
    if (mob->pos.x >= screen_LEVEL_MAX_X) {
        if (mob->periodic) {
            mob->pos.x -= (screen_LEVEL_MAX_X - screen_LEVEL_MIN_X);
        } else {
            mob->pos.x = screen_LEVEL_MAX_X - 1;
            mob->vel.x = 0;
        }
    } else if (mob->pos.x < screen_LEVEL_MIN_X) {
        if (mob->periodic) {
            mob->pos.x += (screen_LEVEL_MAX_X - screen_LEVEL_MIN_X);
        } else {
            mob->pos.x = screen_LEVEL_MIN_X;
            mob->vel.x = 0;
        }
    }
    if (mob->pos.y >= screen_LEVEL_MAX_Y) {
        mob->pos.y = screen_LEVEL_MAX_Y;
    } else if (mob->pos.y < screen_LEVEL_MIN_Y) {
        mob->pos.y = screen_LEVEL_MIN_Y;
        mob->vel.y = 0;
        mob->vel.x = 0;
    }
}


// Halt slow movement:
static void mobs_stop(mobs_mob* mob) {
    if (fabs(mob->vel.x) < 1) {
        mob->vel.x = 0;
    }
    if (fabs(mob->vel.y) < 1) {
        mob->vel.y = 0;
    }
}


// Apply gravity:
static void mobs_gravity(mobs_mob* mob, double timestep) {
    if (mob->gravity > 0) {
        mob->vel.y -= 0.5 * mob->gravity * timestep;
    }
}


// Apply drag friction:
static void mobs_drag(mobs_mob* mob, double timestep) {
    double drag;
    if (mob->drag.x > 0 && mob->vel.x != 0) {
        drag = 0.5 * mob->drag.x * mob->vel.x * mob->vel.x * timestep;
        if (mob->vel.x > 0) {
            mob->vel.x -= drag;
        } else {
            mob->vel.x += drag;
        }
    }
    if (mob->drag.y > 0 && mob->vel.y != 0) {
        drag = 0.5 * mob->drag.y * mob->vel.y * mob->vel.y * timestep;
        if (mob->vel.y > 0) {
            mob->vel.y -= 0.5 * drag;
        } else {
            mob->vel.y += drag;
        }
    }
}
