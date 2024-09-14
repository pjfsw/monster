#include "tilemap_creator.h"

#include <string.h>

static char *map[] = {
    "XXXXXXXXXXXXXXXXXXXX",
    "X        XX        X",
    "X        XX        X",
    "X        XX   XX   X",
    "XXXXX    XX   XX   X",
    "X        XX   XX   X",
    "X        XX   XX   X",
    "X             XX   X",
    "X             XX   X",
    "X        XXXXXXX   X",
    "X        XX        X",
    "XXXXXXXXXXXXXXXXXXXX",
};

Tilemap *tilemap_generate() {
    int height = sizeof(map)/sizeof(char**);
    int width = 0;
    for (int y = 0; y < height; y++) {
        int this_width = strlen(map[y]);
        if (this_width > width) {
            width = this_width;
        }
    }
    Tilemap *tilemap = tilemap_create(height, width);
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            if ((x >= (int)strlen(map[y])) || (map[y][x] != ' ')) {
                tilemap->tiles[y][x].tile_id = 1;
            }
        }
    }
    return tilemap;
}