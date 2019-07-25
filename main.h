#ifndef MAIN_H
#define MAIN_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>

#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480

SDL_Texture* getTextureFromPath(char*, SDL_Renderer*);
void showCursor(SDL_Renderer*, SDL_Texture*);

void waitForFps(size_t fps);
void prError(char*);

#endif // STD_H
