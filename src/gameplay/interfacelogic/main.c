#include "library/main.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>


void handleTipoMenu(GameStruct * game , CChessSettings * settings , SDL_Event * event , Mix_Chunk * sfxarray[]){
    switch(settings->screenAtual){
        case Menu :
            handleJogadaMenuPrincipal(settings,event);
            desenhaInterfaceMenu(settings,*event);
        break;
        case Chess :
            if(game->game_needs_initialization) initializeOfflineGame(game);
            handleJogadaChess(game,settings,*event , sfxarray);
            desenhaInterfaceJogo(game,settings);
        break;
        case Theme :
            handleJogadaThemes(settings,*event);
            desenhaMenuThemes(settings,*event);
        break;
        case WinScreen :
            handleWinScreen(game,settings,*event);
            desenhaWinScreen(game,settings,*event);
        break;
        case DrawScreen :
        
        break;
        case Story :
            handleStoryScreen(game,settings,event);
            handleJogadaStory(game,settings,*event,sfxarray);
            desenhaStoryScreen(game,settings);
        break;
        case Settings :
            desenhaSettings(settings);    
            handleSettingsScreen(settings,event);
        break;
        case Multiplayer :
            handleMultiplayerScreen(settings,event);
            desenhaMultiplayerScreen(settings);
        break;
    }
}


void interfaceCChess(GameStruct * game ,CChessSettings * settings , Mix_Chunk * sfxarray[]){
    SDL_Event event;
    //enquanto o utilizador nao clicar no botao para sair ele continua no jogo
    while(event.type != SDL_QUIT && game->jogada!= Leave){
        SDL_PollEvent(&event);
        SDL_RenderClear(settings->gameRenderer);
        settings->ticks = SDL_GetTicks();
        if(event.type == SDL_MOUSEMOTION){
            settings->posMouseX = event.motion.x;
            settings->posMouseY = event.motion.y;
            SDL_Event tmp;
            while(SDL_PeepEvents(&tmp,1,SDL_GETEVENT,SDL_MOUSEMOTION,SDL_MOUSEMOTION) > 0){
                settings->posMouseX = tmp.motion.x;
                settings->posMouseY = tmp.motion.y;
            }
        }
        handleTipoMenu(game,settings,&event , sfxarray);
        SDL_RenderPresent(settings->gameRenderer);
    }
}

int main(void){
    SDL_Initializators init = sdl_initializer();
    Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);
    CChessSettings settings = initCChessSettings(init.renderer,init.window);
    GameStruct game = initGameStruct();
    Mix_Chunk * sfxarray[10];
    initsfx(sfxarray);
    interfaceCChess(&game,&settings , sfxarray);
    writeNewGameFiles(&settings);
    free_allocated_memory(&game,&settings , sfxarray);
    return 0;
}