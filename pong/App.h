#ifndef APP_H
#define APP_H

#include "Defs.h"
#include "Manager.h"

#include <SDL2/SDL_events.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_video.h>

enum AppStatus {
  APP_QUIT,
  APP_RUN,
  APP_PAUSE,
};

typedef struct {
  SDL_Renderer *renderer;
  SDL_Window *window;
  SDL_Event event;
  Manager *manager;
  enum AppStatus status;
  int keyboard[APP_MAX_KEYBOARD_KEYS];
} App;

extern App app;

#endif // APP_H
