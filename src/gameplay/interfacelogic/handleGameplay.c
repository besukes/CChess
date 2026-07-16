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


void handleBoardChange(CChessSettings * settings,Boolean ant){
    if(ant){
        if(settings->client_settings.cosmeticos.tabuleiroSelecionado <= 0) settings->client_settings.cosmeticos.tabuleiroSelecionado = 6;
        else settings->client_settings.cosmeticos.tabuleiroSelecionado--;
    }
    else{
        if(settings->client_settings.cosmeticos.tabuleiroSelecionado >= 6) settings->client_settings.cosmeticos.tabuleiroSelecionado = 0;
        else settings->client_settings.cosmeticos.tabuleiroSelecionado++;
    }
}

void handleThemesChange(CChessSettings * settings , Boolean ant){
    if(ant){
        if(settings->client_settings.cosmeticos.themes_piece <= 0) settings->client_settings.cosmeticos.themes_piece = 2;
        else settings->client_settings.cosmeticos.themes_piece--;
    }
    else{
        if(settings->client_settings.cosmeticos.themes_piece >= 6) settings->client_settings.cosmeticos.themes_piece = 0;
        else settings->client_settings.cosmeticos.themes_piece++;
    }
}

void handleEffectChanges(CChessSettings * settings , Boolean ant_checkmate , Boolean prox_checkmate , Boolean ant_check){
    if(ant_checkmate){
        if(settings->client_settings.cosmeticos.efeito_checkmateSelecionado <= 0) settings->client_settings.cosmeticos.efeito_checkmateSelecionado = 7;
        else settings->client_settings.cosmeticos.efeito_checkmateSelecionado--;
    }
    else if(prox_checkmate){
        if(settings->client_settings.cosmeticos.efeito_checkmateSelecionado >= 7) settings->client_settings.cosmeticos.efeito_checkmateSelecionado = 0;
        else settings->client_settings.cosmeticos.efeito_checkmateSelecionado++;
    }
    else if(ant_check){
        if(settings->client_settings.cosmeticos.efeito_checkSelecionado <= 0) settings->client_settings.cosmeticos.efeito_checkSelecionado = 6;
        else settings->client_settings.cosmeticos.efeito_checkSelecionado--;
    }
    else{
        if(settings->client_settings.cosmeticos.efeito_checkSelecionado >= 6) settings->client_settings.cosmeticos.efeito_checkSelecionado = 0;
        else settings->client_settings.cosmeticos.efeito_checkSelecionado++;
    }
}


void handleVolumeChange(CChessSettings * settings , Boolean ant_vol , Boolean prox_vol , Boolean ant_track , Boolean prox_track , Boolean ant_sfx){
    if(ant_vol){
        if(settings->client_settings.volume_music <= 0) settings->client_settings.volume_music = 100;
        else settings->client_settings.volume_music-=10;
    }
    else if(prox_vol){
        if(settings->client_settings.volume_music >= 100) settings->client_settings.volume_music = 0;
        else settings->client_settings.volume_music+=10;
    }
    else if(ant_track){
        if(settings->client_settings.cosmeticos.musicaSelecionada <= 0) settings->client_settings.cosmeticos.musicaSelecionada = 6;
        else settings->client_settings.cosmeticos.musicaSelecionada--;
    }
    else if(prox_track){
        if(settings->client_settings.cosmeticos.musicaSelecionada >= 6) settings->client_settings.cosmeticos.musicaSelecionada = 0;
        else settings->client_settings.cosmeticos.musicaSelecionada++;
    }
    else if(ant_track){
        if(settings->client_settings.volume_sfx <= 0) settings->client_settings.volume_sfx = 100;
        else settings->client_settings.volume_sfx-=10;
    }
    else{
        if(settings->client_settings.volume_sfx >= 100) settings->client_settings.volume_sfx = 0;
        else settings->client_settings.volume_sfx+=10;
    }
}


void handleWindowChange(CChessSettings * settings , Boolean ant_w_type , Boolean prox_w_type , Boolean ant_w_res){
    if(ant_w_type){
        if(settings->client_settings.window_type <= 0) settings->client_settings.window_type = 2;
        else settings->client_settings.window_type--;
        set_new_window_size(settings->client_settings.window_type,settings,1);
    }
    else if(prox_w_type){
        if(settings->client_settings.window_type >= 2) settings->client_settings.window_type = 0;
        else settings->client_settings.window_type++;
        set_new_window_size(settings->client_settings.window_type,settings,1);
    }
    else if(ant_w_res && !is_window_fullscreen(settings->window)){
        if(settings->client_settings.window_res <= 0) settings->client_settings.window_res = 2;
        else settings->client_settings.window_res--;
        set_new_window_size(settings->client_settings.window_res,settings,0);
    }
    else if(!is_window_fullscreen(settings->window)){
        if(settings->client_settings.window_res >= 2) settings->client_settings.window_res = 0;
        else settings->client_settings.window_res++;
        set_new_window_size(settings->client_settings.window_res,settings,0);
    }
}


