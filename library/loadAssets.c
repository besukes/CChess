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
    assets->miscTextures[0] = IMG_LoadTexture(sdl_renderer,"assets/misc/menu.png");
    assets->miscTextures[1] = IMG_LoadTexture(sdl_renderer,"assets/pieces/1.png");
    assets->tabTextures[0] = IMG_LoadTexture(sdl_renderer,"assets/tabuleiro/chessTableTest.png");
}