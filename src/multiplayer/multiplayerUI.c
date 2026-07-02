#include "library/main.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL2_gfxPrimitives.h>
#include <stdio.h>


void desenhaMultiplayerScreen(CChessSettings * settings){
    desenhaFundo(settings,settings->textures.miscTextures[8]);
    SDL_Rect button = {710,650,500,100};
    SDL_RenderCopy(settings->gameRenderer,settings->textures.buttonsTextures[5],NULL,&button);
}
