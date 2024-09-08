#include "mengine.h"

#include <stdlib.h>
#include <stdio.h>

MEngine *me_create() {
    MEngine *me = calloc(1, sizeof(MEngine));
    me->renderer = renderer_create(320,180);
    if (me->renderer == NULL) {
        me_destroy(me);
        return NULL;
    }
    me->input = input_create();
    return me;
}

void me_run(MEngine *me) {
    Input *input = me->input;
    Renderer *renderer = me->renderer;
    while (true) {
        input_poll(input);
        if (input_is_quit(input)) {
            printf("Termination requested\n");
            return;
        }
        renderer_render_frame(renderer);
    }    
}

void me_destroy(MEngine *me) {
    if (me->input != NULL) {
        input_destroy(me->input);
    }
    if (me->renderer != NULL) {
        renderer_destroy(me->renderer);
    }
    free(me);
}
