#include "library/main.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <stdio.h>


CChessSettings initCChessSettings(SDL_Renderer * sdl_renderer){
    CChessSettings settings;
    settings.fonteJogo = NULL; //temos de mudar
    settings.gameRenderer = sdl_renderer;
    settings.screenAtual = Menu;
    settings.posMouseX = 0;
    settings.posMouseY = 0;
    settings.textures.temaSelecionado = CChess;
    settings.nivelDificuldade = Floresta;
    settings.ticks = 0;
    settings.ticks_checkmate = 0;
    initTexturasJogo(&settings.textures,sdl_renderer);
    return settings;
}

EstadoJogo initEstadoJogo(void){
    EstadoJogo es;
    es.checkMate = 0;
    es.king_in_check[brancas] = 0;
    es.king_in_check[pretas] = 0;
    es.enpassant = 0;
    es.stalemate = 0;
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
    return game;
}
