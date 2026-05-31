#include "main.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <stdio.h>



void loadTexturasPieces(SDL_Texture * chessPieces[16],SDL_Texture * sdl_renderer){
    for(int i=0;i<16;i++){
        char str[30];
        sprintf(str,"assets/pieces/%d",i);
        chessPieces[i] = IMG_LoadTexture(sdl_renderer,str);
    }
}

void initTexturasJogo(AssetsCChess * assets,SDL_Texture * sdl_renderer){
    loadTexturasPieces(assets->chessPieces,sdl_renderer);
}