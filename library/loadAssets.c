#include "main.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <stdio.h>



void loadTexturasPieces(CChessSettings * settings ,SDL_Texture * chessPieces[12],SDL_Renderer * sdl_renderer){
    for(int i=0;i<12;i++){
        settings->num_imgsLoaded++;
        char str[30];
        sprintf(str,"assets/pieces/%d.png",i+1);
        chessPieces[i] = IMG_LoadTexture(sdl_renderer,str);
    }
}


void loadButtons(SDL_Texture * buttonsTextures[20],SDL_Renderer * sdl_renderer){
    buttonsTextures[0] = IMG_LoadTexture(sdl_renderer,"assets/buttons/back_button_circle.png");
    buttonsTextures[1] = IMG_LoadTexture(sdl_renderer,"assets/buttons/multiplayer_button.png");
    buttonsTextures[2] = IMG_LoadTexture(sdl_renderer,"assets/buttons/offline_button.png");
    buttonsTextures[3] = IMG_LoadTexture(sdl_renderer,"assets/buttons/settings_button.png");
    buttonsTextures[4] = IMG_LoadTexture(sdl_renderer,"assets/buttons/story_button.png");
    buttonsTextures[5] = IMG_LoadTexture(sdl_renderer,"assets/buttons/go_back.png");
}



void loadMiscAssets(AssetsCChess * assets,SDL_Renderer * sdl_renderer){
    assets->miscTextures[0] = IMG_LoadTexture(sdl_renderer,"assets/menu/menu_inicial.png");
    assets->miscTextures[1] = IMG_LoadTexture(sdl_renderer,"assets/menu/shop.png");
    assets->miscTextures[2] = IMG_LoadTexture(sdl_renderer,"assets/menu/CChess_name.png");
    assets->miscTextures[3] = IMG_LoadTexture(sdl_renderer,"assets/tabuleiro/checkerboard.png");
    assets->miscTextures[4] = IMG_LoadTexture(sdl_renderer,"assets/menu/coins.png");
    assets->miscTextures[5] = IMG_LoadTexture(sdl_renderer,"assets/misc/white_moves.png");
    assets->miscTextures[6] = IMG_LoadTexture(sdl_renderer,"assets/misc/black_moves.png");
    assets->miscTextures[7] = IMG_LoadTexture(sdl_renderer,"assets/misc/settings.png");
    assets->miscTextures[8] = IMG_LoadTexture(sdl_renderer,"assets/niveis/not_finished.png");
    assets->miscTextures[9] = IMG_LoadTexture(sdl_renderer,"assets/misc/ball_grey.png");
    assets->miscTextures[10] = IMG_LoadTexture(sdl_renderer,"assets/misc/ball_green.png");
    assets->miscTextures[11] = IMG_LoadTexture(sdl_renderer,"assets/misc/orb_laranja.png");
    assets->miscTextures[12] = IMG_LoadTexture(sdl_renderer,"assets/misc/orb_cinzenta.png");
}



void initTexturasJogo(CChessSettings * settings ,AssetsCChess * assets,SDL_Renderer * sdl_renderer){
    //assets->tabTextures[0] = IMG_LoadTexture(sdl_renderer,"");
    assets->tabTextures[0] = IMG_LoadTexture(sdl_renderer,"assets/tabuleiro/tab_1.png");


    assets->niveisTextures[0] = IMG_LoadTexture(sdl_renderer,"assets/niveis/nivel1.png");
    assets->niveisTextures[1] = IMG_LoadTexture(sdl_renderer,"assets/niveis/forest.png");
    assets->niveisTextures[2] = IMG_LoadTexture(sdl_renderer,"assets/niveis/forestlvl(2).png");
    assets->niveisTextures[3] = IMG_LoadTexture(sdl_renderer,"assets/niveis/test_forest(2).jpg");

    loadMiscAssets(assets,sdl_renderer);
    
    settings->num_imgsLoaded+= 6;
    loading_screen(settings,settings->num_imgsLoaded);

    loadTexturasPieces(settings,assets->chessPieces,sdl_renderer);
    
    loadButtons(assets->buttonsTextures,sdl_renderer);
    settings->num_imgsLoaded+=5;
}