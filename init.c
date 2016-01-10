#include "init.h"

int init(SDL_Window** window, SDL_Renderer** renderer){
    int success = 1;

    if (SDL_Init(SDL_INIT_EVERYTHING) < 0){
        prError("SDL_Init cant run");
        success = 0;
    }
    else
    {
        *window = SDL_CreateWindow("Tower Defence", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                                   SCREEN_WIDTH, SCREEN_HEIGHT,   SDL_WINDOW_SHOWN);
        if (*window == NULL){
            prError("Cant create window");
            success = 0;
        }
        else{
            *renderer = SDL_CreateRenderer(*window, -1, SDL_RENDERER_ACCELERATED);
            if (*renderer == NULL){
                prError("Renderer could not be created");
                success = 0;
            }
            else{
                int imgFlags = IMG_INIT_PNG;
                SDL_SetRenderDrawColor(*renderer, 0xFF, 0xFF, 0xFF, 0xFF);
                if (TTF_Init() == -1){
                    printf("Unable to initialize SDL_ttf: %s \n", TTF_GetError());
                }
                if( !(IMG_Init(imgFlags) & imgFlags) )
                {
                    printf("Unable to initialize SDL_image: %s \n", IMG_GetError());
                    success = 0;
                }
                if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0){
                    printf( "SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError() );
                    success = 0;
                }
            }
        }
    }
    return success;
}

void close(SDL_Texture** texture, SDL_Renderer** renderer, SDL_Window** window, TTF_Font* Font){
    SDL_DestroyTexture(*texture);
    *texture= NULL;

    SDL_DestroyRenderer(*renderer);
    *renderer = NULL;

    SDL_DestroyWindow(*window);
    *window = NULL;

    TTF_CloseFont(Font);
    Font = NULL;

    //Quit SDL subsystems
    SDL_Delay(7000);
    Mix_Quit();
    IMG_Quit();
    TTF_Quit();
    SDL_Quit();
}
