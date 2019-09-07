#ifndef MAIN_H
#define MAIN_H


#include "include_sdl2.h"
#include "bg.h"


#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480


typedef enum GameStates{
    IN_MENU,
    START,
    IN_GAME,
    GAME_OVER,
    WIN,
    EXIT
} GameStates;


void playLastScene(SDL_Renderer* Renderer, SDL_Window* Window, block* block_head, GameStates state);
SDL_Texture* getTextureFromPath(char* path, SDL_Renderer* Renderer);
int isInsideRect(int x, int y, SDL_Rect Rect);
void showCursor(SDL_Renderer* Renderer, SDL_Texture* cursor_texture);
void getFps(void);
void waitForFps(size_t fps);
void prError(char* str);


#endif // MAIN_H
