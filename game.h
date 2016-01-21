#ifndef GAME_H
#define GAME_H

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>

#include "main.h"
#include "startscreen.h"
#include "wave.h"
#include "tower.h"

#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480


int game(SDL_Renderer*, block*);
SDL_Texture* getTextureFromInt(int number, char* buff, TTF_Font* Font, SDL_Color textColor, SDL_Renderer* Renderer);


#endif // GAME_H
