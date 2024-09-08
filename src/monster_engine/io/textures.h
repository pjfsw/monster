#ifndef _M_TEXTURES_H
#define _M_TEXTURES_H

#include "SDL.h"

typedef struct _Textures Textures;
typedef struct _Texture Texture;

Textures *textures_create(int capacity, SDL_Renderer *renderer);

Texture *textures_add(Textures *textures, int width, int height);

void textures_destroy(Textures *textures);

int texture_get_width(Texture *texture);

int texture_get_height(Texture *texture);

#endif