#include "main.h"
#include "init.h"
#include "bg.h"
#include "game.h"
#include "startscreen.h"
#include "utils.h"


SDL_Window* Window = NULL;
SDL_Renderer* Renderer = NULL;


int main(int argc, char* args[]){
    block* block_head = NULL;
    GameStates state;

    if (init(&Window, &Renderer)){
        SDL_ShowCursor(0);
        BG_list_create(Renderer, &block_head);

        state = menu(Renderer);
        if (state == START){
            state = game(Renderer, block_head);
            playLastScene(Renderer, Window, block_head, state);
        }
    }
    closeSDLResources(&Renderer, &Window);
    return 0;
}

void playLastScene(SDL_Renderer* Renderer, SDL_Window* Window, block* block_head, GameStates state){
    SDL_Texture* lastWords = NULL;
    SDL_Color textColor = {255, 0, 0};
    TTF_Font* Font = TTF_OpenFont("TTFtext/GOST-type-B-Standard.ttf", 1000);
    SDL_Rect textRect = {SCREEN_WIDTH / 4, SCREEN_HEIGHT / 4, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2};

    int blend = 0;
    SDL_Rect bgRect = {0, 0, SCREEN_WIDTH, SCREEN_HEIGHT};
    SDL_Surface* oldSurface = SDL_GetWindowSurface(Window);
    SDL_Texture* oldTexture = SDL_CreateTextureFromSurface(Renderer, oldSurface);

    SDL_Texture* cursor_texture = getTextureFromPath("BMPimages/Cursor/1.bmp", Renderer);
    GameStates new_state = IN_GAME;
    SDL_Event event;

    size_t FPS = 70;

    if (state == WIN){
        lastWords = loadTextTexture("YOU WIN", Font, textColor, Renderer);
    }
    if (state == GAME_OVER){
        lastWords = loadTextTexture("YOU LOST", Font, textColor, Renderer);
    }
    if (state != EXIT){
        Mix_FadeOutMusic(5000);
        while (new_state != EXIT){
            while (SDL_PollEvent(&event)){
                if (event.type == SDL_QUIT | event.type == SDL_MOUSEBUTTONDOWN){
                    new_state = EXIT;
                }
            }
            SDL_SetRenderDrawColor(Renderer, 0xFF, 0xFF, 0xFF, 0xFF);
            SDL_RenderClear(Renderer);

            BG_list_render(Renderer, block_head);
            SDL_SetRenderDrawBlendMode(Renderer, SDL_BLENDMODE_BLEND);
            SDL_SetRenderDrawColor(Renderer, 0, 0, 0, blend);
            SDL_RenderFillRect(Renderer, &bgRect);

            SDL_RenderCopy(Renderer, lastWords, NULL, &textRect);

            showCursor(Renderer, cursor_texture);
            SDL_RenderPresent(Renderer);

            if (blend < 253) blend += 1;

            waitForFps(FPS);
            getFps();
        }
    }
}
