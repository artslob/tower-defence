#include "game.h"

int game(SDL_Renderer* Renderer, block* BGhead){
    int state = IN_GAME;
    SDL_Event event;
    SDL_Texture* cursor_texture = getTextureFromPath("BMPimages/Cursor/1.png", Renderer);
    int timer = 0;
    Uint64 frame = 0;
    int x = 0, y = 0;
    char buff[10];

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

    int FPS = 55;

    SDL_Color textColor = {0, 0, 0};
    TTF_Font* Font = TTF_OpenFont("TTFtext/GOST-type-B-Standard.ttf", 1000);
    SDL_Texture* waveTexture = loadTextTexture("Wave", Font, textColor, Renderer);
    SDL_Texture* waveCountTexture = getTextureFromInt(Wave, buff, Font, textColor, Renderer);
    SDL_Rect waveTextureRect = {BLOCK_WIDTH, 0, 5 / 2 * BLOCK_WIDTH, BLOCK_HEIGHT};
    SDL_Rect waveCountRect = {7 / 2 * BLOCK_WIDTH, 0, BLOCK_WIDTH * 6 / 11, BLOCK_HEIGHT};

    SDL_Texture* hpIconTexture = getTextureFromPath("BMPimages/Icons/hearth.png", Renderer);
    SDL_Texture* hpNumberTexture = getTextureFromInt(HealthPoints, buff, Font, textColor, Renderer);
    SDL_Rect hpIconRect = {9 * BLOCK_WIDTH, 0, BLOCK_WIDTH, BLOCK_HEIGHT};
    SDL_Rect hpNumberRect = {10 * BLOCK_WIDTH, 0, 2 * BLOCK_WIDTH, BLOCK_HEIGHT};

    SDL_Texture* coinTexture = getTextureFromPath("BMPimages/Icons/coin1.png", Renderer);
    SDL_Rect coinRect = {13 * BLOCK_WIDTH, 0, BLOCK_WIDTH, BLOCK_HEIGHT};
    SDL_Texture* coinNumberTexture = getTextureFromInt(Gold, buff, Font, textColor, Renderer);
    SDL_Rect coinNumberRect = {14 * BLOCK_WIDTH, 0, 2 * BLOCK_WIDTH, BLOCK_HEIGHT};

    createListEnemy(&enemy_head, Renderer, enemy_sprites);
    init_points_up(points_up);
    init_points_down(points_down);
    initTowerTextures(tow_textures, Renderer);
    createListTower(&tow_head);

    while(state == IN_GAME){
        timer = SDL_GetTicks();
        while(SDL_PollEvent(&event)){
            SDL_GetMouseState(&x, &y);
            if (event.type == SDL_MOUSEBUTTONDOWN){
                clickedUpgradeMenu(choosedTowerPoint, tow_textures, x, y, &Gold);
                choosedTowerPoint = clickedOnTowerPosition(tow_head, x, y);
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
        renderTowersAndShoot(tow_head, enemy_head, Renderer, &Gold, frame);
        showTowerUpgradeMenu(choosedTowerPoint, Renderer, tow_textures, Gold);


        SDL_RenderCopy(Renderer, waveTexture, NULL, &waveTextureRect);
        SDL_RenderCopy(Renderer, waveCountTexture, NULL, &waveCountRect);
        SDL_RenderCopy(Renderer, hpIconTexture, NULL, &hpIconRect);
        SDL_RenderCopy(Renderer, hpNumberTexture, NULL, &hpNumberRect);
        SDL_RenderCopy(Renderer, coinTexture, NULL, &coinRect);
        SDL_RenderCopy(Renderer, coinNumberTexture, NULL, &coinNumberRect);

        showCursor(Renderer, cursor_texture);
        SDL_RenderPresent(Renderer);

        state = getGameState(enemy_head, HealthPoints);
        if (makeNewWaveIfAllIsDead(enemy_head, enemy_sprites)) Wave++;
        if (Wave != ExWave | ExHealthPoints != HealthPoints | ExGold != Gold){
            ExWave = Wave;
            ExHealthPoints = HealthPoints;
            ExGold = Gold;
            SDL_DestroyTexture(waveCountTexture);
            waveCountTexture = getTextureFromInt(Wave, buff, Font, textColor, Renderer);
            SDL_DestroyTexture(hpNumberTexture);
            hpNumberTexture = getTextureFromInt(HealthPoints, buff, Font, textColor, Renderer);
            SDL_DestroyTexture(coinNumberTexture);
            coinNumberTexture = getTextureFromInt(Gold, buff, Font, textColor, Renderer);
        }

        frame++;
        if (frame == FPS) frame = 0;
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
