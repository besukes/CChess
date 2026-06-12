#include "library/main.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <stdio.h>
#include "pl_mpeg.h"

#define PL_MPEG_IMPLEMENTATION




void desenhaStats(GameStruct * game ,CChessSettings * settings,SDL_Event event){

}


void desenhaEndGameUI(CChessSettings * settings){
    SDL_SetRenderDrawBlendMode(settings->gameRenderer, SDL_BLENDMODE_BLEND);
    SDL_SetRenderDrawColor(settings->gameRenderer, 255, 255, 255, 246); 
    SDL_Rect quadrado;
    quadrado.x = 560; 
    quadrado.y = 140; 
    quadrado.w = 800;  
    quadrado.h = 800;
    SDL_RenderFillRect(settings->gameRenderer, &quadrado);
}


void desenhaAnimacaoCheckmate(int temp_inicial, CChessSettings * settings){
    double tempo_decorrido = (double)(settings->ticks - temp_inicial) / 2000.0;
    plm_decode(settings->videoPlayer->plm, tempo_decorrido);
}

void desenhaWinScreen(GameStruct * game ,CChessSettings * settings,SDL_Event event){
    int temp_inicial = settings->ticks_checkmate, tempo_animacao = temp_inicial + 2000;
    desenhaInterfaceJogo(game,settings,event);
    if(settings->ticks < tempo_animacao){
        desenhaAnimacaoCheckmate(temp_inicial,settings);
    }
    else{
        if(settings->videoPlayer->plm != NULL){
            plm_destroy(settings->videoPlayer->plm);
            SDL_DestroyTexture(settings->videoPlayer->texture);
            free(settings->videoPlayer);
            settings->videoPlayer = NULL;
        }
        desenhaEndGameUI(settings);
        desenhaStats(game,settings,event);  
    }
}