#include "renderer.h"

#include <stdlib.h>

Renderer *renderer_create(int width, int height) {
    Renderer *instance = calloc(1, sizeof(Renderer));
    instance->width = width;
    instance->height = height;

    if (SDL_CreateWindowAndRenderer(1280,720,
            SDL_WINDOW_ALLOW_HIGHDPI | SDL_WINDOW_RESIZABLE | SDL_RENDERER_ACCELERATED,
            &instance->window,
            &instance->renderer)) {
        fprintf(stderr, "Failed to create window: %s\n", SDL_GetError());
        renderer_destroy(instance);
        return NULL;
    }

    instance->textures = textures_create(10000, instance->renderer);
    if (NULL == (instance->output = textures_add(instance->textures, width, height))) {
        fprintf(stderr, "Failed to create output texture: %s\n", SDL_GetError());
        renderer_destroy(instance);
        return NULL;
    }

    return instance;
}

void renderer_destroy(Renderer *instance) {
    if (instance->renderer != NULL) {
        SDL_DestroyRenderer(instance->renderer);
    }
    if (instance->window != NULL) {
        SDL_DestroyWindow(instance->window);
    }
    if (instance->textures != NULL) {
        textures_destroy(instance->textures);
    }
    free(instance);
}

void renderer_render_frame(Renderer *instance) {
    SDL_Renderer *renderer = instance->renderer;
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
    SDL_RenderClear(renderer);
    SDL_RenderPresent(renderer);
}
