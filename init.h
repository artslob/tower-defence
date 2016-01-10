#ifndef INIT_H
#define INIT_H

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>

/* screen dimension constants */
#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480


/* initialazion, load media, delete media and close sdl */
int init(SDL_Window**, SDL_Renderer**);
void close();

#endif // INIT_H
