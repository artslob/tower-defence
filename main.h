#ifndef MAIN_H
#define MAIN_H

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>

#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480

SDL_Texture* getTextureFromPath(char*, SDL_Renderer*);
void showCursor(SDL_Renderer*, SDL_Texture*);

void waitForFps(size_t fps);
void prError(char*);

#endif // STD_H
