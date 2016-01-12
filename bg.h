#ifndef BG_H
#define BG_H

#include <stdlib.h>
#include <stdio.h>
#include <malloc.h>

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>

#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480

#define COUNT_BLOCKS_WIDTH 16
#define COUNT_BLOCKS_HEIGHT 12

#define BLOCK_WIDTH 40
#define BLOCK_HEIGHT 40

typedef struct block{
    SDL_Texture* texture;
    struct block* next;
}block;

typedef struct tiles{
    SDL_Texture* texture1;
    SDL_Texture* texture2;
    SDL_Texture* texture3;
    SDL_Texture* texture4;
    SDL_Texture* texture5;
    SDL_Texture* texture6;
    SDL_Texture* texture7;
    SDL_Texture* texture8;
    SDL_Texture* texture9;
    SDL_Texture* texture10;
    SDL_Texture* texture11;
    SDL_Texture* texture12;
    SDL_Texture* texture13;
    SDL_Texture* texture14;
    SDL_Texture* texture15;
    SDL_Texture* texture16;
}tiles;

block* block_create(SDL_Texture*);
void BG_list_create(SDL_Renderer*, block**);
void add_block(block**, block**, SDL_Texture*);
int* openMap(char*);
tiles* init_tales(SDL_Renderer*);
void BG_list_render(SDL_Renderer*, block*);


#endif // BG_H
