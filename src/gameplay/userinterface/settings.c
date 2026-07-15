#include "library/main.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL2_gfxPrimitives.h>
#include <stdio.h>



/* ─────────────────────────────────────────────
   Paleta — combina com o fundo dourado/escuro
   ───────────────────────────────────────────── */
#define COL_PANEL_R   12
#define COL_PANEL_G    8
#define COL_PANEL_B    4
#define COL_PANEL_A  210    /* painel escuro semitransparente */

#define COL_GOLD_R   210
#define COL_GOLD_G   160
#define COL_GOLD_B    40

#define COL_SEL_R     80
#define COL_SEL_G     55
#define COL_SEL_B     10
#define COL_SEL_A    220    /* fundo da opção selecionada */


/* ─────────────────────────────────────────────
   Layout (1920 × 1080)
   Dois painéis lado a lado + header
   ───────────────────────────────────────────── */
#define HDR_Y1       40
#define HDR_Y2      130
#define HDR_X1      460
#define HDR_X2     1460

/* Painel esquerdo  — tabuleiro + tema peças */
#define PNL_L_X1    100
#define PNL_L_X2    900
#define PNL_Y1      140
#define PNL_Y2      850
#define PNL_R        38

/* Painel direito  — música + efeitos */
#define PNL_R_X1   1020
#define PNL_R_X2   1820

/* Altura de cada linha de opção */
#define ROW_H        72
#define ROW_GAP      12
#define ROW_PAD_X    30


static void intToStr(int v, char * buf){ sprintf(buf, "%d", v); }


/* ─────────────────────────────────────────────
   Utilitário: rect de uma linha de opção
   ───────────────────────────────────────────── */
static SDL_Rect rowRect(int panel_x1, int panel_x2, int y){
    return (SDL_Rect){
        panel_x1 + ROW_PAD_X,
        y,
        (panel_x2 - panel_x1) - 2 * ROW_PAD_X,
        ROW_H
    };
}




/* ─────────────────────────────────────────────
   Desenha um painel arredondado com borda dourada
   ───────────────────────────────────────────── */
static void desenhaPainel(SDL_Renderer * r, int x1, int y1, int x2, int y2){
    /* Sombra */
    for(int i = 10; i > 0; i -= 2)
        roundedBoxRGBA(r, x1-i, y1-i, x2+i, y2+i, PNL_R+i, 0,0,0, (Uint8)(12*i));

    /* Corpo */
    roundedBoxRGBA(r, x1, y1, x2, y2, PNL_R,COL_PANEL_R, COL_PANEL_G, COL_PANEL_B, COL_PANEL_A);

    /* Borda dourada dupla */
    roundedRectangleRGBA(r, x1,   y1 + 3,   x2 + 3 ,   y2,   PNL_R,   COL_GOLD_R, COL_GOLD_G, COL_GOLD_B, 200);
    roundedRectangleRGBA(r, x1+3, y1 + 4, x2-3, y2-3, PNL_R-2, COL_GOLD_R, COL_GOLD_G, COL_GOLD_B,  80);
}



/* ─────────────────────────────────────────────
   Secção dentro de um painel
   Devolve o y onde a próxima secção começa
   ───────────────────────────────────────────── */
static int desenhaSectionTitle(CChessSettings * s,int px1, int px2, int y,const char * titulo){
    SDL_Renderer * r = s->gameRenderer;

    /* Linha separadora dourada */
    SDL_SetRenderDrawBlendMode(r, SDL_BLENDMODE_BLEND);
    SDL_SetRenderDrawColor(r, COL_GOLD_R, COL_GOLD_G, COL_GOLD_B, 120);
    SDL_RenderDrawLine(r, px1+20, y+1, px2-20, y+1);
    SDL_SetRenderDrawColor(r, COL_GOLD_R, COL_GOLD_G, COL_GOLD_B, 60);
    SDL_RenderDrawLine(r, px1+20, y+2, px2-20, y+2);

    SDL_Color dourado = {COL_GOLD_R, COL_GOLD_G, COL_GOLD_B, 255};
    renderTextoCentradoBasico(r, s->fonteJogoSmallerTitles,titulo, dourado,(px1+px2)/2, y+10, 0.85f);
    return y + 70;
}




/* ─────────────────────────────────────────────
   Linha de opção com setas de navegação  ◄  N  ►
   Devolve o y da próxima linha
   ───────────────────────────────────────────── */
