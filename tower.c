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

void renderTowers(tower* tow_head, enemy* enemy_head, SDL_Renderer* Renderer){
    SDL_Rect Rect;
    enemy* cur_enemy = enemy_head;
    SDL_RendererFlip Flip = SDL_FLIP_NONE;
    while (tow_head != NULL){
        if (tow_head->texture != NULL){
            tow_head->angle = 180;
            Rect.x = tow_head->x;
            Rect.y = tow_head->y;
            Rect.w = BLOCK_WIDTH;
            Rect.h = BLOCK_HEIGHT;
            while(cur_enemy != NULL){
                if (pow(tow_head->x - cur_enemy->x, 2) + pow(tow_head->y - cur_enemy->y, 2) <= pow(tow_head->radius, 2)){
                    if (cur_enemy->x - tow_head->x == 0 & cur_enemy->y - tow_head->y > 0) tow_head->angle = 90;
                    else if (cur_enemy->x - tow_head->x == 0 & cur_enemy->y - tow_head->y < 0) tow_head->angle = -90;
                    else tow_head->angle = atan((cur_enemy->y - tow_head->y) / (cur_enemy->x - tow_head->x));
                    printf("%f\n", tow_head->angle);
                }
                cur_enemy = cur_enemy->next;
            }
            cur_enemy = enemy_head;
            SDL_RenderCopyEx(Renderer, tow_head->texture, NULL, &Rect, tow_head->angle, NULL, Flip);
        }
        tow_head = tow_head->next;
    }
}

void clickedUpgradeMenu(tower* cur_tower, towerTextures* tow_textures, int x, int y, int* gold){
    if (cur_tower != NULL){
        if (cur_tower->level == 0){
            if (cur_tower->x <= x && x <= cur_tower->x + BLOCK_WIDTH &&
            cur_tower->y - BLOCK_HEIGHT - 5 <= y && y <= cur_tower->y - 5){
                upgradeTower(cur_tower, tow_textures, gold);
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
                upgradeTower(cur_tower, tow_textures, gold);
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
    cur_tower->damage = cur_tower->damage * 5 / 4;
    cur_tower->level++;
    cur_tower->radius += 10;
}

void destroyTower(tower* cur_tower, towerTextures* tow_textures, int* gold){
    *gold += cur_tower->cost * 3;
    cur_tower->cost = 40;
    cur_tower->damage = 15;
    cur_tower->level = 0;
    cur_tower->radius = 5 * BLOCK_WIDTH / 2;
    cur_tower->texture = NULL;
}

void showTowerUpgradeMenu(tower* cur_tower, SDL_Renderer* Renderer, towerTextures* tow_textures, int gold){
    SDL_Rect towRect;
    SDL_Rect destRect;
    if (cur_tower != NULL){
        towRect.x = cur_tower->x - BLOCK_WIDTH / 2;
        towRect.y = cur_tower->y - BLOCK_HEIGHT - 5;
        towRect.w = BLOCK_WIDTH;
        towRect.h = BLOCK_HEIGHT;

        destRect.x = cur_tower->x + BLOCK_WIDTH / 2;
        destRect.y = cur_tower->y - BLOCK_HEIGHT - 5;
        destRect.w = BLOCK_WIDTH;
        destRect.h = BLOCK_HEIGHT;

        SDL_SetRenderDrawColor(Renderer, 0x5F, 0x9E, 0xA0, 0xFF);
        switch(cur_tower->level){
        case 0:
            towRect.x = cur_tower->x;
            //SDL_RenderFilltowRect(Renderer, &towRect);
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
            destRect.x = cur_tower->x;
            SDL_RenderCopy(Renderer, tow_textures->destroy_tower, NULL, &destRect);
            break;
        }
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

tower* createTower(void){
    tower* new_tower = malloc(sizeof(tower));
    new_tower->next = NULL;
    new_tower->radius = 5 * BLOCK_WIDTH / 2;
    new_tower->speed = 1;
    new_tower->damage = 15;
    new_tower->level = 0;
    new_tower->cost = 40;
    new_tower->angle = 180;
    new_tower->texture = NULL;
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
