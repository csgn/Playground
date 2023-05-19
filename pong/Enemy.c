#include "Actor.h"
#include "App.h"
#include "Defs.h"

#include <SDL2/SDL_pixels.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_scancode.h>

#include <stdio.h>
#include <stdlib.h>

static void render() {
  Actor *enemy = app.manager->actors[1];
  SDL_SetRenderDrawColor(app.renderer, enemy->color.r, enemy->color.g,
                         enemy->color.b, enemy->color.a);
  SDL_RenderFillRect(app.renderer, &(enemy->object));
}

static void update() {
  Actor *enemy = app.manager->actors[1];

  if (app.keyboard[SDL_SCANCODE_UP] && enemy->object.y > 0) {
    enemy->object.y += -8;
  }

  if (app.keyboard[SDL_SCANCODE_DOWN] &&
      enemy->object.y < APP_WINDOW_HEIGHT - enemy->object.h) {
    enemy->object.y += 8;
  }
}

void enemy_init(Actor *enemy) {
  SDL_Color color = {255, 0, 0, 0};
  enemy->render = render;
  enemy->update = update;
  enemy->id = 1;
  enemy->tag = 0;
  enemy->index = 1;
  enemy->object.x = APP_WINDOW_WIDTH - enemy->object.w;
  enemy->object.y = APP_WINDOW_HEIGHT / 2 - enemy->object.h / 2;
  enemy->color = color;

  app.manager->actors[enemy->index] = enemy;
  app.manager->actor_count++;
}
