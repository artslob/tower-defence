#include "wave.h"

enemy* createEnemy(SDL_Texture* texture){
    enemy* newEnemy = malloc(sizeof(enemy));
    newEnemy->textureEnemy = texture;
    newEnemy->next = NULL;
    return newEnemy;
}

void createListEnemy(enemy** head, SDL_Renderer* Renderer){
    sprites_enemy* sprites = init_sprites_enemy(Renderer);
    enemy* current_enemy = NULL;
    int count;

    for (count = 0; count < COUNT_IN_WAVE; count++){
        add_enemy(head, sprites->sprite_enemy1);
    }
    current_enemy = *head;
    for (count = 0; count < COUNT_IN_WAVE; count++){
        current_enemy->health = 100;
        current_enemy->isAlive = 1;
        current_enemy->level = 1;
        current_enemy->angle = 0;
        if (count < COUNT_IN_WAVE / 2){
            current_enemy->position = POS_UP;
            current_enemy->y = 40;
            current_enemy->x = -200 + BLOCK_WIDTH * count;
        }
        else{
            current_enemy->position = POS_DOWN;
            current_enemy->y = 400;
            current_enemy->x = -400 + BLOCK_WIDTH * count;
        }
        current_enemy = current_enemy->next;
    }

}

void moveEnemies(enemy* head, points* points_up, points* points_down){
    int count = 0;
    int check = 0;
    enemy* current_enemy = head;
    for (count = 0; count < COUNT_IN_WAVE; count++){
        if (current_enemy->position == POS_UP){
            if (current_enemy->y == points_up->pos_y_1) current_enemy->x++;
            if (current_enemy->x == points_up->pos_x_2) {
                current_enemy->y++;
                current_enemy->angle = 90;
            }
            if (current_enemy->y == points_up->pos_y_2) {
                current_enemy->x++;
                current_enemy->angle = 0;
            }
            if (current_enemy->x == points_up->pos_x_3){
                current_enemy->y++;
                current_enemy->angle = 90;
            }
            if (current_enemy->y == points_up->pos_y_4 & current_enemy->x < points_up->pos_x_7){
                current_enemy->x++;
                current_enemy->angle = 0;
            }
            if (current_enemy->x == points_up->pos_x_5){
                current_enemy->y++;
                current_enemy->angle = 90;
            }
            if (current_enemy->y == points_up->pos_y_6){
                current_enemy->x++;
                current_enemy->angle = 0;
            }
            if (current_enemy->x == points_up->pos_x_7){
                current_enemy->y--;
                current_enemy->angle = -90;
            }
            if (current_enemy->x == points_up->pos_x_9){
                current_enemy->y++;
                current_enemy->angle = 90;
            }
        }
        else{
            if (current_enemy->y == points_down->pos_y_1){
                current_enemy->x++;
                current_enemy->angle = 0;
            }
            if (current_enemy->x == points_down->pos_x_2) {
                current_enemy->y--;
                current_enemy->angle = -90;
            }
            if (current_enemy->y == points_down->pos_y_3 & current_enemy->x < points_down->pos_x_8) {
                current_enemy->x++;
                current_enemy->angle = 0;
            }
            if (current_enemy->x == points_down->pos_x_4){
                current_enemy->y--;
                current_enemy->angle = -90;
            }
            if (current_enemy->y == points_down->pos_y_5 & current_enemy->x < points_down->pos_x_8){
                current_enemy->x++;
                current_enemy->angle = 0;
            }
            if (current_enemy->x == points_up->pos_x_6){
                current_enemy->y--;
                current_enemy->angle = -90;
            }
            if (current_enemy->y == points_up->pos_y_6){
                current_enemy->x++;
                current_enemy->angle = 0;
            }
            if (current_enemy->x == points_up->pos_x_7){
                current_enemy->y++;
                current_enemy->angle = 90;
            }
            if (current_enemy->x == points_up->pos_x_9){
                current_enemy->y--;
                current_enemy->angle = -90;
            }
        }
        current_enemy = current_enemy->next;
    }
}

void enemyEnterCave(enemy* head, points* points, int* hp){
    while(head != NULL){
        if (head->x >= points->pos_x_11) {
            head->isAlive = 0;
            if (*hp > 0) *hp -= 10;
        }
        head = head->next;
    }
}

