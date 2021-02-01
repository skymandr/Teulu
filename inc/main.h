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
 *  File: main.h
 *  Main game loop and logic
 */

#ifndef TEULU_MAIN
#define TEULU_MAIN

#include "SDL/SDL.h"


/* Global definitions */

#define MAIN_APP_NAME       "Teulu"
#define MAIN_APP_VER        "v0.0.2"
#define MAIN_APP_FRAMERATE  50
#define MAIN_APP_TITLE      MAIN_APP_NAME " " MAIN_APP_VER
#define MAIN_APP_DBL_CLK    500


/* Global variables */

extern SDL_Surface* main_screen;
extern int          main_softscale;

#endif
