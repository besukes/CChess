#include "library/main.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <stdio.h>





//No futuro sera suposto ler o ficheiro de jogo do utilizador
void initCosmeticos(CChessSettings * settings){
    /*settings->cosmeticos.efeito_checkSelecionado = 0;
    settings->cosmeticos.efeito_checkmateSelecionado = 3;
    settings->cosmeticos.musicaSelecionada = 0;
    settings->cosmeticos.tabuleiroSelecionado = 0;*/
    settings->cosmeticos.gif_checkmate = gif_utilizador_checkmate(settings, settings->cosmeticos.efeito_checkmateSelecionado);
}


CChessSettings initCChessSettings(SDL_Renderer * sdl_renderer){
    CChessSettings settings;
    settings.fonteJogo = NULL; //temos de mudar
    settings.gameRenderer = sdl_renderer;
    settings.screenAtual = Menu;
    settings.posMouseX = 0;
    settings.posMouseY = 0;
    /*settings.textures.temaSelecionado = CChess;
    settings.nivelDificuldade = Floresta;
    settings.nivelSelecionado = 0;*/
    settings.ticks = 0;
    settings.ticks_checkmate = 0;
    settings.num_imgsTotais = 100;
    settings.num_imgsLoaded = 0;
    initTexturasJogo(&settings,&settings.textures,sdl_renderer);
    initGameFiles(&settings);
    initCosmeticos(&settings);
    return settings;
}

EstadoJogo initEstadoJogo(void){
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
    initTabuleiro(&(es.tabuleirojogo[1][0]),5);
    init_other_bitboards(&es);
    return es;
}

GameStruct initGameStruct(SDL_Renderer * sdl_renderer){
    GameStruct game;
    game.estadoJogo = initEstadoJogo();
    game.isKeyPressedDown = 0;
    game.jogada = Valid;
    game.pieceSelecionada = Empty;
    game.turnoJogador = brancas;
    game.pieceCoords = 0;
    game.lastmoves = NULL;
    game.pawnPromoted = 0;
    game.active_ultimate = NULL;
    game.promotedSucessfully = 0;
    return game;
}
