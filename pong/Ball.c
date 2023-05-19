#include "Actor.h"
#include "App.h"
#include "Defs.h"

#include <SDL2/SDL_pixels.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_scancode.h>

#include <stdio.h>
#include <stdlib.h>

Actor *ball;

static void render() {
  Actor *ball = app.manager->actors[2];
  SDL_SetRenderDrawColor(app.renderer, ball->color.r, ball->color.g,
                         ball->color.b, ball->color.a);
  SDL_RenderFillRect(app.renderer, &(ball->object));
}

static void update() {
  Actor *ball = app.manager->actors[2];
  Actor *e = app.manager->actors[1];
  Actor *p = app.manager->actors[0];
}

void ball_init(Actor *ball) {
  ball->render = render;
  ball->update = update;
  ball->id = 2;
  ball->tag = 1;
  ball->index = 2;
  ball->object.w = 10;
  ball->object.h = 10;
  ball->object.x = APP_WINDOW_WIDTH / 2 - ball->object.w;
  ball->object.y = APP_WINDOW_HEIGHT / 2 - ball->object.h;
  ball->velocity = 4;

  app.manager->actors[ball->index] = ball;
  app.manager->actor_count++;
}
