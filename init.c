#include "init.h"
#include "utils.h"


int init(SDL_Window** window, SDL_Renderer** renderer) {
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
        prError("SDL_Init could not init with flag SDL_INIT_EVERYTHING");
        return 0;
    }

    *window = SDL_CreateWindow(
        "Tower Defence",
        SDL_WINDOWPOS_UNDEFINED,
        SDL_WINDOWPOS_UNDEFINED,
        SCREEN_WIDTH,
        SCREEN_HEIGHT,
        SDL_WINDOW_SHOWN
    );

    if (*window == NULL) {
        prError("Cant create window");
        return 0;
    }

    *renderer = SDL_CreateRenderer(*window, -1, SDL_RENDERER_ACCELERATED);
    if (*renderer == NULL) {
        prError("Renderer could not be created");
        return 0;
    }

    SDL_SetRenderDrawColor(*renderer, 0xFF, 0xFF, 0xFF, 0xFF);

    if (TTF_Init() == -1) {
        fprintf(stderr, "Unable to initialize SDL_ttf: %s.\n", TTF_GetError());
        return 0;
    }

    if (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG)) {
        fprintf(stderr, "Unable to initialize SDL_image: %s.\n", IMG_GetError());
        return 0;
    }

    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
        fprintf(stderr, "SDL_mixer could not initialize! SDL_mixer Error: %s.\n", Mix_GetError());
        return 0;
    }

    return 1;
}

void closeSDLResources(SDL_Renderer** renderer, SDL_Window** window) {
    Mix_HaltMusic();

    SDL_DestroyRenderer(*renderer);
    SDL_DestroyWindow(*window);

    Mix_Quit();
    IMG_Quit();
    TTF_Quit();
    SDL_Quit();
}
