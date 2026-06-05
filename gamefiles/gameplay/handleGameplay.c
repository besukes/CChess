#include "library/main.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>


void handleJogadaMenuPrincipal(CChessSettings * settings,SDL_Event event){
   SDL_Point point = {settings->posMouseX,settings->posMouseY};
   SDL_Rect botaoJogar = {700,400,500,100};
   if(SDL_PointInRect(&point,&botaoJogar))
   {
     if (event.type == SDL_MOUSEBUTTONDOWN && event.button.button == SDL_BUTTON_LEFT)
     {
        settings->screenAtual = Chess;
     }
   }
}

void resetGrabbedPiece(GameStruct * game){
    
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
            resetGrabbedPiece(game);
        }
    }
}


void handleJogadaThemes(CChessSettings * settings,SDL_Event event){

}


void handleWinScreen(GameStruct * game ,CChessSettings * settings,SDL_Event event){

}
