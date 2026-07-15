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
        break;
    }
}


void loading_screen(CChessSettings * settings,int perc){
    SDL_RenderClear(settings->gameRenderer);

    SDL_Rect fundo = {0,0,1920,1080};
    SDL_Rect cchess = {490,-60,900,500};
    SDL_RenderCopy(settings->gameRenderer,settings->textures.miscTextures[0],NULL,&fundo);
    SDL_RenderCopy(settings->gameRenderer,settings->textures.miscTextures[2],NULL,&cchess);

    SDL_SetRenderDrawColor(settings->gameRenderer, 255, 255, 255, 255);
    SDL_Rect barBorder = {610,1000,700,40};
    SDL_RenderDrawRect(settings->gameRenderer, &barBorder);

    SDL_SetRenderDrawColor(settings->gameRenderer, 80, 180, 255, 255);
    SDL_Rect barFill = {612,1000, (6.7)* perc, 36};
    SDL_RenderFillRect(settings->gameRenderer, &barFill);
    SDL_RenderPresent(settings->gameRenderer);
    SDL_Delay(10);
}


SDL_Texture ** gif_utilizador_checkmate(CChessSettings * settings, int efeito_checkmateSelecionado){
    loading_screen(settings,settings->num_imgsLoaded);
    char str[256];
    pathAnimacaoCheckmate(str,efeito_checkmateSelecionado);
    IMG_Animation* gif = IMG_LoadAnimation(str);
    int n_frames = gif->count;
    SDL_Texture * * textures = malloc(sizeof(SDL_Texture*) * n_frames);
    for(int i = 0; i < n_frames; i++) {
        settings->num_imgsLoaded++;
        textures[i] = SDL_CreateTextureFromSurface(settings->gameRenderer, gif->frames[i]);
        loading_screen(settings,settings->num_imgsLoaded);
    }
    settings->client_settings.cosmeticos.n_frames_gif = n_frames;
    IMG_FreeAnimation(gif);
    return textures;
}





