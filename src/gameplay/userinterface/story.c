#include "library/main.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL2_gfxPrimitives.h>
#include <stdio.h>




void desenhaFundoStory(CChessSettings * settings){
    SDL_Rect fundo = {0,0,1920,1080};
    if(settings->nivelDificuldade == 0){
        SDL_RenderCopy(settings->gameRenderer,settings->textures.niveisTextures[2],NULL,&fundo);
    }
}


void desenhaOrbsLvl0(int lvl,CChessSettings * settings,SDL_Color branco , SDL_Color red , SDL_Texture * orb_laranja , SDL_Texture * orb_cinzenta){
    SDL_Rect orb2 = {720,290,190,90} , orb3 = {690,420,190,90} , orb4 = {540,500,190,90} , orb5 = {670,570,190,90} ,
             orb6 = {830,650,190,90} , orb7 = {988,735,190,90} , orb8 = {1124,815,190,90} , orb9 = {994,896,190,90} , 
             orb10 = {870,975,190,90};
    SDL_Rect orbsJuntas[9] = {orb2,orb3,orb4,orb5,orb6,orb7,orb8,orb9,orb10};
    char str[256];
    for(int i=2;i<11;i++){
        SDL_Rect orb_temp = orbsJuntas[i-2];
        if(i + 10*lvl <= settings->nivelMaxDesbloqueado) SDL_RenderCopy(settings->gameRenderer,orb_laranja,NULL,&orb_temp);
        else SDL_RenderCopy(settings->gameRenderer,orb_cinzenta,NULL,&orb_temp);
        int x = orb_temp.x + orb_temp.w/2 , y = orb_temp.y + orb_temp.h/2 - 20;
        sprintf(str,"%d",i + 10*lvl);
        renderTextoCentradoBasico(settings->gameRenderer,settings->fonteJogoSmallerTitles,str, branco, x , y , 0.8);
    }  
}


void desenhaOrbsNiveis(CChessSettings * settings){
    int lvl = settings->nivelDificuldade;
    SDL_Texture * orb_laranja = settings->textures.miscTextures[11], 
                * orb_cinzenta = settings->textures.miscTextures[12];
    SDL_Color branco = {255,255,255,255} , red = {255,0,0,255};
    if(lvl == 0){
        SDL_Rect orb1 = {600,240,190,90};
        SDL_RenderCopy(settings->gameRenderer,orb_laranja,NULL,&orb1);
        renderTextoCentradoBasico(settings->gameRenderer,settings->fonteJogoSmallerTitles,"1", branco, 695 , 265 , 0.8);
        desenhaOrbsLvl0(lvl,settings,branco,red,orb_laranja,orb_cinzenta);
    }
}



void desenhaNivelTitleStory(CChessSettings * settings){
    SDL_Color branco = {255,255,255,255};
    roundedBoxRGBA(settings->gameRenderer, 0 , 0 , 1920 , 170 , 40 , 0, 0, 0, 150);
    if(settings->nivelDificuldade == 0){
        renderTextoCentradoBasico(settings->gameRenderer,settings->fonteJogoTitles,"IN THE DAWN", branco, 400 , 4 , 4);
    }
}



void desenhaStoryScreen(GameStruct * game,CChessSettings * settings){
    desenhaFundoStory(settings);

    SDL_Rect go_back = {100,950,100,100};
    SDL_RenderCopy(settings->gameRenderer,settings->textures.buttonsTextures[0],NULL,&go_back);

    desenhaOrbsNiveis(settings);
    desenhaNivelTitleStory(settings);
}