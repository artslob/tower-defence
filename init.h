#ifndef INIT_H
#define INIT_H


#include <stdlib.h>
#include <stdio.h>

#include "include_sdl2.h"


#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480


int init(SDL_Window**, SDL_Renderer**);
void closeSDLResources(SDL_Renderer**, SDL_Window**);


#endif // INIT_H
