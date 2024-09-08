#include "input.h"

#include <stdlib.h>

#include "SDL.h"

Input *input_create() {
    Input *input = calloc(1, sizeof(Input));
    return input;
}

static void handle_event(Input *input, SDL_Event *event) {  
    if (event->type == SDL_QUIT) {
        input->state.is_quit = true;
    }  
    if (event->type == SDL_KEYDOWN) {
        SDL_Scancode scancode = event->key.keysym.scancode;
        //Uint16 mod = event->key.keysym.mod;
        if (scancode == SDL_SCANCODE_ESCAPE) {
            input->state.is_quit = true;
        }
    }
}

void input_poll(Input *input) {
    SDL_Event event;
    memset(&input->state, 0, sizeof(input->state));
    while (SDL_PollEvent(&event)) {
        handle_event(input, &event);
    }
}

bool input_is_quit(Input *input) {
    return input->state.is_quit;
}


void input_destroy(Input *input) {
    free(input);
}
