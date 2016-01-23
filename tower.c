#include "tower.h"

tower* clickedOnTowerPosition(tower* head, int x, int y){
    tower* cur_tower = head;
    while (cur_tower != NULL){
        if (cur_tower->x <= x && x <= cur_tower->x + BLOCK_WIDTH &&
            cur_tower->y <= y && y <= cur_tower->y + BLOCK_HEIGHT){
            return cur_tower;
        }
        cur_tower = cur_tower->next;
    }
    return NULL;
}

void renderTowersAndShoot(tower* tow_head, enemy* enemy_head, SDL_Renderer* Renderer, int* Gold){
    SDL_Rect Rect;
    enemy* cur_enemy = enemy_head;
    enemy* enemy_for_shoot = NULL;
    SDL_RendererFlip Flip = SDL_FLIP_NONE;

    double towx, towy, enx, eny;
    double delta_x, delta_y, radius, highest_radius, righter;

    while (tow_head != NULL){
        if (tow_head->texture != NULL){
            tow_head->angle = 180;
            Rect.x = tow_head->x;
            Rect.y = tow_head->y;
            Rect.w = BLOCK_WIDTH;
            Rect.h = BLOCK_HEIGHT;

            towx = tow_head->x + BLOCK_WIDTH / 2;
            towy = tow_head->y + BLOCK_HEIGHT / 2;

            highest_radius = 0;
            righter = 0;

            while(cur_enemy != NULL){
                enx = cur_enemy->x + BLOCK_WIDTH / 2;
                eny = cur_enemy->y + BLOCK_HEIGHT / 2;

                delta_x = towx - enx;
                delta_y = towy - eny;
                radius = sqrt(pow(delta_x, 2) + pow(delta_y, 2));


                if (cur_enemy->isAlive == 1 && radius <= tow_head->radius && righter <= enx ){
                    highest_radius = radius;
                    righter = enx;
                    enemy_for_shoot = cur_enemy;

                    if (enx - towx == 0 & eny - towy > 0) tow_head->angle = 90;
                    else if (enx - towx == 0 & eny - towy < 0) tow_head->angle = -90;
                    else tow_head->angle = atan((eny - towy) / (enx - towx)) * 180 / PI;
                    if (enx - towx < 0) tow_head->angle += 180;
                }
                cur_enemy = cur_enemy->next;
            }
            cur_enemy = enemy_head;
            SDL_RenderCopyEx(Renderer, tow_head->texture, NULL, &Rect, tow_head->angle, NULL, Flip);
            if (enemy_for_shoot != NULL) renderShootingInEnemy(Renderer, enemy_for_shoot, tow_head, Gold);
        }
        tow_head = tow_head->next;
        enemy_for_shoot = NULL;
    }
}

void renderShootingInEnemy(SDL_Renderer* Renderer, enemy* cur_enemy, tower* cur_tower, int* Gold){
    int towx = cur_tower->x + BLOCK_WIDTH / 2;
    int towy = cur_tower->y + BLOCK_HEIGHT / 2;
    int enx = cur_enemy->x + BLOCK_WIDTH / 2;
    int eny = cur_enemy->y + BLOCK_HEIGHT / 2;

    SDL_SetRenderDrawColor(Renderer, 0xFF, 0x00, 0x00, 0xFF);

    SDL_RenderDrawLine(Renderer, towx, towy, enx, eny);
    cur_enemy->health -= cur_tower->damage;

    if (cur_enemy->health <= 0){
        cur_enemy->isAlive = 0;
        *Gold += cur_enemy->price;
    }
}

