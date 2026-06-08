#include "library/main.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>



void efetuaEventoClique(GameStruct * game , CChessSettings * settings,SDL_Event event){
    int mouseX = event.button.x , mouseY = event.button.y;
    uint64_bit click = click_table_position(mouseX,mouseY);
    if(click != 0){
        Pieces piece = comparePiece(game->estadoJogo ,game->turnoJogador, click);
        game->pieceCoords = click;
        game->pieceSelecionada = piece;
        if(piece==Empty) game->jogada = Invalid;
        updateBitboard_ClickEvent(game->turnoJogador,piece,&(game->estadoJogo),click);
    }
    else{
        if(dentroDoBotao(mouseX,mouseY,20,20,20,20)){

        }
        else if(1){

        }
    }
}

void efetuaEventoSoltar(GameStruct * game , CChessSettings * settings , SDL_Event event){
    int mouseX = event.button.x , mouseY = event.button.y;
    Boolean castles = 0, enpassant = 0;
    uint64_bit click = click_table_position(mouseX,mouseY);
    if(click != 0 && isPseudoValidMove(game,click,&castles,&enpassant)){
        atualizaJogada(game,click,castles,enpassant);
        game->jogada = check_or_mate(game);
        if(game->jogada==Invalid){
            undoMove(game,click);
        }
        else if(game->jogada == Checkmate) isCheckMate(game);
        else {
            notInCheck(game);
            update_en_passant(game);
        }
    }
    else{
        game->jogada = Invalid;
    }
}