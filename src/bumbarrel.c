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
 *  File: bumbarrel.c
 *  Logic specific to bumbarrels
 */

#include <math.h>

#include "bumbarrel.h"
#include "mobs.h"
#include "sprites.h"
#include "util.h"


/* Global variables */

// Sprite states:
sprites_state bumbarrel_perch = {
    .index  = bumbarrel_SPRITE_PERCH,
    .frames = 4,
    .pad    = bumbarrel_SPRITE_OFFS,
    .width  = bumbarrel_SPRITE_SIZE,
    .height = bumbarrel_SPRITE_SIZE,
    .time   = 200,
    .transitions = {
        {0.5, 0.7, 0.9, 1.0},
        {0.7, 0.0, 1.0, 0.0},
        {0.2, 0.3, 0.8, 1.0},
        {0.1, 0.0, 1.0, 0.0}
    }
};
sprites_state bumbarrel_perch_no_tail = {
    .index  = bumbarrel_SPRITE_PERCH_NT,
    .frames = 4,
    .pad    = bumbarrel_SPRITE_OFFS,
    .width  = bumbarrel_SPRITE_SIZE,
    .height = bumbarrel_SPRITE_SIZE,
    .time   = 200,
    .transitions = {
        {0.5, 0.7, 0.9, 1.0},
        {0.7, 0.0, 1.0, 0.0},
        {0.2, 0.3, 0.8, 1.0},
        {0.1, 0.0, 1.0, 0.0}
    }
};
sprites_state bumbarrel_fly = {
    .index  = bumbarrel_SPRITE_FLY,
    .frames = 6,
    .pad    = bumbarrel_SPRITE_OFFS,
    .width  = bumbarrel_SPRITE_SIZE,
    .height = bumbarrel_SPRITE_SIZE,
    .time   = 125,
    .transitions = {
        {0.0, 0.8, 0.0, 0.0, 1.0, 0.0},
        {0.2, 0.0, 0.6, 0.7, 0.0, 1.0},
        {0.3, 0.0, 0.6, 0.0, 0.8, 1.0},
        {0.0, 0.6, 0.0, 0.0, 1.0, 0.0},
        {0.3, 0.0, 0.6, 0.8, 0.0, 1.0},
        {0.2, 0.0, 0.5, 0.0, 0.7, 1.0},
    }
};
sprites_state bumbarrel_glide = {
    .index  = bumbarrel_SPRITE_GLIDE,
    .frames = 2,
    .pad    = bumbarrel_SPRITE_OFFS,
    .width  = bumbarrel_SPRITE_SIZE,
    .height = bumbarrel_SPRITE_SIZE,
    .time   = 167,
    .transitions = {
        {0.4, 1.0},
        {0.2, 1.0},
    }
};
sprites_state bumbarrel_land = {
    .index  = bumbarrel_SPRITE_LAND,
    .frames = 3,
    .pad    = bumbarrel_SPRITE_OFFS,
    .width  = bumbarrel_SPRITE_SIZE,
    .height = bumbarrel_SPRITE_SIZE,
    .time   = 111,
    .transitions = {
        {0.0, 1.0, 0.0},
        {0.0, 0.0, 1.0},
        {0.0, 0.0, 1.0},
    }
};
sprites_state bumbarrel_sleep = {
    .index  = bumbarrel_SPRITE_SLEEP,
    .frames = 4,
    .pad    = bumbarrel_SPRITE_OFFS,
    .width  = bumbarrel_SPRITE_SIZE,
    .height = bumbarrel_SPRITE_SIZE,
    .time   = 500,
    .transitions = {
        {0.6, 0.8, 0.9, 1.0},
        {0.2, 0.8, 0.9, 1.0},
        {0.1, 0.2, 0.8, 1.0},
        {0.1, 0.2, 0.4, 1.0}
    }
};
sprites_state bumbarrel_sleep_no_tail = {
    .index  = bumbarrel_SPRITE_SLEEP_NT,
    .frames = 4,
    .pad    = bumbarrel_SPRITE_OFFS,
    .width  = bumbarrel_SPRITE_SIZE,
    .height = bumbarrel_SPRITE_SIZE,
    .time   = 500,
    .transitions = {
        {0.6, 0.8, 0.9, 1.0},
        {0.2, 0.8, 0.9, 1.0},
        {0.1, 0.2, 0.8, 1.0},
        {0.1, 0.2, 0.4, 1.0}
    }
};


/* Function prototypes */

static void bumbarrel_set_next_frame(bumbarrel* bbl);


/* External function definitions */

