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
    initTexturasJogo(&settings.textures,sdl_renderer);
    return settings;
}

EstadoJogo initEstadoJogo(void){
    EstadoJogo es;
    es.checkMate = 0;
    es.checkBrancas = 0;
    es.checkPretas = 0;
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
    return game;
}
