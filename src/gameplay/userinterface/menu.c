#include "library/main.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL2_gfxPrimitives.h>
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

void verificaNumberCoins(int coins_qntd , char * coins){
    if(coins_qntd == 10000) sprintf(coins,"%s","10K");
    else if(coins_qntd > 10000) sprintf(coins,"%s","10K+");
    else sprintf(coins,"%d",coins_qntd);
}


void desenhaCoins(CChessSettings * settings){
    SDL_Rect coins_shower = {1500,42,240,80};
    SDL_RenderCopy(settings->gameRenderer,settings->textures.miscTextures[4],NULL,&coins_shower);

    
    char coins[6];
    verificaNumberCoins(settings->ccoins_qntd,coins);
    renderTextoCentradoSombra(settings->gameRenderer,settings->fonteJogo,coins,(SDL_Color){255, 255, 255, 255},1613,48,2);
}



void desenhaMisc(CChessSettings * settings,SDL_Event event){
    SDL_Rect fundo = {0,0,1920,1080};
    SDL_Rect shop = {1780,30,100,100};
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
    roundedBoxRGBA(settings->gameRenderer, 660 , 370 , 1260 , 1040 , 40 , 0, 0, 0, 150);
    desenhaButtons(settings,event);
    desenhaCoins(settings);
}