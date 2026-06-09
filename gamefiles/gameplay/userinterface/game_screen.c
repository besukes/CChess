#include "library/main.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <stdio.h>






void desenhaInterfaceJogo(GameStruct * game ,CChessSettings * settings,SDL_Event event){
    SDL_Rect tabuleiro = {200,40,1000,1000};
    SDL_RenderCopy(settings->gameRenderer,settings->textures.tabTextures[1],NULL,&tabuleiro);
    for(int i = 0 ; i < 6 ; i++){
        desenhaTipoPiece(game->estadoJogo.tabuleirojogo[0][i],(Pieces)i,settings,game,0);
    }
    for( int i = 0; i < 6; i++){
        desenhaTipoPiece(game->estadoJogo.tabuleirojogo[1][i],(Pieces)(i),settings,game,6);
    }

}