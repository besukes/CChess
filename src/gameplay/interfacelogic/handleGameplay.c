#include "library/main.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>



void handleJogadaMenuPrincipal(CChessSettings * settings,SDL_Event * event){
    int mouseX = event->button.x , mouseY = event->button.y;
    SDL_Point point = {mouseX,mouseY};
    SDL_Rect botaoOffline = {710,640,500,100},
             botaoStory = {710,400,500,100},
             botaoMultiplayer = {710,520,500,100},
             botaoSettings = {710,760,500,100};
    if (event->type == SDL_MOUSEBUTTONDOWN && event->button.button == SDL_BUTTON_LEFT){
        if(SDL_PointInRect(&point,&botaoOffline))  settings->screenAtual = Chess;
        else if(SDL_PointInRect(&point,&botaoStory)) settings->screenAtual = Story;
        else if(SDL_PointInRect(&point,&botaoMultiplayer)) settings->screenAtual = Multiplayer;
        else if(SDL_PointInRect(&point,&botaoSettings)) settings->screenAtual = Settings;
        else if(dentroDoBotao(mouseX,mouseY,1750,1850,1000,1050)) event->type = SDL_QUIT;
    }
}

void softReset(GameStruct * game){
    game->pieceCoords = 0;
    game->pieceSelecionada = Empty;
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
            if(game->jogada != Invalid && !game->pawnPromoted){
                game->turnoJogador = (game->turnoJogador == brancas) ? pretas : brancas;
                if(game->turnoJogador == brancas) game->turns++;
            }
            softReset(game);
        }
    }
}


void handleStoryScreen(GameStruct * game , CChessSettings * settings,SDL_Event * event){
    int mouseX = event->button.x , mouseY = event->button.y;
    SDL_Point point = {mouseX,mouseY};
    SDL_Rect lvl1 = {710,640,500,100};
    SDL_Rect leave = {100,950,100,100};
    if (event->type == SDL_MOUSEBUTTONDOWN && event->button.button == SDL_BUTTON_LEFT){
        if(0){
            settings->nivelDificuldade++;
        }
        else if(0){
            initStoryGame(game,settings,1);
        }
        else if(0){
            initStoryGame(game,settings,2);
        }
        else if(SDL_PointInRect(&point,&leave)){ 
            settings->screenAtual = Menu;
            game->game_needs_initialization = 1;
        }
        printf("Mouse x: %d , Mouse y: %d\n",event->button.x,event->button.y);
    }
}



void handleJogadaStory(GameStruct* game , CChessSettings * settings,SDL_Event event){
    Boolean valido_turno = game->turnoJogador == brancas;
    if(!valido_turno){
        
    }
    else if(event.type == SDL_MOUSEBUTTONDOWN){
        if(event.button.button == SDL_BUTTON_LEFT && game->isKeyPressedDown == 0 ){
            game->isKeyPressedDown = 1;
            efetuaEventoClickStory(game,settings,&event,valido_turno);
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



void handleJogadaThemes(CChessSettings * settings,SDL_Event event){

}


void handleWinScreen(GameStruct * game ,CChessSettings * settings,SDL_Event event){

}


void handleSettingsScreen(GameStruct * game , CChessSettings * settings,SDL_Event * event){
    int mouseX = event->button.x , mouseY = event->button.y;
    SDL_Point point = {mouseX,mouseY};
    SDL_Rect voltar = {1750,890,150,150};
    if (event->type == SDL_MOUSEBUTTONDOWN && event->button.button == SDL_BUTTON_LEFT){
        if(SDL_PointInRect(&point,&voltar))  settings->screenAtual = Menu;
    }
}