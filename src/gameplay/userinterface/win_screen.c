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


void desenhaAnimacaoCheckmate(int temp_inicial, CChessSettings * settings , Boolean default_animation){
    int frames = settings->client_settings.cosmeticos.n_frames_gif , offset = 32;
    if(default_animation) offset = 36;
    int indx = ((settings->ticks - temp_inicial) / offset ) % frames;
    SDL_Texture * gif_frame = settings->client_settings.cosmeticos.gif_checkmate[indx];
    SDL_SetTextureBlendMode(gif_frame,SDL_BLENDMODE_BLEND);
    SDL_RenderCopy(settings->gameRenderer, settings->client_settings.cosmeticos.gif_checkmate[indx], NULL, NULL);
}


void desenhaWinScreen(GameStruct * game ,CChessSettings * settings,SDL_Event event){
    SDL_Renderer * r = settings->gameRenderer;
    Boolean default_animation = settings->client_settings.cosmeticos.efeito_checkmateSelecionado == 2;
    int offset_timer = (default_animation) ? 1200 : 1800;
    int temp_inicial = settings->ticks_checkmate, tempo_animacao = temp_inicial + offset_timer;
    while(settings->ticks < tempo_animacao){
        SDL_RenderClear(r);
        desenhaInterfaceJogo(game,settings);
        desenhaAnimacaoCheckmate(temp_inicial,settings,default_animation);
        SDL_RenderPresent(r);
        SDL_PollEvent(&event);
        settings->ticks = (int)SDL_GetTicks();
    }
    desenhaInterfaceJogo(game,settings);
    desenhaEndGameUI(settings);
    desenhaStats(game,settings,event);
}