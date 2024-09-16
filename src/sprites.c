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
 *  File: sprites.c
 *  Logic and data structurse for sprites
 */

#include "SDL/SDL.h"
#include "SDL/SDL_image.h"

#include "sprites.h"
#include "main.h"


/* Global variables */

SDL_Surface* sprites_bumbarrel;


/* External function definitions */

// Initialise sprites:
int sprites_init(void) {
    SDL_Surface*    temp_surface;
    SDL_Surface*    opt_surface;
    Uint32          colourkey;
    
    // Load sprite:
    temp_surface = IMG_Load("./resources/sprites/bumbarrel.sprite.png");
    opt_surface = SDL_ConvertSurface(temp_surface, main_screen->format, 0);
    sprites_bumbarrel = SDL_DisplayFormat(opt_surface);
    SDL_FreeSurface(temp_surface);
    SDL_FreeSurface(opt_surface);
    
    // Set colour key:
    colourkey = SDL_MapRGB(main_screen->format, 182, 219, 146);
    SDL_SetColorKey(
        sprites_bumbarrel,
        SDL_SRCCOLORKEY| SDL_RLEACCEL,
        colourkey
    );

    return 0;
}
