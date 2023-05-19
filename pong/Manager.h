#ifndef MANAGER_H
#define MANAGER_H

#include "Actor.h"

typedef struct {
  Actor **actors;
  int actor_count;
} Manager;

Actor *actor_init();

#endif // MANAGER_H
