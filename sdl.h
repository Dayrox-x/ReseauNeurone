#ifndef SDL_H
#define SDL_H

#include "population.h"
#include <SDL2/SDL.h>
#include <assert.h>

void renderImage(Image image, SDL_Renderer* renderer, SDL_Window* window, SDL_Rect pixel, int pxl_size);

#endif