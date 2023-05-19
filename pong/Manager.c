#include "Manager.h"
#include "Actor.h"
#include "App.h"
#include "Defs.h"
#include <SDL2/SDL_pixels.h>
#include <stdio.h>
#include <stdlib.h>

Actor *actor_init() {
  Actor *actor = (Actor *)malloc(sizeof(Actor));
  SDL_Color color = {255, 255, 255, 0};

  actor->id = 0;
  actor->index = 0;
  actor->tag = 0;
  actor->object.x = 0;
  actor->object.y = 0;
  actor->object.w = 16;
  actor->object.h = 48;
  actor->velocity = 8;
  actor->dirX = 1;
  actor->dirY = 1;
  actor->color = color;

  return actor;
}