static int desenhaOptionRow(CChessSettings * s,int px1, int px2, int y,const char * label,const char * valor , int type){
    SDL_Renderer * r = s->gameRenderer;

    SDL_Rect row = rowRect(px1, px2, y);

    /* Fundo da linha */
    roundedBoxRGBA(r, row.x, row.y, row.x+row.w, row.y+row.h, 10,25, 18, 6, mouseOver(s, row) ? 160 : 100);
    roundedRectangleRGBA(r, row.x, row.y - 2, row.x+row.w + 1, row.y+row.h + 1 , 10,COL_GOLD_R, COL_GOLD_G, COL_GOLD_B,mouseOver(s, row) ? 180 : 70);

    /* Label à esquerda */
    SDL_Color branco     = {230, 215, 180, 255};
    SDL_Color dourado    = {COL_GOLD_R, COL_GOLD_G, COL_GOLD_B, 255};
    SDL_Color cinzento   = {140, 130, 110, 255};

    int offset = (type == 2) ? row.x + 200 : row.x + 160;
    renderTextoCentradoBasico(r, s->fonteJogoSmallerTitles,label, cinzento,offset, row.y + 18, 0.75f);

    /* Seta ◄ */
    int arrow_sz = 40;
    int mid_y    = row.y + row.h / 2;
    int cx       = row.x + row.w / 2 + 90;

    SDL_Rect prev_r =  {cx - 140, mid_y - arrow_sz/2, arrow_sz, arrow_sz},
             next_r = {cx + 70, mid_y - arrow_sz/2, arrow_sz, arrow_sz};

    /* Setas — triângulos preenchidos */
    Uint8 arrow_a = mouseOver(s, prev_r) ? 255 : 160;
    filledTrigonRGBA(r,prev_r.x + prev_r.w, prev_r.y,prev_r.x,prev_r.y + prev_r.h/2,prev_r.x + prev_r.w, prev_r.y + prev_r.h,
                    COL_GOLD_R, COL_GOLD_G, COL_GOLD_B, arrow_a);

    arrow_a = mouseOver(s, next_r) ? 255 : 180;
    filledTrigonRGBA(r,next_r.x,next_r.y,next_r.x + next_r.w, next_r.y + next_r.h/2,next_r.x,next_r.y + next_r.h,
                    COL_GOLD_R, COL_GOLD_G, COL_GOLD_B, arrow_a);

    /* Valor atual centrado entre as setas */
    if(type == 1){ //Para verificar se estamos a desenhar a resolução do jogo, que é um caso especial
        int resX = 0, resY = 0;
        if(is_window_fullscreen(s->window)){
            renderTextoCentradoSombra(r, s->fonteJogoSmallerTitles,"Fullscreen", branco,cx - 20, row.y + 16, 0.85f);
        }
        else{
            SDL_GetWindowSize(s->window, &resX, &resY);
            char str[256];
            sprintf(str, "%dx%d", resX, resY);
            renderTextoCentradoSombra(r, s->fonteJogoSmallerTitles,str, branco,cx - 20, row.y + 16, 0.85f);
        }
    }
    else renderTextoCentradoSombra(r, s->fonteJogoSmallerTitles,valor, branco,cx - 20, row.y + 16, 0.85f);

    /* Linha separadora inferior subtil */
    SDL_SetRenderDrawBlendMode(r, SDL_BLENDMODE_BLEND);
    SDL_SetRenderDrawColor(r, COL_GOLD_R, COL_GOLD_G, COL_GOLD_B, 30);
    SDL_RenderDrawLine(r, row.x+10, row.y+row.h+ROW_GAP/2,
                          row.x+row.w-10, row.y+row.h+ROW_GAP/2);

    return y + ROW_H + ROW_GAP;
}


/* ─────────────────────────────────────────────
   Preview do tabuleiro selecionado (painel esq)
   ───────────────────────────────────────────── */
static void desenhaTabPreview(CChessSettings * s, int x1, int x2, int y){
    SDL_Renderer * r = s->gameRenderer;
    int pw = x2 - x1 - 80;
    int ph = pw;   /* quadrado */
    SDL_Rect preview = {x1 + 40, y, pw, ph};

    /* Borda dourada */
    roundedRectangleRGBA(r, preview.x-3, preview.y-3,preview.x+preview.w+3, preview.y+preview.h+3,
                            8, COL_GOLD_R, COL_GOLD_G, COL_GOLD_B, 180);

    int idx = s->client_settings.cosmeticos.tabuleiroSelecionado;
    if(idx >= 0 && idx < 7 && s->textures.tabTextures[idx])
        SDL_RenderCopy(r, s->textures.tabTextures[idx], NULL, &preview);
    else{};
}


/* ─────────────────────────────────────────────
   Nomes para os valores dos settings
   ───────────────────────────────────────────── */
