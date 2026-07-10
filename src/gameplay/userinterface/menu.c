#include "library/main.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL2_gfxPrimitives.h>
#include <stdio.h>

/*Hover — verifica se o rato está sobre o rect*/
int mouseOver(CChessSettings * settings, SDL_Rect r){
    SDL_Point mousePos = {settings->posMouseX, settings->posMouseY};
    return (SDL_PointInRect(&mousePos, &r));
}


/* ─────────────────────────────────────────────
   Botão com efeito hover dourado
   ───────────────────────────────────────────── */
static void desenhaButton(CChessSettings * settings, SDL_Texture * tex, SDL_Rect rect){
    SDL_Renderer * r = settings->gameRenderer;

    if(mouseOver(settings, rect)){
        /* Halo dourado ligeiro atrás do botão */
        for(int i = 8; i > 0; i -= 2){
            Uint8 a = (Uint8)(20 * i);
            roundedBoxRGBA(r,
                rect.x - i, rect.y - i,
                rect.x + rect.w + i, rect.y + rect.h + i,
                18, 210, 165, 40, a);
        }
        /* Botão ligeiramente maior (escala +4px em cada lado) */
        SDL_Rect hover = {rect.x - 4, rect.y - 4, rect.w + 8, rect.h + 8};
        SDL_RenderCopy(r, tex, NULL, &hover);
        /* Tint dourado semitransparente por cima */
        SDL_SetTextureColorMod(tex, 255, 220, 130);
        SDL_SetTextureAlphaMod(tex, 230);
        SDL_RenderCopy(r, tex, NULL, &hover);
        SDL_SetTextureColorMod(tex, 255, 255, 255);
        SDL_SetTextureAlphaMod(tex, 255);
    } else {
        SDL_RenderCopy(r, tex, NULL, &rect);
    }
}


void desenhaButtons(CChessSettings * settings,SDL_Event event){
    SDL_Rect botaoStory = {710,400,500,100};
    SDL_Rect botaoMultiplayer = {710,520,500,100};
    SDL_Rect botaoOffline = {710,640,500,100};
    SDL_Rect botaoSettings = {710,760,500,100};

    /*SDL_RenderCopy(settings->gameRenderer,settings->textures.buttonsTextures[4],NULL,&botaoStory);
    SDL_RenderCopy(settings->gameRenderer,settings->textures.buttonsTextures[1],NULL,&botaoMultiplayer);
    SDL_RenderCopy(settings->gameRenderer,settings->textures.buttonsTextures[2],NULL,&botaoOffline);
    SDL_RenderCopy(settings->gameRenderer,settings->textures.buttonsTextures[3],NULL,&botaoSettings);*/
    desenhaButton(settings, settings->textures.buttonsTextures[4], botaoStory);
    desenhaButton(settings, settings->textures.buttonsTextures[1], botaoMultiplayer);
    desenhaButton(settings, settings->textures.buttonsTextures[2], botaoOffline);
    desenhaButton(settings, settings->textures.buttonsTextures[3], botaoSettings);
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
    renderTextoCentradoSombra(settings->gameRenderer,settings->fonteJogoSmallerTitles,coins,(SDL_Color){255, 255, 255, 255},1613,48,1);
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