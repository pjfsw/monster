#include "monster_engine.h"

#include <stdlib.h>

MonsterEngine *me_create() {
    MonsterEngine *me = calloc(1, sizeof(MonsterEngine));
    return me;
}

void me_destroy(MonsterEngine *me) {
    free(me);
}
