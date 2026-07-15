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
            settings->client_settings.cosmeticos.ultimo_efeito_checkmateSelecionado = settings->client_settings.cosmeticos.efeito_checkmateSelecionado;
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
            cleanArrowEvent(game);
            efetuaEventoClique(game,settings,&event);
            game->jogada = Valid;
        }
        else if(event.button.button = SDL_BUTTON_RIGHT && game->arrows.is_drawing_arrows == 0){
            efetuaEventoClickArrows(game,event);
        }
    }
    else if(event.type == SDL_MOUSEBUTTONUP){
        if(event.button.button == SDL_BUTTON_LEFT){
            game->isKeyPressedDown = 0;
            efetuaEventoSoltar(game,settings,event);
            if(game->jogada != Invalid && !game->promoted.pawnPromoted){
                game->turnoJogador = (game->turnoJogador == brancas) ? pretas : brancas;
                if(game->turnoJogador == brancas) game->turns++;
            }
            softReset(game);
        }
        else if(event.button.button = SDL_BUTTON_RIGHT && game->arrows.is_drawing_arrows){
           efetuaEventoSoltarArrows(game,event);
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
            cleanArrowEvent(game);
            efetuaEventoClickStory(game,settings,&event,valido_turno);
            game->jogada = Valid;
        }
    }
    else if(event.type == SDL_MOUSEBUTTONUP){
        if(event.button.button == SDL_BUTTON_LEFT){
            game->isKeyPressedDown = 0;
            efetuaEventoSoltar(game,settings,event);
            if(game->jogada != Invalid && !game->promoted.pawnPromoted) game->turnoJogador = (game->turnoJogador == brancas) ? pretas : brancas;
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
    if(settings->client_settings.cosmeticos.efeito_checkmateSelecionado == 2)settings->num_imgsLoaded = 40;
    for(int i = 0; i < settings->client_settings.cosmeticos.n_frames_gif; i++){
        SDL_DestroyTexture(settings->client_settings.cosmeticos.gif_checkmate[i]);
    }
    free(settings->client_settings.cosmeticos.gif_checkmate);
    settings->client_settings.cosmeticos.gif_checkmate = gif_utilizador_checkmate(settings,settings->client_settings.cosmeticos.efeito_checkmateSelecionado);
}



void handleSettingsScreen(GameStruct * game , CChessSettings * settings,SDL_Event * event){
    int mouseX = event->button.x , mouseY = event->button.y;
    SDL_Point point = {mouseX,mouseY};
    SDL_Rect voltar = {1750,890,150,150};
    SDL_Rect ant_board = {450,246,40,40} , prox_board = {660,246,40,40};
    SDL_Rect ant_themes = {450,420,40,40} , prox_themes = {660,420,40,40};
    SDL_Rect ant_checkmate = {450,594,40,40} , prox_checkmate = {660,594,40,40};
    SDL_Rect ant_check = {450,678,40,40} , prox_check = {660,678,40,40};
    SDL_Rect ant_res = {1370,246,40,40} , prox_res = {1580,246,40,40};
    SDL_Rect ant_track = {1370,678,40,40} , prox_track = {1580,678,40,40};
    SDL_Rect ant_volume = {1370,762,40,40} , prox_volume = {1580,762,40,40};
    if (event->type == SDL_MOUSEBUTTONDOWN && event->button.button == SDL_BUTTON_LEFT){
        if(SDL_PointInRect(&point,&voltar)){
            int last = settings->client_settings.cosmeticos.ultimo_efeito_checkmateSelecionado ,
                new = settings->client_settings.cosmeticos.efeito_checkmateSelecionado;
            if(new != last) load_new_animations(settings);
            settings->screenAtual = Menu;
        }
        else if(SDL_PointInRect(&point,&ant_board)){
            if(settings->client_settings.cosmeticos.tabuleiroSelecionado <= 0) settings->client_settings.cosmeticos.tabuleiroSelecionado = 6;
            else settings->client_settings.cosmeticos.tabuleiroSelecionado--;
        }
        else if(SDL_PointInRect(&point,&prox_board)){
            if(settings->client_settings.cosmeticos.tabuleiroSelecionado >= 6) settings->client_settings.cosmeticos.tabuleiroSelecionado = 0;
            else settings->client_settings.cosmeticos.tabuleiroSelecionado++;
        }
        else if(SDL_PointInRect(&point,&ant_themes)){
            if(settings->client_settings.cosmeticos.themes_piece <= 0) settings->client_settings.cosmeticos.themes_piece = 2;
            else settings->client_settings.cosmeticos.themes_piece--;
        }
        else if(SDL_PointInRect(&point,&prox_themes)){
            if(settings->client_settings.cosmeticos.themes_piece >= 6) settings->client_settings.cosmeticos.themes_piece = 0;
            else settings->client_settings.cosmeticos.themes_piece++;
        }
        else if(SDL_PointInRect(&point,&ant_res)){
            if(settings->client_settings.window_optn <= 0) settings->client_settings.window_optn = 3;
            else settings->client_settings.window_optn--;
            set_new_window_size(settings->client_settings.window_optn,settings);
        }
        else if(SDL_PointInRect(&point,&prox_res)){
            if(settings->client_settings.window_optn >= 3) settings->client_settings.window_optn = 0;
            else settings->client_settings.window_optn++;
            set_new_window_size(settings->client_settings.window_optn,settings);
        }
        else if(SDL_PointInRect(&point,&ant_checkmate)){
            if(settings->client_settings.cosmeticos.efeito_checkmateSelecionado <= 0) settings->client_settings.cosmeticos.efeito_checkmateSelecionado = 7;
            else settings->client_settings.cosmeticos.efeito_checkmateSelecionado--;
        }
        else if(SDL_PointInRect(&point,&prox_checkmate)){
            if(settings->client_settings.cosmeticos.efeito_checkmateSelecionado >= 7) settings->client_settings.cosmeticos.efeito_checkmateSelecionado = 0;
            else settings->client_settings.cosmeticos.efeito_checkmateSelecionado++;
        }
        else if(SDL_PointInRect(&point,&ant_check)){
            if(settings->client_settings.cosmeticos.efeito_checkSelecionado <= 0) settings->client_settings.cosmeticos.efeito_checkSelecionado = 6;
            else settings->client_settings.cosmeticos.efeito_checkSelecionado--;
        }
        else if(SDL_PointInRect(&point,&prox_check)){
            if(settings->client_settings.cosmeticos.efeito_checkSelecionado >= 6) settings->client_settings.cosmeticos.efeito_checkSelecionado = 0;
            else settings->client_settings.cosmeticos.efeito_checkSelecionado++;
        }
        else if(SDL_PointInRect(&point,&ant_track)){
            if(settings->client_settings.cosmeticos.musicaSelecionada <= 0) settings->client_settings.cosmeticos.musicaSelecionada = 6;
            else settings->client_settings.cosmeticos.musicaSelecionada--;
        }
        else if(SDL_PointInRect(&point,&prox_track)){
            if(settings->client_settings.cosmeticos.musicaSelecionada >= 6) settings->client_settings.cosmeticos.musicaSelecionada = 0;
            else settings->client_settings.cosmeticos.musicaSelecionada++;
        }
        else if(SDL_PointInRect(&point,&ant_volume)){
            if(settings->client_settings.volume_music <= 0) settings->client_settings.volume_music = 100;
            else settings->client_settings.volume_music-=10;
        }
        else if(SDL_PointInRect(&point,&prox_volume)){
            if(settings->client_settings.volume_music >= 100) settings->client_settings.volume_music = 0;
            else settings->client_settings.volume_music+=10;
        }
    }
}