// Initialise player:
bumbarrel bumbarrel_init_player(int x, int y) {
    int             frame = 0;
    bumbarrel_state state = bumbarrel_PERCH;
    mobs_mob        mob = mobs_new();
    SDL_Rect rect = {
        .x = 0, .y = 0,
        .w = bumbarrel_SPRITE_SIZE, .h = bumbarrel_SPRITE_SIZE
    };
    SDL_Rect src_rect = {
        .x = 0, .y = 0,
        .w = bumbarrel_SPRITE_SIZE, .h = bumbarrel_SPRITE_SIZE
    };
    mob.pos.x = x;
    mob.pos.y = y;
    bumbarrel player = {
        .sprite     = sprites_bumbarrel,
        .rect       = rect,
        .src_rect   = src_rect,
        .state      = state,
        .frame      = frame,
        .mob        = mob
    };
    
    bumbarrel_update(&player);
    bumbarrel_set_next_frame(&player);

    return player;
}


void bumbarrel_update(bumbarrel* bbl) {
    bumbarrel_state state   = bbl->state;
    mobs_velocity   vel;

    switch (bbl->state) {
    case bumbarrel_SLEEP:
    case bumbarrel_PERCH:
        break;
    case bumbarrel_LAND:
        if (bbl->frame == bumbarrel_land.frames - 1) {
            bbl->state = bumbarrel_PERCH;
        }
        break;
    default:
        mobs_kinematics(&(bbl->mob), 1e-2);
        vel = bbl->mob.vel;
        if (vel.x > 0) {
            bbl->mob.dir = (bbl->mob.dir & ~mobs_DIR_HOR) | mobs_DIR_RIGHT;
        } else if (vel.x < 0) {
            bbl->mob.dir = (bbl->mob.dir & ~mobs_DIR_HOR) | mobs_DIR_LEFT;
        }
        if (vel.x == 0 && vel.y == 0) {
            bbl->state = bumbarrel_LAND;
            bbl->frame = -1;
        } else if (vel.y < 0 && (fabs(vel.x) < fabs(vel.y))) {
            bbl->state = bumbarrel_GLIDE;
        } else {
            bbl->state = bumbarrel_FLY;
        }
        break;
    }

    bbl->rect.x = bbl->mob.pos.x + bbl->rect.w / 2;
    bbl->rect.y = screen_HEIGHT - (bbl->mob.pos.y + bbl->rect.h / 2);


    if (state != bbl->state) {
        bumbarrel_set_next_frame(bbl);
    }
    bumbarrel_set_next_frame(bbl);
}

void bumbarrel_land_now(bumbarrel* bbl) {
    bbl->mob.vel.x = 0;
    bbl->mob.vel.y = 0;
    bbl->state = bumbarrel_LAND;
    bbl->frame = -1;
}


void bumbarrel_sleep_now(bumbarrel* bbl) {
    if (bbl->state != bumbarrel_PERCH) {
        return;
    }

    bbl->state = bumbarrel_SLEEP;
    bbl->frame = -1;
}


void bumbarrel_fly_towards(util_vector pos, bumbarrel* bbl) {
    util_vector delta = {
        .x = pos.x - bbl->mob.pos.x,
        .y = pos.y - bbl->mob.pos.y
    };
    float norm = sqrt(delta.x * delta.x + delta.y * delta.y);
    if (norm == 0) {
        return;
    }
    util_vector speed = {
        .x = bumbarrel_SPEED * delta.x / norm,
        .y = bumbarrel_SPEED * delta.y / norm
    };

    bbl->mob.vel.x += speed.x;
    bbl->mob.vel.y += speed.y;
    bbl->state = bumbarrel_FLY;
}


void bumbarrel_face(util_vector pos, bumbarrel* bbl) {
    if (pos.x > bbl->mob.pos.x) {
        bbl->mob.dir = (bbl->mob.dir & ~mobs_DIR_HOR) | mobs_DIR_RIGHT;
    } else if (pos.x < bbl->mob.pos.x) {
        bbl->mob.dir = (bbl->mob.dir & ~mobs_DIR_HOR) | mobs_DIR_LEFT;
    }
}


/* Static function definitions: */

// Set next frame given state:
static void bumbarrel_set_next_frame(bumbarrel* bbl) {
    sprites_state*  state;
    double          random;

    switch (bbl->state) {
    case bumbarrel_PERCH:
        state = &bumbarrel_perch;
        break;
    case bumbarrel_FLY:
        state = &bumbarrel_fly;
        break;
    case bumbarrel_GLIDE:
        state = &bumbarrel_glide;
        break;
    case bumbarrel_LAND:
        state = &bumbarrel_land;
        break;
    case bumbarrel_SLEEP:
        state = &bumbarrel_sleep;
        break;
    default:
        break;
    }

    if (bbl->frame < 0 || bbl->frame >= state->frames) {
        bbl->frame = 0;
    } else {
        random = (double) rand() / RAND_MAX;
        for (int i = 0; i < state->frames; i++) {
            if (random < state->transitions[bbl->frame][i]) {
                bbl->frame = i;
                break;
            }
        }
    }
    bbl->src_rect.x = bbl->frame * (state->width + state->pad) + state->pad;
    bbl->src_rect.y = (bbl->mob.dir * bumbarrel_STATES_COUNT + state->index)
                      * (state->height + state->pad) + state->pad;
}
