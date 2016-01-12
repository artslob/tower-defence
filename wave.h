#ifndef WAVE_H
#define WAVE_H

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>

#include "bg.h"

#define COUNT_IN_WAVE 10

enum WavePosition{
    POS_UP,
    POS_DOWN
};

typedef struct points{
    int pos_x_1;
    int pos_y_1;
    int pos_x_2;
    int pos_y_2;
    int pos_x_3;
    int pos_y_3;
    int pos_x_4;
    int pos_y_4;
    int pos_x_5;
    int pos_y_5;
    int pos_x_6;
    int pos_y_6;
    int pos_x_7;
    int pos_y_7;
    int pos_x_8;
    int pos_y_8;
    int pos_x_9;
    int pos_y_9;
    int pos_x_10;
    int pos_y_10;
    int pos_x_11;
    int pos_y_11;
}points;

typedef struct enemy{
    SDL_Texture* textureEnemy;
    float health;
    int angle;
    int isAlive;
    int level;
    int position;
    int x;
    int y;
    struct enemy* next;
}enemy;

typedef struct sprites_enemy{
    SDL_Texture* sprite_enemy1;
    SDL_Texture* sprite_enemy2;
    SDL_Texture* sprite_enemy3;
    SDL_Texture* sprite_enemy4;
    SDL_Texture* sprite_enemy5;
    SDL_Texture* sprite_enemy6;
    SDL_Texture* sprite_enemy7;
    SDL_Texture* sprite_enemy8;
    SDL_Texture* sprite_enemy9;
    SDL_Texture* sprite_enemy10;
    SDL_Texture* sprite_enemy11;
    SDL_Texture* sprite_enemy12;
    SDL_Texture* sprite_enemy13;
    SDL_Texture* sprite_enemy14;
    SDL_Texture* sprite_enemy15;
}sprites_enemy;

enemy* createEnemy(SDL_Texture*);
void add_enemy(enemy**, SDL_Texture*);
sprites_enemy* init_sprites_enemy(SDL_Renderer*);
void createListEnemy(enemy**, SDL_Renderer*);
void moveEnemies(enemy*,points*, points*);
void renderEnemies(SDL_Renderer*, enemy*);
int check_point(enemy*, points*);
void enemyEnterCave(enemy*, points*, int* hp);

#endif // WAVE_H
