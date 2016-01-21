#include "global.h"

/* the window be rendering to */
SDL_Window* Window = NULL;
/* window renderer */
SDL_Renderer* Renderer = NULL;

/*  */
int main(int argc, char* args[]){
    block* block_head = NULL;
    int state = 0;

    if (init(&Window, &Renderer)){
        SDL_ShowCursor(0);
        BG_list_create(Renderer, &block_head);

        state = menu(Renderer);
        if (state == START){
            state = game(Renderer, block_head);
            playLastScene(Renderer, Window, block_head, state);
        }
    }
    close(&Renderer, &Window);
    return 0;
}

void playLastScene(SDL_Renderer* Renderer, SDL_Window* Window, block* block_head, int state){
    SDL_Texture* lastWords = NULL;
    SDL_Color textColor = {255, 0, 0};
    TTF_Font* Font = TTF_OpenFont("TTFtext/GOST-type-B-Standard.ttf", 1000);
    SDL_Rect textRect = {SCREEN_WIDTH / 4, SCREEN_HEIGHT / 4, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2};

    int blend = 0;
    SDL_Rect bgRect = {0, 0, SCREEN_WIDTH, SCREEN_HEIGHT};
    SDL_Surface* oldSurface = SDL_GetWindowSurface(Window);
    SDL_Texture* oldTexture = SDL_CreateTextureFromSurface(Renderer, oldSurface);

    SDL_Texture* cursor_texture = getTextureFromPath("BMPimages/Cursor/1.png", Renderer);
    int new_state = IN_GAME;
    SDL_Event event;

    int FPS = 70;
    int timer = 0;
    int frame = 0;

    if (state == WIN){
        lastWords = loadTextTexture("YOU WIN", Font, textColor, Renderer);
    }
    if (state == GAME_OVER){
        lastWords = loadTextTexture("YOU LOST", Font, textColor, Renderer);
    }
    if (state != EXIT){
        while (new_state != EXIT){
            timer = SDL_GetTicks();
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

            if (blend < 253 & frame % 2 == 0) blend += 2;

            frame++;
            waitForFps(timer, FPS);
            getFps();
        }
    }
}

SDL_Texture* getTextureFromPath(char* path, SDL_Renderer* Renderer){
    SDL_Texture* newTexture = NULL;
    SDL_Surface* loadedSurface = NULL;
    if ((loadedSurface = IMG_Load(path)) == NULL)
        printf("Unable to load image %s! SDL_image Error: %s\n", path, IMG_GetError());
    else{
        if ((newTexture = SDL_CreateTextureFromSurface(Renderer, loadedSurface)) == NULL){
            printf( "Unable to create texture from %s! SDL Error: %s\n", path, SDL_GetError() );
        }
        SDL_FreeSurface(loadedSurface);
    }
    return newTexture;
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
    static int frameWindow = 0;
    static int currentTime1 = 0;
    static int currentTime2 = 0;
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

void waitForFps(int timer, int fps){
    static float delta = 0;
    static float time = 0;
    time = (float) 1000 / fps;
    delta = SDL_GetTicks() - timer;
    if (delta < time){
        SDL_Delay(time - delta);
    }
}

void prError(char* str){
    printf("%s! %s\n", str, SDL_GetError());
}
