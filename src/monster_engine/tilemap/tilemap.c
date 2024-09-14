#include "tilemap.h"

#include <stdlib.h>

Tilemap *tilemap_create(int height, int width) {
    Tilemap *tm = calloc(1, sizeof(Tilemap));
    tm->height = height;
    tm->width = width;
    tm->tiles = calloc(height, sizeof(Tile*));
    for (int i = 0; i < height; i++) {
        tm->tiles[i] = calloc(width, sizeof(Tile));
    }
    return tm;
}

void tilemap_destroy(Tilemap *tm) {
    for (int i = 0; i < tm->height; i++) {
        free(tm->tiles[i]);
    }
    free(tm->tiles);
    free(tm);
}
