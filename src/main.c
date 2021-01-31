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
 *  File: main.c
 *  Main game loop and logic
 */

#include <stdbool.h>
#include <stdio.h>
#include <time.h>

#include "SDL/SDL.h"
#include "SDL/SDL_image.h"

#include "main.h"
#include "screen.h"
#include "sprites.h"
#include "bumbarrel.h"


/* Global variables */

SDL_Surface*    main_screen;
SDL_Surface*    main_background;
bool            main_quit_flag = FALSE;
bumbarrel       main_player;



/* Function prototypes */

static int main_init(void);
static int main_loop(void);
static int main_quit(void);
static void main_events(void);
static void main_draw(void);
static void main_handle_key_press(SDL_KeyboardEvent key);
static void main_handle_mouse_press(SDL_MouseButtonEvent key);


/* External function definitions */

// Main entry function:
int main(void) {
    int status;

    status |= main_init();
    if (status == 0) {
        status |= main_loop();
    }
    status |= main_quit();

    return status;
}


/* Static function definitions */

// Initialise application:
static int main_init(void) {
    int status      = 0;
    int img_flags   = IMG_INIT_PNG;

    // Seed random numbers:
    srand(time(NULL));

    // Initialise SDL:
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        printf("SDL could not initialise! "
               "SDL Error: %s\n", SDL_GetError());
        return 1;
    };

    // Initialise screen:
    main_screen = SDL_SetVideoMode(
        screen_WIDTH,
        screen_HEIGHT,
        0,
        SDL_DOUBLEBUF | SDL_HWSURFACE
    );
    if (main_screen == NULL) {
        printf("Screen could not be created! "
               "SDL Error: %s\n", SDL_GetError());
        return 1;
    }
    SDL_WM_SetCaption(MAIN_APP_TITLE, MAIN_APP_NAME);
    
    //Initialise PNG loading:
    if(!(IMG_Init(img_flags) & img_flags)) {
        printf("SDL_image could not initialise! "
               "SDL_image Error: %s\n", IMG_GetError());
        return 1;
    }

    // Initialise sprites:
    status |= sprites_init();
    main_background = IMG_Load("./resources/bg.png");

    // Initialise player:
    main_player = bumbarrel_init_player(470, 320);

    return status;
}


// Handle keyboard interaction:
static void main_handle_key_press(SDL_KeyboardEvent key) {
    SDL_QuitEvent   quit;
    quit.type = SDL_QUIT;

    switch (key.keysym.sym) {
    case SDLK_ESCAPE:
    case SDLK_q:
        if (key.state == SDL_RELEASED) {
            SDL_PushEvent((SDL_Event*) &quit);
        }
        break;
    case SDLK_c:
        if (key.state == SDL_PRESSED) {
            printf("Call!\n");
        }
        break;
    case SDLK_x:
        if (key.state == SDL_PRESSED) {
            printf("Warn!\n");
        }
        break;
    case SDLK_z:
        if (key.state == SDL_PRESSED) {
            printf("Sleep...\n");
            bumbarrel_sleep_now(&main_player);
        }
        break;
    default:
        break;
    }
}


// Handle mouse interaction:
static void main_handle_mouse_press(SDL_MouseButtonEvent button) {
    util_vector     mouse_pos;

    if (button.type == SDL_MOUSEBUTTONUP) {
        return;
    }

    mouse_pos = screen_screen_to_world(button.x, button.y);
    switch (button.button) {
    case SDL_BUTTON_LEFT:
        printf("Fly: %d %d\n", button.x, button.y);
        bumbarrel_fly_towards(mouse_pos, &main_player);
        break;
    case SDL_BUTTON_RIGHT:
        printf("Eat: %d %d\n", button.x, button.y);
        bumbarrel_land_now(&main_player);
        bumbarrel_face(mouse_pos, &main_player);
        break;
    default:
        break;
    }

}


// Main loop:
static int main_loop(void) {

    while(!main_quit_flag) {
        main_events();
        bumbarrel_update(&main_player);
        main_draw();
        SDL_Delay(100);
    }
    return 0;
}


// Handle events:
static void main_events(void) {
    SDL_Event   event;

    if (!SDL_PollEvent(&event)) {
        return;
    }

    switch (event.type) {
    case SDL_KEYDOWN:
    case SDL_KEYUP:
        main_handle_key_press(event.key);
        break;
    case SDL_MOUSEBUTTONDOWN:
    case SDL_MOUSEBUTTONUP:
        main_handle_mouse_press(event.button);
        break;
    case SDL_QUIT:
        main_quit_flag = TRUE;
    default:
        break;
    }

    return;
}


static void main_draw(void) {
    SDL_FillRect(main_screen, NULL, 0);
    SDL_BlitSurface(
        main_background,
        NULL,
        main_screen,
        NULL
    );
    SDL_BlitSurface(
        main_player.sprite,
        &(main_player.src_rect),
        main_screen,
        &(main_player.rect)
    );
    SDL_Flip(main_screen);
}


// Clean shutdown:
static int main_quit(void) {
    SDL_FreeSurface(main_screen);
    SDL_Quit();
    return 0;
}

