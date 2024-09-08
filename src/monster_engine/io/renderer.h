#ifndef _M_RENDERER_H_
#define _M_RENDERER_H_

#include "SDL.h"
#include "textures.h"


typedef struct {
    // Playfield width
    int width;
    // Playfield height
    int height;
    SDL_Window *window;
    SDL_Renderer *renderer;
    Textures *textures;
    Texture *output;
} Renderer;

Renderer *renderer_create(int width, int height);

void renderer_render_frame(Renderer *instance);

void renderer_destroy(Renderer *instance);

#endif
