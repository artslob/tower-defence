#include "global.h"

/* the window be rendering to */
SDL_Window* Window = NULL;
/* window renderer */
SDL_Renderer* Renderer = NULL;

/*  */
int main(int argc, char* args[]){
    block* head = NULL;
    int state = 0;

    if (init(&Window, &Renderer)){
        SDL_ShowCursor(0);
        BG_list_create(Renderer, &head);
        state = menu(Renderer);

        if (state == START){
            game(Renderer, head);
        }
    }
    close(&Renderer, &Window);
    return 0;
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
    static int x, y;
    static SDL_Rect cursorRect;
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
//        while (quit != 1){
//            timer = SDL_GetTicks();
//            while( SDL_PollEvent( &e ) != 0 )
//            {
//                if( e.type == SDL_QUIT )
//                {
//                    quit = 1;
//                }
//            }
//            SDL_SetRenderDrawColor(Renderer, 0xFF, 0xFF, 0xFF, 0xFF);
//            SDL_RenderClear(Renderer);
//
//            BG_list_render(Renderer, head);
//
//            SDL_RenderPresent(Renderer);
//
//            getFps();
//            //waitForFps(timer, 16.666);
//        }
//    }

//            currentTime = SDL_GetTicks()/1000;
//            itoa(currentTime, timeStr, 10);
//            timeTexture = loadTextTexture(timeStr, Font, timeColor, Renderer);
//            SDL_RenderCopy(Renderer, timeTexture, NULL, &timeRect);
