#include "library/main.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL2_gfxPrimitives.h>
#include <stdio.h>

#define ORB_WIDTH 190
#define ORB_HEIGHT 97


void desenhaOrbsLvl0(int lvl,CChessSettings * settings,SDL_Color branco , SDL_Color red , SDL_Texture * orb_laranja , SDL_Texture * orb_cinzenta){
    SDL_Rect orb2 = {720,290,ORB_WIDTH,ORB_HEIGHT} , orb3 = {690,420,ORB_WIDTH,ORB_HEIGHT} , orb4 = {540,500,ORB_WIDTH,ORB_HEIGHT} , orb5 = {670,570,ORB_WIDTH,ORB_HEIGHT} ,
             orb6 = {830,650,ORB_WIDTH,ORB_HEIGHT} , orb7 = {988,735,ORB_WIDTH,ORB_HEIGHT} , orb8 = {1124,815,ORB_WIDTH,ORB_HEIGHT} , orb9 = {994,896,ORB_WIDTH,ORB_HEIGHT} , 
             orb10 = {870,975,ORB_WIDTH,ORB_HEIGHT};
    SDL_Rect orbsJuntas[9] = {orb2,orb3,orb4,orb5,orb6,orb7,orb8,orb9,orb10};
    char str[256];
    for(int i=2;i<11;i++){
        SDL_Rect orb_temp = orbsJuntas[i-2];
        if(i + 10*lvl <= settings->nivelMaxDesbloqueado) SDL_RenderCopy(settings->gameRenderer,orb_laranja,NULL,&orb_temp);
        else{
            SDL_RenderCopy(settings->gameRenderer,orb_cinzenta,NULL,&orb_temp);
            filledCircleRGBA(settings->gameRenderer, orb_temp.x + orb_temp.w/2, orb_temp.y + orb_temp.h/2, 46 , 0 , 0, 0, 150);
        }
        sprintf(str,"%d",i + 10*lvl);
        int x = orb_temp.x + orb_temp.w/2 , y = orb_temp.y + orb_temp.h/2 - 20;
        renderTextoCentradoBasico(settings->gameRenderer,settings->fonteJogoSmallerTitles,str, branco, x , y , 0.8);
    }  
}


void desenhaOrbsNiveis(CChessSettings * settings){
    int lvl = settings->nivelDificuldade;
    SDL_Texture * orb_laranja = settings->textures.miscTextures[11], 
                * orb_cinzenta = settings->textures.miscTextures[12];
    SDL_Color branco = {255,255,255,255} , red = {255,0,0,255};
    if(lvl == 0){
        SDL_Rect orb1 = {600,240,ORB_WIDTH,ORB_HEIGHT};
        SDL_RenderCopy(settings->gameRenderer,orb_laranja,NULL,&orb1);
        renderTextoCentradoBasico(settings->gameRenderer,settings->fonteJogoSmallerTitles,"1", branco, 695 , 265 , 0.8);
        desenhaOrbsLvl0(lvl,settings,branco,red,orb_laranja,orb_cinzenta);
    }
}


void desenhaFundoStory(CChessSettings * settings){
    SDL_Rect fundo = {0, 0, 1920, 1080};
    if(settings->nivelDificuldade == 0)
        SDL_RenderCopy(settings->gameRenderer,
                       settings->textures.niveisTextures[2], NULL, &fundo);

    /* Vinheta — 80px de fade nas 4 bordas */
    SDL_Renderer * r = settings->gameRenderer;
    SDL_SetRenderDrawBlendMode(r, SDL_BLENDMODE_BLEND);
    for(int i = 0; i < 80; i++){
        Uint8 a = (Uint8)(140 * (1.0f - (float)i / 80.0f));
        SDL_SetRenderDrawColor(r, 0, 0, 0, a);
        SDL_RenderDrawRect(r, &(SDL_Rect){i, i, 1920-2*i, 1080-2*i});
    }
}



void desenhaNivelTitleStory(CChessSettings * settings){
    SDL_Renderer * r = settings->gameRenderer;

    /* Fundo do header — gradiente manual de cima para baixo */
    for(int y = 0; y < 150; y++){
        Uint8 a = (Uint8)(210 * (1.0f - (float)y / 150.0f * 0.5f));
        SDL_SetRenderDrawColor(r, 10, 10, 10, a);
        SDL_SetRenderDrawBlendMode(r, SDL_BLENDMODE_BLEND);
        SDL_RenderDrawLine(r, 0, y, 1920, y);
    }

    /* Linha dourada separadora */
    SDL_SetRenderDrawBlendMode(r, SDL_BLENDMODE_BLEND);
    for(int i = 0; i < 5; i++){
        Uint8 a = (i == 2) ? 255 : 160;
        SDL_SetRenderDrawColor(r, 210, 165, 50, a);
        SDL_RenderDrawLine(r, 0, 150 + i, 1920, 150 + i);
    }

    SDL_Color dourado = {220, 175, 55, 255};
    SDL_Color cinzento_claro = {200, 200, 200, 255};

    if(settings->nivelDificuldade == 0){
        /* Título centrado horizontalmente */
        renderTextoCentradoSombra(r, settings->fonteJogoTitles,
                                  "IN THE DAWN", dourado, 960, 10, 3.2f);
        /* Sub-linha discreta */
        renderTextoCentradoBasico(r, settings->fonteJogoSmallerTitles,
                                  "Chapter I   -   Select a Level",
                                  cinzento_claro, 960, 100, 0.9f);
    }
}



void desenhaStoryScreen(GameStruct * game,CChessSettings * settings){
    desenhaFundoStory(settings);

    SDL_Rect go_back = {100,950,100,100};
    SDL_RenderCopy(settings->gameRenderer,settings->textures.buttonsTextures[0],NULL,&go_back);

    desenhaOrbsNiveis(settings);
    desenhaNivelTitleStory(settings);
}