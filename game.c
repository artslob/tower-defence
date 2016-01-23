#include "game.h"

int game(SDL_Renderer* Renderer, block* BGhead){
    int state = IN_GAME;
    SDL_Event event;
    SDL_Texture* cursor_texture = getTextureFromPath("BMPimages/Cursor/1.bmp", Renderer);
    int timer = 0;
    int frame = 0;
    int x = 0, y = 0;
    char string_buff[10];

    points* points_up = malloc(sizeof(points));
    points* points_down = malloc(sizeof(points));

    towerTextures* tow_textures = malloc(sizeof(towerTextures));
    tower* tow_head = NULL;
    tower* choosedTowerPoint = NULL;

    enemy* enemy_head = NULL;
    sprites_enemy* enemy_sprites = init_sprites_enemy(Renderer);

    int HealthPoints = 100;
    int ExHealthPoints = 100;
    int Gold = 100;
    int ExGold = 100;
    int Wave = 1;
    int ExWave = 1;

    rewind_button* RewButton = malloc(sizeof(rewind_button));
    SDL_Texture* RewTexture = NULL;
    int isRewind = NOT_IN_REWIND;

    int FPS = 60;

    SDL_Color textColor = {0, 0, 0};
    TTF_Font* Font = TTF_OpenFont("TTFtext/GOST-type-B-Standard.ttf", 1000);
    SDL_Texture* waveTexture = loadTextTexture("Wave", Font, textColor, Renderer);
    SDL_Texture* waveCountTexture = getTextureFromInt(Wave, string_buff, Font, textColor, Renderer);
    SDL_Rect waveTextureRect = {BLOCK_WIDTH, 0, 5 / 2 * BLOCK_WIDTH, BLOCK_HEIGHT};
    SDL_Rect waveCountRect = {7 / 2 * BLOCK_WIDTH, 0, BLOCK_WIDTH * 6 / 11, BLOCK_HEIGHT};

    SDL_Texture* hpIconTexture = getTextureFromPath("BMPimages/Icons/hearth.png", Renderer);
    SDL_Texture* hpNumberTexture = getTextureFromInt(HealthPoints, string_buff, Font, textColor, Renderer);
    SDL_Rect hpIconRect = {9 * BLOCK_WIDTH, 0, BLOCK_WIDTH, BLOCK_HEIGHT};
    SDL_Rect hpNumberRect = {10 * BLOCK_WIDTH, 0, 2 * BLOCK_WIDTH, BLOCK_HEIGHT};

    SDL_Texture* coinTexture = getTextureFromPath("BMPimages/Icons/coin1.png", Renderer);
    SDL_Rect coinRect = {13 * BLOCK_WIDTH, 0, BLOCK_WIDTH, BLOCK_HEIGHT};
    SDL_Texture* coinNumberTexture = getTextureFromInt(Gold, string_buff, Font, textColor, Renderer);
    SDL_Rect coinNumberRect = {14 * BLOCK_WIDTH, 0, 2 * BLOCK_WIDTH, BLOCK_HEIGHT};

    createListEnemy(&enemy_head, Renderer, enemy_sprites);
    initRewindButton(RewButton, Renderer);
    init_points_up(points_up);
    init_points_down(points_down);
    initTowerTextures(tow_textures, Renderer);
    createListTower(&tow_head);
    RewTexture = RewButton->rewindOff_outside;
    while(state == IN_GAME){
        timer = SDL_GetTicks();
        while(SDL_PollEvent(&event)){
            SDL_GetMouseState(&x, &y);
            if (event.type == SDL_MOUSEBUTTONDOWN){
                clickedRewind(RewButton, &RewTexture, x, y, &isRewind, &FPS, tow_head);
                clickedUpgradeMenu(choosedTowerPoint, tow_textures, x, y, &Gold);
                choosedTowerPoint = clickedOnTowerPosition(tow_head, x, y);
            }
            if (event.type == SDL_MOUSEMOTION){
                mouseInsideRewindButton(RewButton, &RewTexture, x, y, isRewind);
            }
            if (event.type == SDL_QUIT){
                state = EXIT;
            }
        }
        SDL_SetRenderDrawColor(Renderer, 0xFF, 0xFF, 0xFF, 0xFF);
        SDL_RenderClear(Renderer);

        BG_list_render(Renderer, BGhead);

        moveEnemies(enemy_head, points_up, points_down);
        enemyEnterCave(enemy_head, points_up, &HealthPoints);
        renderEnemies(Renderer, enemy_head, frame / (FPS / 3));
        showHPbar(Renderer, enemy_head);
        renderTowersAndShoot(tow_head, enemy_head, Renderer, &Gold);
        showTowerUpgradeMenu(choosedTowerPoint, Renderer, tow_textures, Gold);


        SDL_RenderCopy(Renderer, waveTexture, NULL, &waveTextureRect);
        SDL_RenderCopy(Renderer, waveCountTexture, NULL, &waveCountRect);
        SDL_RenderCopy(Renderer, hpIconTexture, NULL, &hpIconRect);
        SDL_RenderCopy(Renderer, hpNumberTexture, NULL, &hpNumberRect);
        SDL_RenderCopy(Renderer, coinTexture, NULL, &coinRect);
        SDL_RenderCopy(Renderer, coinNumberTexture, NULL, &coinNumberRect);
        SDL_RenderCopy(Renderer, RewTexture, NULL, &RewButton->Rect);

        showCursor(Renderer, cursor_texture);
        SDL_RenderPresent(Renderer);

        state = getGameState(enemy_head, HealthPoints);
        if (makeNewWaveIfAllIsDead(enemy_head, enemy_sprites)) Wave++;
        if (Wave != ExWave | ExHealthPoints != HealthPoints | ExGold != Gold){
            ExWave = Wave;
            ExHealthPoints = HealthPoints;
            ExGold = Gold;
            SDL_DestroyTexture(waveCountTexture);
            waveCountTexture = getTextureFromInt(Wave, string_buff, Font, textColor, Renderer);
            SDL_DestroyTexture(hpNumberTexture);
            hpNumberTexture = getTextureFromInt(HealthPoints, string_buff, Font, textColor, Renderer);
            SDL_DestroyTexture(coinNumberTexture);
            coinNumberTexture = getTextureFromInt(Gold, string_buff, Font, textColor, Renderer);
        }

        frame++;
        if (frame >= FPS) frame = 0;
        waitForFps(timer, FPS);
        getFps();
    }
    return state;
}

