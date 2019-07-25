#ifndef WAVE_H
#define WAVE_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>

#include "bg.h"

#define COUNT_IN_WAVE 10
#define PICT_SIZE 48

#define ENEMY_COUNT_SPRITES 7
#define POINTS_COUNT 11

enum WavePosition{
    POS_UP,
    POS_DOWN
};

enum Directiom{
    MOV_UP,
    MOV_DOWN,
    MOV_RIGHT
};

typedef struct point{
    int x;
    int y;
}point;

 typedef struct enemy{
    SDL_Texture* textureEnemy;
    float Max_health;
    float health;
    int angle;
    int price;
    int isAlive;
    int inCave;
    int level;
    int position;
    int x;
    int y;
    struct enemy* next;
}enemy;

enemy* createEnemy(SDL_Texture*);
void add_enemy(enemy**, SDL_Texture*);
void createListEnemy(enemy** head, SDL_Renderer* Renderer, SDL_Texture* enemy_sprites[ENEMY_COUNT_SPRITES]);
void moveEnemies(enemy* head, point points_up[POINTS_COUNT], point points_down[POINTS_COUNT]);
void renderEnemies(SDL_Renderer*, enemy*, int);
void enemyEnterCave(enemy* head, point array_points[POINTS_COUNT], int* hp);
void showHPbar(SDL_Renderer*, enemy*);
point createPoint(int x, int y);

#endif // WAVE_H
