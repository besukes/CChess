#include "library/main.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <stdio.h>




void desenhaInterfaceMenu(CChessSettings * settings,SDL_Event event){
    SDL_SetRenderDrawColor(settings->gameRenderer, 0, 0, 0, 180); 
    SDL_SetRenderDrawBlendMode(settings->gameRenderer, SDL_BLENDMODE_BLEND);
    SDL_Rect fundo = {0,0,1920,1080};
    SDL_Rect botaoJogar = {700,400,500,100};
    SDL_Rect cchess = {490,(-60),900,500};
    SDL_Rect menuOptions = {660,380,600,670};
    SDL_RenderCopy(settings->gameRenderer,settings->textures.miscTextures[0],NULL,&fundo);
    SDL_RenderFillRect(settings->gameRenderer, &menuOptions);
    SDL_RenderCopy(settings->gameRenderer,settings->textures.miscTextures[1],NULL,&botaoJogar);
    SDL_RenderCopy(settings->gameRenderer,settings->textures.miscTextures[3],NULL,&cchess);
}