void clickedUpgradeMenu(tower* cur_tower, towerTextures* tow_textures, int x, int y, int* gold){
    if (cur_tower != NULL){
        if (cur_tower->level == 0){
            if (cur_tower->x <= x && x <= cur_tower->x + BLOCK_WIDTH &&
            cur_tower->y - BLOCK_HEIGHT - 5 <= y && y <= cur_tower->y - 5){
                if (cur_tower->cost <= *gold) upgradeTower(cur_tower, tow_textures, gold);
            }
        }
        else if (cur_tower->level == 7){
            if (cur_tower->x <= x && x <= cur_tower->x + BLOCK_WIDTH &&
            cur_tower->y - BLOCK_HEIGHT - 5 <= y && y <= cur_tower->y - 5){
                destroyTower(cur_tower, tow_textures, gold);
            }
        }
        else if (1 <= cur_tower->level & cur_tower->level <= 6){
            if (cur_tower->x - BLOCK_WIDTH / 2 <= x && x <= cur_tower->x + BLOCK_WIDTH / 2 &&
            cur_tower->y - BLOCK_HEIGHT - 5 <= y && y <= cur_tower->y - 5){
                if (cur_tower->cost <= *gold) upgradeTower(cur_tower, tow_textures, gold);
            }
            if (cur_tower->x + BLOCK_WIDTH / 2 <= x && x <= cur_tower->x + BLOCK_WIDTH * 3 / 2 &&
            cur_tower->y - BLOCK_HEIGHT - 5 <= y && y <= cur_tower->y - 5){
                destroyTower(cur_tower, tow_textures, gold);
            }
        }
    }
}

void upgradeTower(tower* cur_tower, towerTextures* tow_textures, int* gold){
    *gold -= cur_tower->cost;
    switch(cur_tower->level){
    case 0:
        cur_tower->texture = tow_textures->textureTowerOne;
        break;
    case 1:
        cur_tower->texture = tow_textures->textureTowerTwo;
        break;
    case 2:
        cur_tower->texture = tow_textures->textureTowerThree;
        break;
    case 3:
        cur_tower->texture = tow_textures->textureTowerFour;
        break;
    case 4:
        cur_tower->texture = tow_textures->textureTowerFive;
        break;
    case 5:
        cur_tower->texture = tow_textures->textureTowerSix;
        break;
    case 6:
        cur_tower->texture = tow_textures->textureTowerSeven;
        break;
    }
    cur_tower->cost = cur_tower->cost * 5 / 4;
    cur_tower->damage = cur_tower->damage * 6 / 4;
    cur_tower->level++;
    cur_tower->radius += 5;
}

void destroyTower(tower* cur_tower, towerTextures* tow_textures, int* gold){
    *gold += cur_tower->cost / 2;
    makeStartStatesForTower(cur_tower);
}

void showTowerUpgradeMenu(tower* cur_tower, SDL_Renderer* Renderer, towerTextures* tow_textures, int gold){
    SDL_Rect towRect;
    SDL_Rect destRect;
    if (cur_tower != NULL){
        if (cur_tower->level == 0) towRect.x = cur_tower->x;
        else towRect.x = cur_tower->x - BLOCK_WIDTH / 2;
        towRect.y = cur_tower->y - BLOCK_HEIGHT - 5;
        towRect.w = BLOCK_WIDTH;
        towRect.h = BLOCK_HEIGHT;

        if (cur_tower->level == 7) destRect.x = cur_tower->x;
        else destRect.x = cur_tower->x + BLOCK_WIDTH / 2;
        destRect.y = cur_tower->y - BLOCK_HEIGHT - 5;
        destRect.w = BLOCK_WIDTH;
        destRect.h = BLOCK_HEIGHT;

        switch(cur_tower->level){
        case 0:
            SDL_RenderCopy(Renderer, tow_textures->textureTowerOne, NULL, &towRect);
            break;
        case 1:
            SDL_RenderCopy(Renderer, tow_textures->textureTowerTwo, NULL, &towRect);
            SDL_RenderCopy(Renderer, tow_textures->destroy_tower, NULL, &destRect);
            break;
        case 2:
            SDL_RenderCopy(Renderer, tow_textures->textureTowerThree, NULL, &towRect);
            SDL_RenderCopy(Renderer, tow_textures->destroy_tower, NULL, &destRect);
            break;
        case 3:
            SDL_RenderCopy(Renderer, tow_textures->textureTowerFour, NULL, &towRect);
            SDL_RenderCopy(Renderer, tow_textures->destroy_tower, NULL, &destRect);
            break;
        case 4:
            SDL_RenderCopy(Renderer, tow_textures->textureTowerFive, NULL, &towRect);
            SDL_RenderCopy(Renderer, tow_textures->destroy_tower, NULL, &destRect);
            break;
        case 5:
            SDL_RenderCopy(Renderer, tow_textures->textureTowerSix, NULL, &towRect);
            SDL_RenderCopy(Renderer, tow_textures->destroy_tower, NULL, &destRect);
            break;
        case 6:
            SDL_RenderCopy(Renderer, tow_textures->textureTowerSeven, NULL, &towRect);
            SDL_RenderCopy(Renderer, tow_textures->destroy_tower, NULL, &destRect);
            break;
        case 7:
            SDL_RenderCopy(Renderer, tow_textures->destroy_tower, NULL, &destRect);
            break;
        }
        SDL_SetRenderDrawColor(Renderer, 0x80, 0x80, 0x80, 0x90);
        SDL_SetRenderDrawBlendMode(Renderer, SDL_BLENDMODE_BLEND);
        if (cur_tower->cost > gold & cur_tower->level != 7) SDL_RenderFillRect(Renderer, &towRect);
    }
}

