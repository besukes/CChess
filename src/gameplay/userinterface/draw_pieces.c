#include "library/main.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <stdio.h>



void desenharPiece(Pieces tipoPiece , int linha , int coluna , CChessSettings * settings, int offset){
    SDL_Rect posicaoPeca = {100*coluna+260, 1080 - (100 * linha + 246),100,100};
    SDL_RenderCopy(settings->gameRenderer,settings->textures.chessPieces[tipoPiece + offset],NULL,&posicaoPeca);
}


void desenharPieceDrag(Pieces tipoPiece , int mouseX , int mouseY , CChessSettings * settings , int offset)
{
    SDL_Rect centro = {mouseX-51,mouseY-51,100,100};
    SDL_RenderCopyEx(settings->gameRenderer,settings->textures.chessPieces[tipoPiece + offset], NULL, &centro, 0, NULL, SDL_FLIP_NONE);
}


void desenhaTipoPiece(uint64_bit pos_pieces,Pieces tipoPiece , CChessSettings * settings, GameStruct * game, int offset){
    int counter=0 , linha , coluna;
    uint64_bit casaAtual=1ULL;
    while(pos_pieces!=0){
        if(casaAtual & pos_pieces){
            linha = counter/8; coluna = counter%8;
            if( game->isKeyPressedDown && game->pieceSelecionada == tipoPiece && game->pieceCoords == (1ULL<<counter) && !game->pawnPromoted)
                desenharPieceDrag(tipoPiece,settings->posMouseX,settings->posMouseY,settings,offset);
            else
            desenharPiece(tipoPiece,linha,coluna,settings, offset);
        }
        pos_pieces = (pos_pieces>>1);
        counter++;
    }
}

