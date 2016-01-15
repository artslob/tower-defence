#include "game.h"

int game(SDL_Renderer* Renderer, block* BGhead){
    int state = IN_GAME;
    SDL_Event event;
    SDL_Texture* cursor_texture = getTextureFromPath("BMPimages/Cursor/1.png", Renderer);
    int timer = 0;
    Uint64 frame = 0;
    int x = 0, y = 0;

    points* points_up = malloc(sizeof(points));
    points* points_down = malloc(sizeof(points));

    towerTextures* tow_textures = malloc(sizeof(towerTextures));
    tower* tow_head = NULL;
    tower* choosedTowerPoint = NULL;

    enemy* enemy_head = NULL;

    int HealthPoints = 100;
    int Gold = 100;


    createListEnemy(&enemy_head, Renderer);
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
        renderEnemies(Renderer, enemy_head, frame / 17);
        showHPbar(Renderer, enemy_head);
        renderTowers(tow_head, enemy_head, Renderer);
        showTowerUpgradeMenu(choosedTowerPoint, Renderer, tow_textures, Gold);


        showCursor(Renderer, cursor_texture);
        SDL_RenderPresent(Renderer);

        frame++;
        if (frame == 51) frame = 0;
        waitForFps(timer, 51);
        getFps();
    }

}
