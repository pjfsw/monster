#include <stdio.h>
#include "monster_engine.h"

int main(int argc, char **argv) {
    MonsterEngine *me = me_create();
    me_destroy(me);
}
