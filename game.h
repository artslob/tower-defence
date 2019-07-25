#ifndef GAME_H
#define GAME_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>

#include "main.h"
#include "global.h"
#include "startscreen.h"
#include "wave.h"
#include "tower.h"

#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480

#define REWIND_FACTOR (18 / 10)

enum states_tewind{
    IN_REWIND,
    NOT_IN_REWIND
};

typedef struct rewind_button{
    SDL_Texture* rewindOn_inside;
    SDL_Texture* rewindOn_outside;
    SDL_Texture* rewindOff_inside;
    SDL_Texture* rewindOff_outside;
    SDL_Rect Rect;
}rewind_button;


int game(SDL_Renderer*, block*);
SDL_Texture* getTextureFromInt(int number, char* buff, TTF_Font* Font, SDL_Color textColor, SDL_Renderer* Renderer);


#endif // GAME_H
