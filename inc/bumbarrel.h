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
 *  File: bumbarrel.h
 *  Logic specific to bumbarrels
 */

#ifndef TEULU_BUMBARREL
#define TEULU_BUMBARREL

#include "SDL/SDL.h"

#include "sprites.h"
#include "mobs.h"
#include "util.h"


/* Definitions */

#define bumbarrel_SPRITE_SIZE       12
#define bumbarrel_SPRITE_OFFS       1
#define bumbarrel_SPRITE_PERCH      0
#define bumbarrel_SPRITE_PERCH_NT   5
#define bumbarrel_SPRITE_FLY        1
#define bumbarrel_SPRITE_GLIDE      2
#define bumbarrel_SPRITE_LAND       3
#define bumbarrel_SPRITE_SLEEP      4
#define bumbarrel_SPRITE_SLEEP_NT   4
#define bumbarrel_STATES_COUNT      7
#define bumbarrel_SPEED             4


/* Type definitions */

typedef enum {
    bumbarrel_PERCH,
    bumbarrel_FLY,
    bumbarrel_GLIDE,
    bumbarrel_LAND,
    bumbarrel_SLEEP,
} bumbarrel_state;


typedef struct bumbarrel {
    SDL_Surface*    sprite;
    SDL_Rect        rect;
    SDL_Rect        src_rect;
    bumbarrel_state state;
    int             frame;
    mobs_mob        mob;
} bumbarrel;


/* Global variables */

// Sprite states:
extern sprites_state bumbarrel_perch;
extern sprites_state bumbarrel_perch_no_tail;
extern sprites_state bumbarrel_fly;
extern sprites_state bumbarrel_glide;
extern sprites_state bumbarrel_land;
extern sprites_state bumbarrel_sleep;
extern sprites_state bumbarrel_sleep_no_tail;


/* Function prototypes */

bumbarrel bumbarrel_init_player(int x, int y);
void bumbarrel_update(bumbarrel* bbl);
void bumbarrel_land_now(bumbarrel* bbl);
void bumbarrel_sleep_now(bumbarrel* bbl);
void bumbarrel_fly_towards(util_vector pos, bumbarrel* bbl);
void bumbarrel_face(util_vector pos, bumbarrel* bbl);

#endif