SDL_Texture* getTextureFromInt(int number, char* buff, TTF_Font* Font, SDL_Color textColor, SDL_Renderer* Renderer){
    SDL_Texture* newTexture = NULL;
    itoa(number, buff, 10);
    newTexture = loadTextTexture(buff, Font, textColor, Renderer);
    return newTexture;
}

void clickedRewind(rewind_button* button, SDL_Texture** RewTexture, int x, int y, int* isRewind, int* FPS, tower* tow_head){
    tower* cur_tower = tow_head;
    if (isInsideRect(x, y, button->Rect)){
        if (*isRewind == IN_REWIND){
            *isRewind = NOT_IN_REWIND;
            *FPS /= 2;
            *RewTexture = button->rewindOff_inside;
        }
        else{
            *isRewind = IN_REWIND;
            *FPS *= 2;
            *RewTexture = button->rewindOn_inside;
        }
    }
}

void mouseInsideRewindButton(rewind_button* button, SDL_Texture** RewTexture, int x, int y, int IsRewind){
    if (isInsideRect(x, y, button->Rect)){
        if (IsRewind == IN_REWIND){
            *RewTexture = button->rewindOn_inside;
        }
        else{
            *RewTexture = button->rewindOff_inside;
        }
    }
    else{
        if (IsRewind == IN_REWIND){
            *RewTexture = button->rewindOn_outside;
        }
        else{
            *RewTexture = button->rewindOff_outside;
        }
    }
}

void initRewindButton(rewind_button* button, SDL_Renderer* Renderer){
    button->Rect.x = SCREEN_WIDTH - BLOCK_WIDTH;
    button->Rect.y = SCREEN_HEIGHT - BLOCK_HEIGHT;
    button->Rect.w = BLOCK_WIDTH;
    button->Rect.h = BLOCK_HEIGHT;

    button->rewindOff_inside = getTextureFromPath("BMPimages/Icons/rewindOff_inside.png", Renderer);
    button->rewindOff_outside = getTextureFromPath("BMPimages/Icons/rewindOff_outside.png", Renderer);
    button->rewindOn_inside = getTextureFromPath("BMPimages/Icons/rewindOn_inside.png", Renderer);
    button->rewindOn_outside = getTextureFromPath("BMPimages/Icons/rewindOn_outside.png", Renderer);
}

int getGameState(enemy* enemy_head, int HealthPoint){
    if (HealthPoint <= 0) return GAME_OVER;
    enemy* current_enemy = enemy_head;
    while (current_enemy != NULL){
        if (current_enemy->isAlive == 1 && current_enemy->inCave != 1){
            return IN_GAME;
        }
        current_enemy = current_enemy->next;
    }
    if (enemy_head->level == 7) return WIN;
    else return IN_GAME;
}
