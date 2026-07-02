#include "library/main.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL2_gfxPrimitives.h>
#include <stdio.h>




void desenhaSettings(CChessSettings * settings , SDL_Event * event){
    desenhaFundo(settings,settings->textures.miscTextures[7]);
}