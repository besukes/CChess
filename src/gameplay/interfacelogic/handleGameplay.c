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
        else if(SDL_PointInRect(&point,&botaoSettings)) {
            settings->screenAtual = Settings;
            settings->cosmeticos.ultimo_efeito_checkmateSelecionado = settings->cosmeticos.efeito_checkmateSelecionado;
        }
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


void load_new_animations(CChessSettings * settings){
    settings->num_imgsLoaded = 24;
    settings->num_imgsTotais = 60;
    if(settings->cosmeticos.efeito_checkmateSelecionado == 2)settings->num_imgsLoaded = 40;
    for(int i = 0; i < settings->cosmeticos.n_frames_gif; i++){
        SDL_DestroyTexture(settings->cosmeticos.gif_checkmate[i]);
    }
    free(settings->cosmeticos.gif_checkmate);
    settings->cosmeticos.gif_checkmate = gif_utilizador_checkmate(settings,settings->cosmeticos.efeito_checkmateSelecionado);
}



void handleSettingsScreen(GameStruct * game , CChessSettings * settings,SDL_Event * event){
    int mouseX = event->button.x , mouseY = event->button.y;
    SDL_Point point = {mouseX,mouseY};
    SDL_Rect voltar = {1750,890,150,150};
    SDL_Rect ant_board = {450,246,40,40} , prox_board = {660,246,40,40};
    SDL_Rect ant_res = {1370,246,40,40} , prox_res = {1580,246,40,40};
    SDL_Rect ant_checkmate = {1370,420,40,40} , prox_checkmate = {1580,420,40,40};
    SDL_Rect ant_check = {1370,504,40,40} , prox_check = {1580,504,40,40};
    SDL_Rect ant_track = {1370,678,40,40} , prox_track = {1580,678,40,40};
    SDL_Rect ant_volume = {1370,762,40,40} , prox_volume = {1580,762,40,40};
    if (event->type == SDL_MOUSEBUTTONDOWN && event->button.button == SDL_BUTTON_LEFT){
        if(SDL_PointInRect(&point,&voltar)){
            int last = settings->cosmeticos.ultimo_efeito_checkmateSelecionado ,
                new = settings->cosmeticos.efeito_checkmateSelecionado;
            if(new != last) load_new_animations(settings);
            settings->screenAtual = Menu;
        }
        else if(SDL_PointInRect(&point,&ant_board)){
            if(settings->cosmeticos.tabuleiroSelecionado <= 0) settings->cosmeticos.tabuleiroSelecionado = 6;
            else settings->cosmeticos.tabuleiroSelecionado--;
        }
        else if(SDL_PointInRect(&point,&prox_board)){
            if(settings->cosmeticos.tabuleiroSelecionado >= 6) settings->cosmeticos.tabuleiroSelecionado = 0;
            else settings->cosmeticos.tabuleiroSelecionado++;
        }
        else if(SDL_PointInRect(&point,&ant_res)){
            if(settings->window_optn <= 0) settings->window_optn = 3;
            else settings->window_optn--;
            set_new_window_size(settings->window_optn,settings);
        }
        else if(SDL_PointInRect(&point,&prox_res)){
            if(settings->window_optn >= 3) settings->window_optn = 0;
            else settings->window_optn++;
            set_new_window_size(settings->window_optn,settings);
        }
        else if(SDL_PointInRect(&point,&ant_checkmate)){
            if(settings->cosmeticos.efeito_checkmateSelecionado <= 0) settings->cosmeticos.efeito_checkmateSelecionado = 7;
            else settings->cosmeticos.efeito_checkmateSelecionado--;
        }
        else if(SDL_PointInRect(&point,&prox_checkmate)){
            if(settings->cosmeticos.efeito_checkmateSelecionado >= 7) settings->cosmeticos.efeito_checkmateSelecionado = 0;
            else settings->cosmeticos.efeito_checkmateSelecionado++;
        }
        else if(SDL_PointInRect(&point,&ant_check)){
            if(settings->cosmeticos.efeito_checkSelecionado <= 0) settings->cosmeticos.efeito_checkSelecionado = 6;
            else settings->cosmeticos.efeito_checkSelecionado--;
        }
        else if(SDL_PointInRect(&point,&prox_check)){
            if(settings->cosmeticos.efeito_checkSelecionado >= 6) settings->cosmeticos.efeito_checkSelecionado = 0;
            else settings->cosmeticos.efeito_checkSelecionado++;
        }
        else if(SDL_PointInRect(&point,&ant_track)){
            if(settings->cosmeticos.musicaSelecionada <= 0) settings->cosmeticos.musicaSelecionada = 6;
            else settings->cosmeticos.musicaSelecionada--;
        }
        else if(SDL_PointInRect(&point,&prox_track)){
            if(settings->cosmeticos.musicaSelecionada >= 6) settings->cosmeticos.musicaSelecionada = 0;
            else settings->cosmeticos.musicaSelecionada++;
        }
        else if(SDL_PointInRect(&point,&ant_volume)){
            if(settings->volume <= 0) settings->volume= 100;
            else settings->volume-=10;
        }
        else if(SDL_PointInRect(&point,&prox_volume)){
            if(settings->volume >= 100) settings->volume = 0;
            else settings->volume+=10;
        }
    }
}