void createListTower(tower** head){
    tower* current_tower = NULL;
    int count = 0;

    for (count = 0; count < COUNT_TOWER; count++){
        addTower(head);
    }
    current_tower = *head;
    current_tower->x = BLOCK_WIDTH * 3;
    current_tower->y = BLOCK_HEIGHT * 1;
    current_tower = current_tower->next;

    current_tower->x = BLOCK_WIDTH * 6;
    current_tower->y = BLOCK_HEIGHT * 6;
    current_tower = current_tower->next;

    current_tower->x = BLOCK_WIDTH * 3;
    current_tower->y = BLOCK_HEIGHT * 10;
    current_tower = current_tower->next;

    current_tower->x = BLOCK_WIDTH * 10;
    current_tower->y = BLOCK_HEIGHT * 3;
    current_tower = current_tower->next;

    current_tower->x = BLOCK_WIDTH * 10;
    current_tower->y = BLOCK_HEIGHT * 9;
}

void addTower(tower** head){
    tower* new_tower = createTower();
    tower* current_tower = *head;
    if (current_tower != NULL){
        while (current_tower->next != NULL)
            current_tower = current_tower->next;
        current_tower->next = new_tower;
    }
    else *head = new_tower;
}

void makeStartStatesForTower(tower* cur_tower){
    cur_tower->radius = 5 * BLOCK_WIDTH / 2;
    cur_tower->damage = 2,5;
    cur_tower->level = 0;
    cur_tower->cost = 50;
    cur_tower->angle = 180;
    cur_tower->texture = NULL;
}

tower* createTower(void){
    tower* new_tower = malloc(sizeof(tower));
    new_tower->next = NULL;
    makeStartStatesForTower(new_tower);
    return new_tower;
}

void initTowerTextures(towerTextures* tow_textures, SDL_Renderer* Renderer){
    tow_textures->textureTowerOne = getTextureFromPath("BMPimages/Towers/1.png", Renderer);
    tow_textures->textureTowerTwo = getTextureFromPath("BMPimages/Towers/2.png", Renderer);
    tow_textures->textureTowerThree = getTextureFromPath("BMPimages/Towers/3.png", Renderer);
    tow_textures->textureTowerFour = getTextureFromPath("BMPimages/Towers/4.png", Renderer);
    tow_textures->textureTowerFive = getTextureFromPath("BMPimages/Towers/5.png", Renderer);
    tow_textures->textureTowerSix = getTextureFromPath("BMPimages/Towers/6.png", Renderer);
    tow_textures->textureTowerSeven= getTextureFromPath("BMPimages/Towers/7.png", Renderer);
    tow_textures->destroy_tower = getTextureFromPath("BMPimages/Towers/dest_tow.png", Renderer);
}
