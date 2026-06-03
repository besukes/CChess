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
    }
    else{
        if(dentroDoBotao(mouseX,mouseY,20,20,20,20)){

        }
        else if(1){

        }
    }
}

void efetuaEventoSoltar(GameStruct * game , CChessSettings * settings , SDL_Event event){

}