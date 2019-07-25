#ifndef STARTSCREEN_H
#define STARTSCREEN_H

#include <stdlib.h>
#include <stdio.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>

#include "global.h"

#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480

#define BG_SPRITES 4

typedef struct ButtonMenu{
    SDL_Rect Rect;
    SDL_Texture* cur_texture;
    SDL_Texture* mouseInside;
    SDL_Texture* mouseOutside;
}ButtonMenu;

typedef struct VolumeMenu{
    SDL_Rect Rect;
    SDL_Texture* cur_texture;
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
