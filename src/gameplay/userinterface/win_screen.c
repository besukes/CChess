#include "library/main.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <stdio.h>




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
    int indx = ((settings->ticks - temp_inicial) / 32 ) % 60;
    SDL_RenderCopy(settings->gameRenderer, settings->cosmeticos.gif_checkmate[indx], NULL, NULL);
}


void desenhaWinScreen(GameStruct * game ,CChessSettings * settings,SDL_Event event){
    int temp_inicial = settings->ticks_checkmate, tempo_animacao = temp_inicial + 1800;
    while(settings->ticks < tempo_animacao){
        SDL_RenderClear(settings->gameRenderer);
        desenhaInterfaceJogo(game,settings,event);
        desenhaAnimacaoCheckmate(temp_inicial,settings);
        SDL_RenderPresent(settings->gameRenderer);
        SDL_PollEvent(&event);
        settings->ticks = SDL_GetTicks();
    }
    desenhaInterfaceJogo(game,settings,event);
    desenhaEndGameUI(settings);
    desenhaStats(game,settings,event);
}