void handleSettingsScreen(GameStruct * game , CChessSettings * settings,SDL_Event * event){
    int mouseX = event->button.x , mouseY = event->button.y;
    SDL_Point point = {mouseX,mouseY};
    SDL_Rect voltar = {1750,890,150,150};
    SDL_Rect ant_board = {450,246,40,40} , prox_board = {660,246,40,40};
    SDL_Rect ant_themes = {450,420,40,40} , prox_themes = {660,420,40,40};
    SDL_Rect ant_checkmate = {450,594,40,40} , prox_checkmate = {660,594,40,40} , 
             ant_check = {450,678,40,40} , prox_check = {660,678,40,40};
    SDL_Rect ant_window_type = {1370,246,40,40} , prox_window_type = {1580,246,40,40} , 
             ant_window_res = {1370,330,40,40} , prox_window_res = {1580,330,40,40};
    SDL_Rect ant_track = {1370,504,40,40} , prox_track = {1580,504,40,40} ,
             ant_volume = {1370,588,40,40} , prox_volume = {1580,588,40,40},
             ant_sfx = {1370,672,40,40} , prox_sfx = {1580,672,40,40};
    Boolean b_ant_board = SDL_PointInRect(&point,&ant_board) , b_prox_board = SDL_PointInRect(&point,&prox_board) ,
            b_ant_themes = SDL_PointInRect(&point,&ant_themes) , b_prox_themes = SDL_PointInRect(&point,&prox_themes) ,
            b_ant_window_type = SDL_PointInRect(&point,&ant_window_type) , b_prox_window_type = SDL_PointInRect(&point,&prox_window_type) ,
            b_ant_window_res = SDL_PointInRect(&point,&ant_window_res) , b_prox_window_res = SDL_PointInRect(&point,&prox_window_res) ,
            b_ant_checkmate = SDL_PointInRect(&point,&ant_checkmate) , b_prox_checkmate = SDL_PointInRect(&point,&prox_checkmate) ,
            b_ant_check = SDL_PointInRect(&point,&ant_check) , b_prox_check = SDL_PointInRect(&point,&prox_check) ,
            b_ant_track = SDL_PointInRect(&point,&ant_track) , b_prox_track = SDL_PointInRect(&point,&prox_track) , 
            b_ant_volume = SDL_PointInRect(&point,&ant_volume) , b_prox_volume = SDL_PointInRect(&point,&prox_volume),
            b_ant_sfx = SDL_PointInRect(&point,&ant_sfx) , b_prox_sfx = SDL_PointInRect(&point,&prox_sfx);
    Boolean board_event = b_ant_board || b_prox_board , 
            themes_event = b_ant_themes || b_prox_themes , 
            window_event = b_ant_window_type || b_prox_window_type || b_ant_window_res || b_prox_window_res , 
            effects_event = b_ant_check || b_prox_check || b_ant_checkmate || b_prox_checkmate , 
            volume_event = b_ant_track || b_prox_track || b_ant_volume || b_prox_volume || b_ant_sfx || b_prox_sfx;
    if (event->type == SDL_MOUSEBUTTONDOWN && event->button.button == SDL_BUTTON_LEFT){
        if(SDL_PointInRect(&point,&voltar)){
            int last = settings->client_settings.cosmeticos.ultimo_efeito_checkmateSelecionado ,
                new = settings->client_settings.cosmeticos.efeito_checkmateSelecionado;
            if(new != last) load_new_animations(settings);
            settings->screenAtual = Menu;
        }
        else if(board_event) handleBoardChange(settings,b_ant_board);
        else if(themes_event) handleThemesChange(settings,b_ant_themes);
        else if(effects_event) handleEffectChanges(settings,b_ant_checkmate,b_prox_checkmate,b_ant_check);
        else if(volume_event) handleVolumeChange(settings,b_ant_volume,b_prox_volume,b_ant_track,b_prox_track , b_ant_sfx);
        else if(window_event) handleWindowChange(settings , b_ant_window_type , b_prox_window_type , b_ant_window_res);
    }
}