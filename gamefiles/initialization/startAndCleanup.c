#include "library/main.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <stdlib.h>



SDL_Renderer * sdl_initializer(void){
    SDL_Init(SDL_INIT_VIDEO);
    SDL_Window* window = SDL_CreateWindow("CChess", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 0 , 0, SDL_WINDOW_FULLSCREEN_DESKTOP);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    //para não precisar de dar scale às imagens no ecrã
    SDL_RenderSetLogicalSize(renderer, 1920, 1080);
    return renderer;
}


void free_allocated_memory(GameStruct game , CChessSettings user){

}