#include "library/main.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>



void handleTipoMenu(GameStruct * game , CChessSettings * settings , SDL_Event * event){
    switch(settings->screenAtual){
        case Menu :
            handleJogadaMenuPrincipal(settings,event);
            desenhaInterfaceMenu(settings,*event);
        break;
        case Chess :
            handleJogadaChess(game,settings,*event);
            desenhaInterfaceJogo(game,settings,*event);
        break;
        case Theme :
            handleJogadaThemes(settings,*event);
            desenhaMenuThemes(settings,*event);
        break;
        case WinScreen :
            handleWinScreen(game,settings,*event);
            desenhaWinScreen(game,settings,*event);
        break;
    }
}


void interfaceCChess(GameStruct * game ,CChessSettings * settings){
    SDL_Event event;
    //enquanto o utilizador nao clicar no botao para sair ele continua no jogo
    while(event.type != SDL_QUIT && game->jogada!= Leave){
        SDL_PollEvent(&event);
        SDL_RenderClear(settings->gameRenderer);
        settings->ticks = SDL_GetTicks();
        if(event.type == SDL_MOUSEMOTION){
            settings->posMouseX = event.motion.x;
            settings->posMouseY = event.motion.y;
        }
        handleTipoMenu(game,settings,&event);
        SDL_RenderPresent(settings->gameRenderer);
    }
}

int main(void){
    SDL_Renderer * sdl_renderer = sdl_initializer();
    CChessSettings settings = initCChessSettings(sdl_renderer);
    GameStruct game = initGameStruct(sdl_renderer);
    interfaceCChess(&game,&settings);
    free_allocated_memory(&game,&settings);
    return 0;
}