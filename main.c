#include "global.h"

/* the window be rendering to */
SDL_Window* Window = NULL;
/* window renderer */
SDL_Renderer* Renderer = NULL;
/* current displayed texture */
SDL_Texture* Texture = NULL;

/*  */
int main(int argc, char* args[]){
    int quit = 0; /* main loop */
    SDL_Event e; /* event queue */

    block* head = NULL;

    int timer = 0;

    /* initialization SDL */
    if (init(&Window, &Renderer)){
        BG_list_create(Renderer, &head);
        menu(Renderer);
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
    close(&Texture, &Renderer, &Window);
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

void waitForFps(int timer, double fps){
    static int delta = 0;
    delta = SDL_GetTicks() - timer;
    printf("Delta :%d\n", delta);
    if (delta < fps) SDL_Delay(fps - delta);
}

void prError(char* str){
    printf("%s! %s\n", str, SDL_GetError());
}

//            currentTime = SDL_GetTicks()/1000;
//            itoa(currentTime, timeStr, 10);
//            timeTexture = loadTextTexture(timeStr, Font, timeColor, Renderer);
//            SDL_RenderCopy(Renderer, timeTexture, NULL, &timeRect);
