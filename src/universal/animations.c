#include "library/main.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <stdio.h>




void pathAnimacaoCheckmate(char * str , int efeito_checkmateSelecionado){
    switch(efeito_checkmateSelecionado){
        case 0:
            sprintf(str,"animations/checkmate/anime.gif");
        break;
        case 1:
            sprintf(str,"animations/checkmate/beast.gif");
        break;
        case 2:
            sprintf(str,"animations/checkmate/default.gif");
        break;
        case 3:
            sprintf(str,"animations/checkmate/flames.gif");
        break;
        case 4 :
            sprintf(str,"animations/checkmate/new_years.gif");
        break;
        case 5 :
            sprintf(str,"animations/checkmate/purple_explosion.gif");
        break;
        case 6 :
            sprintf(str,"animations/checkmate/refraction.gif");
        break;
        default :
            sprintf(str,"animations/checkmate/space.gif");
    }
}


void loading_screen(CChessSettings * settings,int perc){
    SDL_RenderClear(settings->gameRenderer);

    SDL_Rect fundo = {0,0,1920,1080};
    SDL_Rect cchess = {490,-60,900,500};
    SDL_RenderCopy(settings->gameRenderer,settings->textures.miscTextures[0],NULL,&fundo);
    SDL_RenderCopy(settings->gameRenderer,settings->textures.miscTextures[2],NULL,&cchess);

    SDL_SetRenderDrawColor(settings->gameRenderer, 255, 255, 255, 255);
    SDL_Rect barBorder = {610,1000,700,40};
    SDL_RenderDrawRect(settings->gameRenderer, &barBorder);

    SDL_SetRenderDrawColor(settings->gameRenderer, 80, 180, 255, 255);
    SDL_Rect barFill = {612,1000, (6.7)* perc, 36};
    SDL_RenderFillRect(settings->gameRenderer, &barFill);
    SDL_RenderPresent(settings->gameRenderer);
    SDL_Delay(10);
}


SDL_Texture ** gif_utilizador_checkmate(CChessSettings * settings, int efeito_checkmateSelecionado){
    loading_screen(settings,settings->num_imgsLoaded);
    char str[256];
    pathAnimacaoCheckmate(str,efeito_checkmateSelecionado);
    IMG_Animation* gif = IMG_LoadAnimation(str);
    int n_frames = gif->count;
    SDL_Texture * * textures = malloc(sizeof(SDL_Texture*) * n_frames);
    for(int i = 0; i < n_frames; i++) {
        settings->num_imgsLoaded++;
        textures[i] = SDL_CreateTextureFromSurface(settings->gameRenderer, gif->frames[i]);
        loading_screen(settings,settings->num_imgsLoaded);
    }
    IMG_FreeAnimation(gif);
    return textures;
}



void updateMovingAnimation(GameStruct * game , CChessSettings * settings , uint64_bit click){
    MovingAnimation * mov = &game->piece_animation;
    mov->is_moving_piece = 1;
    int current_pos = posTabuleiro(game->pieceCoords), 
        end_pos = posTabuleiro(click);
    int current_line = current_pos / 8, current_col = current_pos % 8,
        end_line = end_pos / 8, end_col = end_pos % 8;
    mov->current_position.x = 100 * current_col + 260;
    mov->current_position.y = 1080 - (100 * current_line + 246);
    mov->end_position.x = 100 * end_col + 260;
    mov->end_position.y = 1080 - (100 * end_line + 246);
    mov->ticks_animation_start = settings->ticks;
    mov->bitboard_end = click;
}



int getPositionAnimation(GameStruct * game , CChessSettings * settings , int offset , int type){
    static float time_animation = 500.0f; //Duração da animação em milissegundos
    int distf = (type)? game->piece_animation.end_position.x : game->piece_animation.end_position.y;
    int disti = (type)? game->piece_animation.current_position.x : game->piece_animation.current_position.y;
    float delta_dist = distf - disti , deltaTime = settings->ticks - game->piece_animation.ticks_animation_start;
    float pos = (float)offset + ( (deltaTime/time_animation) * delta_dist);
    return ((int)pos);
}


void verificaAnimations(GameStruct * game , CChessSettings * settings){
    if(game->piece_animation.is_moving_piece){
        if(settings->ticks - game->piece_animation.ticks_animation_start > 500){
                initMovingAnimation(&game->piece_animation);
        }
        else {
            int posX = posTabuleiro(game->pieceCoords)%8,
                posY = posTabuleiro(game->pieceCoords)/8;
            int offsety = 1080 - (100 * posY + 246),
                offsetx = 100*posX+260;
            game->piece_animation.current_position.x = getPositionAnimation(game,settings,offsetx,1);
            game->piece_animation.current_position.y = getPositionAnimation(game,settings,offsety,0);
        }
    }
}