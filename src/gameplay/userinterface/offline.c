#include "library/main.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <stdio.h>



void desenhaFundo(CChessSettings * settings){
    SDL_Rect fundo = {0,0,1920,1080};
    SDL_RenderCopy(settings->gameRenderer,settings->textures.niveisTextures[0],NULL,&fundo);
}




void desenhaMenu(GameStruct * ngame , CChessSettings * settings){
    SDL_SetRenderDrawColor(settings->gameRenderer, 0, 0, 0, 180); 
    SDL_SetRenderDrawBlendMode(settings->gameRenderer, SDL_BLENDMODE_BLEND);
    SDL_Rect menu = {1167,0,800,1080};
    SDL_RenderFillRect(settings->gameRenderer, &menu);
}


void desenhaNivelTitle(CChessSettings * settings){
    SDL_Rect title = {1240,(-5),600,210};
    if(settings->nivelDificuldade == 0){
        SDL_RenderCopy(settings->gameRenderer,settings->textures.niveisTextures[1],NULL,&title);
    }
}


void desenhaInterfaceJogo(GameStruct * game ,CChessSettings * settings,SDL_Event event){
    desenhaFundo(settings);
    SDL_Rect tabuleiro = {260,140,800,800};
    SDL_RenderCopy(settings->gameRenderer,settings->textures.tabTextures[1],NULL,&tabuleiro);
    if(game->selected_piece_attacks != 0){
        uint64_bit op = get_opposing_colour_bitboard(&game->estadoJogo,game->turnoJogador);
        desenharPieceAttacks(settings,game->estadoJogo.enpassant, game->selected_piece_attacks , op);
    }
    desenhaCheck(game,settings);
    for(int i = 0 ; i < 6 ; i++){
        desenhaTipoPiece(game->estadoJogo.tabuleirojogo[0][i],(Pieces)i,settings,game,0);
    }
    for( int i = 0; i < 6; i++){
        desenhaTipoPiece(game->estadoJogo.tabuleirojogo[1][i],(Pieces)(i),settings,game,6);
    }
    SDL_Rect go_back = {100,950,100,100};
    SDL_RenderCopy(settings->gameRenderer,settings->textures.buttonsTextures[0],NULL,&go_back);

    desenhaMenu(game,settings);
    if(game->pawnPromoted) desenhaPromotion(game,settings);

    SDL_Rect turn = {300,(-40),700,210};
    SDL_RenderCopy(settings->gameRenderer,settings->textures.miscTextures[5 + game->turnoJogador],NULL,&turn);
    desenhaNivelTitle(settings);
}