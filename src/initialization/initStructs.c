#include "library/main.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <stdio.h>




//No futuro sera suposto ler o ficheiro de jogo do utilizador
void initCosmeticos(CChessSettings * settings){
    settings->cosmeticos.gif_checkmate = gif_utilizador_checkmate(settings, settings->cosmeticos.efeito_checkmateSelecionado);
}


void zeroCustomPieces(CustomPieces * sets){
    sets->indx_ult_unlocked = 0;
    sets->ultimates_unlocked = NULL;

    sets->indx_ult_owned = 0;
    sets->ultimates_owned = NULL;

    sets->indx_ep_owned = 0;
    sets->extraPieces_owned = NULL;
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
    settings.story_st_line = NULL;
    settings.indx_starting_line = 0;
    settings.selected_pieces_power = NULL;
    settings.indx_selected_ults = 0;
    settings.volume = 100;
    zeroCustomPieces(&settings.user_custom_items);
    initTexturasJogo(&settings,&settings.textures,sdl_renderer);
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

GameStruct initGameStruct(SDL_Renderer * sdl_renderer){
    GameStruct game;
    game.game_needs_initialization = 1;
    game.isKeyPressedDown = 0;
    game.jogada = Valid;
    game.pieceSelecionada = Empty;
    game.turnoJogador = brancas;
    game.pieceCoords = 0;
    game.lastmoves = NULL;
    game.pawnPromoted = 0;
    game.active_ultimate = NULL;
    game.promotedSucessfully = 0;
    game.selected_piece_attacks = 0;
    game.promoted_square = 0;
    game.score_game = 0;
    game.turns=0;
    game.trying_to_leave = 0;
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
    freeLinkedList(game->lastmoves);
    game->lastmoves = NULL;
    game->pawnPromoted = 0;
    free(game->active_ultimate);
    game->active_ultimate = NULL;
    game->promotedSucessfully = 0;
    game->selected_piece_attacks = 0;
    game->promoted_square = 0;
    game->score_game = 0;
    game->turns=0;
    game->trying_to_leave = 0;
}