void renderEnemies(SDL_Renderer* Renderer, enemy* head){
    int i = 0;
    SDL_Rect Rect;
    SDL_RendererFlip Flip = SDL_FLIP_NONE;
    for (i = 0; i < COUNT_IN_WAVE; i++){
        Rect.x = head->x;
        Rect.y = head->y;
        Rect.w = BLOCK_WIDTH;
        Rect.h = BLOCK_HEIGHT;
        if (head->isAlive) SDL_RenderCopyEx(Renderer, head->textureEnemy, NULL, &Rect, head->angle, NULL, Flip);
        head = head->next;
    }
}

void init_points_up(points* points_up){
    points_up->pos_x_1 = 80;
    points_up->pos_y_1 = 40;
    points_up->pos_x_2 = 80;
    points_up->pos_y_2 = 80;
    points_up->pos_x_3 = 240;
    points_up->pos_y_3 = 80;
    points_up->pos_x_4 = 240;
    points_up->pos_y_4 = 200;
    points_up->pos_x_5 = 280;
    points_up->pos_y_5 = 200;
    points_up->pos_x_6 = 280;
    points_up->pos_y_6 = 240;
    points_up->pos_x_7 = 360;
    points_up->pos_y_7 = 240;
    points_up->pos_x_8 = 360;
    points_up->pos_y_8 = 80;
    points_up->pos_x_9 = 440;
    points_up->pos_y_9 = 80;
    points_up->pos_x_10 = 440;
    points_up->pos_y_10 = 240;
    points_up->pos_x_11 = 480;
    points_up->pos_y_11 = 240;
}

void init_points_down(points* points_down){
    points_down->pos_x_1 = 80;
    points_down->pos_y_1 = 400;
    points_down->pos_x_2 = 80;
    points_down->pos_y_2 = 360;
    points_down->pos_x_3 = 160;
    points_down->pos_y_3 = 360;
    points_down->pos_x_4 = 160;
    points_down->pos_y_4 = 280;
    points_down->pos_x_5 = 280;
    points_down->pos_y_5 = 280;
    points_down->pos_x_6 = 280;
    points_down->pos_y_6 = 240;
    points_down->pos_x_7 = 360;
    points_down->pos_y_7 = 240;
    points_down->pos_x_8 = 360;
    points_down->pos_y_8 = 400;
    points_down->pos_x_9= 440;
    points_down->pos_y_9 = 400;
    points_down->pos_x_10 = 440;
    points_down->pos_y_10 = 240;
    points_down->pos_x_11 = 480;
    points_down->pos_y_11 = 240;
}

void add_enemy(enemy** head, SDL_Texture* texture){
    enemy* new_enemy = createEnemy(texture);
    enemy* current_enemy = *head;
    if (current_enemy != NULL){
        while (current_enemy->next != NULL){
            current_enemy = current_enemy->next;
        }
        current_enemy->next = new_enemy;
    }
    else *head = new_enemy;

}

sprites_enemy* init_sprites_enemy(SDL_Renderer* Renderer){
    sprites_enemy* new_sprites = malloc(sizeof(sprites_enemy));
    new_sprites->sprite_enemy1 = getTextureFromPath("BMPimages/Wave/1.png", Renderer);
//    new_sprites->sprite_enemy2 = getTextureFromPath("BMPimages/Wave/2.png", Renderer);
//    new_sprites->sprite_enemy3 = getTextureFromPath("BMPimages/Wave/3.png", Renderer);
//    new_sprites->sprite_enemy4 = getTextureFromPath("BMPimages/Wave/4.png", Renderer);
//    new_sprites->sprite_enemy5 = getTextureFromPath("BMPimages/Wave/5.png", Renderer);
//    new_sprites->sprite_enemy6 = getTextureFromPath("BMPimages/Wave/6.png", Renderer);
//    new_sprites->sprite_enemy7 = getTextureFromPath("BMPimages/Wave/7.png", Renderer);
//    new_sprites->sprite_enemy8 = getTextureFromPath("BMPimages/Wave/8.png", Renderer);
//    new_sprites->sprite_enemy9 = getTextureFromPath("BMPimages/Wave/9.png", Renderer);
//    new_sprites->sprite_enemy10 = getTextureFromPath("BMPimages/Wave/10.png", Renderer);
//    new_sprites->sprite_enemy11 = getTextureFromPath("BMPimages/Wave/11.png", Renderer);
//    new_sprites->sprite_enemy12 = getTextureFromPath("BMPimages/Wave/12.png", Renderer);
//    new_sprites->sprite_enemy13 = getTextureFromPath("BMPimages/Wave/13.png", Renderer);
//    new_sprites->sprite_enemy14 = getTextureFromPath("BMPimages/Wave/14.png", Renderer);
//    new_sprites->sprite_enemy15 = getTextureFromPath("BMPimages/Wave/15.png", Renderer);
    return new_sprites;
}
