#include "library/main.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <stdio.h>
#include "pl_mpeg.h"

#define PL_MPEG_IMPLEMENTATION




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



void video_callback(plm_t *plm, plm_frame_t *frame, void *user_data) {
    // O 'user_data' é a textura que passaste na função plm_set_video_decode_callback
    SDL_Texture *texture = (SDL_Texture *)user_data;
    
    // Atualiza os 3 planos de cores do vídeo (Y, U, V) na textura do SDL2
    SDL_UpdateYUVTexture(
        texture, 
        NULL,
        frame->y.data,  frame->y.width,   // Plano Y (Brilho/Preto e Branco)
        frame->cb.data,  frame->cb.width,   // Plano U (Cores Azuis)
        frame->cr.data,  frame->cr.width    // Plano V (Cores Vermelhas)
    );
}


VideoPlayer* init_video(SDL_Renderer *renderer, const char* caminho_ficheiro, Uint32 ticks_atuais) {
    VideoPlayer *video = malloc(sizeof(VideoPlayer));
    
    // Abre o ficheiro de vídeo
    video->plm = plm_create_with_filename(caminho_ficheiro);
    if (!video->plm) {
        printf("Erro ao abrir o vídeo %s\n", caminho_ficheiro);
        free(video);
        return NULL;
    }

    // Pega as dimensões reais do vídeo
    video->largura = plm_get_width(video->plm);
    video->altura = plm_get_height(video->plm);
    video->ticks_inicial = ticks_atuais;

    // Cria a textura SDL no formato YV12 (específico para vídeos YUV)
    video->texture = SDL_CreateTexture(
        renderer, 
        SDL_PIXELFORMAT_YV12, 
        SDL_TEXTUREACCESS_STREAMING, 
        video->largura, 
        video->altura
    );

    // Liga o vídeo à nossa função de callback e passa a textura como argumento (user_data)
    plm_set_video_decode_callback(video->plm, video_callback, video->texture);

    return video;
}