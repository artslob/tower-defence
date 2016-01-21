#include "bg.h"

void BG_list_render(SDL_Renderer* Renderer, block* head){
    int i = 0, j = 0;
    block* currentBlock = head;
    SDL_Rect Rect;
    for (i = 0; i < COUNT_BLOCKS_HEIGHT; i++){
        for (j = 0; j < COUNT_BLOCKS_WIDTH; j++){
            Rect.x = j * BLOCK_WIDTH;
            Rect.y = i * BLOCK_HEIGHT;
            Rect.w = BLOCK_WIDTH;
            Rect.h = BLOCK_HEIGHT;
            SDL_RenderCopy(Renderer, currentBlock->texture, NULL, &Rect);
            currentBlock = currentBlock->next;
        }
    }
}

void BG_list_create(SDL_Renderer* Renderer, block** head){
    int i, j;
    block* end = NULL;
    tiles* tiles = NULL;
    int *map;

    tiles = init_tales(Renderer);
    map = openMap("BMPimages/Map/map.txt");

    for (i = 0; i < COUNT_BLOCKS_HEIGHT; i++){
        for (j = 0; j < COUNT_BLOCKS_WIDTH; j++){
            switch (*(map + i * COUNT_BLOCKS_WIDTH + j)){
            case 1:
                add_block(&end, head, tiles->texture1);
                break;
            case 2:
                add_block(&end, head, tiles->texture2);
                break;
            case 3:
                add_block(&end, head, tiles->texture3);
                break;
            case 4:
                add_block(&end, head, tiles->texture4);
                break;
            case 5:
                add_block(&end, head, tiles->texture5);
                break;
            case 6:
                add_block(&end, head, tiles->texture6);
                break;
            case 7:
                add_block(&end, head, tiles->texture7);
                break;
            case 8:
                add_block(&end, head, tiles->texture8);
                break;
            case 9:
                add_block(&end, head, tiles->texture9);
                break;
            case 10:
                add_block(&end, head, tiles->texture10);
                break;
            case 11:
                add_block(&end, head, tiles->texture11);
                break;
            case 12:
                add_block(&end, head, tiles->texture12);
                break;
            case 13:
                add_block(&end, head, tiles->texture13);
                break;
            case 14:
                add_block(&end, head, tiles->texture14);
                break;
            case 15:
                add_block(&end, head, tiles->texture15);
                break;
            case 16:
                add_block(&end, head, tiles->texture16);
                break;
            }
        }
    }
    free(tiles);
    tiles = NULL;
}

void add_block(block** end, block** head, SDL_Texture* texture){
    block* newblock = block_create(texture);
    block* currentblock = *end;
    if (*end == NULL){
        *head = newblock;
        *end = newblock;
    }
    else{
        currentblock->next = newblock;
        *end = newblock;
    }
//    block* currentblock = *head;
//    if (currentblock !=NULL){
//        while (currentblock->next != NULL){
//            currentblock = currentblock->next;
//        }
//        currentblock->next = newblock;
//    }
//    else {
//        *head = newblock;
//    }
}

int* openMap(char* str){
    int* buff = malloc(sizeof(int) * COUNT_BLOCKS_HEIGHT * COUNT_BLOCKS_WIDTH);
    FILE* fp = NULL;
    if ((fp = fopen(str, "r")) != NULL){
        char c = 0;
        int i = 0;
        int j = 0;
        int q = 0;
        while (feof(fp) == 0){
            c = getc(fp);
            if (c != ' ' && c != '\n'){
                q++;
                if (q == 1) *(buff + i * COUNT_BLOCKS_WIDTH + j) = c - '0';
                else if (q == 2) *(buff + i * COUNT_BLOCKS_WIDTH + j) =
                    10 * (*(buff + i * COUNT_BLOCKS_WIDTH + j)) + c - '0';
            }
            else if (c == ' ') {
                q = 0;
                j++;
            }
            else if (c == '\n'){
                q = 0;
                j = 0;
                i++;
            }
        }
    }
    else printf("Cant open map! Path: %s.\n", str);
    fclose(fp);
    return buff;
}

tiles* init_tales(SDL_Renderer* Renderer){
    tiles* newtiles = malloc(sizeof(tiles));
    newtiles->texture1 = getTextureFromPath("BMPimages/Map/1.png", Renderer);
    newtiles->texture2 = getTextureFromPath("BMPimages/Map/2.png", Renderer);
    newtiles->texture3 = getTextureFromPath("BMPimages/Map/3.png", Renderer);
    newtiles->texture4 = getTextureFromPath("BMPimages/Map/4.png", Renderer);
    newtiles->texture5 = getTextureFromPath("BMPimages/Map/5.png", Renderer);
    newtiles->texture6 = getTextureFromPath("BMPimages/Map/6.png", Renderer);
    newtiles->texture7 = getTextureFromPath("BMPimages/Map/7.png", Renderer);
    newtiles->texture8 = getTextureFromPath("BMPimages/Map/8.png", Renderer);
    newtiles->texture9 = getTextureFromPath("BMPimages/Map/9.png", Renderer);
    newtiles->texture10 = getTextureFromPath("BMPimages/Map/10.png", Renderer);
    newtiles->texture11 = getTextureFromPath("BMPimages/Map/11.png", Renderer);
    newtiles->texture12 = getTextureFromPath("BMPimages/Map/12.png", Renderer);
    newtiles->texture13 = getTextureFromPath("BMPimages/Map/13.png", Renderer);
    newtiles->texture14 = getTextureFromPath("BMPimages/Map/14.png", Renderer);
    newtiles->texture15 = getTextureFromPath("BMPimages/Map/15.png", Renderer);
    newtiles->texture16 = getTextureFromPath("BMPimages/Map/16.png", Renderer);
    return newtiles;
}

block* block_create(SDL_Texture* texture){
    block* newblock = malloc(sizeof(block));
    newblock->texture = texture;
    newblock->next = NULL;
    return newblock;
}
