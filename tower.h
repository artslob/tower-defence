#ifndef TOWER_H
#define TOWER_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>
#include <math.h>

#include "bg.h"
#include "wave.h"

#define COUNT_TOWER 5
#define COUNT_SPRITES_TOWER 8
#define PI 3.14159265

typedef struct tower{
    SDL_Texture* texture;
    float damage;
    int level;
    int cost;
    int x;
    int y;
    int angle;
    int radius;
    struct tower* next;
}tower;

tower* createTower(void);
void addTower(tower**);
void createListTower(tower**);
tower* clickedOnTowerPosition(tower*, int, int);

void initTowerTextures(SDL_Texture* enemy_sprites[COUNT_SPRITES_TOWER], SDL_Renderer* Renderer);

#endif // TOWER_H
