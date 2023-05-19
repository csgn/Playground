#ifndef ACTOR_H
#define ACTOR_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_pixels.h>
#include <SDL2/SDL_rect.h>

typedef struct {
  long int id;     // object id
  int index;       // index number
  int tag;         // object tag
  int velocity;    // movement speed
  SDL_Color color; // object color
  SDL_Rect object; // rectangle object

  void (*render)(void);
  void (*update)(void);
} Actor;

#endif // ACTOR_H
