#include "main.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <stdio.h>



void loadTexturasPieces(SDL_Texture * chessPieces[12],SDL_Renderer * sdl_renderer){
    for(int i=0;i<12;i++){
        char str[30];
        sprintf(str,"assets/pieces/%d.png",i+1);
        chessPieces[i] = IMG_LoadTexture(sdl_renderer,str);
    }
}

void initTexturasJogo(AssetsCChess * assets,SDL_Renderer * sdl_renderer){
    loadTexturasPieces(assets->chessPieces,sdl_renderer);
}