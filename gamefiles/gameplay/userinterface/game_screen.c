#include "library/main.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <stdio.h>



void desenhaFundo(CChessSettings * settings){
    SDL_Rect fundo = {0,0,1920,1080};
    SDL_RenderCopy(settings->gameRenderer,settings->textures.niveisTextures[0],NULL,&fundo);
}


void desenhaPromotion(GameStruct * game , CChessSettings * settings){
    int offsetY = ( (posTabuleiro(game->pieceCoords) / 8 ) < 1) ? 1000 : 0,
        offsetX = posTabuleiro(game->pieceCoords)%8;
    int offset_textura = (game->turnoJogador == brancas) ? 0 : 6;
    SDL_Rect promotion_sq = {100*offsetX,100 + offsetY,100,100};
    SDL_RenderCopy(settings->gameRenderer,settings->textures.miscTextures[3],NULL,&promotion_sq);

    SDL_Rect queen = {125*offsetX,125 + offsetY,50,50};
    SDL_Rect rook = {175*offsetX,125 + offsetY,50,50};
    SDL_Rect bishop = {125*offsetX,175 + offsetY,50,50};
    SDL_Rect knight = {175*offsetX,175 + offsetY,50,50};

    SDL_RenderCopy(settings->gameRenderer,settings->textures.tabTextures[Queen + offset_textura],NULL,&queen);
    SDL_RenderCopy(settings->gameRenderer,settings->textures.tabTextures[Rook + offset_textura],NULL,&rook);
    SDL_RenderCopy(settings->gameRenderer,settings->textures.tabTextures[Bishop + offset_textura],NULL,&bishop);
    SDL_RenderCopy(settings->gameRenderer,settings->textures.tabTextures[Horse + offset_textura],NULL,&knight);
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
    if(game->pawnPromoted) desenhaPromotion(game,settings);
}