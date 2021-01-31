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
    File: screen.c
    Functions for handling the screen
*/

#include "screen.h"
#include "util.h"


/* External function definitions */

// Convert screen coordinates to world coordinates:
util_vector screen_screen_to_world(int x, int y) {
    util_vector world_pos = {.x = x, .y = screen_HEIGHT - y};
    return world_pos;
}


// Convert world coordinates to screen coordinates:
util_vector screen_world_to_screen(util_vector pos) {
    util_vector screen_pos = {.x = pos.x, .y = screen_HEIGHT - pos.y};
    return screen_pos;
}
