#include "renderer.h"

#include <stdlib.h>

Renderer *renderer_create(int width, int height) {
    SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS);

    SDL_Rect display_rect;
    int display_index = 0; // TODO multiple display support
    if (SDL_GetDisplayUsableBounds(display_index, &display_rect)) {
        fprintf(stderr, "Failed to get display bounds: %s\n", SDL_GetError());
        return NULL;
    }

    Renderer *instance = calloc(1, sizeof(Renderer));
    instance->width = width;
    instance->height = height;
    int hscale = display_rect.w / width;
    int vscale = display_rect.h / height;
    int w = (hscale < vscale) ? width * hscale : width * vscale;
    int h = (hscale < vscale) ? height * hscale : height * vscale;

    if (SDL_CreateWindowAndRenderer(w,h,
            SDL_WINDOW_RESIZABLE | SDL_RENDERER_ACCELERATED,
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
    SDL_Quit();
    free(instance);
}

static void render_test(Renderer *instance) {
    SDL_SetRenderDrawColor(instance->renderer, 255,255,255,255);
    SDL_Rect rect;
    rect.w = 4;
    rect.h = 4;
    rect.x = 0;
    rect.y = 0;
    SDL_RenderDrawRect(instance->renderer, &rect);
    rect.x = instance->width-4;
    rect.y = instance->height-4;
    SDL_RenderDrawRect(instance->renderer, &rect);
}

void renderer_render_frame(Renderer *instance) {
    SDL_Renderer *renderer = instance->renderer;
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
    SDL_RenderClear(renderer);
    SDL_SetRenderTarget(renderer, instance->output->texture);
    SDL_RenderClear(renderer);
    render_test(instance);
    SDL_SetRenderTarget(renderer, NULL);
    int w;
    int h;
    SDL_GetWindowSize(instance->window, &w, &h);
    int h_scale = w/instance->width;
    int v_scale = h/instance->height;

    int render_width = (h_scale < v_scale) ? (instance->width * h_scale) : (instance->width * v_scale);    
    int render_height = (h_scale < v_scale) ? (instance->height * h_scale) : (instance->height * v_scale);
    int render_x = (w-render_width)/2;
    int render_y = (h-render_height)/2;
    SDL_Rect dest_rect = {.x = render_x, .y = render_y, .w = render_width, .h = render_height};

    SDL_RenderCopy(renderer, instance->output->texture, NULL, &dest_rect);
    SDL_RenderPresent(renderer);
}
