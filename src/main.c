#include <stdio.h>
#include "mengine.h"

int main(int argc, char **argv) {
    MEngine *me = me_create();
    if (me == NULL) {
        return 1;
    }
    me_run(me);
    me_destroy(me);
    return 0;
}
