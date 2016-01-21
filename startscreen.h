#ifndef STARTSCREEN_H
#define STARTSCREEN_H

#include <stdlib.h>
#include <stdio.h>

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>

#include "main.h"

#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480


typedef struct ButtonMenu{
    SDL_Rect Rect;
    SDL_Texture* mouseInside;
    SDL_Texture* mouseOutside;
}ButtonMenu;

typedef struct VolumeMenu{
    SDL_Rect Rect;
    SDL_Texture* mouseInside_volOn;
    SDL_Texture* mouseOutside_volOn;
    SDL_Texture* mouseInside_volOff;
    SDL_Texture* mouseOutside_volOff;
}VolumeMenu;

int menu(SDL_Renderer*);
void initButtons(SDL_Renderer*, TTF_Font*, ButtonMenu*, ButtonMenu*, VolumeMenu*);
void renderInfinityText(SDL_Renderer*, SDL_Texture*,int*, int, int, float);
SDL_Texture* loadTextTexture(char*, TTF_Font*, SDL_Color, SDL_Renderer*);




#endif // STARTSCREEN_H
