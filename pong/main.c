#include "Actor.h"
#include "App.h"
#include "Ball.h"
#include "Defs.h"
#include "Enemy.h"
#include "Manager.h"
#include "Player.h"

#include <SDL2/SDL.h>
#include <SDL2/SDL_error.h>
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_scancode.h>
#include <SDL2/SDL_timer.h>
#include <SDL2/SDL_video.h>

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

App app;

static void keydown(SDL_KeyboardEvent *event) {
  if (event->repeat == 0 && event->keysym.scancode < APP_MAX_KEYBOARD_KEYS) {
    app.keyboard[event->keysym.scancode] = 1;
  }
}

static void keyup(SDL_KeyboardEvent *event) {
  if (event->repeat == 0 && event->keysym.scancode < APP_MAX_KEYBOARD_KEYS) {
    app.keyboard[event->keysym.scancode] = 0;
  }
}

static void flush() {
  SDL_SetRenderDrawColor(app.renderer, 0, 0, 0, 0);
  SDL_RenderClear(app.renderer);
}

static void event_poll() {
  // input
  while (SDL_PollEvent(&(app.event))) {
    switch (app.event.type) {
    case SDL_QUIT:
      exit(EXIT_SUCCESS);
      break;
    case SDL_KEYDOWN:
      keydown(&(app.event).key);
      break;
    case SDL_KEYUP:
      keyup(&(app.event).key);
      break;
    default:
      break;
    }
  }
}

static void loop() {
  while (app.status != APP_QUIT) {
    flush();
    event_poll();

    for (int i = 0; i < app.manager->actor_count; i++) {
      if (app.status != APP_PAUSE) {
        app.manager->actors[i]->update();
      }
      app.manager->actors[i]->render();
    }

    if (app.keyboard[SDL_SCANCODE_P]) {
      app.status = APP_PAUSE;
    }

    if (app.keyboard[SDL_SCANCODE_N]) {
      app.status = APP_RUN;
    }

    SDL_RenderPresent(app.renderer);
    SDL_Delay(16);
  }
}

static int init() {
  SDL_Window *window;
  SDL_Renderer *renderer;
  SDL_Event event;
  Manager *manager;

  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    return EXIT_FAILURE;
  }

  window = SDL_CreateWindow(APP_WINDOW_TITLE, SDL_WINDOWPOS_UNDEFINED,
                            SDL_WINDOWPOS_UNDEFINED, APP_WINDOW_WIDTH,
                            APP_WINDOW_HEIGHT, SDL_WINDOW_SHOWN);

  if (window == NULL) {
    printf("Window is not created: %s\n", SDL_GetError());
    SDL_Quit();
    return EXIT_FAILURE;
  }

  renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
  manager = (Manager *)malloc((sizeof(Manager)));
  memset(manager, 0, sizeof(Manager));

  if (renderer == NULL) {
    printf("Renderer is not created: %s\n", SDL_GetError());
    SDL_DestroyWindow(window);
    SDL_Quit();
    return EXIT_FAILURE;
  }

  if (manager == NULL) {
    printf("Manager is not created\n");
    SDL_DestroyWindow(window);
    SDL_Quit();
    return EXIT_FAILURE;
  }

  manager->actors = (Actor **)malloc(sizeof(Actor *));
  manager->actor_count = 0;
  memset(manager->actors, 0, sizeof(Actor *));

  app.status = APP_RUN;
  app.event = event;
  app.window = window;
  app.renderer = renderer;
  app.manager = manager;

  Actor *player = actor_init();
  Actor *enemy = actor_init();
  Actor *ball = actor_init();

  player_init(player);
  enemy_init(enemy);
  ball_init(ball);

  for (int i = 0; i < app.manager->actor_count; i++) {
    Actor *a = app.manager->actors[i];
    printf("Actor: %ld (x: %d, y: %d)\n", a->id, a->object.x, a->object.y);
  }

  loop();

  return EXIT_SUCCESS;
}

int main(int argc, char *argv[]) { exit(init()); }
