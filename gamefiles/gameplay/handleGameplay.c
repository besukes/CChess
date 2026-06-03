#include "library/main.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>


void handleJogadaMenuPrincipal(CChessSettings * settings,SDL_Event event){

}


void handleJogadaChess(GameStruct* game , CChessSettings * settings,SDL_Event event){
    if(event.type == SDL_MOUSEBUTTONDOWN){
        if(event.button.button == SDL_BUTTON_LEFT && game->isKeyPressedDown ==0){
            game->isKeyPressedDown = 1;
            efetuaEventoClique(game,settings,event);
        }
    }
    else if(event.type == SDL_MOUSEBUTTONUP){
        if(event.button.button == SDL_BUTTON_LEFT){
            game->isKeyPressedDown = 0;
            efetuaEventoSoltar(game,settings,event);
            if(game->jogada == Invalid) ;
        }
    }
}


void handleJogadaThemes(CChessSettings * settings,SDL_Event event){

}


void handleWinScreen(GameStruct * game ,CChessSettings * settings,SDL_Event event){

}
