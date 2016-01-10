#ifndef MAIN_H
#define MAIN_H

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>

#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480


void render(int, int, SDL_Rect*, SDL_Surface*, SDL_Renderer*, SDL_Texture*, double, SDL_Point*, SDL_RendererFlip);
SDL_Texture* getTextureFromPath(char*, SDL_Renderer*);

void prError(char*);

#endif // STD_H
