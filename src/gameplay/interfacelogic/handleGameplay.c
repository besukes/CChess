#include "library/main.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>



void handleJogadaMenuPrincipal(CChessSettings * settings,SDL_Event * event){
    int mouseX = event->button.x , mouseY = event->button.y;
    SDL_Point point = {mouseX,mouseY};
    SDL_Rect botaoOffline = {710,640,500,100};
    if (event->type == SDL_MOUSEBUTTONDOWN && event->button.button == SDL_BUTTON_LEFT){
        if(SDL_PointInRect(&point,&botaoOffline))  settings->screenAtual = Chess;
        else if(dentroDoBotao(mouseX,mouseY,1750,1850,1000,1050)) event->type = SDL_QUIT;
    }
}



void handleJogadaChess(GameStruct* game , CChessSettings * settings,SDL_Event event){
    if(event.type == SDL_MOUSEBUTTONDOWN){
        if(event.button.button == SDL_BUTTON_LEFT && game->isKeyPressedDown ==0){
            game->isKeyPressedDown = 1;
            efetuaEventoClique(game,settings,&event);
            game->jogada = Valid;
        }
    }
    else if(event.type == SDL_MOUSEBUTTONUP){
        if(event.button.button == SDL_BUTTON_LEFT){
            game->isKeyPressedDown = 0;
            efetuaEventoSoltar(game,settings,event);
            if(game->jogada != Invalid && !game->pawnPromoted) game->turnoJogador = (game->turnoJogador == brancas) ? pretas : brancas;
        }
    }
}


void handleStoryScreen(GameStruct * game , CChessSettings * settings,SDL_Event * event){
    int mouseX = event->button.x , mouseY = event->button.y;
    SDL_Point point = {mouseX,mouseY};
    SDL_Rect lvl1 = {710,640,500,100};
    if(1){
        settings->nivelDificuldade++;
    }
    else if(1){
        initStoryGame(game,settings,1);
    }
    else if(2){
        initStoryGame(game,settings,2);
    }
}



void handleJogadaStory(GameStruct* game , CChessSettings * settings,SDL_Event event){
    Boolean valido_turno = game->turnoJogador == brancas;
    if(event.type == SDL_MOUSEBUTTONDOWN){
        if(event.button.button == SDL_BUTTON_LEFT && game->isKeyPressedDown == 0){
            game->isKeyPressedDown = 1;
            efetuaEventoClickStory(game,settings,&event,valido_turno);
            game->jogada = Valid;
        }
    }
    else if(event.type == SDL_MOUSEBUTTONUP && valido_turno){
        if(event.button.button == SDL_BUTTON_LEFT){
            game->isKeyPressedDown = 0;
            efetuaEventoSoltar(game,settings,event);
            if(game->jogada != Invalid && !game->pawnPromoted) game->turnoJogador = (game->turnoJogador == brancas) ? pretas : brancas;
        }
    }
}



void handleJogadaThemes(CChessSettings * settings,SDL_Event event){

}


void handleWinScreen(GameStruct * game ,CChessSettings * settings,SDL_Event event){

}
