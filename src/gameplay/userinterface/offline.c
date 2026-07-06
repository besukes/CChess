#include "library/main.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL2_gfxPrimitives.h>
#include <stdio.h>




void desenhaMenu(GameStruct * game , CChessSettings * settings){
    SDL_SetRenderDrawColor(settings->gameRenderer, 0, 0, 0, 150); 
    SDL_SetRenderDrawBlendMode(settings->gameRenderer, SDL_BLENDMODE_BLEND);
    SDL_Rect menu = {1131,0,789,1080};
    SDL_RenderFillRect(settings->gameRenderer,&menu);
    SDL_Color branco = {255, 255, 255, 255};

    SDL_SetRenderDrawColor(settings->gameRenderer, 0, 0, 0, 200); 
    SDL_Rect rect = {1130,0,5,1080};
    SDL_RenderFillRect(settings->gameRenderer,&rect);

    roundedBoxRGBA(settings->gameRenderer, 1241 , 50 , 1811 , 170 , 30 , 0, 0, 0, 160);

    roundedBoxRGBA(settings->gameRenderer, 1241 , 210 , 1811 , 597 , 30 , 0, 0, 0, 160);
    renderTextoCentradoSombra(settings->gameRenderer,settings->fonteJogoTitles,"Victory Conditions",branco,1530,210,2);


    //70 dist
    roundedBoxRGBA(settings->gameRenderer, 1260 , 300 , 1790 , 370 , 30 , 0, 0, 0, 180);
    SDL_Rect bola1 = {1270 , 310 , 50 , 50};
    SDL_RenderCopy(settings->gameRenderer,settings->textures.miscTextures[9],NULL,&bola1);
    renderTextoCentradoBasico(settings->gameRenderer,settings->fonteJogoSmallerTitles,"Checkmate",branco,1410,315,0.8);

    roundedBoxRGBA(settings->gameRenderer, 1260 , 400 , 1790 , 470 , 30 , 0, 0, 0, 180);
    SDL_Rect bola2 = {1270 , 410 , 50 , 50};
    SDL_RenderCopy(settings->gameRenderer,settings->textures.miscTextures[9],NULL,&bola2);
    renderTextoCentradoBasico(settings->gameRenderer,settings->fonteJogoSmallerTitles,"Take all non-king pieces",branco,1496,415,0.8);

    roundedBoxRGBA(settings->gameRenderer, 1260 , 500 , 1790 , 570 , 30 , 0, 0, 0, 180);
    SDL_Rect bola3 = {1270 , 510 , 50 , 50};
    SDL_RenderCopy(settings->gameRenderer,settings->textures.miscTextures[9],NULL,&bola3);
    renderTextoCentradoBasico(settings->gameRenderer,settings->fonteJogoSmallerTitles,"Check 10 times in a row",branco,1497,514,0.8);


    roundedBoxRGBA(settings->gameRenderer, 1241 , 637 , 1511 , 920 , 30 , 0, 0, 0, 160);
    drawScore(game->score_game,settings->gameRenderer,settings->fonteJogoSmallerTitles,1347,681,0.8);
    drawTurns(game->turns,settings->gameRenderer,settings->fonteJogoSmallerTitles, 1347 , 741 , 0.8);

    roundedBoxRGBA(settings->gameRenderer, 1541 , 637 , 1811 , 920 , 30 , 0, 0, 0, 160);
    
    /*SDL_Rect menu = {1167,0,800,1080};
    SDL_RenderFillRect(settings->gameRenderer, &menu);*/
}


void desenhaNivelTitle(CChessSettings * settings){
    SDL_Color branco = {255, 255, 255, 255};
    if(settings->nivelDificuldade == 0){
        renderTextoCentradoSombra(settings->gameRenderer,settings->fonteJogoTitles,"In the dawn",branco,1410,69,2);
    }
}


void desenhaInterfaceJogo(GameStruct * game ,CChessSettings * settings,SDL_Event event){
    desenhaFundo(settings,settings->textures.niveisTextures[0]);
    SDL_Rect tabuleiro = {210,140,800,800};
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
    SDL_Rect go_back = {50,950,100,100};
    SDL_RenderCopy(settings->gameRenderer,settings->textures.buttonsTextures[0],NULL,&go_back);

    desenhaMenu(game,settings);
    if(game->pawnPromoted) desenhaPromotion(game,settings);

    SDL_Rect turn = {250,(-40),700,210};
    SDL_RenderCopy(settings->gameRenderer,settings->textures.miscTextures[5 + game->turnoJogador],NULL,&turn);
    desenhaNivelTitle(settings);
}