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
 *  File: screen.h
 *  Functions for handling the screen
 */

#ifndef TEULU_SCREEN
#define TEULU_SCREEN

#include "util.h"


/* Definitions */

#define screen_WIDTH    640
#define screen_HEIGHT   480
#define screen_PAD_HOR  12
#define screen_PAD_TOP  12
#define screen_PAD_BTM  48
#define screen_PX_TO_CM 1
#define screen_CM_TO_PX 1
#define screen_PX_TO_M  0.01
#define screen_M_TO_PX  100

// LEVEL coordinates ar logically decoupled from screen:
#define screen_LEVEL_MIN_X screen_PAD_HOR
#define screen_LEVEL_MIN_Y screen_PAD_BTM
// TODO: At least MAX_X should be decoupled from screen_WIDTH:
#define screen_LEVEL_MAX_X (screen_WIDTH - 2 * screen_PAD_HOR)
#define screen_LEVEL_MAX_Y (screen_HEIGHT - screen_PAD_TOP - screen_PAD_BTM)


/* Function prototypes */

util_vector screen_screen_to_world(int x, int y);
util_vector screen_world_to_screen(util_vector pos);

#endif
