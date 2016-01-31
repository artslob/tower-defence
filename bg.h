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

#define BG_TALES_COUNT 16

typedef struct block{
    SDL_Texture* texture;
    struct block* next;
}block;

block* block_create(SDL_Texture*);
void BG_list_create(SDL_Renderer*, block**);
void add_block(block**, block**, SDL_Texture*);
int* openMap(char*);
void BG_list_render(SDL_Renderer*, block*);
static void init_bg_tales(SDL_Texture* array_tales[BG_TALES_COUNT], SDL_Renderer* Renderer);


#endif // BG_H
