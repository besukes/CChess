#include "library/main.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>
#include <stdio.h>



void efetuaEventoClique(GameStruct * game , CChessSettings * settings,SDL_Event * event){
    int mouseX = event->button.x , mouseY = event->button.y;
    uint64_bit click = click_table_position(mouseX,mouseY);
    if(game->pawnPromoted){
        int did_promote = clickPromotingPiece(game,mouseX,mouseY);
        if(did_promote) game->promotedSucessfully = 1;
    }
    else if(click != 0){
        Pieces piece = comparePiece(game->estadoJogo ,game->turnoJogador, click);
        game->pieceCoords = click;
        game->pieceSelecionada = piece;
        if(piece==Empty) game->jogada = Invalid;
    }
    else{
        if(dentroDoBotao(mouseX,mouseY,50,250,1000,1050)){ 
            settings->screenAtual = Menu;
            resetGame(game);
        }
        else if(1){
            
        }
    }
}



void eventoCheckmate(CChessSettings * settings){
    settings->screenAtual = WinScreen;
    settings->ticks_checkmate = settings->ticks;
}



void eventoPromotePiece(GameStruct * game , CChessSettings * settings,uint64_bit click){
    game->jogada = check_or_mate(game,0,click);
    game->promotedSucessfully = 0;
    if(game->jogada == Checkmate) eventoCheckmate(settings);
    else if(game->jogada == Invalid) game->jogada = Valid; //Apenas para prevenir bugs
}



void efetuaEventoSoltar(GameStruct * game , CChessSettings * settings , SDL_Event event){
    int mouseX = event.button.x , mouseY = event.button.y;
    Boolean castles = 0, enpassant = 0 , promote = 0;
    uint64_bit click = click_table_position(mouseX,mouseY);
    if(game->promotedSucessfully) eventoPromotePiece(game,settings,click);
    else if(click != 0 && isPseudoValidMove(game,click,&castles,&enpassant,&promote) && !game->pawnPromoted){
            int check_antes = game->estadoJogo.king_in_check[game->turnoJogador];
            atualizaJogada(game,click,castles,enpassant);
            game->jogada = check_or_mate(game,castles,click);
            if(game->jogada==Invalid){
                undoMove(game,click,castles);
                game->estadoJogo.king_in_check[game->turnoJogador] = check_antes;
            }
            else if(game->jogada == Checkmate) eventoCheckmate(settings);
            else {
                notInCheck(game);
                update_en_passant(game);
                game->pawnPromoted = promote;
                if(promote) game->pieceCoords = click; //para depois se desenhar o quadrado de promoção na posição correta
            }
    }
    else{
        game->jogada = Invalid;
    }
}