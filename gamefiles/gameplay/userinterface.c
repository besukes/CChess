#include "library/main.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <stdio.h>

void desenharPiece(Pieces tipoPiece , int linha , int coluna , CChessSettings * settings, int offset){
    SDL_Rect posicaoPeca = {125*coluna+200, 1080 - (125 * linha+167),125,125};
    SDL_RenderCopy(settings->gameRenderer,settings->textures.chessPieces[tipoPiece + offset],NULL,&posicaoPeca);
}


void desenhaPieces(uint64_bit pos_pieces,Pieces tipoPiece , CChessSettings * settings, GameStruct * game, int offset){
    int counter=0 , linha , coluna;
    uint64_bit casaAtual=1ULL;
    while(pos_pieces!=0){
        if(casaAtual & pos_pieces){
            linha = counter/8; coluna = counter%8;
            if( game->isKeyPressedDown && game->pieceSelecionada == tipoPiece && game->pieceCoords == (1ULL<<counter))
                desenharPieceDrag(tipoPiece,settings->posMouseX,settings->posMouseY,settings,offset);
            else
            desenharPiece(tipoPiece,linha,coluna,settings, offset);
        }
        pos_pieces = (pos_pieces>>1);
        counter++;
    }
}

void desenharPieceDrag(Pieces tipoPiece , int mouseX , int mouseY , CChessSettings * settings , int offset)
{
    SDL_Rect centro = {mouseX-62,mouseY-62,125,125};
    SDL_RenderCopyEx(settings->gameRenderer,settings->textures.chessPieces[tipoPiece + offset], NULL, &centro, 0, NULL, SDL_FLIP_NONE);
}

void desenhaInterfaceMenu(CChessSettings * settings,SDL_Event event){
    SDL_Rect fundo = {0,0,1920,1080};
    SDL_Rect botaoJogar = {700,400,500,100};
    SDL_RenderCopy(settings->gameRenderer,settings->textures.miscTextures[0],NULL,&fundo);
    SDL_RenderCopy(settings->gameRenderer,settings->textures.miscTextures[1],NULL,&botaoJogar);
}


void desenhaInterfaceJogo(GameStruct * game ,CChessSettings * settings,SDL_Event event){
    SDL_Rect tabuleiro = {200,40,1000,1000};
    SDL_RenderCopy(settings->gameRenderer,settings->textures.tabTextures[0],NULL,&tabuleiro);
    for(int i = 0 ; i < 6 ; i++){
        desenhaPieces(game->estadoJogo.tabuleirojogo[0][i],(Pieces)i,settings,game,0);
    }
    for( int i = 0; i < 6; i++){
        desenhaPieces(game->estadoJogo.tabuleirojogo[1][i],(Pieces)(i),settings,game,6);
    }

}


void desenhaMenuThemes(CChessSettings * settings,SDL_Event event){

}


void desenhaWinScreen(GameStruct * game ,CChessSettings * settings,SDL_Event event){

}