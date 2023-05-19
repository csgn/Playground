#include "Actor.h"
#include "App.h"
#include "Defs.h"

#include <SDL2/SDL_pixels.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_scancode.h>

#include <stdio.h>
#include <stdlib.h>

static void render() {
  Actor *player = app.manager->actors[0];
  SDL_SetRenderDrawColor(app.renderer, player->color.r, player->color.g,
                         player->color.b, player->color.a);
  SDL_RenderFillRect(app.renderer, &(player->object));
}

static void update() {
  Actor *player = app.manager->actors[0];

  if (app.keyboard[SDL_SCANCODE_W] && player->object.y > 0) {
    player->object.y += -8;
  }

  if (app.keyboard[SDL_SCANCODE_S] &&
      player->object.y < APP_WINDOW_HEIGHT - player->object.h) {
    player->object.y += 8;
  }
}

void player_init(Actor *player) {
  SDL_Color color = {0, 0, 255, 0};
  player->render = render;
  player->update = update;
  player->id = 0;
  player->tag = 0;
  player->index = 0;
  player->color = color;
  player->object.y = APP_WINDOW_HEIGHT / 2 - player->object.h / 2;

  app.manager->actors[player->index] = player;
  app.manager->actor_count++;
}
