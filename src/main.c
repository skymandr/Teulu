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
 *  File: main.c
 *  Main game loop and logic
 */

#include <stdbool.h>
#include <stdio.h>
#include <time.h>

#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include "SDL/SDL_rotozoom.h"

#include "main.h"
#include "screen.h"
#include "sprites.h"
#include "bumbarrel.h"


/* Global variables */

SDL_Surface*    main_screen;
SDL_Surface*    main_soft_screen;
SDL_Surface*    main_background;
bool            main_quit_flag = FALSE;
bool            main_fullscreen_flag = FALSE;
bool            main_framerate_flag = FALSE;
int             main_softscale = 1;
uint            main_select_click_time = 0;
uint            main_adjust_click_time = 0;
uint            main_dbl_clk_delay = MAIN_APP_DBL_CLK;
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
int main(int argc, char* args[]) {
    int status = 0;

    if (argc > 1) {
        for (int i = 1; i < argc; i++) {
            if (strncmp(args[i], "-f", 2) == 0) {
                printf("Fullscreen mode enabled\n");
                main_fullscreen_flag = TRUE;
            } else if (strncmp(args[i], "-s", 2) == 0) {
                if (i == argc - 1) {
                    printf(
                        "Soft scale must be between 1 and 4 (got none)\n"
                        "Aborting...\n"
                    );
                    return 1;
                }
                printf("Soft scaling mode enabled\n");
                main_softscale = atoi(args[i+1]);
                if (main_softscale < 1 || main_softscale > 4) {
                    printf(
                        "Soft scale must be between 1 and 4 (got %d)\n"
                        "Aborting...\n",
                        main_softscale
                    );
                    return 1;
                }
                i++;
            } else {
                printf("Unknown option '%s'.\nAborting...\n", args[i]);
                return 1;
            }
        }
    }
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
    SDL_Surface*    temp_surface;
    SDL_Surface*    opt_surface;
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
        screen_WIDTH * main_softscale,
        screen_HEIGHT * main_softscale,
        0,
        SDL_DOUBLEBUF | SDL_HWSURFACE | SDL_HWPALETTE
    );
    if (main_screen == NULL) {
        printf("Screen could not be created! "
               "SDL Error: %s\n", SDL_GetError());
        return 1;
    }
    SDL_WM_SetCaption(MAIN_APP_TITLE, MAIN_APP_NAME);
    if (main_fullscreen_flag) {
        SDL_WM_ToggleFullScreen(main_screen);
    }
    if (main_softscale > 1) {
        temp_surface = SDL_CreateRGBSurface(
            SDL_HWSURFACE,
            screen_WIDTH,
            screen_HEIGHT,
            0, 0, 0, 0, 0
        );
        opt_surface = SDL_ConvertSurface(temp_surface, main_screen->format, 0);
        main_soft_screen = SDL_DisplayFormat(opt_surface);
        SDL_FreeSurface(temp_surface);
        SDL_FreeSurface(opt_surface);
        if (main_soft_screen == NULL) {
            printf("Soft screen could not be created! "
                    "SDL Error: %s\n", SDL_GetError());
            return 1;
        }
    }
    
    //Initialise PNG loading:
    if(!(IMG_Init(img_flags) & img_flags)) {
        printf("SDL_image could not initialise! "
               "SDL_image Error: %s\n", IMG_GetError());
        return 1;
    }

    // Initialise sprites:
    status |= sprites_init();
    temp_surface = IMG_Load("./resources/bg.png");
    opt_surface = SDL_ConvertSurface(temp_surface, main_screen->format, 0);
    main_background = SDL_DisplayFormat(opt_surface);
    SDL_FreeSurface(temp_surface);
    SDL_FreeSurface(opt_surface);

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
    case SDLK_f:
        if (key.state == SDL_PRESSED) {
            main_framerate_flag ^= TRUE;
        }
        break;
    case SDLK_c:
        if (key.state == SDL_PRESSED) {
            if (main_player.state == bumbarrel_SLEEP) {
                main_player.state = bumbarrel_PERCH;
            }
            printf("Call!\n");
        }
        break;
    case SDLK_x:
        if (key.state == SDL_PRESSED) {
            if (main_player.state == bumbarrel_SLEEP) {
                main_player.state = bumbarrel_PERCH;
            }
            printf("Warn!\n");
        }
        break;
    case SDLK_z:
        if (key.state == SDL_PRESSED) {
            if (main_player.state == bumbarrel_PERCH) {
                printf("Sleep...\n");
                bumbarrel_sleep_now(&main_player);
            }
        }
        break;
    default:
        break;
    }
}


