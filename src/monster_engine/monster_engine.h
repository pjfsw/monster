#ifndef _MONSTER_ENGINE_H
#define _MONSTER_ENGINE_H

typedef struct {
    int v;
} MonsterEngine;

MonsterEngine *me_create();

void me_destroy(MonsterEngine *me);
 
#endif