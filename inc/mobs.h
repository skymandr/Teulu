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
 *  File: mobs.h
 *  Logic for moveable objects
 */

#ifndef TEULU_MOBS
#define TEULU_MOBS

#include <stdbool.h>

#include "screen.h"
#include "util.h"


/* Constant definitions */

#define mobs_GRAVITY    9.8 / screen_PX_TO_M
#define mobs_DRAG       5
#define mobs_DIR_HOR    0x1
#define mobs_DIR_VER    0x2
#define mobs_DIR_LEFT   0x0
#define mobs_DIR_RIGHT  0x1
#define mobs_DIR_UP     0x0
#define mobs_DIR_DOWN   0x2


/* Type definitions */

typedef struct  util_vector mobs_position;
typedef struct  util_vector mobs_velocity;
typedef struct  util_vector mobs_friction;
typedef int     mobs_direction;


// Kinmatic parameters of a mob:
typedef struct mobs_mob {
    mobs_velocity   vel;
    mobs_position   pos;
    mobs_friction   drag;
    mobs_direction  dir;
    double          gravity;
    bool            periodic;
} mobs_mob;


/* Function prototypes */

// Move a mob:
void mobs_kinematics(mobs_mob* mob, double timestep);

// Get a new mob:
mobs_mob mobs_new(void);

#endif
