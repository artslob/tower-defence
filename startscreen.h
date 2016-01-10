#ifndef STARTSCREEN_H
#define STARTSCREEN_H

#include <stdlib.h>
#include <stdio.h>

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>

#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480

enum GameStates{
    IN_MENU,
    START,
    EXIT
};

enum MouseStates{
    INSIDE_START,
    INSIDE_EXIT,
    INSIDE_VOLUME,
    PRESSED_START,
    PRESSED_EXIT,
    PRESSED_VOLUME
};

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


void initButtons(SDL_Renderer*, TTF_Font*, ButtonMenu*, ButtonMenu*, VolumeMenu*);
void renderInfinityText(SDL_Renderer*, SDL_Texture* );
SDL_Texture* loadTextTexture(char*, TTF_Font*, SDL_Color, SDL_Renderer*);




#endif // STARTSCREEN_H
