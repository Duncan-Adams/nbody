#ifndef RENDER_H
#define RENDER_H

#include "include.h"

SDL_Window* win;
SDL_Renderer* ren;

void render(Body* list, int n, camera c);


#endif
