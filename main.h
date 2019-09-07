#ifndef MAIN_H
#define MAIN_H


#include "include_sdl2.h"
#include "bg.h"


#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480


typedef enum GameStates {
    IN_MENU,
    START,
    IN_GAME,
    GAME_OVER,
    WIN,
    EXIT
} GameStates;


void playLastScene(SDL_Renderer* Renderer, SDL_Window* Window, block* block_head, GameStates state);


#endif // MAIN_H
