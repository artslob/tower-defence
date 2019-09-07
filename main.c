#include "main.h"
#include "init.h"
#include "bg.h"
#include "game.h"
#include "startscreen.h"
#include "utils.h"


void playLastScene(SDL_Renderer* renderer, SDL_Window* window, block* block_head, GameStates state);


int main(int argc, char* args[]) {
    SDL_Window* window = NULL;
    SDL_Renderer* renderer = NULL;
    block* block_head = NULL;
    GameStates state;

    if (init(&window, &renderer)){
        SDL_ShowCursor(0);
        BG_list_create(renderer, &block_head);

        state = menu(renderer);
        if (state == START){
            state = game(renderer, block_head);
            playLastScene(renderer, window, block_head, state);
        }
    }
    closeSDLResources(&renderer, &window);
    return 0;
}

void playLastScene(SDL_Renderer* renderer, SDL_Window* window, block* block_head, GameStates state) {
    SDL_Texture* lastWords = NULL;
    SDL_Color textColor = {255, 0, 0};
    TTF_Font* Font = TTF_OpenFont("TTFtext/GOST-type-B-Standard.ttf", 1000);
    SDL_Rect textRect = {SCREEN_WIDTH / 4, SCREEN_HEIGHT / 4, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2};

    int blend = 0;
    SDL_Rect bgRect = {0, 0, SCREEN_WIDTH, SCREEN_HEIGHT};
    SDL_Surface* oldSurface = SDL_GetWindowSurface(window);
    SDL_Texture* oldTexture = SDL_CreateTextureFromSurface(renderer, oldSurface);

    SDL_Texture* cursor_texture = getTextureFromPath("BMPimages/Cursor/1.bmp", renderer);
    GameStates new_state = IN_GAME;
    SDL_Event event;

    size_t FPS = 70;

    if (state == WIN){
        lastWords = loadTextTexture("YOU WIN", Font, textColor, renderer);
    }
    if (state == GAME_OVER){
        lastWords = loadTextTexture("YOU LOST", Font, textColor, renderer);
    }
    if (state != EXIT){
        Mix_FadeOutMusic(5000);
        while (new_state != EXIT){
            while (SDL_PollEvent(&event)){
                if (event.type == SDL_QUIT | event.type == SDL_MOUSEBUTTONDOWN){
                    new_state = EXIT;
                }
            }
            SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
            SDL_RenderClear(renderer);

            BG_list_render(renderer, block_head);
            SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
            SDL_SetRenderDrawColor(renderer, 0, 0, 0, blend);
            SDL_RenderFillRect(renderer, &bgRect);

            SDL_RenderCopy(renderer, lastWords, NULL, &textRect);

            showCursor(renderer, cursor_texture);
            SDL_RenderPresent(renderer);

            if (blend < 253) blend += 1;

            waitForFps(FPS);
            getFps();
        }
    }
}
