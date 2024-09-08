#include "textures.h"

#include <stdlib.h>

struct _Texture {
    SDL_Texture *texture;
    int width;
    int height;
};

struct _Textures {
    int capacity;
    int next;
    Texture **textures;
    SDL_Renderer *renderer;
};

Textures *textures_create(int capacity, SDL_Renderer *renderer) {
    Textures *textures = calloc(1, sizeof(Textures));
    textures->textures = calloc(capacity, sizeof(Texture*));
    textures->capacity = capacity;
    textures->renderer = renderer;
    return textures;
}

static Texture *add_or_error(Textures *this, SDL_Texture *sdl_texture, int width, int height) {
    if (sdl_texture == NULL) {
        fprintf(stderr, "Failed to create texture: %s\n", SDL_GetError());
        return NULL;
    }
    if (this->next >= this->capacity-1) {
        fprintf(stderr, "Number of textures exceeded!\n");
        return NULL;
    }
    Texture *texture = calloc(1, sizeof(Texture));
    texture->width = width;
    texture->height = height;
    texture->texture = sdl_texture;
    this->textures[this->next++] = texture;
    return texture;
}

Texture *textures_add(Textures *textures, int width, int height) {
    SDL_Texture *texture =
        SDL_CreateTexture(textures->renderer, SDL_PIXELFORMAT_RGBA32, SDL_TEXTUREACCESS_TARGET, width, height);
    return add_or_error(textures, texture, width, height);
}

void textures_destroy(Textures *textures) {
    for (int i = 0; i < textures->next; i++) {
        SDL_DestroyTexture(textures->textures[i]->texture);
        free(textures->textures[i]);
    }
    free(textures->textures);
    free(textures);
}

int texture_get_width(Texture *texture) {
    return texture->width;
}

int texture_get_height(Texture *texture) {
    return texture->height;
}
