#include "startscreen.h"

int menu(SDL_Renderer* Renderer){
    SDL_Event event;
    SDL_Texture* cursor_texture = getTextureFromPath("BMPimages/Cursor/1.png", Renderer);


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

    SDL_Texture* menu_bg_1 = getTextureFromPath("BMPimages/Parallax/menu_bg_1.png", Renderer);
    SDL_Texture* menu_bg_2 = getTextureFromPath("BMPimages/Parallax/menu_bg_2.png", Renderer);
    SDL_Texture* menu_bg_3 = getTextureFromPath("BMPimages/Parallax/menu_bg_3.png", Renderer);
    SDL_Texture* menu_bg_4 = getTextureFromPath("BMPimages/Parallax/menu_bg_4.png", Renderer);
    int displace_menu_bg_2 = 0;
    int displace_menu_bg_3 = 0;
    int displace_menu_bg_4 = 0;

    Mix_PlayMusic(musicMenu, -1);
    initButtons(Renderer, Font, startButton, exitButton, volumeButton);

    startTexture = startButton->mouseOutside;
    exitTexture = exitButton->mouseOutside;
    volumeTexture = volumeButton->mouseOutside_volOn;

    int timer = 0;

    while(state == IN_MENU){
        timer = SDL_GetTicks();
        while(SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT){
                state = EXIT;
            }
            if (event.type == SDL_MOUSEMOTION){
                SDL_GetMouseState(&x, &y);
                if (isInside(x, y, startButton)) startTexture = startButton->mouseInside;
                else startTexture = startButton->mouseOutside;

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
            if (event.type == SDL_MOUSEBUTTONDOWN){
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

        SDL_RenderCopy(Renderer, menu_bg_1, NULL, &menuRect);
        renderInfinityText(Renderer, menu_bg_2,&displace_menu_bg_2, 544, 2, 1);
        renderInfinityText(Renderer, menu_bg_3,&displace_menu_bg_3, 544, 2, 2);
        renderInfinityText(Renderer, menu_bg_4,&displace_menu_bg_4, 544, 2, 3);


        SDL_RenderCopy(Renderer, startTexture, NULL, &startButton->Rect);
        SDL_RenderCopy(Renderer, volumeTexture, NULL, &volumeButton->Rect);
        SDL_RenderCopy(Renderer, exitTexture, NULL, &exitButton->Rect);

        showCursor(Renderer, cursor_texture);
        SDL_RenderPresent(Renderer);
        getFps();
        waitForFps(timer, 35);
    }
    return state;
}

int isInside(int x, int y, SDL_Rect* Rect){
    if (Rect->x <= x && x <= Rect->x + Rect->w && Rect->y <= y && y <= Rect->y + Rect->h)
        return 1;
    else return 0;
}

void initButtons(SDL_Renderer* Renderer, TTF_Font* Font, ButtonMenu* startButton, ButtonMenu* exitButton, VolumeMenu* volumeButton){
    SDL_Color insideColor = {255, 0, 0};
    SDL_Color outsideColor = {0, 0, 255};

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
    volumeButton->mouseInside_volOn = getTextureFromPath("BMPimages/Icons/volumeOnInside.png", Renderer);
    volumeButton->mouseOutside_volOn = getTextureFromPath("BMPimages/Icons/volumeOnOutside.png", Renderer);
    volumeButton->mouseInside_volOff = getTextureFromPath("BMPimages/Icons/volumeOffInside.png", Renderer);
    volumeButton->mouseOutside_volOff = getTextureFromPath("BMPimages/Icons/volumeOffOutside.png", Renderer);
}

SDL_Texture* loadTextTexture(char* string, TTF_Font* Font, SDL_Color textColor, SDL_Renderer* renderer){
    SDL_Surface* textSurface = TTF_RenderText_Blended(Font, string, textColor);
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

void renderInfinityText(SDL_Renderer* Renderer, SDL_Texture* Texture,int* displace, int width_picture, int count, float speed){
    SDL_Rect textureRect = {*displace, 0, width_picture, SCREEN_HEIGHT};
    SDL_Rect screenRect = {0, 0, SCREEN_WIDTH, SCREEN_HEIGHT};
    SDL_RenderCopy(Renderer, Texture, &textureRect, &screenRect);
    *displace += speed;
    if (*displace + width_picture >= width_picture * count){
        *displace = 0;
    }
}
