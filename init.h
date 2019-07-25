#ifndef INIT_H
#define INIT_H

#include <stdlib.h>
#include <stdio.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>

#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480


int init(SDL_Window**, SDL_Renderer**);
void close();

#endif // INIT_H
