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
    }
}




SDL_Texture ** gif_utilizador_checkmate(CChessSettings * settings, int efeito_checkmateSelecionado){
    char str[256];
    pathAnimacaoCheckmate(str,efeito_checkmateSelecionado);
    IMG_Animation* gif = IMG_LoadAnimation(str);
    SDL_Texture * * textures = malloc(sizeof(SDL_Texture*) * gif->count);
    for(int i = 0; i < gif->count; i++) {
        textures[i] = SDL_CreateTextureFromSurface(settings->gameRenderer, gif->frames[i]);
    }
    IMG_FreeAnimation(gif);
    return textures;
}