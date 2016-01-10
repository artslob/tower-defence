#include "startscreen.h"

int menu(SDL_Renderer* Renderer, SDL_Window* Window){
    SDL_Event* event;
    ButtonMenu* startButton = malloc(sizeof(ButtonMenu));
    ButtonMenu* exitButton = malloc(sizeof(ButtonMenu));
    VolumeMenu* volumeButton = malloc(sizeof(VolumeMenu));

    TTF_Font* Font = TTF_OpenFont("TTFtext/GOST-type-B-Standard.ttf", 1000);
    Mix_Music* musicMenu = Mix_LoadMUS("MIXmusic/space.flac");

    SDL_Texture* startTexture = NULL;
    SDL_Texture* exitTexture = NULL;
    SDL_Texture* volumeTexture = NULL;

    int state = IN_MENU;
    int x, y;
    int volumeOn = 1;

    SDL_Rect menuRect = {0, 0, SCREEN_WIDTH, SCREEN_HEIGHT};

    SDL_Texture* menuBgFirst = getTextureFromPath("BMPimages/Parallax/menu_bg_1.png", Renderer);
//    SDL_Texture* menu_bg_2 = getTextureFromPath("BMPimages/Parallax/menu_bg_2.png", Renderer);
//    SDL_Texture* menu_bg_3 = getTextureFromPath("BMPimages/Parallax/menu_bg_3.png", Renderer);
//    SDL_Texture* menu_bg_4 = getTextureFromPath("BMPimages/Parallax/menu_bg_4.png", Renderer);

    Mix_PlayMusic(musicMenu, -1);
    initButtons(Renderer, Font, startButton, exitButton, volumeButton);
    startTexture = startButton->mouseOutside;
    volumeTexture = volumeButton->mouseOutside_volOn;
    exitTexture = exitButton->mouseOutside;
    while(state == IN_MENU){
        while(SDL_PollEvent(event))
        {
            if (event->type == SDL_QUIT){
                state = EXIT;
            }
            if (event->type == SDL_MOUSEMOTION){
                SDL_GetMouseState(&x, &y);
                //if (isInside(x, y, startButton)) startTexture = startButton->mouseInside;
                //else startTexture = startButton->mouseOutside;

                if (isInside(x, y, exitButton)) exitTexture = exitButton->mouseInside;
                else exitTexture = exitButton->mouseOutside;

                if (isInside(x, y, volumeButton)){
                    if (volumeOn) volumeTexture = volumeButton->mouseInside_volOn;
                    else volumeTexture = volumeButton->mouseInside_volOff;
                }
                else{
                    if (volumeOn) volumeTexture = volumeButton->mouseOutside_volOn;
                    else volumeTexture = volumeButton->mouseOutside_volOff;
                }
            }
            if (event->type == SDL_MOUSEBUTTONDOWN){
                SDL_GetMouseState(&x, &y);
                if (isInside(x, y, startButton)) state = START;

                if (isInside(x, y, exitButton)) state = EXIT;

                if (isInside(x, y, volumeButton)){
                    if (volumeOn){
                        volumeOn = 0;
                        Mix_PauseMusic();
                        volumeTexture = volumeButton->mouseInside_volOff;
                    }
                    else{
                        volumeOn = 1;
                        Mix_ResumeMusic();
                        volumeTexture = volumeButton->mouseInside_volOn;
                    }
                }
            }
        }
        SDL_SetRenderDrawColor(Renderer, 0xFF, 0xFF, 0xFF, 0xFF);
        SDL_RenderClear(Renderer);

        SDL_RenderCopy(Renderer, menuBgFirst, NULL, &menuRect);

        SDL_RenderCopy(Renderer, startTexture, NULL, &startButton->Rect);
        SDL_RenderCopy(Renderer, volumeTexture, NULL, &volumeButton->Rect);
        SDL_RenderCopy(Renderer, exitTexture, NULL, &exitButton->Rect);


        SDL_RenderPresent(Renderer);
        getFps();
        SDL_Delay(10);

    }
}

int isInside(int x, int y, SDL_Rect* Rect){
    if (Rect->x <= x && x <= Rect->x + Rect->w && Rect->y <= y && y <= Rect->y + Rect->h)
        return 1;
    else return 0;
}

void initButtons(SDL_Renderer* Renderer, TTF_Font* Font, ButtonMenu* startButton, ButtonMenu* exitButton, VolumeMenu* volumeButton){
    SDL_Color insideColor = {0, 0, 255};
    SDL_Color outsideColor = {0, 0, 0};

    startButton->Rect.x = 120;
    startButton->Rect.y = 40;
    startButton->Rect.w = 400;
    startButton->Rect.h = 160;
    startButton->mouseInside = loadTextTexture("START", Font, insideColor, Renderer);
    startButton->mouseOutside = loadTextTexture("START", Font, outsideColor, Renderer);

    exitButton->Rect.x = 240;
    exitButton->Rect.y = 378;
    exitButton->Rect.w = 160;
    exitButton->Rect.h = 64;
    exitButton->mouseInside = loadTextTexture("EXIT", Font, insideColor, Renderer);
    exitButton->mouseOutside = loadTextTexture("EXIT", Font, outsideColor, Renderer);

    volumeButton->Rect.x = 580;
    volumeButton->Rect.y = 0;
    volumeButton->Rect.w = 60;
    volumeButton->Rect.h = 60;
    volumeButton->mouseInside_volOn = getTextureFromPath("BMPimages/Icons/volumeOnblue.png", Renderer);
    volumeButton->mouseOutside_volOn = getTextureFromPath("BMPimages/Icons/volumeOnblack.png", Renderer);
    volumeButton->mouseInside_volOff = getTextureFromPath("BMPimages/Icons/volumeOffblue.png", Renderer);
    volumeButton->mouseOutside_volOff = getTextureFromPath("BMPimages/Icons/volumeOffblack.png", Renderer);
}

SDL_Texture* loadTextTexture(char* texturePath, TTF_Font* Font, SDL_Color textColor, SDL_Renderer* renderer){
    SDL_Surface* textSurface = TTF_RenderText_Blended(Font, texturePath, textColor);
    SDL_Texture* texture = NULL;
    if (textSurface == NULL){
        prError("Unable to create texture from rendered text");
        return NULL;
    }
    else{
        texture = SDL_CreateTextureFromSurface(renderer, textSurface);
        if (texture == NULL){
            prError("Unable to create texture from rendered text");
            return NULL;
        }
        SDL_FreeSurface(textSurface);
    }
    return texture;
}

void renderInfinityText(SDL_Renderer* Renderer, SDL_Texture* Texture ){
    static int displace = 0;
    SDL_Rect textureRect = {displace, 0, SCREEN_WIDTH, SCREEN_HEIGHT};
    SDL_Rect screenRect = {0, 0, SCREEN_WIDTH, SCREEN_HEIGHT};
    SDL_RenderCopy(Renderer, Texture, &textureRect, &screenRect);
    displace += 2.5;
    if (displace + SCREEN_WIDTH >= SCREEN_WIDTH * 4){
        displace = 0;
    }
}
