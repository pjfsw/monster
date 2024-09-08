#ifndef _M_ENGINE_H
#define _M_ENGINE_H

#include "io/renderer.h"
#include "io/input.h"

typedef struct {
    Renderer *renderer;
    Input *input;
} MEngine;

MEngine *me_create();

void me_run(MEngine *me);

void me_destroy(MEngine *me);
 
#endif