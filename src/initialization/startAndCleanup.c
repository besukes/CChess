#include "library/main.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <stdlib.h>

int getOption(void){
    int o=0;
    printf("Insira a resolução desejada:\n"
            "(1)- 1280x720\n"
            "(2)- 1600x900\n"
            "(3)- 1920x1080\n"
            "(DEFAULT) - FULLSCREEN\n");
    scanf("%d",&o);
    return o;
}

/*Função que dado uma opção de resolução atribui os valores de largura e altura da janela*/
void setResolution(int * resX,int * resY,int * optn){
    switch(*optn){
        case 1:
            *resX=1280;*resY=720;
        break;
        case 2:
            *resX=1600;*resY=900;
        break;
        case 3:
            *resX=1920;*resY=1080;
        break;
        //Resolução default será fullscreen
        default:
            *optn = 4;
    }
}

SDL_Initializators sdl_initializer(void){
    SDL_Init(SDL_INIT_VIDEO);
    SDL_Window* window;
    int optn = getOption(),resX , resY;
    setResolution(&resX,&resY,&optn);
    if(optn==4) window = SDL_CreateWindow("CChess", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 0 , 0, SDL_WINDOW_FULLSCREEN_DESKTOP);
    else window = SDL_CreateWindow("CChess", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, resX , resY , 0);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    //para não precisar de dar scale às imagens no ecrã
    SDL_RenderSetLogicalSize(renderer, 1920, 1080);
    SDL_Initializators init = {.renderer = renderer , .window = window};
    return init;
}



void freeUserSettings(CChessSettings * user){
    free(user->selected_pieces_power);
    free(user->story_st_line);

    free(user->user_custom_items.extraPieces_owned);
    free(user->user_custom_items.ultimates_owned);
    free(user->user_custom_items.ultimates_unlocked);
}


void free_allocated_memory(GameStruct * game , CChessSettings * user){
    freeLinkedList(game->lastmoves);
    for(int i = 0; i < 12; i++){
        SDL_DestroyTexture(user->textures.chessPieces[i]);
    }
    for(int i = 1; i < 2; i++){
        SDL_DestroyTexture(user->textures.tabTextures[i]);
    }
    for(int i = 0; i < 2; i++){
        SDL_DestroyTexture(user->textures.niveisTextures[i]);
    }
    for(int i = 0; i < 8; i++){
        SDL_DestroyTexture(user->textures.miscTextures[i]);
    }
    for(int i = 0; i < 60; i++){
        SDL_DestroyTexture(user->cosmeticos.gif_checkmate[i]);
    }
    free(user->cosmeticos.gif_checkmate);
    for(int i = 0; i < 5; i++){
        SDL_DestroyTexture(user->textures.buttonsTextures[i]);
    }
    SDL_DestroyRenderer(user->gameRenderer);
    freeUserSettings(user);
}