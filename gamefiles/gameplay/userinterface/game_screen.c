#include "library/main.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <stdio.h>



void desenhaFundo(CChessSettings * settings){
    SDL_Rect fundo = {0,0,1920,1080};
    SDL_RenderCopy(settings->gameRenderer,settings->textures.niveisTextures[0],NULL,&fundo);
}


void desenhaInterfaceJogo(GameStruct * game ,CChessSettings * settings,SDL_Event event){
    desenhaFundo(settings);
    SDL_Rect tabuleiro = {200,40,1000,1000};
    SDL_RenderCopy(settings->gameRenderer,settings->textures.tabTextures[1],NULL,&tabuleiro);
    for(int i = 0 ; i < 6 ; i++){
        desenhaTipoPiece(game->estadoJogo.tabuleirojogo[0][i],(Pieces)i,settings,game,0);
    }
    for( int i = 0; i < 6; i++){
        desenhaTipoPiece(game->estadoJogo.tabuleirojogo[1][i],(Pieces)(i),settings,game,6);
    }
    SDL_Rect go_back = {1750,950,100,100};
    SDL_RenderCopy(settings->gameRenderer,settings->textures.buttonsTextures[0],NULL,&go_back);
}