// Handle mouse interaction:
static void main_handle_mouse_press(SDL_MouseButtonEvent button) {
    util_vector mouse_pos   = screen_screen_to_world(button.x, button.y);
    uint        time        = SDL_GetTicks();

    switch (button.type) {
    case SDL_MOUSEBUTTONDOWN:
        switch (button.button) {
        case SDL_BUTTON_LEFT:
            if (time - main_select_click_time <= main_dbl_clk_delay) {
                printf("Dash: %f, %f\n", mouse_pos.x, mouse_pos.y);
                bumbarrel_fly_towards(mouse_pos, &main_player);
            } else {
                printf("Fly: %f %f\n", mouse_pos.x, mouse_pos.y);
            }
            main_player.state = bumbarrel_FLY_ACTIVE;
            main_select_click_time = time;
            bumbarrel_face(mouse_pos, &main_player);
            break;
        case SDL_BUTTON_RIGHT:
            printf(
                "Eat: %f %f\n",
                main_player.mob.pos.x,
                main_player.mob.pos.y
            );
            bumbarrel_face(mouse_pos, &main_player);
            break;
        default:
            break;
        }
        break;
    case SDL_MOUSEBUTTONUP:
        switch (button.button) {
        case SDL_BUTTON_LEFT:
            if (main_player.state == bumbarrel_FLY_ACTIVE) {
                main_player.state = bumbarrel_FLY;
            }
            break;
        case SDL_BUTTON_RIGHT:
            if (time - main_adjust_click_time < main_dbl_clk_delay) {
                printf(
                    "Land: %f, %f\n",
                    main_player.mob.pos.x,
                    main_player.mob.pos.y
                );
                bumbarrel_land_now(&main_player);
            }
            main_adjust_click_time = time;
            break;
        default:
            break;
        }
        break;
    default:
        break;
    }
}


// Main loop:
static int main_loop(void) {
    int last_update = 0;

    while(!main_quit_flag) {
        main_events();
        if (SDL_GetTicks() - last_update >= 1000 / MAIN_APP_FRAMERATE) {
            if (main_framerate_flag) {
                printf("%f\n", 1000 / (float) (SDL_GetTicks() - last_update));
            }
            bumbarrel_update(&main_player);
            main_draw();
            last_update = SDL_GetTicks();
        }
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
    SDL_Surface* screen;

    if (main_softscale == 1) {
        screen = main_screen;
    } else {
        screen = main_soft_screen;
    }
    
    SDL_FillRect(screen, NULL, 0);
    SDL_BlitSurface(
        main_background,
        NULL,
        screen,
        NULL
    );
    SDL_BlitSurface(
        main_player.sprite,
        &(main_player.src_rect),
        screen,
        &(main_player.rect)
    );

    if (main_softscale != 1) {
        SDL_Surface* scaled = zoomSurface(
            screen,
            main_softscale,
            main_softscale,
            FALSE
        );
        SDL_BlitSurface(
            scaled,
            NULL,
            main_screen,
            NULL
        );
        SDL_FreeSurface(scaled);
    }

    SDL_Flip(main_screen);
}


// Clean shutdown:
static int main_quit(void) {
    if (main_fullscreen_flag) {
        SDL_WM_ToggleFullScreen(main_screen);
    }
    if (main_softscale > 1) {
        SDL_FreeSurface(main_soft_screen);
    }

    IMG_Quit();
    SDL_Quit();
    printf("Good bye!\n");

    return 0;
}
