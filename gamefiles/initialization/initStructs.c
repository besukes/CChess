#include "library/main.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <stdio.h>


void pathAnimacaoCheckmate(char * str , int efeito_checkmateSelecionado){
    switch(efeito_checkmateSelecionado){
        case 0:
            sprintf(str,"animations/checkmate/anime.gif");
        break;
        case 1:
            sprintf(str,"animations/checkmate/beast.gif");
        break;
        case 2:
            sprintf(str,"animations/checkmate/default.gif");
        break;
        case 3:
            sprintf(str,"animations/checkmate/flames.gif");
        break;
        case 4 :
            sprintf(str,"animations/checkmate/new_years.gif");
        break;
        case 5 :
            sprintf(str,"animations/checkmate/purple_explosion.gif");
        break;
        case 6 :
            sprintf(str,"animations/checkmate/refraction.gif");
        break;
        default :
            sprintf(str,"animations/checkmate/space.gif");
    }
}


SDL_Texture ** gif_utilizador_checkmate(CChessSettings * settings, int efeito_checkmateSelecionado){
    char str[256];
    pathAnimacaoCheckmate(str,efeito_checkmateSelecionado);
    IMG_Animation* gif = IMG_LoadAnimation(str);
    SDL_Texture * * textures = malloc(sizeof(SDL_Texture*) * gif->count);
    for(int i = 0; i < gif->count; i++) {
        textures[i] = SDL_CreateTextureFromSurface(settings->gameRenderer, gif->frames[i]);
    }
    IMG_FreeAnimation(gif);
    return textures;
}


//No futuro sera suposto ler o ficheiro de jogo do utilizador
void initCosmeticos(CChessSettings * settings){
    settings->cosmeticos.efeito_checkSelecionado = 0;
    settings->cosmeticos.efeito_checkmateSelecionado = 6;
    settings->cosmeticos.musicaSelecionada = 0;
    settings->cosmeticos.tabuleiroSelecionado = 0;
    settings->cosmeticos.gif_checkmate = gif_utilizador_checkmate(settings, settings->cosmeticos.efeito_checkmateSelecionado);
}

CChessSettings initCChessSettings(SDL_Renderer * sdl_renderer){
    CChessSettings settings;
    settings.fonteJogo = NULL; //temos de mudar
    settings.gameRenderer = sdl_renderer;
    settings.screenAtual = Menu;
    settings.posMouseX = 0;
    settings.posMouseY = 0;
    settings.textures.temaSelecionado = CChess;
    settings.nivelDificuldade = Floresta;
    settings.nivelSelecionado = 0;
    settings.ticks = 0;
    settings.ticks_checkmate = 0;
    initTexturasJogo(&settings.textures,sdl_renderer);
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
