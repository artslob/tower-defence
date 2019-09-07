#include "main.h"
#include "init.h"
#include "bg.h"
#include "game.h"
#include "startscreen.h"


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

SDL_Texture* getTextureFromPath(char* path, SDL_Renderer* Renderer){
    SDL_Texture* newTexture = NULL;
    SDL_Surface* loadedSurface = NULL;
    if ((loadedSurface = IMG_Load(path)) == NULL)
        sprintf(stderr, "Unable to load image %s! SDL_image Error: %s\n", path, IMG_GetError());
    else{
        if ((newTexture = SDL_CreateTextureFromSurface(Renderer, loadedSurface)) == NULL){
            sprintf(stderr, "Unable to create texture from %s! SDL Error: %s\n", path, SDL_GetError() );
        }
        SDL_FreeSurface(loadedSurface);
    }
    return newTexture;
}

int isInsideRect(int x, int y, SDL_Rect Rect){
    if (Rect.x <= x & x <= Rect.x + Rect.w & Rect.y <= y & y <= Rect.y + Rect.h) return 1;
    else return 0;
}

void showCursor(SDL_Renderer* Renderer, SDL_Texture* cursor_texture){
    int x, y;
    SDL_Rect cursorRect;
    SDL_GetMouseState(&x, &y);
    cursorRect.x = x;
    cursorRect.y = y;
    cursorRect.w = 25;
    cursorRect.h = 25;
    SDL_RenderCopy(Renderer, cursor_texture, NULL, &cursorRect);
}

void getFps(void){
    static size_t frameWindow = 0;
    static size_t currentTime1 = 0;
    static size_t currentTime2 = 0;
    static float fps = 0;
    frameWindow++;

    if (frameWindow % 100 == 0){
        currentTime2 = SDL_GetTicks();
        fps = (float) frameWindow * 1000 / (currentTime2 - currentTime1);
        printf("FPS: %0.2f\n", fps);
        currentTime1 = currentTime2;
        currentTime2 = 0;
        frameWindow = 0;
    }
}

void waitForFps(size_t fps){
    static float timer1 = 0;
    static float delta = 0;
    static float time = 0;
    time = (float) 1000 / fps;
    delta = SDL_GetTicks() - timer1;
    if (delta < time){
        SDL_Delay(time - delta);
    }
    timer1 = SDL_GetTicks();
}

void prError(char* str){
    sprintf(stderr, "%s! %s\n", str, SDL_GetError());
}