static const char * themeNome(int type){
    Themes t = (Themes)type;
    switch(t){
        case CChess:      return "CChess";
        case ChessDotCom: return "Chess.com";
        case LiChess:     return "Lichess";
        default:          return "?";
    }
}



void drawPainelEsquerdo(CChessSettings * settings , SDL_Renderer * r){
    /* ── PAINEL ESQUERDO ── */
    desenhaPainel(r, PNL_L_X1, PNL_Y1, PNL_L_X2, PNL_Y2);
    int y = PNL_Y1 + 20;

    /* Secção: Tabuleiro */
    y = desenhaSectionTitle(settings, PNL_L_X1, PNL_L_X2, y, "BOARD");
    char buf[32];
    intToStr(settings->client_settings.cosmeticos.tabuleiroSelecionado + 1, buf);
    y = desenhaOptionRow(settings, PNL_L_X1, PNL_L_X2, y,"Board Theme", buf , 2);

    /* Preview do tabuleiro */
    int preview_h = (PNL_L_X2 - PNL_L_X1 - 80);   /* quadrado */
    desenhaTabPreview(settings, PNL_L_X1, PNL_L_X1 + 140, y - 78);
    y += 20;

    /* Secção: Tema de Peças */
    y = desenhaSectionTitle(settings, PNL_L_X1, PNL_L_X2, y, "PIECE THEME");
    y = desenhaOptionRow(settings, PNL_L_X1, PNL_L_X2, y,"Theme", themeNome(settings->client_settings.cosmeticos.themes_piece),0);
    y+=20;

    /* Secção: Efeitos */
    y = desenhaSectionTitle(settings, PNL_L_X1 - 3, PNL_L_X2 - 3, y, "EFFECTS");

    intToStr(settings->client_settings.cosmeticos.efeito_checkmateSelecionado + 1, buf);
    y = desenhaOptionRow(settings, PNL_L_X1, PNL_L_X2, y,"Checkmate", buf,0);

    intToStr(settings->client_settings.cosmeticos.efeito_checkSelecionado + 1, buf);
    y = desenhaOptionRow(settings, PNL_L_X1, PNL_L_X2, y,"Check", buf,0);

    y += 20;
}




void drawPainelDireito(CChessSettings * settings , SDL_Renderer * r){
    char buf[32];
    /* ── PAINEL DIREITO ── */
    desenhaPainel(r, PNL_R_X1, PNL_Y1, PNL_R_X2, PNL_Y2);
    int y = PNL_Y1 + 20;
    /* Secção: Screen Utilizador */
    y = desenhaSectionTitle(settings, PNL_R_X1, PNL_R_X2, y, "RESOLUTION");
    intToStr(settings->client_settings.cosmeticos.musicaSelecionada + 1, buf);
    desenhaOptionRow(settings, PNL_R_X1, PNL_R_X2, y,"Screen Resolution", buf , 1);
    y += ROW_GAP + ROW_H + 20;


    /* Secção: Musica */
    y = desenhaSectionTitle(settings, PNL_R_X1 - 5, PNL_R_X2 - 5, y, "MUSIC");
    intToStr(settings->client_settings.cosmeticos.musicaSelecionada + 1, buf);
    y = desenhaOptionRow(settings, PNL_R_X1, PNL_R_X2, y,"Track", buf,0);

    intToStr(settings->client_settings.volume_music, buf);
    sprintf(buf, "%d%%", settings->client_settings.volume_music);
    y = desenhaOptionRow(settings, PNL_R_X1, PNL_R_X2, y,"Volume", buf,3);
}





/* ─────────────────────────────────────────────
   desenhaSettings — ponto de entrada
   ───────────────────────────────────────────── */
void desenhaSettings(CChessSettings * settings, SDL_Event * event){
    SDL_Renderer * r = settings->gameRenderer;

    /* Fundo */
    desenhaFundo(settings, settings->textures.miscTextures[7]);

    /* Overlay escuro suave para melhor leitura */
    SDL_SetRenderDrawBlendMode(r, SDL_BLENDMODE_BLEND);
    SDL_SetRenderDrawColor(r, 0, 0, 0, 80);
    SDL_RenderFillRect(r, &(SDL_Rect){0, 0, 1920, 1080});

    drawPainelEsquerdo(settings,r);

    drawPainelDireito(settings,r);


    SDL_Rect leave = {1750,890,150,150};
    if(mouseOver(settings,leave)) filledCircleRGBA(r, leave.x + leave.w/2, leave.y + leave.h/2, 62, COL_GOLD_R, COL_GOLD_G, COL_GOLD_B, 20);
}


