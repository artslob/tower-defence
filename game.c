#include "game.h"

int game(SDL_Renderer* Renderer, block* BGhead){
    int state = IN_GAME;
    SDL_Event event;
    SDL_Texture* cursor_texture = getTextureFromPath("BMPimages/Cursor/1.png", Renderer);
    int timer = 0;

    points* points_up = malloc(sizeof(points));
    points* points_down = malloc(sizeof(points));

    enemy* enemy_head = NULL;

    int gamerHP = 100;

    createListEnemy(&enemy_head, Renderer);
    init_points_up(points_up);
    init_points_down(points_down);
    while(state == IN_GAME){
        timer = SDL_GetTicks();
        while(SDL_PollEvent(&event)){
            if (event.type == SDL_QUIT){
                state = EXIT;
            }
        }
        SDL_SetRenderDrawColor(Renderer, 0xFF, 0xFF, 0xFF, 0xFF);
        SDL_RenderClear(Renderer);

        BG_list_render(Renderer, BGhead);

        moveEnemies(enemy_head, points_up, points_down);
        renderEnemies(Renderer, enemy_head);
        enemyEnterCave(enemy_head, points_up, &gamerHP);


        showCursor(Renderer, cursor_texture);
        SDL_RenderPresent(Renderer);


        waitForFps(timer, 50);
        getFps();
    }

}
