#include "init.h"
#include "main.h"


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
                    sprintf(stderr, "Unable to initialize SDL_ttf: %s \n", TTF_GetError());
                }
                if(!(IMG_Init(imgFlags) & imgFlags))
                {
                    sprintf(stderr, "Unable to initialize SDL_image: %s \n", IMG_GetError());
                    success = 0;
                }
                if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0){
                    sprintf(stderr, "SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError() );
                    success = 0;
                }
            }
        }
    }
    return success;
}

void closeSDLResources(SDL_Renderer** renderer, SDL_Window** window){
    Mix_HaltMusic();
    SDL_DestroyRenderer(*renderer);

    SDL_DestroyWindow(*window);

    Mix_Quit();
    IMG_Quit();
    TTF_Quit();
    SDL_Quit();
}
