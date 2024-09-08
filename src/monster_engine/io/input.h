#ifndef _M_INPUT_H_
#define _M_INPUT_H

#include <stdbool.h>

typedef struct {
    bool is_quit;
} InputState;

typedef struct {
    InputState state;
} Input;

Input *input_create();

void input_poll(Input *input);

bool input_is_quit(Input *input);

void input_destroy(Input *input);

#endif