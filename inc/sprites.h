 /*
 *  Teulu - A game about bumbarrels gathering food and building a family
 *  Copyright (C) 2021  Ida-Sofia Skyman (Bumbarrel Computing)
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
 *  File: sprites.h
 *  Logic and data structurse for sprites
 */

#ifndef TEULU_SPRITES
#define TEULU_SPRITES

#include "SDL/SDL.h"


/* Definitions */

#define sprites_MAX_FRAMES  6


/* Type definitions */

typedef struct sprites_state {
    const int       index;
    const int       frames;
    const int       pad;
    const int       height;
    const int       width;
    const int       delay;
    const float     transitions[sprites_MAX_FRAMES][sprites_MAX_FRAMES];
} sprites_state;


/* Global variables */

extern SDL_Surface* sprites_bumbarrel;


/* Function prototypes */

int sprites_init(void);

#endif
