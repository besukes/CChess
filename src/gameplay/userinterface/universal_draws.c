#include "library/main.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL2_gfxPrimitives.h>
#include <stdio.h>



void desenhaCheck(GameStruct * game , CChessSettings * settings){
    int type = (-1);
    if(game->estadoJogo.king_in_check[0]) type = 0;
    else if(game->estadoJogo.king_in_check[1]) type = 1;
    else return;

    int pos_tab = posTabuleiro(game->estadoJogo.tabuleirojogo[type][King]);

    int coluna = pos_tab % 8 , linha = pos_tab / 8;
    SDL_SetRenderDrawColor(settings->gameRenderer, 255 , 0 , 0, 150); 
    SDL_Rect check = {100*coluna+260, 1080 - (100 * linha + 240),100,100};
    SDL_RenderFillRect(settings->gameRenderer, &check);
}


void desenharPieceAttacks(CChessSettings * settings , uint64_bit passant , uint64_bit attacks , uint64_bit cor_oposta){
    int counter = 0;
    uint64_bit casa_atual = 1ULL;
    while(attacks != 0){
        if(casa_atual & attacks){
            int linha = counter/8 , coluna = counter % 8;
            if(1ULL<<counter & (cor_oposta | passant)){
                filledCircleRGBA(settings->gameRenderer, 100*coluna+310, 1080 - (100 * linha + 192) , 40 , 0 , 0, 0, 150);
            }
            else filledCircleRGBA(settings->gameRenderer, 100*coluna+310, 1080 - (100 * linha + 192) , 10 , 0 , 0, 0, 150);
        }
        attacks = (attacks>>1);
        counter++;
    }
}


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
            Boolean is_selected_piece = game->pieceSelecionada == tipoPiece && game->pieceCoords == (1ULL<<counter);
            if( game->isKeyPressedDown && is_selected_piece && !game->pawnPromoted)
                desenharPieceDrag(tipoPiece,settings->posMouseX,settings->posMouseY,settings,offset);
            else
            desenharPiece(tipoPiece,linha,coluna,settings, offset);
        }
        pos_pieces = (pos_pieces>>1);
        counter++;
    }
}



void desenhaPromotion(GameStruct * game , CChessSettings * settings){
    int offsetY = ( (posTabuleiro(game->pieceCoords) / 8 ) < 1) ? 800 : 0,
        offsetX = posTabuleiro(game->pieceCoords)%8;
    int offset_textura = (game->turnoJogador == brancas) ? 0 : 6;
    SDL_Rect promotion_sq = {300 + 110*offsetX,100 + offsetY,175,175};
    SDL_RenderCopy(settings->gameRenderer,settings->textures.miscTextures[3],NULL,&promotion_sq);

    SDL_Rect queen = {305 + 110*offsetX,105 + offsetY,70,70};
    SDL_Rect rook = {395 + 110*offsetX,105 + offsetY,70,70};
    SDL_Rect bishop = {305 + 110*offsetX,190 + offsetY,70,70};
    SDL_Rect knight = {395 + 110*offsetX,190 + offsetY,70,70};

    SDL_RenderCopy(settings->gameRenderer,settings->textures.chessPieces[Queen + offset_textura],NULL,&queen);
    SDL_RenderCopy(settings->gameRenderer,settings->textures.chessPieces[Rook + offset_textura],NULL,&rook);
    SDL_RenderCopy(settings->gameRenderer,settings->textures.chessPieces[Bishop + offset_textura],NULL,&bishop);
    SDL_RenderCopy(settings->gameRenderer,settings->textures.chessPieces[Horse + offset_textura],NULL,&knight);
}


void desenhaFundo(CChessSettings * settings , SDL_Texture * texture){
    SDL_Rect fundo = {0,0,1920,1080};
    SDL_RenderCopy(settings->gameRenderer,texture,NULL,&fundo);
}