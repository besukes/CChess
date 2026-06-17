#include "library/main.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <stdio.h>


void desenhaButtons(CChessSettings * settings,SDL_Event event){
    SDL_Rect botaoStory = {710,400,500,100};
    SDL_Rect botaoMultiplayer = {710,520,500,100};
    SDL_Rect botaoOffline = {710,640,500,100};
    SDL_Rect botaoSettings = {710,760,500,100};

    SDL_RenderCopy(settings->gameRenderer,settings->textures.buttonsTextures[4],NULL,&botaoStory);
    SDL_RenderCopy(settings->gameRenderer,settings->textures.buttonsTextures[1],NULL,&botaoMultiplayer);
    SDL_RenderCopy(settings->gameRenderer,settings->textures.buttonsTextures[2],NULL,&botaoOffline);
    SDL_RenderCopy(settings->gameRenderer,settings->textures.buttonsTextures[3],NULL,&botaoSettings);
}


void desenhaMisc(CChessSettings * settings,SDL_Event event){
    SDL_Rect fundo = {0,0,1920,1080};
    SDL_Rect shop = {1790,30,100,100};
    SDL_Rect cchess = {490,(-60),900,500};

    SDL_RenderCopy(settings->gameRenderer,settings->textures.miscTextures[0],NULL,&fundo);
    SDL_RenderCopy(settings->gameRenderer,settings->textures.miscTextures[2],NULL,&cchess);
    SDL_RenderCopy(settings->gameRenderer,settings->textures.miscTextures[1],NULL,&shop);
}


void desenhaInterfaceMenu(CChessSettings * settings,SDL_Event event){
    SDL_RenderClear(settings->gameRenderer);
    SDL_SetRenderDrawColor(settings->gameRenderer, 0, 0, 0, 180); 
    SDL_SetRenderDrawBlendMode(settings->gameRenderer, SDL_BLENDMODE_BLEND);

    desenhaMisc(settings,event);
    SDL_Rect menuOptions = {660,380,600,670};
    SDL_RenderFillRect(settings->gameRenderer, &menuOptions);
    desenhaButtons(settings,event);
}