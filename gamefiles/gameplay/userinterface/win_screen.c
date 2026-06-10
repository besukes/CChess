#include "library/main.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <stdio.h>



void desenhaStats(GameStruct * game ,CChessSettings * settings,SDL_Event event){

}


void desenhaEndGameUI(GameStruct * game ,CChessSettings * settings,SDL_Event event){
    SDL_Rect fundo = {100,100,800,800};
    SDL_RenderCopy(settings->gameRenderer,settings->textures.miscTextures[2],NULL,&fundo);
}


void desenhaWinScreen(GameStruct * game ,CChessSettings * settings,SDL_Event event){
    desenhaInterfaceJogo(game,settings,event);
    desenhaEndGameUI(game,settings,event);
    desenhaStats(game,settings,event);
}