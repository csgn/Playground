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

  if ((p->object.x < ball->object.x &&
       p->object.x + p->object.w > ball->object.x) &&
      (p->object.y + p->object.h > ball->object.y &&
       p->object.y < ball->object.y)) {
    ball->dirX = 1;
  } else if ((e->object.x - ball->object.w <= ball->object.x &&
              e->object.x + e->object.w >= ball->object.x) &&
             (e->object.y + e->object.h > ball->object.y &&
              e->object.y < ball->object.y)) {
    ball->dirX = -1;
  } else if (ball->object.y <= 0) {
    ball->dirY = 1;
  } else if (ball->object.y >= APP_WINDOW_HEIGHT - ball->object.h) {
    ball->dirY = -1;
  }
  ball->object.x += ball->velocity * ball->dirX;
  ball->object.y += ball->velocity * ball->dirY;

  if (ball->object.x > APP_WINDOW_WIDTH || ball->object.x < 0) {
    ball->object.x = APP_WINDOW_WIDTH / 2 - ball->object.w;
    ball->object.y = APP_WINDOW_HEIGHT / 2 - ball->object.h;

    ball->dirX *= -1;
    ball->dirY *= -1;
  }
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
