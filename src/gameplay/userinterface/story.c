#include "library/main.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <stdio.h>




void desenhaFundoStory(CChessSettings * settings){
    SDL_Rect fundo = {0,0,1920,1080};
    if(settings->nivelDificuldade == 0){
        SDL_RenderCopy(settings->gameRenderer,settings->textures.niveisTextures[2],NULL,&fundo);
    }
}


void desenhaPromotionStory(GameStruct * game , CChessSettings * settings){
    if(game->turnoJogador == brancas){
        int offsetX = posTabuleiro(game->pieceCoords)%8;
        SDL_Rect promotion_sq = {300 + 130*offsetX,100,175,175};
        SDL_RenderCopy(settings->gameRenderer,settings->textures.miscTextures[3],NULL,&promotion_sq);

        SDL_Rect queen = {305 + 130*offsetX,105 ,70,70};
        SDL_Rect rook = {395 + 130*offsetX,105 ,70,70};
        SDL_Rect bishop = {305 + 130*offsetX,190 ,70,70};
        SDL_Rect knight = {395 + 130*offsetX,190 ,70,70};

        SDL_RenderCopy(settings->gameRenderer,settings->textures.chessPieces[Queen],NULL,&queen);
        SDL_RenderCopy(settings->gameRenderer,settings->textures.chessPieces[Rook],NULL,&rook);
        SDL_RenderCopy(settings->gameRenderer,settings->textures.chessPieces[Bishop],NULL,&bishop);
        SDL_RenderCopy(settings->gameRenderer,settings->textures.chessPieces[Horse],NULL,&knight);
    }
}



void desenhaMenuStory(CChessSettings * settings){
    
}



void desenhaNivelTitleStory(CChessSettings * settings){
    SDL_Rect title = {660,(-20),600,210};
    roundedBoxRGBA(settings->gameRenderer, 0 , 0 , 1920 , 170 , 40 , 0, 0, 0, 150);
    if(settings->nivelDificuldade == 0){
        SDL_RenderCopy(settings->gameRenderer,settings->textures.niveisTextures[1],NULL,&title);
    }
}



void desenhaStoryScreen(GameStruct * game,CChessSettings * settings){
    desenhaFundoStory(settings);

    SDL_Rect go_back = {100,950,100,100};
    SDL_RenderCopy(settings->gameRenderer,settings->textures.buttonsTextures[0],NULL,&go_back);

    if(game->pawnPromoted) desenhaPromotionStory(game,settings);

    desenhaMenuStory(settings);
    desenhaNivelTitleStory(settings);
}