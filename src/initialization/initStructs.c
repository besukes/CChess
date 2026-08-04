#include "library/main.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <stdio.h>




//No futuro sera suposto ler o ficheiro de jogo do utilizador
void initCosmeticos(CChessSettings * settings){
    settings->client_settings.cosmeticos.gif_checkmate = gif_utilizador_checkmate(settings, settings->client_settings.cosmeticos.efeito_checkmateSelecionado);
}


void zeroCustomPieces(CustomPieces * sets){
    sets->indx_ult_unlocked = 0;
    sets->ultimates_unlocked = NULL;

    sets->indx_ult_owned = 0;
    sets->ultimates_owned = NULL;

    sets->indx_ep_owned = 0;
    sets->extraPieces_owned = NULL;
}

void defaultClientSettings(CChessSettings * settings){
    settings->client_settings.story_st_line = NULL;
    settings->client_settings.indx_starting_line = 0;
    settings->client_settings.selected_pieces_power = NULL;
    settings->client_settings.indx_selected_ults = 0;
    settings->client_settings.volume_music = 100;
    settings->client_settings.volume_sfx = 100;
    settings->client_settings.window_res = 0;
    settings->client_settings.window_type = 0;
    settings->client_settings.cosmeticos.efeito_checkmateSelecionado = 0;
    settings->client_settings.cosmeticos.efeito_checkSelecionado = 0;
    settings->client_settings.cosmeticos.gif_checkmate = NULL;
    settings->client_settings.cosmeticos.musicaSelecionada = 0;
    settings->client_settings.cosmeticos.n_frames_gif = 0;
    settings->client_settings.cosmeticos.tabuleiroSelecionado = 0;
    settings->client_settings.cosmeticos.themes_piece = 0;
    settings->client_settings.cosmeticos.ultimo_efeito_checkmateSelecionado = 0;
    settings->client_settings.nivelSelecionado = 0;
    settings->client_settings.nivelDificuldade = 0;
    settings->client_settings.tutorials.tutorial_multiplayer_done = 0;
    settings->client_settings.tutorials.tutorial_offline_done = 0;
    settings->client_settings.tutorials.tutorial_story_done = 0;

    //Nao deviam ser client sided 
    settings->nivelMaxDesbloqueado = 0;
    settings->ccoins_qntd = 0;

}


CChessSettings initCChessSettings(SDL_Renderer * sdl_renderer , SDL_Window * window){
    CChessSettings settings;
    settings.gameRenderer = sdl_renderer;
    settings.window = window;
    settings.screenAtual = Menu;
    settings.posMouseX = 0;
    settings.posMouseY = 0;
    settings.ticks = 0;
    settings.ticks_checkmate = 0;
    settings.num_imgsTotais = 100;
    settings.num_imgsLoaded = 0;
    zeroCustomPieces(&settings.user_custom_items);
    initTexturasJogo(&settings,&settings.textures,sdl_renderer);
    defaultClientSettings(&settings);
    initGameFiles(&settings);
    initCosmeticos(&settings);
    TTF_Init();
    settings.fonteJogoTitles = TTF_OpenFont("assets/ttf/m6x11plus.ttf", 35);
    settings.fonteJogoSmallerTitles = TTF_OpenFont("assets/ttf/m6x11plus.ttf", 48);
    return settings;
}

EstadoJogo initEstadoJogoOffline(void){
    EstadoJogo es;
    es.checkMate = 0;
    es.king_in_check[brancas] = 0;
    es.king_in_check[pretas] = 0;
    es.enpassant = 0;
    es.stalemate = 0;
    es.tabuleiroExtraPieces = NULL;
    es.indx_extra_pieces = 0;
    for(int i=0;i<2;i++){
        es.canCastle[i][0] = 1;
        es.canCastle[i][1] = 1;
    }
    initTabuleiro(&(es.tabuleirojogo[0][0]),0);
    initTabuleiro(&(es.tabuleirojogo[1][0]),56);
    init_other_bitboards(&es);
    return es;
}


void initArrowsStruct(GameStruct * game){
    game->arrows.is_drawing_arrows = 0;
    game->arrows.indx_drawable_arrows=0;
    game->arrows.arrows_vector = NULL; 
}


GameStruct initGameStruct(void){
    GameStruct game;
    game.game_needs_initialization = 1;
    game.isKeyPressedDown = 0;
    game.jogada = Valid;
    game.pieceSelecionada = Empty;
    game.turnoJogador = brancas;
    game.pieceCoords = 0;
    game.indx_lastmoves = 0;
    game.promoted.pawnPromoted = 0;
    game.active_ultimate = NULL;
    game.promoted.promotedSucessfully = 0;
    game.selected_piece_attacks = 0;
    game.promoted.promoted_square = 0;
    game.score_game = 0;
    game.turns=0;
    game.trying_to_leave = 0;
    initArrowsStruct(&game);
    return game;
}



void initializeOfflineGame(GameStruct * game){
    game->estadoJogo = initEstadoJogoOffline();
    game->game_needs_initialization = 0;
    game->isKeyPressedDown = 0;
    game->jogada = Valid;
    game->pieceSelecionada = Empty;
    game->turnoJogador = brancas;
    game->pieceCoords = 0;
    game->indx_lastmoves = 0;
    game->promoted.pawnPromoted = 0;
    free(game->active_ultimate);
    game->active_ultimate = NULL;
    game->promoted.promotedSucessfully = 0;
    game->selected_piece_attacks = 0;
    game->promoted.promoted_square = 0;
    game->score_game = 0;
    game->turns=0;
    game->trying_to_leave = 0;
    initArrowsStruct(game);
}


void initializeStructs(int matrix[2][NUMBER_PIECES],int indx){
    for(int i=0;i<indx;i++){
        matrix[0][i] = 0;
        matrix[1][i] = 0;
    }
}