#ifndef INIT_H
#define INIT_H

#include <stdlib.h>
#include <stdio.h>

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>

#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480


int init(SDL_Window**, SDL_Renderer**);
void close();

#endif // INIT_H
