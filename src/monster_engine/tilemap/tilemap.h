#ifndef _TILEMAP_H_
#define _TILEMAP_H_

typedef struct {
    int tile_id;
} Tile;

typedef struct {
    int width;
    int height;
    Tile **tiles;
} Tilemap;

Tilemap *tilemap_create(int height, int width);

void tilemap_destroy(Tilemap *tilemap);

#endif
