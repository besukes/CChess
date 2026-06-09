#include "library/main.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <stdio.h>




void desenhaInterfaceMenu(CChessSettings * settings,SDL_Event event){
    SDL_Rect fundo = {0,0,1920,1080};
    SDL_Rect botaoJogar = {700,400,500,100};
    SDL_RenderCopy(settings->gameRenderer,settings->textures.miscTextures[0],NULL,&fundo);
    SDL_RenderCopy(settings->gameRenderer,settings->textures.miscTextures[1],NULL,&botaoJogar);
}